#include "userapp.h"

int userapp(void)
{
    while (1)
    {
        int current_led_flag = 0;

        if (Key_Scan(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == KEY_PRESS)
        {
            switch (current_led_flag) 
            {
                case 1:
                    LED_RED;
                    break;
                case 2:
                    LED_GREEN;
                    break;
                case 3:
                    LED_BLUE;
                    break;
                case 4:
                    LED_YELLOW;
                    break;
                case 5:
                    LED_PURPLE;
                    break;
                case 6:
                    LED_CYAN;
                    break;
                case 7:
                    LED_CYAN;
                    break;
                case 8:
                    LED_CYAN;
                    break;
                case 9:
                    LED_WHITE;
                    break;
                case 10:
                    LED_OFF;
                    break;
                default:
                    LED_OFF;
                    break;
            }

            ++current_led_flag;
            current_led_flag%=11;
        }
    }
}
