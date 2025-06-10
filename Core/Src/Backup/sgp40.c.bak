#include "sgp40.h"
#include "main.h"

#define SGP40_I2C_ADDR (0x59 << 1)

HAL_StatusTypeDef SGP40_Init(I2C_HandleTypeDef *hi2c)
{
    uint8_t cmd[2] = {0x20, 0x03};
    return HAL_I2C_Master_Transmit(hi2c, SGP40_I2C_ADDR, cmd, 2, HAL_MAX_DELAY);
}

HAL_StatusTypeDef SGP40_MeasureRaw(I2C_HandleTypeDef *hi2c, uint16_t *voc_raw)
{
    uint8_t cmd[2] = {0x20, 0x08};
    if (HAL_I2C_Master_Transmit(hi2c, SGP40_I2C_ADDR, cmd, 2, HAL_MAX_DELAY) != HAL_OK)
        return HAL_ERROR;

    HAL_Delay(15); 

    uint8_t rx[6];
    if (HAL_I2C_Master_Receive(hi2c, SGP40_I2C_ADDR, rx, 6, HAL_MAX_DELAY) != HAL_OK)
        return HAL_ERROR;

    *voc_raw = (rx[0] << 8) | rx[1];
    return HAL_OK;
}