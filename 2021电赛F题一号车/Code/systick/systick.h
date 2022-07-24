#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "headfile.h"
//#include "core_cm3.h"

void SysTick_Delay_us(uint32_t us);
void SysTick_Delay_ms(uint32_t ms);

//#define delay_us SysTick_Delay_us
//#define delay_ms SysTick_Delay_ms
#endif /* __SYSTICK_H */


