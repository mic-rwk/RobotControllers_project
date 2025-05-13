
#ifndef INC_PAINT_H_
#define INC_PAINT_H_

typedef struct {
    uint8_t *Image;
    uint16_t Width;
    uint16_t Height;
    uint16_t WidthMemory;
    uint16_t HeightMemory;
    uint16_t Color;
    uint16_t Rotate;
    uint16_t Mirror;
    uint16_t WidthByte;
    uint16_t HeightByte;
	uint16_t Scale;
} PAINT;
extern PAINT Paint;

/**
 * Display rotate
**/
#define ROTATE_0            0
#define ROTATE_90           90
#define ROTATE_180          180
#define ROTATE_270          270

/**
 * Display Flip
**/
typedef enum {
    MIRROR_NONE  = 0x00,
    MIRROR_HORIZONTAL = 0x01,
    MIRROR_VERTICAL = 0x02,
    MIRROR_ORIGIN = 0x03,
} MIRROR_IMAGE;
#define MIRROR_IMAGE_DFT MIRROR_NONE

#define WHITE          0xFF
#define BLACK          0x00

#define IMAGE_BACKGROUND    WHITE

void Paint_NewImage(uint8_t *image, uint16_t Width, uint16_t Height, uint16_t Rotate, uint16_t Color);
void Paint_SelectImage(uint8_t *image);
void Paint_SetRotate(uint16_t Rotate);
void Paint_SetMirroring(uint8_t mirror);
void Paint_SetScale(uint8_t scale);

void Paint_Clear(uint16_t Color);
void Paint_ClearWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t Color);

void Paint_DrawBitMap(const unsigned char* image_buffer);
void Paint_DrawBitMapXY(const unsigned char *image_buffer, uint16_t Xstart, uint16_t Ystart, uint16_t Width, uint16_t Height);
void DrawBitMap_DataInversion(uint16_t mode);
void Paint_DrawBitMap_Block(const unsigned char* image_buffer, uint8_t Region);

#endif
