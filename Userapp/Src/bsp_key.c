#include "bsp_key.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void Key_GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK | KEY2_GPIO_PIN, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    
    GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);
    GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);
}

uint8_t Key_Scan(GPIO_TypeDef *GPIO_x, uint16_t GPIO_Pin)
{
    if (GPIO_ReadInputDataBit(GPIO_x, GPIO_Pin) == KEY_PRESS)
    {
        while (GPIO_ReadInputDataBit(GPIO_x, GPIO_Pin) == KEY_PRESS);

        return KEY_PRESS;
    }
    else
    {
        return KEY_RELEASE;    
    }
}

