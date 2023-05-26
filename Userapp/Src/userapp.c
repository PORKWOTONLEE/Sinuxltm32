#include "userapp.h"
#include "bsp_dma.h"
#include "bsp_clkconfig.h"
#include "bsp_led.h"
#include "stm32f10x.h"
#include "stm32f10x_dma.h"
#include <stdint.h>

int userapp(void)
{
    LED_GPIO_Init();

    Delay(3000000);    

    LED_PURPLE;

    DMA_Config();

    while (DMA_GetFlagStatus(DMA_FLAG_TC) == RESET);

    Delay(3000000);    

    if (BufferCompare(aSRC_Const_Buffer, aDST_Buffer, BUFFER_SIZE) == 0)
    {
        LED_GREEN;
    }
    else 
    {
        LED_RED;
    }

    while (1)
    {
    }
}
