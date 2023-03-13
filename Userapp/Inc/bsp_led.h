#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define LED1_GPIO_PORT GPIOB
#define LED1_GPIO_PIN  GPIO_Pin_5
#define LED1_GPIO_CLK  RCC_APB2Periph_GPIOB

#define LED2_GPIO_PORT GPIOB
#define LED2_GPIO_PIN  GPIO_Pin_0
#define LED2_GPIO_CLK  RCC_APB2Periph_GPIOB

#define LED3_GPIO_PORT GPIOB
#define LED3_GPIO_PIN  GPIO_Pin_1
#define LED3_GPIO_CLK  RCC_APB2Periph_GPIOB

#define digitalHi(p,i)     (p->BSRR&=i)
#define digitalLo(p,i)     (p->BRR&=i)
#define digitalToggle(p,i) (p->ODR^=i)

#define LED1_ON     digitalLo(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED1_OFF    digitalHi(LED1_GPIO_PORT,LED1_GPIO_PIN)
#define LED1_TOGGLE digitalToggle(LED1_GPIO_PORT,LED1_GPIO_PIN)

#define LED2_ON     digitalLo(LED2_GPIO_PORT,LED2_GPIO_PIN)
#define LED2_OFF    digitalHi(LED2_GPIO_PORT,LED2_GPIO_PIN)
#define LED2_TOGGLE digitalToggle(LED2_GPIO_PORT,LED2_GPIO_PIN)

#define LED3_ON     digitalLo(LED3_GPIO_PORT,LED3_GPIO_PIN)
#define LED3_OFF    digitalHi(LED3_GPIO_PORT,LED3_GPIO_PIN)
#define LED3_TOGGLE digitalToggle(LED3_GPIO_PORT,LED3_GPIO_PIN)

#define LED_RED    LED1_ON; \
                   LED2_OFF; \
                   LED3_OFF;

#define LED_GREEN  LED1_OFF; \
                   LED2_ON; \
                   LED3_OFF;

#define LED_BLUE   LED1_OFF; \
                   LED2_OFF; \
                   LED3_ON;

#define LED_YELLOW LED1_ON; \
                   LED2_ON; \
                   LED3_OFF;

#define LED_PURPLE LED1_ON; \
                   LED2_OFF; \
                   LED3_ON;

#define LED_CYAN   LED1_ON; \
                   LED2_ON; \
                   LED3_OFF;

#define LED_OFF    LED1_OFF; \
                   LED2_OFF; \
                   LED3_OFF;

#define LED_WHITE  LED1_ON; \
                   LED2_ON; \
                   LED3_ON;

void LED_GPIO_Init(void);

#endif
