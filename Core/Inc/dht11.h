#ifndef DHT11_H
#define DHT11_H

#include "main.h"

// DHT11 GPIO pin configuration
#define DHT11_COM_Pin GPIO_PIN_4
#define DHT11_COM_GPIO_Port GPIOA

// DHT11 timing constants
#define DHT11_BIT_DELAY_US         40
#define DHT11_POST_INPUT_DELAY_US  10
#define DHT11_RESPONSE_DELAY1_US   40
#define DHT11_RESPONSE_DELAY2_US   100
#define DHT11_RESPONSE_DELAY3_US   40   

// Function prototypes
void DHT11_Start(void);
uint8_t DHT11_CheckResponse(void);
uint8_t DHT11_ReadByte(void);
float DHT_Read_Temp(void);
float DHT_Read_Humidity(void);


#endif // DHT11_H
