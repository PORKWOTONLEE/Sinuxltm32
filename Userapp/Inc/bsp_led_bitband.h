#ifndef __BSP_LED_BITBAND_H__
#define __BSP_LED_BITBAND_H__

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define BITBAND(addr,bit)        (addr&0xF0000000)+0x02000000+((addr&0x00FFFFFF)<<5)+(bit<<2)
#define MEM_ADDR(addr)           *((volatile unsigned long *)(addr))
#define BIT_ADDR(addr,bit)       MEM_ADDR(BITBAND((addr),(bit)))

#define GPIOB_ODR_ADDR (GPIOB_BASE+12)

#define PB_SET_OUT(n)   (BIT_ADDR(GPIOB_ODR_ADDR,(n))=1)
#define PB_RESET_OUT(n) (BIT_ADDR(GPIOB_ODR_ADDR,(n))=0)

#define LED1_BITBAND_ON  PB_RESET_OUT(5)
#define LED1_BITBAND_OFF PB_SET_OUT(5)
#define LED2_BITBAND_ON  PB_RESET_OUT(0)
#define LED2_BITBAND_OFF PB_SET_OUT(0)
#define LED3_BITBAND_ON  PB_RESET_OUT(1)
#define LED3_BITBAND_OFF PB_SET_OUT(1)

#define LED_RED_BITBAND    LED1_BITBAND_ON;\
                           LED2_BITBAND_OFF;\
                           LED3_BITBAND_OFF

#define LED_GREEN_BITBAND  LED1_BITBAND_OFF;\
                           LED2_BITBAND_ON;\
                           LED3_BITBAND_OFF

#define LED_BLUE_BITBAND   LED1_BITBAND_OFF;\
                           LED2_BITBAND_OFF;\
                           LED3_BITBAND_ON

#define LED_YELLOW_BITBAND LED1_BITBAND_ON;\
                           LED2_BITBAND_ON;\
                           LED3_BITBAND_OFF

#define LED_PURPLE_BITBAND LED1_BITBAND_ON;\
                           LED2_BITBAND_OFF;\
                           LED3_BITBAND_ON

#define LED_CYAN_BITBAND   LED1_BITBAND_OFF;\
                           LED2_BITBAND_ON;\
                           LED3_BITBAND_ON

#define LED_WHITE_BITBAND  LED1_BITBAND_ON;\
                           LED2_BITBAND_ON;\
                           LED3_BITBAND_ON

#define LED_OFF_BITBAND    LED1_BITBAND_OFF;\
                           LED2_BITBAND_OFF;\
                           LED3_BITBAND_OFF

#endif
