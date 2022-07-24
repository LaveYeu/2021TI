#ifndef __ENCODER_H
#define __ENCODER_H

#include "headfile.h"

#define ENCODER_TIM_PERIOD (u16)(65535)   //103的定时器是16位 2的16次方最大是65536




//ENCODER1
#define  DEBUG_ENCODER1_APBxClkCmd    RCC_APB1PeriphClockCmd
#define  DEBUG_ENCODER1_CLK           RCC_APB1Periph_TIM2
#define  ENCODER1_GPIO_CLK            RCC_APB2Periph_GPIOA
#define  ENCODER1_TIMX                TIM2
#define  ENCODER1_GPIO_PORT           GPIOA
#define  ENCODER1_GPIO1_PIN           GPIO_Pin_0
#define  ENCODER1_GPIO2_PIN           GPIO_Pin_1
#define  ENCODER1_IRQ                 TIM2_IRQn
#define  ENCODER1_IRQHandler          TIM2_IRQHandler

//ENCODER2
#define  DEBUG_ENCODER2_APBxClkCmd    RCC_APB1PeriphClockCmd
#define  DEBUG_ENCODER2_CLK           RCC_APB1Periph_TIM4
#define  ENCODER2_GPIO_CLK            RCC_APB2Periph_GPIOB
#define  ENCODER2_TIMX                TIM4
#define  ENCODER2_GPIO_PORT           GPIOB
#define  ENCODER2_GPIO1_PIN           GPIO_Pin_6
#define  ENCODER2_GPIO2_PIN           GPIO_Pin_7
#define  ENCODER2_IRQ                 TIM4_IRQn
#define  ENCODER2_IRQHandler          TIM4_IRQHandler

void Encoder1_Init(void);
void Encoder2_Init(void);
int  Read_Encoder(u8 TIMX);



#endif    // __ENCODER_H

