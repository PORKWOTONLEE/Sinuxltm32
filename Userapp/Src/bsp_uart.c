#include "misc.h"
#include "core_cm3.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "bsp_uart.h"
#include "stm32f10x_usart.h"

void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    // Priority group config
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // USART NVIC param config 
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);
}

void USART_Config(void)
{
    // GPIO
    GPIO_InitTypeDef GPIO_InitStructure;
    // USART GPIO CLK enable
    USART_GPIO_APBxClkCmd(USART_GPIO_CLK, ENABLE);
    // USART TX GPIO config
    GPIO_InitStructure.GPIO_Pin   = USART_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(USART_TX_GPIO_PORT, &GPIO_InitStructure);
    // USART RX GPIO config
    GPIO_InitStructure.GPIO_Pin   = USART_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Init(USART_RX_GPIO_PORT, &GPIO_InitStructure);

    // USART1
    USART_InitTypeDef USART_InitStructure;
    // USART1 CLK enable
    USART_APBxClkCmd(USART_CLK, ENABLE);
    // USART1 param config
    USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_BaudRate            = USART_BAUDRATE;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_Parity              = USART_Parity_No;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_Init(USARTx, &USART_InitStructure);

    // Interupt
    // Interupt Priority
    NVIC_Configuration(); 
    // Interupt enable
    USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);

    // USART enable
    USART_Cmd(USARTx, ENABLE);
}

void USART_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
    USART_SendData(pUSARTx, ch); 

    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

void USART_SendString(USART_TypeDef *pUSARTx, char *str)
{
    unsigned int bit = 0;

    do 
    {
        USART_SendByte(pUSARTx, str[bit]);

        bit++;
    }while (str[bit] != '\0');


    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}

