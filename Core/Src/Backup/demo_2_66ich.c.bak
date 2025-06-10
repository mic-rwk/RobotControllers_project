/*
 * demo_2_66ich.c
 *
 *  Created on: Feb 13, 2025
 *      Author: Mateusz
 */
#include "SSD1680.h"
#include "stdlib.h"
#include "GUI_Paint.h"
#include "main.h"

#define WIDTH 152
#define HEIGHT 296

extern unsigned char gImage_logo248x46[1488]; //248x46

void demo_2_66ich() {
	const char of[] = {
			"Oficjalny dystrybutor" };
	const char www[] = {
			"www.interelcom.com" };

	uint16_t x_of = (HEIGHT - ((sizeof(of) / sizeof(char) - 1) * Font16.Width)) / 2;
	uint16_t y_of = (WIDTH * 11 / 16) - Font16.Height / 2;
	uint16_t x_www = (HEIGHT - ((sizeof(www) / sizeof(char) - 1) * Font16.Width)) / 2;
	uint16_t y_www = (WIDTH * 11 / 16) + Font16.Height / 2;

	uint8_t *BlackImage, *RedImage;
	uint16_t Imagesize = ((WIDTH % 8 == 0) ? (WIDTH / 8) : (WIDTH / 8 + 1)) * HEIGHT;

	EPD_Init(WIDTH, HEIGHT);
	EPD_Clear(WIDTH, HEIGHT);
	HAL_Delay(1000);

	if ((BlackImage = (uint8_t*) malloc(Imagesize)) == NULL) {
		Error_Handler();
	}
	if ((RedImage = (uint8_t*) malloc(Imagesize)) == NULL) {
		Error_Handler();
	}

	Paint_NewImage(BlackImage, WIDTH, HEIGHT, 90, WHITE);
	Paint_NewImage(RedImage, WIDTH, HEIGHT, 90, WHITE);

	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);
	Paint_DrawBitMapXY(gImage_logo248x46, (WIDTH * 3 / 4) - 46 / 2, (HEIGHT - 248) / 2, 46, 248);

	Paint_DrawString_EN(x_of, y_of, of, &Font16, BLACK, WHITE);
	Paint_DrawString_EN(x_www, y_www, www, &Font16, BLACK, WHITE);

	Paint_SelectImage(RedImage);
	Paint_Clear(BLACK);
	Paint_DrawRectangle(0, WIDTH / 2, HEIGHT, WIDTH, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	Paint_DrawString_EN(x_of, y_of, of, &Font16, BLACK, WHITE);
	Paint_DrawString_EN(x_www, y_www, www, &Font16, BLACK, WHITE);

	EPD_Display(BlackImage, RedImage, WIDTH, HEIGHT);
	HAL_Delay(2000);

	EPD_Sleep();
	free(BlackImage);
	free(RedImage);
	BlackImage = NULL;
	RedImage = NULL;
	//close 5V

	HAL_GPIO_WritePin(EPD_RST_GPIO_Port, EPD_RST_Pin, GPIO_PIN_RESET);
}

extern unsigned char gImage_barcodeImage[1008];

void demo_2_66ichV2() {
	const char first[] = {
			"Pepsi MAX" };
	const char second[] = {
			"8pak 500ml" };
	const char third[] = {
			"12$/L" };
	const char promotion[] = {
			"PROMOCJA" };
	const char last_price[] = {
			"23.99$" };
	const char price[] = {
			"21.99$" };

	uint16_t x_first = 5;
	uint16_t y_first = 5;
	uint16_t x_second = 5;
	uint16_t y_second = 35;
	uint16_t x_third = 5;
	uint16_t y_third = 50;
	uint16_t x_promotion = HEIGHT - (Font20.Width * (sizeof(promotion) / sizeof(char) - 1) + 5);
	uint16_t y_promotion = 6;
	uint16_t x_last_price = HEIGHT - (Font12.Width * (sizeof(last_price) / sizeof(char) - 1));		//205
	uint16_t y_last_price = y_promotion + Font20.Height + 5;			//30
	uint16_t x_price = (HEIGHT - Font24.Width * (sizeof(last_price) / sizeof(char) - 1)) / 2;
	uint16_t y_price = (WIDTH - Font24.Height) / 2;

	uint8_t *BlackImage, *RedImage;
	uint16_t Imagesize = ((WIDTH % 8 == 0) ? (WIDTH / 8) : (WIDTH / 8 + 1)) * HEIGHT;

	EPD_Init(WIDTH, HEIGHT);
	EPD_Clear(WIDTH, HEIGHT);
	HAL_Delay(1000);

	if ((BlackImage = (uint8_t*) malloc(Imagesize)) == NULL) {
		Error_Handler();
	}
	if ((RedImage = (uint8_t*) malloc(Imagesize)) == NULL) {
		Error_Handler();
	}

	Paint_NewImage(BlackImage, WIDTH, HEIGHT, 90, WHITE);
	Paint_NewImage(RedImage, WIDTH, HEIGHT, 90, WHITE);

	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);

	Paint_DrawString_EN(x_first, y_first, first, &Font20, BLACK, WHITE);
	Paint_DrawString_EN(x_second, y_second, second, &Font12, BLACK, WHITE);
	Paint_DrawString_EN(x_third, y_third, third, &Font12, BLACK, WHITE);
	Paint_DrawString_EN(x_last_price, y_last_price, last_price, &Font12, BLACK, WHITE);
	Paint_DrawLine(x_last_price, y_last_price + Font12.Height / 2, x_last_price + (Font12.Width * (sizeof(last_price) / sizeof(char) - 1)), y_last_price + Font12.Height / 2, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawBitMapXY(gImage_barcodeImage, 0, (HEIGHT - 161) / 2, 48, 161);

	Paint_SelectImage(RedImage);
	Paint_Clear(BLACK);

	Paint_DrawRectangle(x_promotion - 5, y_promotion - 5, x_promotion + Font20.Width * (sizeof(promotion) / sizeof(char) - 1) + 5, y_promotion + Font20.Height + 5, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	Paint_DrawString_EN(x_promotion, y_promotion, promotion, &Font20, BLACK, RED);
	Paint_DrawString_EN(x_price, y_price, price, &Font24, RED, BLACK);

	EPD_Display(BlackImage, RedImage, WIDTH, HEIGHT);
	HAL_Delay(2000);

	EPD_Sleep();
	free(BlackImage);
	free(RedImage);
	BlackImage = NULL;
	RedImage = NULL;
	//close 5V

	HAL_GPIO_WritePin(EPD_RST_GPIO_Port, EPD_RST_Pin, GPIO_PIN_RESET);
}

