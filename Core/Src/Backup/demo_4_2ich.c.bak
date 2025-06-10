/*
 * demo_4_2ich.c
 *
 *  Created on: Feb 13, 2025
 *      Author: Mateusz
 */

/*
 * demo_2_9ich.c
 *
 *  Created on: Feb 13, 2025
 *      Author: Mateusz
 */

#include "SSD1680.h"
#include "stdlib.h"
#include "GUI_Paint.h"
#include "main.h"

#define WIDTH 400
#define HEIGHT 300
//https://stackoverflow.com/questions/72381277/how-to-create-array-in-flash-that-can-be-overwritten-with-code-using-stm32cubei
extern unsigned char gImage_logo372x70[3290];

void demo_4_2ich() {
	const char of[] = {
			"Oficjalny dystrybutor" };
	const char www[] = {
			"www.interelcom.com" };

	uint16_t x_of = (WIDTH - ((sizeof(of) / sizeof(char) - 1) * Font24.Width)) / 2;
	uint16_t y_of = (HEIGHT * 11 / 16) - Font24.Height / 2;
	uint16_t x_www = (WIDTH - ((sizeof(www) / sizeof(char) - 1) * Font24.Width)) / 2;
	uint16_t y_www = (HEIGHT * 11 / 16) + Font24.Height / 2;

	uint8_t *BlackImage, *RedImage;
	uint16_t Imagesize = ((WIDTH % 8 == 0) ? (WIDTH / 8) : (WIDTH / 8 + 1)) * HEIGHT;

	EPD_Init(WIDTH, HEIGHT);
	EPD_Clear(WIDTH, HEIGHT);
	HAL_Delay(1000);

	if ((BlackImage = (uint8_t*) malloc(Imagesize)) == NULL) {
		Error_Handler();
	}

	Paint_NewImage(BlackImage, WIDTH, HEIGHT, 0, WHITE);

	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);
	Paint_DrawBitMapXY(gImage_logo372x70, (400 - 372) / 2, 300 / 4 - 70 / 2, 372, 70);

	Paint_DrawString_EN(x_of, y_of, of, &Font24, BLACK, WHITE);
	Paint_DrawString_EN(x_www, y_www, www, &Font24, BLACK, WHITE);

	EPD_Display(BlackImage, NULL, WIDTH, HEIGHT);
	free(BlackImage);
	BlackImage = NULL;

	if ((RedImage = (uint8_t*) malloc(Imagesize)) == NULL) {
		Error_Handler();
	}

	Paint_NewImage(RedImage, WIDTH, HEIGHT, 0, WHITE);

	Paint_SelectImage(RedImage);
	Paint_Clear(BLACK);
	Paint_DrawRectangle(0, 150, 400, 300, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	Paint_DrawString_EN(x_of, y_of, of, &Font24, BLACK, WHITE);
	Paint_DrawString_EN(x_www, y_www, www, &Font24, BLACK, WHITE);

	EPD_Display(NULL, RedImage, WIDTH, HEIGHT);
	free(RedImage);
	RedImage = NULL;
	HAL_Delay(2000);

	EPD_Sleep();

	//close 5V

	HAL_GPIO_WritePin(EPD_RST_GPIO_Port, EPD_RST_Pin, GPIO_PIN_RESET);
}

extern unsigned char gImage_logo248x46_H[1426];
extern unsigned char gImage_number303[1170]; //143,65

void demo_4_2ichV2() {
	const char department[] = {
			"R&D department" };
	const char first[] = {
			"- Adam Nowak [Electrical engineer]" };
	const char second[] = {
			"- Jan Kowalski [Mechanical engineer]" };
	const char third[] = {
			"- Jon Smith [Embedded engineer]" };

	uint16_t x_department = (WIDTH - ((sizeof(department) / sizeof(char) - 1) * Font20.Width)) / 2;
	uint16_t y_department = 200;
	uint16_t x_first = 10;
	uint16_t y_first = 230;
	uint16_t x_second = 10;
	uint16_t y_second = 245;
	uint16_t x_third= 10;
	uint16_t y_third = 260;

	uint8_t *BlackImage, *RedImage;
	uint16_t Imagesize = ((WIDTH % 8 == 0) ? (WIDTH / 8) : (WIDTH / 8 + 1)) * HEIGHT;

	EPD_Init(WIDTH, HEIGHT);
	EPD_Clear(WIDTH, HEIGHT);
	HAL_Delay(1000);

	if ((BlackImage = (uint8_t*) malloc(Imagesize)) == NULL) {
		Error_Handler();
	}

	Paint_NewImage(BlackImage, WIDTH, HEIGHT, 0, WHITE);
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);

	Paint_DrawBitMapXY(gImage_logo248x46_H, (WIDTH - 248) / 2, 10, 248, 46);
	Paint_DrawBitMapXY(gImage_number303, (WIDTH - 143) / 2, 90, 143, 65);

	Paint_DrawString_EN(x_department, y_department, department, &Font20, BLACK, WHITE);
	Paint_DrawString_EN(x_first, y_first, first, &Font12, BLACK, WHITE);
	Paint_DrawString_EN(x_second, y_second, second, &Font12, BLACK, WHITE);
	Paint_DrawString_EN(x_third, y_third, third, &Font12, BLACK, WHITE);

	EPD_Display(BlackImage, NULL, WIDTH, HEIGHT);
	free(BlackImage);
	BlackImage = NULL;

	if ((RedImage = (uint8_t*) malloc(Imagesize)) == NULL) {
		Error_Handler();
	}

	Paint_NewImage(RedImage, WIDTH, HEIGHT, 0, WHITE);
	Paint_SelectImage(RedImage);
	Paint_Clear(BLACK);

	Paint_DrawRectangle(0, 65, 400, 80, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	Paint_DrawRectangle(0, 170, 400, 185, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);

	EPD_Display(NULL, RedImage, WIDTH, HEIGHT);
	free(RedImage);
	RedImage = NULL;

	HAL_Delay(2000);

	EPD_Sleep();

	//close 5V

	HAL_GPIO_WritePin(EPD_RST_GPIO_Port, EPD_RST_Pin, GPIO_PIN_RESET);
}

