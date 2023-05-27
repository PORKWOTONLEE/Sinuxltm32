#include "bsp_dma.h"
#include "stm32f10x.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_rcc.h"
#include <stdint.h>

const uint32_t aSRC_Const_Buffer[DMA_BUFFER_SIZE] = 
{
    0x01020304, 0x05060708, 0x090A0B0C, 0x0D0E0F10, 
    0x11120304, 0x05160718, 0x090A1B0C, 0x0D0E0F10, 
    0x21220304, 0x05260728, 0x090A2B0C, 0x0D0E0F20, 
    0x31320304, 0x05360738, 0x090A3B0C, 0x0D0E0F30, 
    0x41420304, 0x05460748, 0x090A4B0C, 0x0D0E0F40, 
    0x51520304, 0x05560758, 0x090A5B0C, 0x0D0E0F50, 
    0x61620304, 0x05660768, 0x090A6B0C, 0x0D0E0F60, 
    0x71720304, 0x05760778, 0x090A7B0C, 0x0D0E0F70
};

uint32_t aDST_Buffer[DMA_BUFFER_SIZE];

void DMA_Config(void)
{
    // DMA
    DMA_InitTypeDef DMA_InitStructure;
    // DMA Clk enable
    RCC_AHBPeriphClockCmd(DMA_CLK, ENABLE);
    // DMA param config
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) aSRC_Const_Buffer;
    DMA_InitStructure.DMA_MemoryBaseAddr     = (uint32_t) aDST_Buffer;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize         = DMA_BUFFER_SIZE;
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Enable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Enable;
    DMA_Init(DMA_CHANNEL, &DMA_InitStructure);
    // DMA enable
    DMA_Cmd(DMA_CHANNEL, ENABLE);
}

uint8_t BufferCompare(const uint32_t *pSRCBuffer, uint32_t *pDSTBuffer, uint16_t BufferLength)
{
    for (int i=0; i<BufferLength; ++i)
    {
        if (*(pSRCBuffer+i) == *(pDSTBuffer+i))
        {
            continue;
        }
        else 
        {
            return 1;
        }
    }

    return 0;
}
