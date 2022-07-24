/*
* @owner        Sharkespeara
* @file         GPIO.h
* @brief        
* @details      
* @par History  
*          
*/

#ifndef _GPIO_H_
#define _GPIO_H_

#include "stm32f10x.h"

#define EN_GPIOC 
#define EN_GPIOB 
#define EN_GPIOA

void GPIO_SITEA(void);
void GPIO_SITEB(void);
void GPIO_SITEC(void);
#endif
/*
输入模式

    -输入浮空（GPIO_Mode_IN_FLOATING）

    -输入上拉(GPIO_Mode_IPU)

    -输入下拉(GPIO_Mode_IPD)

    -模拟输入(GPIO_Mode_AIN)

输出模式

    -开漏输出(GPIO_Mode_Out_OD)

    -开漏复用功能(GPIO_Mode_AF_OD)

    -推挽式输出(GPIO_Mode_Out_PP)

    -推挽式复用功能(GPIO_Mode_AF_PP)
*/
