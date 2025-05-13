#include "main.h"
#include "paint.h"
#include <stdint.h>

PAINT Paint;

void Paint_NewImage(uint8_t *image, uint16_t Width, uint16_t Height, uint16_t Rotate, uint16_t Color) {
	Paint.Image = NULL;
	Paint.Image = image;

	Paint.WidthMemory = Width;
	Paint.HeightMemory = Height;
	Paint.Color = Color;
	Paint.WidthByte = (Paint.WidthMemory % 8 == 0) ? (Paint.WidthMemory / 8) : (Paint.WidthMemory / 8 + 1);
	Paint.HeightByte = Height;

	Paint.Rotate = Rotate;
	Paint.Mirror = MIRROR_NONE;
	Paint.Scale = 2;
	if (Rotate == ROTATE_0 || Rotate == ROTATE_180) {
		Paint.Width = Width;
		Paint.Height = Height;
	} else {
		Paint.Width = Height;
		Paint.Height = Width;
	}
}

void Paint_SelectImage(uint8_t *image) {
	Paint.Image = image;
}

void Paint_SetRotate(uint16_t Rotate) {
	if (Rotate == ROTATE_0 || Rotate == ROTATE_90 || Rotate == ROTATE_180 || Rotate == ROTATE_270) {
		Paint.Rotate = Rotate;
	}
}

void Paint_SetMirroring(uint8_t mirror) {
	if (mirror == MIRROR_NONE || mirror == MIRROR_HORIZONTAL || mirror == MIRROR_VERTICAL || mirror == MIRROR_ORIGIN) {
		Paint.Mirror = mirror;
	}
}

void Paint_SetScale(uint8_t scale) {
	if (scale == 2) {
		Paint.Scale = 2;
		Paint.WidthByte = (Paint.WidthMemory % 8 == 0) ? (Paint.WidthMemory / 8) : (Paint.WidthMemory / 8 + 1);
	} else if (scale == 4) {
		Paint.Scale = 4;
		Paint.WidthByte = (Paint.WidthMemory % 4 == 0) ? (Paint.WidthMemory / 4) : (Paint.WidthMemory / 4 + 1);
	}
}

void Paint_Clear(uint16_t Color) {
	if (Paint.Scale == 2) {
		for (uint16_t Y = 0; Y < Paint.HeightByte; Y++) {
			for (uint16_t X = 0; X < Paint.WidthByte; X++) {
				uint32_t Addr = X + Y * Paint.WidthByte;
				Paint.Image[Addr] = Color;
			}
		}
	} else if (Paint.Scale == 4) {
		Color = Color % 4;
		if (Color == 0x00) {
			Color = 0;
		} else if (Color == 0x01) {
			Color = 0x55;
		} else if (Color == 0x02) {
			Color = 0xAA;
		} else if (Color == 0x03) {
			Color = 0xff;
		}
		for (uint16_t Y = 0; Y < Paint.HeightByte; Y++) {
			for (uint16_t X = 0; X < Paint.WidthByte; X++) {
				uint32_t Addr = X + Y * Paint.WidthByte;
				Paint.Image[Addr] = Color;
			}
		}
	} else if (Paint.Scale == 7) {
		for (uint16_t Y = 0; Y < Paint.HeightByte; Y++) {
			for (uint16_t X = 0; X < Paint.WidthByte; X++) {
				uint32_t Addr = X + Y * Paint.WidthByte;
				Paint.Image[Addr] = (Color << 4) | Color;
			}
		}
	}
}

void Paint_ClearWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t Color) {
	uint16_t X, Y;
	for (Y = Ystart; Y < Yend; Y++) {
		for (X = Xstart; X < Xend; X++) {
			Paint_SetPixel(X, Y, Color);
		}
	}
}

void Paint_DrawBitMap(const unsigned char *image_buffer) {
	uint16_t x, y;
	uint32_t Addr = 0;
	for (y = 0; y < Paint.HeightByte; y++) {
		for (x = 0; x < Paint.WidthByte; x++) {
			Addr = x + y * Paint.WidthByte;
			Paint.Image[Addr] = (unsigned char) image_buffer[Addr];
		}
	}
}

void Paint_DrawBitMapXY(const unsigned char *image_buffer, uint16_t Xstart, uint16_t Ystart, uint16_t Width, uint16_t Height) {
	uint16_t x, y;
	uint32_t Addr_buff = 0, Addr_image = 0;
	Width = (Width % 8 == 0) ? (Width / 8) : (Width / 8 + 1);
	Xstart = (Xstart % 8 == 0) ? (Xstart / 8) : (Xstart / 8 + 1);
	for (y = 0; y < Height; y++) {
		for (x = 0; x < Width; x++) {
			Addr_image = x + y * Width;
			Addr_buff = (x + Xstart) + (y + Ystart) * Paint.WidthByte;
			Paint.Image[Addr_buff] = (unsigned char) image_buffer[Addr_image];
		}
	}
}

uint16_t DataInversion_GUI = 0;
void DrawBitMap_DataInversion(uint16_t mode) {
	DataInversion_GUI = mode;
}

void Paint_DrawBitMap_Block(const unsigned char *image_buffer, uint8_t Region) {
	uint16_t x, y;
	uint32_t Addr = 0;
	for (y = 0; y < Paint.HeightByte; y++) {
		for (x = 0; x < Paint.WidthByte; x++) {
			Addr = x + y * Paint.WidthByte;
			if (DataInversion_GUI == 0) {
				Paint.Image[Addr] = (unsigned char) image_buffer[Addr + (Paint.HeightByte) * Paint.WidthByte * (Region - 1)];
			} else {
				Paint.Image[Addr] = ~(unsigned char) image_buffer[Addr + (Paint.HeightByte) * Paint.WidthByte * (Region - 1)];
			}

		}
	}
}

