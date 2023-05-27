#include "bsp_dma_uart.h"
#include "bsp_uart.h"
#include "stm32f10x.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include <stdint.h>

uint8_t aSRC_Buffer[UART_DMA_BUFFER_SIZE] = "HeLLo WoRld !!! This is a demo of DMA/UART\n";

void UART_DMA_Config(void)
{
    // DMA
    DMA_InitTypeDef DMA_InitStructure;
    // DMA Clk enable
    RCC_AHBPeriphClockCmd(UART_DMA_CLK, ENABLE);
    // DMA param config
    DMA_InitStructure.DMA_PeripheralBaseAddr = UART_DR_ADDR;
    DMA_InitStructure.DMA_MemoryBaseAddr     = (u32)aSRC_Buffer;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize         = UART_DMA_BUFFER_SIZE;
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_Medium;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(UART_DMA_CHANNEL, &DMA_InitStructure);
    // DMA enable
    DMA_Cmd (UART_DMA_CHANNEL,ENABLE);
    // DMA UART TX enable
    USART_DMACmd(USARTx, USART_DMAReq_Tx, ENABLE);
}

