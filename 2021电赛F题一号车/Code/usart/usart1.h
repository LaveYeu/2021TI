#ifndef __USART1_H
#define	__USART1_H


#include "headfile.h"
	
//USART1
//#define  DEBUG_USART1_APBxClkCmd   RCC_APB2PeriphClockCmd
//#define  DEBUG_USART1_CLK          RCC_APB2Periph_USART1
//#define  USART1_GPIO_CLK           RCC_APB2Periph_GPIOA

//#define  USART1X                   USART1
//#define  USART1_TX_GPIO_PORT       GPIOA
//#define  USART1_TX_GPIO_PIN        GPIO_Pin_9
//#define  USART1_RX_GPIO_PORT       GPIOA
//#define  USART1_RX_GPIO_PIN        GPIO_Pin_10
//#define  USART1_IRQn               USART1_IRQn
//#define  USART1_IRQHandler         USART1_IRQHandler


//USART2
// #define  DEBUG_USART1_APBxClkCmd   RCC_APB1PeriphClockCmd
// #define  DEBUG_USART1_CLK          RCC_APB1Periph_USART2
// #define  USART1_GPIO_CLK           RCC_APB2Periph_GPIOA

// #define  USART1X                   USART2
// #define  USART1_TX_GPIO_PORT       GPIOA
// #define  USART1_TX_GPIO_PIN        GPIO_Pin_2
// #define  USART1_RX_GPIO_PORT       GPIOA
// #define  USART1_RX_GPIO_PIN        GPIO_Pin_3
// #define  USART1_IRQn               USART2_IRQn
// #define  USART1_IRQHandler         USART2_IRQHandler


//USART3
 #define  DEBUG_USART1_APBxClkCmd   RCC_APB1PeriphClockCmd
 #define  DEBUG_USART1_CLK          RCC_APB1Periph_USART3
 #define  USART1_GPIO_CLK           RCC_APB2Periph_GPIOB

 #define  USART1X                   USART3
 #define  USART1_TX_GPIO_PORT       GPIOB
 #define  USART1_TX_GPIO_PIN        GPIO_Pin_10
 #define  USART1_RX_GPIO_PORT       GPIOB
 #define  USART1_RX_GPIO_PIN        GPIO_Pin_11
 #define  USART1X_IRQn              USART3_IRQn
 #define  USART1X_IRQHandler        USART3_IRQHandler


void Usart1_Config(u32 baudrate);



#endif // __USART1_H



