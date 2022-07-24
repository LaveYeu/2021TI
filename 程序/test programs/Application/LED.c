#include "LED.h"

void LED_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);  //使能GPIOD时钟
	                   
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);//初始化 
	GPIO_ResetBits(GPIOD,GPIO_Pin_2);
	GPIO_ResetBits(GPIOD,GPIO_Pin_1);
	GPIO_ResetBits(GPIOD,GPIO_Pin_0);
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //使能GPIOA时钟
	                   
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);//初始化 
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
}
