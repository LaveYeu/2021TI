/*
* @owner        Sharkespeara
* @file         GPIO.c
* @brief        GPIO端口初始化
* @details      
* @par History  见如下说明
*          
*/

#include "GPIO.h"

GPIO_InitTypeDef GPIO_InitStruct;

#ifdef EN_GPIOA
void GPIO_SITEA(void)
{
/*********************************************************************************/
/*******************GPIOA*****************************/
/******************************************************************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //使能GPIOA时钟 //信号发送
	                   
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);//初始化 

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);//初始化 
}
#endif

#ifdef EN_GPIOB
void GPIO_SITEB(void)
{
/*********************************************************************************/
	/*******************GPIOB*****************************/
/********************************************************************************/
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  //使能GPIOB时钟
	                   
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_0|GPIO_Pin_10|GPIO_Pin_3|GPIO_Pin_4;   //1,2,0,10电机端口//3,4指示灯开关
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);//初始化 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_4;   //1,2,0,10电机端口//3,4指示灯开关
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);//初始化 
}
#endif

#ifdef EN_GPIOC
void GPIO_SITEC(void)
{
/*********************************************************************************/
/*******************GPIOC*****************************/
/********************************************************************************/
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);  //使能GPIOC时钟
	                   
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_6;//循迹端口//6 亮灯为0
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;                                                                                //11为循迹停止
	GPIO_Init(GPIOC,&GPIO_InitStruct);//初始化
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_7|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;//循迹端口//6 亮灯为0
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;                                                                                //11为循迹停止
	GPIO_Init(GPIOC,&GPIO_InitStruct);//初始化
	
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4;   //1,2,0,10电机端口//3,4指示灯开关
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);//初始化 
	
}
#endif

#ifdef EN_GPIOD
void GPIO_SITED(void)
{
/*********************************************************************************/
/*******************GPIOD*****************************/
/********************************************************************************/
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);  //使能GPIOD时钟   
	                   
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);//初始化 

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);//初始化 
}
#endif
