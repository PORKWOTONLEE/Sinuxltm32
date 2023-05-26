#ifndef __BSP_DMA_H__
#define __BSP_DMA_H__

#include <stdint.h>
#define DMA_CHANNEL DMA1_Channel1
#define DMA_CLOCK   RCC_AHBPeriph_DMA1
#define DMA_FLAG_TC DMA1_FLAG_TC1

#define BUFFER_SIZE 32

extern const uint32_t aSRC_Const_Buffer[BUFFER_SIZE];
extern uint32_t aDST_Buffer[BUFFER_SIZE];

void DMA_Config(void);
uint8_t BufferCompare(const uint32_t *pSRCBuffer, uint32_t *pDSTBuffer, uint16_t BufferLength);

#endif
