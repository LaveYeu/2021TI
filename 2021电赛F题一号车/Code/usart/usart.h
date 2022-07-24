#ifndef __USART_H
#define	__USART_H


#include "headfile.h"
	
//USART1
#define  DEBUG_USART_APBxClkCmd   RCC_APB2PeriphClockCmd
#define  DEBUG_USART_CLK          RCC_APB2Periph_USART1
#define  USART_GPIO_CLK           RCC_APB2Periph_GPIOA

#define  USARTX                   USART1
#define  USART_TX_GPIO_PORT       GPIOA
#define  USART_TX_GPIO_PIN        GPIO_Pin_9
#define  USART_RX_GPIO_PORT       GPIOA
#define  USART_RX_GPIO_PIN        GPIO_Pin_10
#define  USART_IRQn               USART1_IRQn
#define  USART_IRQHandler         USART1_IRQHandler


//USART2
// #define  DEBUG_USART_APBxClkCmd   RCC_APB1PeriphClockCmd
// #define  DEBUG_USART_CLK          RCC_APB1Periph_USART2
// #define  USART_GPIO_CLK           RCC_APB2Periph_GPIOA

// #define  USARTX                   USART2
// #define  USART_TX_GPIO_PORT       GPIOA
// #define  USART_TX_GPIO_PIN        GPIO_Pin_2
// #define  USART_RX_GPIO_PORT       GPIOA
// #define  USART_RX_GPIO_PIN        GPIO_Pin_3
// #define  USART_IRQn               USART2_IRQn
// #define  USART_IRQHandler         USART2_IRQHandler


//USART3
// #define  DEBUG_USART_APBxClkCmd   RCC_APB1PeriphClockCmd
// #define  DEBUG_USART_CLK          RCC_APB1Periph_USART3
// #define  USART_GPIO_CLK           RCC_APB2Periph_GPIOB

// #define  USARTX                   USART3
// #define  USART_TX_GPIO_PORT       GPIOB
// #define  USART_TX_GPIO_PIN        GPIO_Pin_10
// #define  USART_RX_GPIO_PORT       GPIOB
// #define  USART_RX_GPIO_PIN        GPIO_Pin_11
// #define  USART_IRQn               USART3_IRQn
// #define  USART_IRQHandler         USART3_IRQHandler


void Usart_Config(u32 baudrate);
void USART_SendByte(USART_TypeDef* USARTx,u8 c);


#endif // __USART_H



