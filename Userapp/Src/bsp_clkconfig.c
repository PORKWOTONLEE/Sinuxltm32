#include "bsp_clkconfig.h"
#include "stm32f10x.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_rcc.h"
#include <stdint.h>


void HSE_SetSysCLock(uint32_t pllmul)
{
    __IO uint32_t HSEStartUpStatus = 0;

    RCC_DeInit();

    RCC_HSEConfig(RCC_HSE_ON);

    HSEStartUpStatus = RCC_WaitForHSEStartUp();

    if (HSEStartUpStatus == SUCCESS)
    {
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

        FLASH_SetLatency(FLASH_Latency_2);

        RCC_HCLKConfig(RCC_SYSCLK_Div1);

        RCC_PCLK1Config(RCC_HCLK_Div2);

        RCC_PCLK2Config(RCC_HCLK_Div1);

        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, pllmul);

        RCC_PLLCmd(ENABLE);

        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {}

        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

        while (RCC_GetSYSCLKSource() != 0x08)
        {}
    }
    else 
    {
        while (1)
        {}
    }
}

void HSI_SetSysCLock(uint32_t pllmul)
{
    __IO uint32_t HSEStartUpStatus = 0;

    RCC_DeInit();

    RCC_HSICmd(ENABLE);

    HSEStartUpStatus = RCC->CR & RCC_CR_HSIRDY; 

    if (HSEStartUpStatus == RCC_CR_HSIRDY)
    {
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

        FLASH_SetLatency(FLASH_Latency_2);

        RCC_HCLKConfig(RCC_SYSCLK_Div1);

        RCC_PCLK1Config(RCC_HCLK_Div2);

        RCC_PCLK2Config(RCC_HCLK_Div1);

        RCC_PLLConfig(RCC_PLLSource_HSI_Div2, pllmul);

        RCC_PLLCmd(ENABLE);

        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {}

        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

        while (RCC_GetSYSCLKSource() != 0x08)
        {}
    }
    else 
    {
        while (1)
        {}
    }
}

void Delay(uint32_t nCount)
{
    for (; nCount!=0;nCount--);
}
