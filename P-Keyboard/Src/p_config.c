#include "p_config.h"
#include "stm32f10x_gpio.h"
#include "usb_pwr.h"
#include "usb_regs.h"
#include "usb_sil.h"
#include "usb_type.h"
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
__IO uint8_t ReportXferComplete = TRUE;
__IO uint8_t ReportRecvComplete = FALSE;
__IO uint8_t ComXferComplete = TRUE;
__IO uint8_t ComRecvComplete = FALSE;

#if CUSTOM_LANGID_STRING == P_TRUE 
/* USB String Descriptors (optional) */
const uint8_t Composite_StringLangID[CUSTOM_SIZ_STRING_LANGID] =
  {
    CUSTOM_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04
  }; /* LangID = 0x0409: U.S. English */
#endif

#if CUSTOM_VENDOR_STRING == P_TRUE 
const uint8_t Composite_StringVendor[CUSTOM_SIZ_STRING_VENDOR] =
  {
    CUSTOM_SIZ_STRING_VENDOR, /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType*/
    /* Manufacturer: "STMicroelectronics" */
    'C', 0, 'U', 0, 'S', 0, 'T', 0, 'O', 0, 'M', 0, 
    'V', 0, 'E', 0, 'N', 0, 'D', 0, 'O', 0, 'R', 0
  };
#endif

#if CUSTOM_DEVICE_STRING == P_TRUE
const uint8_t Composite_StringProduct[CUSTOM_SIZ_STRING_PRODUCT] =
  {
    CUSTOM_SIZ_STRING_PRODUCT,          /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'C', 0, 'U', 0, 'S', 0, 'T', 0, 'O', 0, 'M', 0, 
    'D', 0, 'E', 0, 'V', 0, 'I', 0, 'C', 0, 'E', 0
  };
#endif

#if CUSTOM_SERIAL_STRING == P_TRUE
const uint8_t Composite_StringSerial[CUSTOM_SIZ_STRING_SERIAL] =
  {
    CUSTOM_SIZ_STRING_SERIAL,           /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,        /* bDescriptorType */
    'C', 0, 'U', 0, 'S', 0, 'T', 0, 'O', 0, 'M', 0, 
    'S', 0, 'E', 0, 'R', 0, 'I', 0, 'A', 0, 'L', 0
  };
#endif

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Extern functions ----------------------------------------------------------*/
void Send_HID_Report(uint8_t *HIDBuffer, uint32_t HIDBufferLength)
{
    if (HIDBufferLength > 64)
    {
        HIDBufferLength = 64;
    }

    if (!ReportXferComplete)
    {
        return;
    }

    ReportXferComplete = FALSE;

    USB_SIL_Write(EP1_IN, HIDBuffer, HIDBufferLength);

    SetEPTxValid(ENDP1); 
}

uint32_t Recv_HID_Report(uint8_t *HIDBuffer)
{
    uint32_t HIDBufferLength;

    if (!ReportRecvComplete)
    {
        return 0;
    }

    ReportRecvComplete = FALSE;

    HIDBufferLength = USB_SIL_Read(EP1_OUT, HIDBuffer);

    SetEPRxValid(ENDP1); 

    return HIDBufferLength;
}

void Send_CDC_Msg(uint8_t *CDCBuffer, uint32_t CDCBufferLength)
{
    if (CDCBufferLength > 64)
    {
        CDCBufferLength = 64;
    }

    while (!ComXferComplete);

    ComXferComplete = FALSE;

    USB_SIL_Write(EP2_IN, CDCBuffer, CDCBufferLength);

    SetEPTxValid(ENDP2); 
}

uint32_t Recv_CDC_Msg(uint8_t *CDCBuffer)
{
    uint32_t CDCBufferLength;

    if (!ComRecvComplete)
    {
        return 0;
    }

    ComRecvComplete = FALSE;

    CDCBufferLength = USB_SIL_Read(EP2_OUT, CDCBuffer);

    SetEPRxValid(ENDP2); 

    return CDCBufferLength;
}

uint32_t Debug(const char *format, ...)
{
    uint8_t DebugBuffer[64] = {0};
    uint32_t FormatLength = 0;
    va_list ap;

    FormatLength = strlen(format) + 1;

    if (FormatLength > 64)
    {
        FormatLength = 63;
    }

    va_start(ap, format);
    vsnprintf((char *)DebugBuffer, FormatLength, format, ap);     
    va_end(ap);

    Send_CDC_Msg(DebugBuffer, strlen(format)+1);

    return FormatLength;
}

