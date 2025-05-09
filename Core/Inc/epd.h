#ifndef INC_EPD_H_
#define INC_EPD_H_

#include "stdint.h"

void EPD_Init(uint16_t width, uint16_t height);
void EPD_Clear(uint16_t width, uint16_t height);
void EPD_Display(const uint8_t *image, uint16_t width, uint16_t height);
void EPD_Sleep();


#endif
