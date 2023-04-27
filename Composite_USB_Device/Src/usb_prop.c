/**
  ******************************************************************************
  * @file    usb_prop.c
  * @author  MCD Application Team
  * @version V4.1.0
  * @date    26-May-2017
  * @brief   All processing related to Composite USB Device Demo
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

#include "hw_config.h" 
#include "stm32f10x_gpio.h"
#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "usb_regs.h"
#include "usb_type.h"


/* Private typedef -----------------------------------------------------------*/ 
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t ProtocolValue;
__IO uint8_t Request = 0;
uint8_t Report_Buf[2];   
/* -------------------------------------------------------------------------- */
/*  Structures initializations */
/* -------------------------------------------------------------------------- */

DEVICE Device_Table =
  {
    EP_NUM,
    1
  };

DEVICE_PROP Device_Property =
  {
    Composite_init,
    Composite_Reset,
    Composite_Status_In,
    Composite_Status_Out,
    Composite_Data_Setup,
    Composite_NoData_Setup,
    Composite_Get_Interface_Setting,
    Composite_GetDeviceDescriptor,
    Composite_GetConfigDescriptor,
    Composite_GetStringDescriptor,
    0,
    0x40 /*MAX PACKET SIZE*/
  };
USER_STANDARD_REQUESTS User_Standard_Requests =
  {
    Composite_GetConfiguration,
    Composite_SetConfiguration,
    Composite_GetInterface,
    Composite_SetInterface,
    Composite_GetStatus,
    Composite_ClearFeature,
    Composite_SetEndPointFeature,
    Composite_SetDeviceFeature,
    Composite_SetDeviceAddress
  };

ONE_DESCRIPTOR Device_Descriptor =
  {
    (uint8_t*)Composite_DeviceDescriptor,
    COMPOSITE_SIZ_DEVICE_DESC
  };

ONE_DESCRIPTOR Config_Descriptor =
  {
    (uint8_t*)Composite_ConfigDescriptor,
    COMPOSITE_SIZ_CONFIG_DESC
  };

ONE_DESCRIPTOR Composite_Report_Descriptor =
  {
    (uint8_t *)Composite_ReportDescriptor,
    CUSTOMHID_SIZ_REPORT_DESC
  };

ONE_DESCRIPTOR Composite_Hid_Descriptor =
  {
    (uint8_t*)Composite_ConfigDescriptor + CUSTOMHID_OFF_HID_DESC,
    CUSTOMHID_SIZ_HID_DESC
  };

LINE_CODING linecoding =
  {
    115200, /* baud rate*/
    0x00,   /* stop bits-1*/
    0x00,   /* parity - none*/
    0x08    /* no. of bits 8*/
  };

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/*Composite_SetReport_Feature function prototypes*/
uint8_t *Composite_SetReport_Feature(uint16_t Length);

/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Composite_init.
* Description    : Custom HID init routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Composite_init(void)
{
  pInformation->Current_Configuration = 0;

  /* Connect the device */
  PowerOn();

  /* Perform basic device initialization operations */
  USB_SIL_Init();

  bDeviceState = UNCONNECTED;
}

/*******************************************************************************
* Function Name  : Composite_Reset.
* Description    : Custom HID reset routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Composite_Reset(void)
{
  /* Set Composite_DEVICE as not configured */
  pInformation->Current_Configuration = 0;
  pInformation->Current_Interface = 0;/*the default Interface*/
  
  /* Current Feature initialization */
  pInformation->Current_Feature = Composite_ConfigDescriptor[7];
 
  SetBTABLE(BTABLE_ADDRESS);

  /* Initialize Endpoint 0 */
  SetEPType(ENDP0, EP_CONTROL);
  SetEPTxStatus(ENDP0, EP_TX_STALL);
  SetEPRxAddr(ENDP0, ENDP0_RXADDR);
  SetEPTxAddr(ENDP0, ENDP0_TXADDR);
  Clear_Status_Out(ENDP0);
  SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);
  SetEPRxValid(ENDP0);

  /* Initialize Endpoint 1 */
  SetEPType(ENDP1, EP_INTERRUPT);
  SetEPTxAddr(ENDP1, ENDP1_TXADDR);
  SetEPRxAddr(ENDP1, ENDP1_RXADDR);
  SetEPTxCount(ENDP1, Device_Property.MaxPacketSize);
  SetEPRxCount(ENDP1, Device_Property.MaxPacketSize);
  SetEPRxStatus(ENDP1, EP_RX_VALID);
  SetEPTxStatus(ENDP1, EP_TX_NAK);

  /* Initialize Endpoint 2 */
  SetEPType(ENDP2, EP_BULK);
  SetEPTxAddr(ENDP2, ENDP2_TXADDR);
  SetEPRxAddr(ENDP2, ENDP2_RXADDR);
  SetEPTxCount(ENDP2, Device_Property.MaxPacketSize);
  SetEPRxCount(ENDP2, Device_Property.MaxPacketSize);
  SetEPRxStatus(ENDP2, EP_RX_VALID);
  SetEPTxStatus(ENDP2, EP_TX_NAK);

  /* Initialize Endpoint 3 */
  SetEPType(ENDP3, EP_INTERRUPT);
  SetEPTxAddr(ENDP3, ENDP3_TXADDR);
  SetEPTxCount(ENDP3, Device_Property.MaxPacketSize);
  SetEPTxStatus(ENDP3, EP_TX_NAK);

  /* Set this device to response on default address */
  SetDeviceAddress(0);
  bDeviceState = ATTACHED;
}
/*******************************************************************************
* Function Name  : Composite_SetConfiguration.
* Description    : Update the device state to configured and command the ADC 
*                  conversion.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Composite_SetConfiguration(void)
{
  if (pInformation->Current_Configuration != 0)
  {
    /* Device configured */
    bDeviceState = CONFIGURED;
  }
}

/*******************************************************************************
* Function Name  : Composite_SetDeviceAddress.
* Description    : Update the device state to addressed.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Composite_SetDeviceAddress (void)
{
  bDeviceState = ADDRESSED;
}
/*******************************************************************************
* Function Name  : Composite_Status_In.
* Description    : Composite USB Device status IN routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Composite_Status_In(void)
{  
}

/*******************************************************************************
* Function Name  : Composite_Status_Out
* Description    : Composite USB Device status OUT routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Composite_Status_Out (void)
{
}

/*******************************************************************************
* Function Name  : Composite_Data_Setup
* Description    : Handle the data class specific requests.
* Input          : Request Nb.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
RESULT Composite_Data_Setup(uint8_t RequestNo)
{
  uint8_t *(*CopyRoutine)(uint16_t);
  
  CopyRoutine = NULL;

  // Standard Request
  if ( (RequestNo == GET_DESCRIPTOR)
      && (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT)) )
  {
    
    if (pInformation->USBwValue1 == REPORT_DESCRIPTOR)
    {
      CopyRoutine = Composite_GetReportDescriptor;
    }
    else if (pInformation->USBwValue1 == USB_HID_DESCRIPTOR_TYPE)
    {
      CopyRoutine = Composite_GetHIDDescriptor;
    }
    
  }
  
  // Class Special Request
  else if ( (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT)) )
  {         
    switch( RequestNo )
    {
    // HID class request
    case GET_PROTOCOL:
      CopyRoutine = CustomHID_GetProtocolValue;
      break;
    case SET_REPORT:
      CopyRoutine = Composite_SetReport_Feature;
      Request = SET_REPORT;
      break;

    // CDC class request
    case GET_LINE_CODING:
      CopyRoutine = Virtual_Com_Port_GetLineCoding;
      break;
    case SET_LINE_CODING:
      CopyRoutine = Virtual_Com_Port_SetLineCoding;
      Request = SET_LINE_CODING;
      break;

    default:
      break;
    }
  }
  
  if (CopyRoutine == NULL)
  {
    return USB_UNSUPPORT;
  }
  
  pInformation->Ctrl_Info.CopyData = CopyRoutine;
  pInformation->Ctrl_Info.Usb_wOffset = 0;
  (*CopyRoutine)(0);
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Composite_SetReport_Feature
* Description    : Set Feature request handling
* Input          : Length.
* Output         : None.
* Return         : Buffer
*******************************************************************************/
uint8_t *Composite_SetReport_Feature(uint16_t Length)
{
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = 2;
    return NULL;
  }
  else
  {
    return Report_Buf;
  }
}

/*******************************************************************************
* Function Name  : Composite_NoData_Setup
* Description    : handle the no data class specific requests
* Input          : Request Nb.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
RESULT Composite_NoData_Setup(uint8_t RequestNo)
{
  if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
  {
    // CDC class request
    switch( RequestNo )
    {
    case SET_COMM_FEATURE:
      return USB_SUCCESS;
      break;
    case SET_CONTROL_LINE_STATE:
      return USB_SUCCESS;
      break;

    // HID class request
    case SET_PROTOCOL:
      return CustomHID_SetProtocol();
      break;
    default:
      break;
    }
  }

  return USB_UNSUPPORT;
}

/*******************************************************************************
* Function Name  : Composite_GetDeviceDescriptor.
* Description    : Gets the device descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the device descriptor.
*******************************************************************************/
uint8_t *Composite_GetDeviceDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &Device_Descriptor);
}

/*******************************************************************************
* Function Name  : Composite_GetConfigDescriptor.
* Description    : Gets the configuration descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the configuration descriptor.
*******************************************************************************/
uint8_t *Composite_GetConfigDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &Config_Descriptor);
}

/*******************************************************************************
* Function Name  : Composite_GetStringDescriptor
* Description    : Gets the string descriptors according to the needed index
* Input          : Length
* Output         : None.
* Return         : The address of the string descriptors.
*******************************************************************************/
uint8_t *Composite_GetStringDescriptor(uint16_t Length)
{
  return NULL;
}

/*******************************************************************************
* Function Name  : Composite_GetReportDescriptor.
* Description    : Gets the HID report descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the configuration descriptor.
*******************************************************************************/
uint8_t *Composite_GetReportDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &Composite_Report_Descriptor);
}

/*******************************************************************************
* Function Name  : Composite_GetHIDDescriptor.
* Description    : Gets the HID descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the configuration descriptor.
*******************************************************************************/
uint8_t *Composite_GetHIDDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &Composite_Hid_Descriptor);
}

/*******************************************************************************
* Function Name  : Composite_Get_Interface_Setting.
* Description    : tests the interface and the alternate setting according to the
*                  supported one.
* Input          : - Interface : interface number.
*                  - AlternateSetting : Alternate Setting number.
* Output         : None.
* Return         : USB_SUCCESS or USB_UNSUPPORT.
*******************************************************************************/
RESULT Composite_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : CustomHID_SetProtocol
* Description    : CusteomHID Set Protocol request routine.
* Input          : None.
* Output         : None.
* Return         : USB SUCCESS.
*******************************************************************************/
RESULT CustomHID_SetProtocol(void)
{
  uint8_t wValue0 = pInformation->USBwValue0;
  ProtocolValue = wValue0;
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : CusteomHID_GetProtocolValue
* Description    : get the protocol value
* Input          : Length.
* Output         : None.
* Return         : address of the protocol value.
*******************************************************************************/
uint8_t *CustomHID_GetProtocolValue(uint16_t Length)
{
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = 1;
    return NULL;
  }
  else
  {
    return (uint8_t *)(&ProtocolValue);
  }
}

/*******************************************************************************
* Function Name  : Virtual_Com_Port_GetLineCoding.
* Description    : send the linecoding structure to the PC host.
* Input          : Length.
* Output         : None.
* Return         : Linecoding structure base address.
*******************************************************************************/
uint8_t *Virtual_Com_Port_GetLineCoding(uint16_t Length)
{
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = sizeof(linecoding);
    return NULL;
  }
  return(uint8_t *)&linecoding;
}

/*******************************************************************************
* Function Name  : Virtual_Com_Port_SetLineCoding.
* Description    : Set the linecoding structure fields.
* Input          : Length.
* Output         : None.
* Return         : Linecoding structure base address.
*******************************************************************************/
uint8_t *Virtual_Com_Port_SetLineCoding(uint16_t Length)
{
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = sizeof(linecoding);
    return NULL;
  }
  return(uint8_t *)&linecoding;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
