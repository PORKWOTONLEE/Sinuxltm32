#include "userapp.h"
#include "bsp_key.h"
#include "bsp_led.h"
#include "bsp_led_bitband.h"
#include "stm32f10x.h"

uint8_t Key1_state = KEY_OFF;
uint8_t Key2_state = KEY_OFF;

int userapp(void)
{
    LED_GPIO_Init();
    Key_GPIO_Init();

    int current_led_flag = 1;

    while (1)
    {
        if (Key_Scan(KEY1_GPIO_PORT, KEY1_GPIO_PIN, &Key1_state) == KEY_PRESS)
        {
            ++current_led_flag;
            current_led_flag%=8;
        }

        if (Key_Scan(KEY2_GPIO_PORT, KEY2_GPIO_PIN, &Key2_state) == KEY_RELEASE)
        {
            --current_led_flag;
            (current_led_flag<0)?current_led_flag=7:current_led_flag;
        }

        switch (current_led_flag) 
        {
            case 1:
                LED_RED_BITBAND;
                break;
            case 2:
                LED_GREEN_BITBAND;
                break;
            case 3:
                LED_BLUE_BITBAND;
                break;
            case 4:
                LED_YELLOW_BITBAND;
                break;
            case 5:
                LED_PURPLE_BITBAND;
                break;
            case 6:
                LED_CYAN_BITBAND;
                break;
            case 7:
                LED_WHITE_BITBAND;
                break;
            default:
                LED_OFF_BITBAND;
                break;
        }
    }
}
