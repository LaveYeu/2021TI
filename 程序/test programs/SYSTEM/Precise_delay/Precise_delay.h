/**
* @owner        Sharkespeara
* @file         delay.h
* @brief        精确延时函数头文件
* @details      
* @par History  见如下说明
*          
*/
#ifndef __DELAY_H
#define __DELAY_H 			   
#include "sys.h"  


	 
void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif

