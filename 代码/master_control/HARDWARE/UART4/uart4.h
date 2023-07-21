#ifndef __UART4_H
#define __UART4_H
#include "sys.h"
#include "stdio.h"


//pc11   ½ÓÊÕ

// ´®¿Ú4-UART4
#define  DEBUG_USARTx                   UART4
#define  DEBUG_USART_BAUDRATE           115200

    
#define  DEBUG_USART_TX_GPIO_PORT         GPIOC   
#define  DEBUG_USART_TX_GPIO_PIN          GPIO_Pin_10
#define  DEBUG_USART_RX_GPIO_PORT         GPIOC
#define  DEBUG_USART_RX_GPIO_PIN          GPIO_Pin_11

#define  DEBUG_USART_IRQ                UART4_IRQn
#define  DEBUG_USART_IRQHandler         UART4_IRQHandler


void USART_Config(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);

#endif  
