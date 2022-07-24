/*
* @owner        Sharkespeara
* @file         GPIO.c
* @brief        GPIO�˿ڳ�ʼ��
* @details      
* @par History  ������˵��
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //ʹ��GPIOAʱ�� //�źŷ���
	                   
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);//��ʼ�� 

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);//��ʼ�� 
}
#endif

#ifdef EN_GPIOB
void GPIO_SITEB(void)
{
/*********************************************************************************/
	/*******************GPIOB*****************************/
/********************************************************************************/
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  //ʹ��GPIOBʱ��
	                   
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_0|GPIO_Pin_10|GPIO_Pin_3|GPIO_Pin_4;   //1,2,0,10����˿�//3,4ָʾ�ƿ���
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);//��ʼ�� 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3|GPIO_Pin_4;   //1,2,0,10����˿�//3,4ָʾ�ƿ���
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);//��ʼ�� 
}
#endif

#ifdef EN_GPIOC
void GPIO_SITEC(void)
{
/*********************************************************************************/
/*******************GPIOC*****************************/
/********************************************************************************/
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);  //ʹ��GPIOCʱ��
	                   
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_6;//ѭ���˿�//6 ����Ϊ0
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;                                                                                //11Ϊѭ��ֹͣ
	GPIO_Init(GPIOC,&GPIO_InitStruct);//��ʼ��
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_7|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;//ѭ���˿�//6 ����Ϊ0
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;                                                                                //11Ϊѭ��ֹͣ
	GPIO_Init(GPIOC,&GPIO_InitStruct);//��ʼ��
	
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4;   //1,2,0,10����˿�//3,4ָʾ�ƿ���
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);//��ʼ�� 
	
}
#endif

#ifdef EN_GPIOD
void GPIO_SITED(void)
{
/*********************************************************************************/
/*******************GPIOD*****************************/
/********************************************************************************/
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);  //ʹ��GPIODʱ��   
	                   
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);//��ʼ�� 

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);//��ʼ�� 
}
#endif
