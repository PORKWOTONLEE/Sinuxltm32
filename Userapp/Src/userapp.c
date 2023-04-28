#include "userapp.h"

#include "hw_config.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "usb_conf.h"
#include "usb_core.h"
#include "usb_init.h"
#include "usb_mem.h"
#include "usb_pwr.h"
#include "usb_type.h"
#include "usb_sil.h"
#include "usb_regs.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "p_config.h"

int userapp(void)
{
    Set_System();

    USB_Interrupts_Config();

    Set_USBClock();

    USB_Init();

    // test
    int8_t key_status; // 0 released/1 pressed
    int8_t send_cdc_msg_allow; 

    while (1)
    {
        if (bDeviceState == CONFIGURED)
        {
            uint8_t keyboard_report[8] = {0};
            uint8_t com_recv_report[64] = {0};
            uint32_t com_recv_report_length;

            if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1)
            {
                keyboard_report[2] = 1<<3;

                Send_HID_Report(keyboard_report, 8);

                if (key_status != 1)
                {
                    key_status = 1;
                    send_cdc_msg_allow = 1;
                }
            }
            else 
            {
                Send_HID_Report(keyboard_report, 8);

                if (key_status != 0)
                {
                    key_status = 0;
                    send_cdc_msg_allow = 1;
                }
            }

            if (send_cdc_msg_allow)
            {
                if (key_status)
                {
                    Debug("Key Pressed\n");
                }
                else 
                {
                    Debug("Key Released\n");
                }

                send_cdc_msg_allow = 0;
            }

            com_recv_report_length = Recv_CDC_Msg(com_recv_report);
            if (com_recv_report_length > 0)
            {
                uint8_t tmp[64] = {0};

                strcat(tmp, "[loopback]");
                strncat(tmp, com_recv_report, com_recv_report_length);
                strcat(tmp, "\n\0");

                Debug(tmp);
            }
        }
    }

    return 0;
}
