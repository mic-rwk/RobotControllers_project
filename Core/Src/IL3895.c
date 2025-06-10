#ifndef SRC_SSD1680_C_
#define SRC_SSD1680_C_

#include "main.h"

static void RESET_HIG() {
	HAL_GPIO_WritePin(EPD_RST_GPIO_Port, EPD_RST_Pin, GPIO_PIN_SET);
}

static void RESET_LOW() {
	HAL_GPIO_WritePin(EPD_RST_GPIO_Port, EPD_RST_Pin, GPIO_PIN_RESET);
}

static void CS_HIG() {
	HAL_GPIO_WritePin(EPD_CS_GPIO_Port, EPD_CS_Pin, GPIO_PIN_SET);
}

static void CS_LOW() {
	HAL_GPIO_WritePin(EPD_CS_GPIO_Port, EPD_CS_Pin, GPIO_PIN_RESET);
}

static void DC_HIG() {
	HAL_GPIO_WritePin(EPD_DC_GPIO_Port, EPD_DC_Pin, GPIO_PIN_SET);
}

static void DC_LOW() {
	HAL_GPIO_WritePin(EPD_DC_GPIO_Port, EPD_DC_Pin, GPIO_PIN_RESET);
}

static uint8_t BUSY_READ() {
	return HAL_GPIO_ReadPin(EPD_BUSY_GPIO_Port, EPD_BUSY_Pin);
}

static void Delay_ms(uint16_t ms) {
	HAL_Delay(ms);
}

extern SPI_HandleTypeDef hspi1;
static void SPI_WriteByte(uint8_t value) {
	HAL_SPI_Transmit(&hspi1, &value, 1, 1000);
}

static void EPD_Reset(void) {
	RESET_HIG();
	Delay_ms(20);
	RESET_LOW();
	Delay_ms(2);
	RESET_HIG();
	Delay_ms(20);
}

static void EPD_SendCommand(uint8_t Reg) {
	DC_LOW();
	CS_LOW();
	SPI_WriteByte(Reg);
	CS_HIG();
}

static void EPD_SendData(uint8_t Data) {
	DC_HIG();
	CS_LOW();
	SPI_WriteByte(Data);
	CS_HIG();
}

static void EPD_ReadBusy(void) {
	while (1) {	 //=1 BUSY
		if (BUSY_READ() == 0)
			break;
		Delay_ms(10);
	}
	Delay_ms(10);
}

static void EPD_SetWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend) {
	EPD_SendCommand(0x44); // SET_RAM_X_ADDRESS_START_END_POSITION
	EPD_SendData((Xstart >> 3) & 0xFF);
	EPD_SendData((Xend >> 3) & 0xFF);

	EPD_SendCommand(0x45); // SET_RAM_Y_ADDRESS_START_END_POSITION
	EPD_SendData(Ystart & 0xFF);
	EPD_SendData((Ystart >> 8) & 0xFF);
	EPD_SendData(Yend & 0xFF);
	EPD_SendData((Yend >> 8) & 0xFF);
}

static void EPD_SetCursor(uint8_t Xstart, uint16_t Ystart) {
	EPD_SendCommand(0x4E); // SET_RAM_X_ADDRESS_COUNTER
	EPD_SendData(Xstart & 0xFF);

	EPD_SendCommand(0x4F); // SET_RAM_Y_ADDRESS_COUNTER
	EPD_SendData(Ystart & 0xFF);
	EPD_SendData((Ystart >> 8) & 0xFF);
}

static void EPD_TurnOnDisplay(void) {
	EPD_SendCommand(0x18);
	EPD_SendData(0X80);
	EPD_SendCommand(0x22);
	EPD_SendData(0XF7);
	EPD_SendCommand(0x20); // Activate Display Update Sequence
	EPD_ReadBusy();
}

void EPD_Init(uint16_t Width, uint16_t Height) {
	EPD_Reset();

	EPD_ReadBusy();
	EPD_SendCommand(0x12);  //SWRESET
	EPD_ReadBusy();

	EPD_SendCommand(0x01); //Driver output control
	EPD_SendData(Height - 1); //(EPD_WIDTH -1) & 0xff
	EPD_SendData(((Height - 1) >> 8) & 0x01); //(EPD_WIDTH -1) & 0x100
	EPD_SendData(0x00); // 0x01 TB/ 0x02 SM/ 0x04 GD
	/* 0x01 TB Change scanning direction of gate driver.
	 This bit defines the scanning direction of the gate for flexible layout of signals in module either from up to down (TB
	 = 0) or from bottom to up (TB = 1). */

	/* 0x02 SM: Change scanning order of gate driver.
	 When SM is set to 0, left and right interlaced is performed.
	 When SM is set to 1, no splitting odd / even of the GATE signal is performed,
	 Output pin assignment sequence is shown as below (for 296 MUX ratio):
	 SM=0 SM=0 SM=1 SM=1
	 GD=0 GD=1 GD=0 GD=1
	 G0 ROW0 ROW1 ROW0 ROW148
	 G1 ROW1 ROW0 ROW148 ROW0
	 G2 ROW2 ROW3 ROW1 ROW149
	 G3 ROW3 ROW2 ROW149 ROW1
	 : : : : :
	 G146 ROW146 ROW147 ROW73 ROW222
	 G147 ROW147 ROW146 ROW222 ROW73
	 G148 ROW148 ROW149 ROW74 ROW223
	 G149 ROW149 ROW148 ROW223 ROW74
	 : : : : :
	 G292 ROW292 ROW293 ROW146 ROW294
	 G293 ROW293 ROW292 ROW294 ROW146
	 G294 ROW294 ROW295 ROW147 ROW295
	 G295 ROW295 ROW294 ROW295 ROW147*/

	/* 0x04 GD: Selects the 1st output Gate
	 This bit is made to match the GATE layout connection on the panel. It defines the first scanning line. */

	EPD_SendCommand(0x11); //data entry mode
	EPD_SendData(0x03); //0x04 Am / 0x03 ID[1:0]
	/* ID[1:0]: The address counter is automatically incremented by 1, after data is written to the RAM
	 when ID[1:0] = “01”. The address counter is automatically decremented by 1, after data is written
	 to the RAM when ID[1:0] = “00”. The setting of incrementing or decrementing of the address
	 counter can be made independently in each upper and lower bit of the address. The direction of
	 the address when data is written to the RAM is set by AM bits. */

	/* AM Set the direction in which the address counter is updated automatically after data are written to
	 the RAM. When AM = “0”, the address counter is updated in the X direction. When AM = “1”, the
	 address counter is updated in the Y direction. When window addresses are selected, data are written
	 to the RAM area specified by the window addresses in the manner specified with ID[1:0] and AM
	 bits. */

	EPD_SetWindows(0, 0, Width - 1, Height - 1);
	EPD_SetCursor(0, 0);

	EPD_SendCommand(0x3C); //BorderWavefrom
	EPD_SendData(0x05);

	EPD_SendCommand(0x21); //  Display update control
	EPD_SendData(0x00);
	EPD_SendData(0x80);

	EPD_ReadBusy();
}

void EPD_Clear(uint16_t Width, uint16_t Height) {
	Width = (Width % 8 == 0) ? (Width / 8) : (Width / 8 + 1);

	EPD_SendCommand(0x24);
	for (uint16_t j = 0; j < Height; j++) {
		for (uint16_t i = 0; i < Width; i++) {
			EPD_SendData(0XFF);
		}
	}
	EPD_SendCommand(0x26);
	for (uint16_t j = 0; j < Height; j++) {
		for (uint16_t i = 0; i < Width; i++) {
			EPD_SendData(0X00);
		}
	}
	EPD_TurnOnDisplay();
}

void EPD_Display(const uint8_t *blackImage, const uint8_t *redImage, uint16_t Width, uint16_t Height) {
	Width = (Width % 8 == 0) ? (Width / 8) : (Width / 8 + 1);

	if (blackImage != NULL) {
		EPD_SendCommand(0x24);
		for (uint16_t j = 0; j < Height; j++) {
			for (uint16_t i = 0; i < Width; i++) {
				EPD_SendData(blackImage[i + j * Width]);
			}
		}
	}
	if (redImage != NULL) {
		EPD_SendCommand(0x26);
		for (uint16_t j = 0; j < Height; j++) {
			for (uint16_t i = 0; i < Width; i++) {
				EPD_SendData(redImage[i + j * Width]);
			}
		}
	}
	EPD_TurnOnDisplay();
}

void EPD_Sleep() {
	EPD_SendCommand(0x10); //enter deep sleep
	EPD_SendData(0x01);
	Delay_ms(100);
}

#endif /* SRC_SSD1680_C_ */
