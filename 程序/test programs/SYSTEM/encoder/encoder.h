/**
* @owner        Sharkespeara
* @file         encoder.h
* @brief        编码器函数
* @details      
* @par History  见如下说明
*          
*/
#ifndef  _ENCODER_H
#define  _ENCODER_H

#include "sys.h" 




int Read_Speed(int TIMx);
int Read_Encoder_TIM2(void);
void Encoder_TIM2_Init(void);
void Encoder_TIM3_Init(void);
void Encoder_TIM4_Init(void);
void Encoder_TIM5_Init(void);
#endif


