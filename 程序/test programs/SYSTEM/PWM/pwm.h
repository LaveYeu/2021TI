/**
* @owner        Sharkespeara
* @file         pwm.h
* @brief        PWMͷ�ļ�
* @details      
* @par History  ������˵��
*          
*/
#ifndef _PWM_H
#define _PWM_H

#include "stm32f10x.h" 

#define EN_TIM1
void TIM1_PWM_Init(u16 arr,u16 psc);


#endif /*  _PWM_H  */
