#ifndef __BSP_UART_H__
#define __BSP_UART_H__

#include "stm32f10x_usart.h"

// GPIO for USART1
#define USART_GPIO_CLK        (RCC_APB2Periph_GPIOA)
#define USART_GPIO_APBxClkCmd RCC_APB2PeriphClockCmd

#define USART_TX_GPIO_PORT    GPIOA
#define USART_TX_GPIO_PIN     GPIO_Pin_9 
#define USART_RX_GPIO_PORT    GPIOA
#define USART_RX_GPIO_PIN     GPIO_Pin_10

// USART1
#define USARTx                USART1
#define USART_CLK             RCC_APB2Periph_USART1
#define USART_APBxClkCmd      RCC_APB2PeriphClockCmd
#define USART_BAUDRATE        115200

#define USART_IRQ             USART1_IRQn 
#define USART_IRQHandler      USART1_IRQHandler 

void NVIC_Configuration(void);
void USART_Config(void);
void USART_SendByte(USART_TypeDef *pUSARTx, uint8_t ch);
void USART_SendString(USART_TypeDef *pUSARTx, char *str);

#endif
