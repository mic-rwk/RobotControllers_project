#include "dht11.h"
#include "main.h"

#define DHT11_COM_Pin GPIO_PIN_4
#define DHT11_COM_GPIO_Port GPIOA

#define DHT11_BIT_DELAY_US         40
#define DHT11_POST_INPUT_DELAY_US  10
#define DHT11_RESPONSE_DELAY1_US   40
#define DHT11_RESPONSE_DELAY2_US   100
#define DHT11_RESPONSE_DELAY3_US   40   

void delay_us(uint16_t us)
{
    __HAL_TIM_SET_COUNTER(&htim1, 0);
    while (__HAL_TIM_GET_COUNTER(&htim1) < us);
}

void DHT11_Start(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DHT11_COM_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DHT11_COM_GPIO_Port, &GPIO_InitStruct);

    HAL_GPIO_WritePin(DHT11_COM_GPIO_Port, DHT11_COM_Pin, GPIO_PIN_RESET);
    HAL_Delay(18);
    HAL_GPIO_WritePin(DHT11_COM_GPIO_Port, DHT11_COM_Pin, GPIO_PIN_SET);
    delay_us(20);

    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DHT11_COM_GPIO_Port, &GPIO_InitStruct);

    delay_us(DHT11_POST_INPUT_DELAY_US);
}

uint8_t DHT11_CheckResponse(void)
{
    uint8_t response = 0;
    delay_us(DHT11_RESPONSE_DELAY1_US);
    if (!HAL_GPIO_ReadPin(DHT11_COM_GPIO_Port, DHT11_COM_Pin))
    {
        delay_us(DHT11_RESPONSE_DELAY2_US);
        if (HAL_GPIO_ReadPin(DHT11_COM_GPIO_Port, DHT11_COM_Pin)) response = 1;
        delay_us(DHT11_RESPONSE_DELAY3_US);
    }
    return response;
}

uint8_t DHT11_ReadByte(void)
{
    uint8_t j, byte = 0;
    for (j = 0; j < 8; j++)
    {
        while (!HAL_GPIO_ReadPin(DHT11_COM_GPIO_Port, DHT11_COM_Pin));
        delay_us(DHT11_BIT_DELAY_US);
        if (HAL_GPIO_ReadPin(DHT11_COM_GPIO_Port, DHT11_COM_Pin))
            byte |= (1 << (7 - j));
        while (HAL_GPIO_ReadPin(DHT11_COM_GPIO_Port, DHT11_COM_Pin));
    }
    return byte;
}