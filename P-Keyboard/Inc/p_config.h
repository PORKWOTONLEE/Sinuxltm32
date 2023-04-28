/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __P_CONFIG__
#define __P_CONFIG__

/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define P_TRUE  1
#define P_FALSE 0

#define CUSTOM_VENDOR_STRING      P_FALSE
#define CUSTOM_DEVICE_STRING      P_FALSE
#define CUSTOM_LANGID_STRING      P_FALSE
#define CUSTOM_SERIAL_STRING      P_FALSE

#if CUSTOM_LANGID_STRING == P_TRUE
#define CUSTOM_SIZ_STRING_LANGID  4
#endif

#if CUSTOM_VENDOR_STRING == P_TRUE
#define CUSTOM_SIZ_STRING_VENDOR  26
#endif

#if CUSTOM_DEVICE_STRING == P_TRUE
#define CUSTOM_SIZ_STRING_PRODUCT 26
#endif

#if CUSTOM_SERIAL_STRING == P_TRUE
#define CUSTOM_SIZ_STRING_SERIAL  26
#endif

#define USB_STRING_DESCRIPTOR_TYPE 0x03

/* Exported define -----------------------------------------------------------*/
extern __IO uint8_t ReportXferComplete;
extern __IO uint8_t ReportRecvComplete;
extern __IO uint8_t ComXferComplete;
extern __IO uint8_t ComRecvComplete;

#if CUSTOM_LANGID_STRING == P_TRUE
extern const uint8_t Composite_StringLangID[CUSTOM_SIZ_STRING_LANGID];
#endif

#if CUSTOM_VENDOR_STRING == P_TRUE
extern const uint8_t Composite_StringVendor[CUSTOM_SIZ_STRING_VENDOR];
#endif

#if CUSTOM_DEVICE_STRING == P_TRUE
extern const uint8_t Composite_StringProduct[CUSTOM_SIZ_STRING_PRODUCT];
#endif

#if CUSTOM_SERIAL_STRING == P_TRUE
extern const uint8_t Composite_StringSerial[CUSTOM_SIZ_STRING_SERIAL];
#endif

/* Exported functions ------------------------------------------------------- */
void Send_HID_Report(uint8_t *HIDBuffer, uint32_t HIDBufferLength);
uint32_t Recv_HID_Report(uint8_t *HIDBuffer);
void Send_CDC_Msg(uint8_t *CDCBuffer, uint32_t CDCBufferLength);
uint32_t Recv_CDC_Msg(uint8_t *CDCBuffer);
uint32_t Debug(const char *format, ...);

#endif
