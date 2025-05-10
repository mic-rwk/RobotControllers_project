#ifndef EPD_H_
#define EPD_H_

#include "stdint.h"

#define DRIVER_OUTPUT_CONTROL                       0x01
#define BOOSTER_SOFT_START_CONTROL                  0x0C
#define GATE_SCAN_START_POSITION                    0x0F
#define DEEP_SLEEP_MODE                             0x10
#define DATA_ENTRY_MODE_SETTING                     0x11
#define SW_RESET                                    0x12
#define SET_TEMPERATURE_SENSOR_CONTROL              0x18
#define MASTER_ACTIVATION                           0x20
#define DISPLAY_UPDATE_CONTROL_1                    0x21
#define DISPLAY_UPDATE_CONTROL_2                    0x22
#define WRITE_RAM                                   0x24
#define WRITE_VCOM_REGISTER                         0x2C
#define WRITE_LUT_REGISTER                          0x32
#define SET_DUMMY_LINE_PERIOD                       0x3A
#define SET_GATE_TIME                               0x3B
#define BORDER_WAVEFORM_CONTROL                     0x3C
#define SET_RAM_X_ADDRESS_START_END_POSITION        0x44
#define SET_RAM_Y_ADDRESS_START_END_POSITION        0x45
#define SET_RAM_X_ADDRESS_COUNTER                   0x4E
#define SET_RAM_Y_ADDRESS_COUNTER                   0x4F
#define SET_INTERNAL_TEMPERATURE_SENSOR				0x80
#define UPDATE_SEQUENCE_OPTION						0xD7	//?
#define TERMINATE_FRAME_READ_WRITE                  0xFF

static void RESET_HIGH();
static void RESET_LOW();
static void CS_HIG();
static void CS_LOW();
static void DC_HIG();
static uint8_t BUSY_READ();
static void Delay_ms(uint16_t ms);
static void SPI_WriteByte(uint8_t value);

static void EPD_Reset(void);
static void EPD_SendCommand(uint8_t command);
static void EPD_SendData(uint8_t data);
static void EPD_ReadBusy(void);

void EPD_Init(uint16_t width, uint16_t height);
void EPD_Clear(uint16_t width, uint16_t height);
void EPD_Display(const uint8_t *image, uint16_t width, uint16_t height);
void EPD_Sleep();

static void EPD_SetWindows(uint16_t xStart, uint16_t yStart, uint16_t xEnd, uint16_t yEnd);
static void EPD_SetCursor(uint8_t xStart, uint16_t yStart);
static void EPD_TurnOnDisplay(void);

#endif
