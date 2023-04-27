/**
  ******************************************************************************
  * @file    usb_desc.c
  * @author  MCD Application Team
  * @version V4.1.0
  * @date    26-May-2017
  * @brief   Descriptors for Composite USB Device Demo
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_desc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* USB Standard Device Descriptor */
const uint8_t Composite_DeviceDescriptor[COMPOSITE_SIZ_DEVICE_DESC] =
  {
    0x12,                       /*bLength */
    USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType*/
    0x00,                       /*bcdUSB */
    0x02,
    0xEF,                       /*bDeviceClass*/
    0x02,                       /*bDeviceSubClass*/
    0x01,                       /*bDeviceProtocol*/
    0x40,                       /*bMaxPacketSize64*/
    0x83,                       /*idVendor (0x0483)*/
    0x04,
    0x50,                       /*idProduct = 0x5750*/
    0x57,
    0x00,                       /*bcdDevice rel. 2.00*/
    0x02,
    0,                          /*Index of string descriptor describing
                                              manufacturer */
    0,                          /*Index of string descriptor describing
                                             product*/
    0,                          /*Index of string descriptor describing the
                                             device serial number */
    0x01                        /*bNumConfigurations*/
  }
  ; /* Composite_DeviceDescriptor */


/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const uint8_t Composite_ConfigDescriptor[COMPOSITE_SIZ_CONFIG_DESC] =
  {
    /************** Descriptor of Configuration ****************/
    0x09, /* bLength: Configuration Descriptor size */
    USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration */
    COMPOSITE_SIZ_CONFIG_DESC,
    /* wTotalLength: Bytes returned */
    0x00,
    0x03,         /* bNumInterfaces: 3 interface */
    0x01,         /* bConfigurationValue: Configuration value */
    0x00,         /* iConfiguration: Index of string descriptor describing
                                 the configuration*/
    0xC0,         /* bmAttributes: Self powered */
    0x32,         /* MaxPower 100 mA: this current is used for detecting Vbus */

    /************** Descriptor of Interface Association ****************/
    /* 09 */
    0x08,   /*  bLength  */
    USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE,   /*  bDescriptorType*/
    0x00,   /*  bFirstInterface: 0 */
    0x01,   /*  bInterfaceCount */
    0x03,   /*  bFunctionClass --HID */
    0x01,   /*  bFunctionSubClass */
    0x01,   /*  bFunctionProtocol */
    0x00,   /*  iFunction */
    /************** Descriptor of Custom HID interface ****************/
    /* 17 */
    0x09,         /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESCRIPTOR_TYPE,/* bDescriptorType: Interface descriptor type */
    0x00,         /* bInterfaceNumber: Number of Interface */
    0x00,         /* bAlternateSetting: Alternate setting */
    0x02,         /* bNumEndpoints */
    0x03,         /* bInterfaceClass: HID */
    0x01,         /* bInterfaceSubClass : 1=BOOT, 0=no boot */
    0x01,         /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
    0,            /* iInterface: Index of string descriptor */
    /******************** Descriptor of Custom HID HID ********************/
    /* 26 */
    0x09,         /* bLength: HID Descriptor size */
    USB_HID_DESCRIPTOR_TYPE, /* bDescriptorType: HID */
    0x10,         /* bcdHID: HID Class Spec release number */
    0x01,
    0x00,         /* bCountryCode: Hardware target country */
    0x01,         /* bNumDescriptors: Number of HID class descriptors to follow */
    0x22,         /* bDescriptorType */
    CUSTOMHID_SIZ_REPORT_DESC,/* wItemLength: Total length of Report descriptor */
    0x00,
    /******************** Descriptor of Custom HID endpoints ******************/
    /* 35 */
    0x07,          /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,	/* bDescriptorType: Endpoint descriptor type */
    0x81,          /* bEndpointAddress: Endpoint Address (IN1) */
    0x03,          /* bmAttributes: Interrupt endpoint */
    0x08,          /* wMaxPacketSize: 8 Bytes max */
    0x00,
    0x20,          /* bInterval: Polling Interval (32 ms) */
    /* 42 */
    0x07,	/* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,	/* bDescriptorType: Endpoint descriptor type */
    0x01,	/* bEndpointAddress: Endpoint Address (OUT1) */
    0x03,	/* bmAttributes: Interrupt endpoint */
    0x02,	/* wMaxPacketSize: 2 Bytes max  */
    0x00,
    0x20,	/* bInterval: Polling Interval (32 ms) */

    /************** Descriptor of Interface Association ****************/
    /* 49 */
    0x08,   /*  bLength  */
    USB_INTERFACE_ASSOCIATION_DESCRIPTOR_TYPE,   /*  bDescriptorType*/
    0x01,   /*  bFirstInterface: 0 */
    0x02,   /*  bInterfaceCount */
    0x02,   /*  bFunctionClass --CDC */
    0x02,   /*  bFunctionSubClass */
    0x01,   /*  bFunctionProtocol */
    0x00,   /*  iFunction */
    /************** Descriptor of CDC interface ****************/
    /* 57 */
    0x09,   /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESCRIPTOR_TYPE,  /* bDescriptorType: Interface */
    0x01,   /* bInterfaceNumber: Number of Interface */
    0x00,   /* bAlternateSetting: Alternate setting */
    0x01,   /* bNumEndpoints: One endpoints used */
    0x02,   /* bInterfaceClass: Communication Interface Class */
    0x02,   /* bInterfaceSubClass: Abstract Control Model */
    0x01,   /* bInterfaceProtocol: Common AT commands */
    0x00,   /* iInterface: */
    /************** Descriptor of CDC Header Functional ****************/
    /* 66 */
    0x05,   /* bLength: Endpoint Descriptor size */
    0x24,   /* bDescriptorType: CS_INTERFACE */
    0x00,   /* bDescriptorSubtype: Header Func Desc */
    0x10,   /* bcdCDC: spec release number */
    0x01,
    /************** Descriptor of CDC Call Management Functional ****************/
    /* 71 */
    0x05,   /* bFunctionLength */
    0x24,   /* bDescriptorType: CS_INTERFACE */
    0x01,   /* bDescriptorSubtype: Call Management Func Desc */
    0x00,   /* bmCapabilities: D0+D1 */
    0x01,   /* bDataInterface: 1 */
    /************** Descriptor of CDC ACM Functional ****************/
    /* 76 */
    0x04,   /* bFunctionLength */
    0x24,   /* bDescriptorType: CS_INTERFACE */
    0x02,   /* bDescriptorSubtype: Abstract Control Management desc */
    0x02,   /* bmCapabilities */
    /************** Descriptor of CDC Union Functional ****************/
    /* 80 */
    0x05,   /* bFunctionLength */
    0x24,   /* bDescriptorType: CS_INTERFACE */
    0x06,   /* bDescriptorSubtype: Union func desc */
    0x00,   /* bMasterInterface: Communication class interface */
    0x01,   /* bSlaveInterface0: Data Class Interface */
    /******************** Descriptor of CDC endpoints ******************/
    /* 85 */
    0x07,   /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint */
    0x83,   /* bEndpointAddress: (IN3) */
    0x03,   /* bmAttributes: Interrupt */
    VIRTUAL_COM_PORT_INT_SIZE,      /* wMaxPacketSize: */
    0x00,
    0x02,   /* bInterval: */
    /************** Descriptor of CDC Data class interface ****************/
    /* 92 */
    0x09,   /* bLength: Endpoint Descriptor size */
    USB_INTERFACE_DESCRIPTOR_TYPE,  /* bDescriptorType: */
    0x02,   /* bInterfaceNumber: Number of Interface */
    0x00,   /* bAlternateSetting: Alternate setting */
    0x02,   /* bNumEndpoints: Two endpoints used */
    0x0A,   /* bInterfaceClass: CDC */
    0x00,   /* bInterfaceSubClass: */
    0x00,   /* bInterfaceProtocol: */
    0x00,   /* iInterface: */
    /******************** Descriptor of CDC endpoints ******************/
    /* 101 */
    0x07,   /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint */
    0x02,   /* bEndpointAddress: (OUT2) */
    0x02,   /* bmAttributes: Bulk */
    VIRTUAL_COM_PORT_DATA_SIZE,             /* wMaxPacketSize: */
    0x00,
    0x00,   /* bInterval: ignore for Bulk transfer */
    /* 108 */
    0x07,   /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint */
    0x82,   /* bEndpointAddress: (IN2) */
    0x02,   /* bmAttributes: Bulk */
    VIRTUAL_COM_PORT_DATA_SIZE,             /* wMaxPacketSize: */
    0x00,
    0x00    /* bInterval */
    /* 115 */
  };

/* Composite_ConfigDescriptor */
const uint8_t Composite_ReportDescriptor[CUSTOMHID_SIZ_REPORT_DESC] ={
    0x05, 0x01,           // Usage Page (Generic Desktop)
    0x09, 0x06,           // Usage (Keyboard)
    0xA1, 0x01,           // Collection (Application)
    
    0x05, 0x07,           // Usage Page (Key Codes)
    0x19, 0xE0,           // Usage Minimum (224)
    0x29, 0xE7,           // Usage Maximum (231)
    0x15, 0x00,           // Logical Minimum (0)
    0x25, 0x01,           // Logical Maximum (1)
    0x75, 0x01,           // Report Size (1)
    0x95, 0x08,           // Report Count (8)
    0x81, 0x02,           // Input (Data, Variable, Absolute) ; Modifier byte
    0x95, 0x01,           // Report Count (1)
    0x75, 0x08,           // Report Size (8)
    0x81, 0x01,           // Input (Constant) ; Reserved byte

    0x95, 0x05,           // Report Count (5)
    0x75, 0x01,           // Report Size (1)
    0x05, 0x08,           // Usage Page (LEDs)
    0x19, 0x01,           // Usage Minimum (1)
    0x29, 0x05,           // Usage Maximum (5)
    0x91, 0x02,           // Output (Data, Variable, Absolute) ; LED report
    0x95, 0x01,           // Report Count (1)
    0x75, 0x03,           // Report Size (3)
    0x91, 0x01,           // Output (Constant) ; LED report padding

    0x95, 0x06,           // Report Count (48)
    0x75, 0x08,           // Report Size (1)
    0x15, 0x00,           // Logical Minimum (0)
    0x25, 0x65,           // Logical Maximum (101)
    0x05, 0x07,           // Usage Page (Key Codes)
    0x19, 0x00,           // Usage Minimum (0)
    0x29, 0x65,           // Usage Maximum (101)
    0x81, 0x00,           // Input (Data, Array) ; Key array (6 keys)

    0xC0                  // End Collection
};

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

