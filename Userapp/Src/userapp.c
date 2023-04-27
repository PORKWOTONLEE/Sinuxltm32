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

__IO uint8_t PrevReportXferComplete;
__IO uint8_t PrevComXferComplete;
__IO uint8_t ComRecvComplete;

int userapp(void)
{
    Set_System();

    USB_Interrupts_Config();

    Set_USBClock();

    USB_Init();

    // custom varies
    PrevReportXferComplete = 1;
    PrevComXferComplete = 1;
    ComRecvComplete = 0;

    while (1)
    {
        if (bDeviceState == CONFIGURED)
        {
        }
    }

    return 0;
}
