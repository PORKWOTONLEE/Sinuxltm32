#include "userapp.h"
#include "bsp_clkconfig.h"
#include "bsp_exti.h"
#include "bsp_key.h"
#include "bsp_led.h"
#include "bsp_led_bitband.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"

uint8_t Key1_state = KEY_OFF;
uint8_t Key2_state = KEY_OFF;

int userapp(void)
{
    HSE_SetSysCLock(RCC_PLLMul_8);
    LED_GPIO_Init();
    KEY_EXTI_Init();

    while (1)
    {
        LED_RED;
        Delay(10000000);
        LED_GREEN;
        Delay(10000000);
        LED_BLUE;
        Delay(10000000);
    }
}
