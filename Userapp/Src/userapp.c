#include "userapp.h"
#include "bsp_clkconfig.h"
#include "bsp_uart.h"
#include "bsp_dma_uart.h"
#include "bsp_led.h"
#include "stm32f10x.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_usart.h"
#include <stdint.h>

int userapp(void)
{
    LED_GPIO_Init();

    LED_PURPLE;

    USART_Config();

    Delay(5000000);

    UART_DMA_Config();

    while (1)
    {
        LED_GREEN;
        Delay(5000000);
        LED_OFF;
        Delay(5000000);
    }
}
