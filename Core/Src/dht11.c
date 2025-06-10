#include "dht11.h"
#include "main.h"
#include "tim.h"

#define DHT_Pin GPIO_PIN_4
#define DHT_GPIO_Port GPIOA

#define DHT11_BIT_DELAY_US         40
#define DHT11_POST_INPUT_DELAY_US  10
#define DHT11_RESPONSE_DELAY1_US   40
#define DHT11_RESPONSE_DELAY2_US   100
#define DHT11_RESPONSE_DELAY3_US   40   


extern TIM_HandleTypeDef htim6;
void delay_us(uint16_t us)
{
    __HAL_TIM_SET_COUNTER(&htim6, 0);
    while (__HAL_TIM_GET_COUNTER(&htim6) < us);
}

void DHT11_Start(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DHT11_COM_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DHT_GPIO_Port, &GPIO_InitStruct);

    HAL_GPIO_WritePin(DHT_GPIO_Port, DHT_Pin, GPIO_PIN_RESET);
    delay_us(18);
    HAL_GPIO_WritePin(DHT_GPIO_Port, DHT_Pin, GPIO_PIN_SET);
    delay_us(20);

    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DHT_GPIO_Port, &GPIO_InitStruct);

    delay_us(DHT11_POST_INPUT_DELAY_US);
}

uint8_t DHT11_CheckResponse(void)
{
    uint8_t response = 0;
    delay_us(DHT11_RESPONSE_DELAY1_US);
    if (!HAL_GPIO_ReadPin(DHT11_COM_GPIO_Port, DHT11_COM_Pin))
    {
        delay_us(DHT11_RESPONSE_DELAY2_US);
        if (HAL_GPIO_ReadPin(DHT_GPIO_Port, DHT_Pin)) response = 1;
        delay_us(DHT11_RESPONSE_DELAY3_US);
    }
    return response;
}

uint8_t DHT11_ReadByte(void)
{
    uint8_t j, byte = 0;
    for (j = 0; j < 8; j++)
    {
        while (!HAL_GPIO_ReadPin(DHT_GPIO_Port, DHT_Pin));
        delay_us(DHT11_BIT_DELAY_US);
        if (HAL_GPIO_ReadPin(DHT_GPIO_Port, DHT_Pin))
            byte |= (1 << (7 - j));
        while (HAL_GPIO_ReadPin(DHT_GPIO_Port, DHT_Pin));
    }
    return byte;
}

float DHT_Read_Temp(void)
{
    DHT11_Start();
    if (DHT11_CheckResponse())
    {
        uint8_t Rh_byte1 = DHT11_ReadByte();
        uint8_t Rh_byte2 = DHT11_ReadByte();
        uint8_t Temp_byte1 = DHT11_ReadByte();
        uint8_t Temp_byte2 = DHT11_ReadByte();
        uint8_t checksum = DHT11_ReadByte();

        uint16_t raw_temp = (Temp_byte1 << 8 ) | Temp_byte2;
        float temperature = raw_temp / 10.0f;
        if (raw_temp & 0x8000)
            temperature = -((raw_temp & 0x7FFF) / 10.0f);

        if (((Rh_byte1 + Rh_byte2 + Temp_byte1 + Temp_byte2) & 0xFF) == checksum)
            return temperature;
    }
    return -1000.0f; // wartość błędna
}

float DHT_Read_Humidity(void)
{
    DHT11_Start();
    if (DHT11_CheckResponse())
    {
        uint8_t Rh_byte1 = DHT11_ReadByte();
        uint8_t Rh_byte2 = DHT11_ReadByte();
        uint8_t Temp_byte1 = DHT11_ReadByte();
        uint8_t Temp_byte2 = DHT11_ReadByte();
        uint8_t checksum = DHT11_ReadByte();

        uint16_t raw_hum = (Rh_byte1 << 8 ) | Rh_byte2;
        float humidity = raw_hum / 10.0f;

        if (((Rh_byte1 + Rh_byte2 + Temp_byte1 + Temp_byte2) & 0xFF) == checksum)
            return humidity;
    }
    return -1.0f; // wartość błędna
}
