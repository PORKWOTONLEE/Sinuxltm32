#include "userapp.h"
#include "bsp_exti.h"
#include "bsp_uart.h"
#include "bsp_key.h"
#include <stdint.h>

uint8_t KEY1_STATE = KEY_ON;

int userapp(void)
{
    USART_Config();
    Key_GPIO_Init();

    uint8_t Key1_state;
    while (1)
    {
        Key1_state = Key_Scan(KEY1_INT_GPIO_PORT, KEY1_GPIO_PIN, &KEY1_STATE);
        if (Key1_state == KEY_PRESS)
        {
            USART_SendString(USARTx, "KEY 1 Pressed\n");
        }
        else if (Key1_state == KEY_RELEASE)
        {
            USART_SendString(USARTx, "KEY 1 Released\n");
        }
    }
}
