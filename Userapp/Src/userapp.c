#include "userapp.h"

#include "hw_config.h"
#include "usb_init.h"

int userapp(void)
{
    Set_System();

    USB_Interrupts_Config();

    Set_USBClock();

    USB_Init();

    return 0;
}
