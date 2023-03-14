#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include <stdint.h>

#define KEY_OFF     0 
#define KEY_ON      1
#define KEY_PRESS   2 
#define KEY_RELEASE 3

#define KEY1_GPIO_PORT GPIOA
#define KEY1_GPIO_PIN  GPIO_Pin_0
#define KEY1_GPIO_CLK  RCC_APB2Periph_GPIOA

#define KEY2_GPIO_PORT GPIOC
#define KEY2_GPIO_PIN  GPIO_Pin_13
#define KEY2_GPIO_CLK  RCC_APB2Periph_GPIOC

void Key_GPIO_Init(void);

uint8_t Key_Scan(GPIO_TypeDef *GPIO_x, uint16_t GPIO_Pin, uint8_t *GPIO_Pin_State);

#endif
