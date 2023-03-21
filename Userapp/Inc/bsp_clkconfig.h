#ifndef __BSP_CLKCONFIG_H__
#define __BSP_CLKCONFIG_H__

#include "stm32f10x.h"
#include <stdint.h>

void HSE_SetSysCLock(uint32_t pllmul);

void HSI_SetSysCLock(uint32_t pllmul);

void Delay(uint32_t nCount); 

#endif
