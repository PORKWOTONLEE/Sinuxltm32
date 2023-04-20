#include "userapp.h"

#include "hw_config.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "usb_core.h"
#include "usb_init.h"
#include "usb_pwr.h"
#include "usb_type.h"
#include "usb_sil.h"
#include "usb_regs.h"
#include <stdint.h>

__IO uint8_t PrevXferComplete;

int userapp(void)
{
    Set_System();

    USB_Interrupts_Config();

    Set_USBClock();

    USB_Init();

    while (1)
    {
        if (bDeviceState == CONFIGURED)
        {
            uint8_t report_buf[8] = {0};

            if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1)
            {
                report_buf[2] |= 1<<2;

                GPIO_ResetBits(GPIOB, GPIO_Pin_5);
            }
            else 
            {
                GPIO_SetBits(GPIOB, GPIO_Pin_5);
            }

            /* Reset the control token to inform upper layer that a transfer is ongoing */
            PrevXferComplete = 0;

            /* Copy mouse position info in ENDP1 Tx Packet Memory Area*/
            USB_SIL_Write(EP1_IN, report_buf, 8);

            SetEPTxValid(ENDP1);
        }
    }

    return 0;
}
