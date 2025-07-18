#include <IL3895.h>
#include "stdlib.h"
#include "GUI_Paint.h"
#include "main.h"
#include <string.h>
#include <stdint.h>
#include "dht11.h"
#include "sgp40.h"
#include "usart.h"
#include <stdio.h>


#define WIDTH 120
#define HEIGHT 250

void demo_V11();
void demo_V22();

extern unsigned char gImage_logo248x46[1488]; //248x46

void demo_V11() {
    static uint8_t BlackImage[120/8 * 250];
    static uint8_t RedImage[120/8 * 250];

    int width_bytes = 128 / 8;

    EPD_Init(120, 250);
    HAL_Delay(300);

    // 1. Wyczyść oba bufory na biało (bit 1 = biały)
    memset(BlackImage, 0xFF, sizeof(BlackImage));


    // 2. Prostokąt 2: czarny (128x100) od wiersza 100 do 199
    for (int y = 50; y < 100; y++) {
        int offset = y * width_bytes;
        memset(&BlackImage[offset], 0x00, width_bytes);
    }

    // 3. Prostokąt 3: czerwony (128x96) od wiersza 200 do 295
    for (int y = 200; y < 296; y++) {
        int offset = y * width_bytes;
        memset(&BlackImage[offset], 0x00, width_bytes);
    }

    // 5. Wyświetl
    EPD_Display(BlackImage, RedImage, 120, 250);
    HAL_Delay(3000);

    EPD_Sleep();
}

void demo_V22(){

    static uint8_t BlackImage[120/8 * 250];
    static uint8_t RedImage[120/8 * 250];

    EPD_Init(120, 250);
    HAL_Delay(300);

    memset(BlackImage, 0xFF, sizeof(BlackImage));

    Paint_NewImage(BlackImage, 120, 250, 0, WHITE);
    Paint_SelectImage(BlackImage);
    Paint_DrawBitMapXY(gImage_logo248x46,0,40,46,100);
    // 5. Wyświetl
    EPD_Display(BlackImage, RedImage, 120, 250);
    HAL_Delay(3000);

    EPD_Sleep();
}


//int _write(int file, char* ptr, int len){
//	HAL_UART_Transmit(&huart2, ptr, len, 50);
//	return len;
//}

void demo_V33(){
    float temperature = 0.0f, humidity = 0.0f;
    char temp_value_str[5] = "Brak danych";


    temperature = DHT_Read_Temp();
    humidity = DHT_Read_Humidity();

    if (temperature > -100.0f)
    {
        snprintf(temp_value_str, sizeof(temp_value_str), "%d C", temperature);
        char buf[64];
        snprintf(buf, sizeof(buf), "%.1f C", temperature);
        HAL_UART_Transmit(&huart4, (uint8_t *)buf, strlen(buf), HAL_MAX_DELAY);
    }
    else
    {
        strcpy(temp_value_str, "1");
        char err[] = "DHT11 read error\r\n";
        HAL_UART_Transmit(&huart4, (uint8_t*)err, strlen(err), HAL_MAX_DELAY);
    }

    uint16_t voc_raw = 0;
    char co2_value_str[4] = "ERR";
    if (SGP40_MeasureRaw(&voc_raw) == HAL_OK)
    {
        snprintf(co2_value_str, sizeof(co2_value_str), "%d", voc_raw);
        char buf[64];
        snprintf(buf, sizeof(buf), "SGP40 VOC: %u raw", voc_raw);
        HAL_UART_Transmit(&huart4, (uint8_t*)buf, strlen(buf), HAL_MAX_DELAY);
    }
    else
    {
        strcpy(co2_value_str, "Błąd");
        char err[] = "SGP40 read error\r\n";
        HAL_UART_Transmit(&huart4, (uint8_t*)err, strlen(err), HAL_MAX_DELAY);
    }
    HAL_Delay(1000);

    uint16_t x_temp_title_text = 0;
    uint16_t y_temp_title_text = 5;
    uint16_t x_co2_title_text = 0;
    uint16_t y_co2_title_text = 50;

    static uint8_t BlackImage[120/8 * 250];
    static uint8_t RedImage[120/8 * 250];

    int width_bytes = 128 / 8;

    EPD_Init(120, 250);
    HAL_Delay(300);

    // 1. Wyczyść oba bufory na biało (bit 1 = biały)
    memset(BlackImage, 0xFF, sizeof(BlackImage));

    // 4. Teraz wczytaj tekst do BlackImage i RedImage za pomocą Paint:
    Paint_NewImage(BlackImage, 120, 250, 0, WHITE);
    Paint_SelectImage(BlackImage);
    char temp_full_str[64];
    char co2_full_str[64];
    snprintf(temp_full_str, sizeof(temp_full_str), "temp%s", temp_value_str);
    snprintf(co2_full_str, sizeof(co2_full_str), "TVOC: %s", co2_value_str);

    Paint_DrawString_EN(x_temp_title_text, y_temp_title_text, temp_full_str, &Font12, BLACK, WHITE);
    Paint_DrawString_EN(x_co2_title_text, y_co2_title_text, co2_full_str, &Font12, BLACK, WHITE);

    // 5. Wyświetl
    EPD_Display(BlackImage, RedImage, 120, 250);
    HAL_Delay(3000);

    EPD_Sleep();
}

void demo4(const char * txt){

	    uint16_t x_temp_title_text = 0;
	    uint16_t y_temp_title_text = 5;

	    static uint8_t BlackImage[120/8 * 250];
	    static uint8_t RedImage[120/8 * 250];

	    int width_bytes = 128 / 8;

	    EPD_Init(120, 250);
	    HAL_Delay(300);

	    // 1. Wyczyść oba bufory na biało (bit 1 = biały)
	    memset(BlackImage, 0xFF, sizeof(BlackImage));

	    // 4. Teraz wczytaj tekst do BlackImage i RedImage za pomocą Paint:
	    Paint_NewImage(BlackImage, 120, 250, 0, WHITE);
	    Paint_SelectImage(BlackImage);

	    Paint_DrawString_EN(x_temp_title_text, y_temp_title_text, txt, &Font12, BLACK, WHITE);

	    // 5. Wyświetl
	    __disable_irq();
	    EPD_Display(BlackImage, RedImage, 120, 250);
	    __enable_irq();

	    HAL_Delay(3000);


	    EPD_Sleep();
}

