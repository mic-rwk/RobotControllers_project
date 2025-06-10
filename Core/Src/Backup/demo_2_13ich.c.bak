#include <IL3895.h>
#include "stdlib.h"
#include "GUI_Paint.h"
#include "main.h"
#include <string.h>
#include <stdint.h>

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

void demo_V33(uint16_t temp, uint16_t co2){
    const char temp_title_text[] = "Temperatura: ";
    const char co2_title_text[] = "CO2: ";

    uint16_t x_temp_title_text = 0;
    uint16_t y_temp_title_text = 5;
    uint16_t x_co2_title_text = 0;
    uint16_t y_co2_title_text = 50;

    uint16_t x_temp_value = 100;
    uint16_t y_temp_value = 5;
    uint16_t x_co2_value = 100;
    uint16_t y_co2_value = 50;

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
    Paint_DrawString_EN(x_temp_title_text, y_temp_title_text, temp_title_text, &Font12, BLACK, WHITE);
    Paint_DrawString_EN(x_co2_title_text, y_co2_title_text, co2_title_text, &Font12, BLACK, WHITE);

    // 5. Wyświetl
    EPD_Display(BlackImage, RedImage, 120, 250);
    HAL_Delay(3000);

    EPD_Sleep();
}

