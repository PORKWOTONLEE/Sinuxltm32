#ifndef __BSP_DMA_UART_H__
#define __BSP_DMA_UART_H__

#include "stm32f10x_usart.h"

#define UART_DR_ADDR         (USART1_BASE + 0x04)

// DMA
#define UART_DMA_CLK              RCC_AHBPeriph_DMA1
#define UART_DMA_CHANNEL          DMA1_Channel4 // channel 4 support only
#define UART_DMA_BUFFER_SIZE      64

extern uint8_t aSRC_Buffer[UART_DMA_BUFFER_SIZE];

void UART_DMA_Config(void);

#endif
