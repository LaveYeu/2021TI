#ifndef __SYSTIME_H
#define __SYSTIME_H

#include "headfile.h"


#define  DEBUG_SYSTIME_APBxClkCmd     RCC_APB1PeriphClockCmd
#define  DEBUG_SYSTIME_CLK            RCC_APB1Periph_TIM3
#define  SYSTIME_TIMX                 TIM3
#define  SYSTIME_IRQn                 TIM3_IRQn
#define  SYSTIME_IRQHandler           TIM3_IRQHandler


extern uint16_t time_count_20us;
extern uint16_t time_count_ms;
extern uint16_t time_count_s;
extern uint16_t time_count_min;
extern uint16_t time_count_h;


void Systime_Init(uint32_t time_us);
uint32_t Get_Time_us(void);
uint32_t Get_Time_ms(void);
uint32_t Get_Time_s(void);
uint32_t Get_Time_min(void);
uint32_t Get_Time_h(void);


#endif  //__SYSTIME_H


