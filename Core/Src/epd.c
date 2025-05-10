
#include "main.h"
#include "spi.h"
#include "epd.h"

static void RESET_HIGH() {
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

static void SPI_WriteByte(uint8_t value) {
	HAL_SPI_Transmit(&hspi2, &value, 1, 1000);
}

static void EPD_Reset(void) {
	RESET_HIGH();
	Delay_ms(20);
	RESET_LOW();
	Delay_ms(2);
	RESET_HIGH();
	Delay_ms(20);
}

static void EPD_SendCommand(uint8_t command) {
	DC_LOW();
	CS_LOW();
	SPI_WriteByte(command);
	CS_HIG();
}

static void EPD_SendData(uint8_t data) {
	DC_HIG();
	CS_LOW();
	SPI_WriteByte(data);
	CS_HIG();
}

static void EPD_ReadBusy(void) {
	while (1) {
		if (BUSY_READ() == 0)
			break;
		Delay_ms(10);
	}
	Delay_ms(10);
}

static void EPD_SetWindows(uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd) {
	EPD_SendCommand(SET_RAM_X_ADDRESS_START_END_POSITION);
	EPD_SendData((xStart >> 3) & 0xFF);
	EPD_SendData((xEnd >> 3) & 0xFF);

	EPD_SendCommand(SET_RAM_Y_ADDRESS_START_END_POSITION);
	EPD_SendData(yStart & 0xFF);
	//EPD_SendData((yStart >> 8) & 0xFF);
	EPD_SendData(yEnd & 0xFF);
	//EPD_SendData((yEnd >> 8) & 0xFF);
}

static void EPD_SetCursor(uint8_t xStart, uint16_t yStart) {
	EPD_SendCommand(SET_RAM_X_ADDRESS_COUNTER);
	EPD_SendData(xStart & 0xFF);

	EPD_SendCommand(SET_RAM_Y_ADDRESS_COUNTER);
	EPD_SendData(yStart & 0xFF);
	//EPD_SendData((yStart >> 8) & 0xFF);
}

static void EPD_TurnOnDisplay(void) {
	//EPD_SendCommand(SET_TEMPERATURE_SENSOR_CONTROL);
	//EPD_SendData(SET_INTERNAL_TEMPERATURE_SENSOR);
	EPD_SendCommand(DISPLAY_UPDATE_CONTROL_2);
	EPD_SendData(UPDATE_SEQUENCE_OPTION);
	EPD_SendCommand(MASTER_ACTIVATION);
	EPD_ReadBusy();
}

void EPD_Init(uint16_t width, uint16_t height) {
	EPD_Reset();

	EPD_ReadBusy();
	EPD_SendCommand(SW_RESET);
	EPD_ReadBusy();

	EPD_SendCommand(DRIVER_OUTPUT_CONTROL);
	EPD_SendData(height - 1);
	//EPD_SendData(((height - 1) >> 8) & 0x01);
	EPD_SendData(0x00);


	EPD_SendCommand(DATA_ENTRY_MODE_SETTING);
	EPD_SendData(0x03);

	EPD_SetWindows(0, 0, width - 1, height - 1);
	EPD_SetCursor(0, 0);

	EPD_SendCommand(BORDER_WAVEFORM_CONTROL);
	EPD_SendData(0x05);

	EPD_SendCommand(DISPLAY_UPDATE_CONTROL_1);
	EPD_SendData(0x00);	//0x00 / 0x01
	EPD_SendData(0x80);

	EPD_ReadBusy();
}

void EPD_Clear(uint16_t width, uint16_t height) {
	width = (width % 8 == 0) ? (width / 8) : (width / 8 + 1);

	EPD_SendCommand(WRITE_RAM);
	for (uint16_t i = 0; i < height; i++) {
		for (uint16_t j = 0; j < width; j++) {
			EPD_SendData(0xFF);
		}
	}

	EPD_TurnOnDisplay();
}

void EPD_Display(const uint8_t *image, uint16_t width, uint16_t height) {
	width = (width % 8 == 0) ? (width / 8) : (width / 8 + 1);

	if (image != NULL) {
		EPD_SendCommand(WRITE_RAM);
		for (uint16_t i = 0; i < width; i++) {
			for (uint16_t j = 0; j < width; j++) {
				EPD_SendData(image[j + i * width]);
			}
		}
	}

	EPD_TurnOnDisplay();
}

void EPD_Sleep() {
	EPD_SendCommand(DEEP_SLEEP_MODE);
	EPD_SendData(0x01);	//enter deep sleep mode
	Delay_ms(100);
}
