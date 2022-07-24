/**
* @owner        Sharkespeara
* @file         pwm.c
* @brief        PWM函数
* @details      
* @par History  见如下说明
*          
*/

#include "stm32f10x.h"
#include "PWM.h"
#include <stdlib.h>
#include <string.h>

#ifdef EN_TIM1
/**************************TIM1**********************************************************/
void TIM1_PWM_Init(u16 arr,u16 psc)//arr 自动重装载寄存器的值  psc TIMX预分频的值
{

	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	
 
   //设置该引脚为复用输出功能,输出TIM8 CH2的PWM脉冲波形	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11; //TIM_CH1,CH2,CH3,CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM1
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM1 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	//TIM_OCInitStructure.TIM_Pulse=0;
	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 OC2
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM1在CCR2上的预装载寄存器

	TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 OC2
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM1在CCR2上的预装载寄存器
	
//	TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 OC2
//	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM1在CCR2上的预装载寄存器
//	
//	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 OC2
//	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM1在CCR2上的预装载寄存器
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	
	TIM_Cmd(TIM1, ENABLE);  //使能TIM1
}
#endif
#ifdef EN_TIM2
/**************************TIM2**********************************************************/
/* 若与TIM5同时使用（限定STM32F103RCTX）则通道变为
   CH1--- PA15
   CH2--- PB3
   CH3--- PB10
   CH4--- PB11*/
void TIM2_PWM_Init(u16 arr,u16 psc)//arr 自动重装载寄存器的值  psc TIMX预分频的值
{

	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体
	TIM_OCInitTypeDef TIM_OCInitStructure;//定义结构体
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;//定义初始化结构体

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);//使能GPIO外设和AFIO复用功能模块时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//使能定时器2时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //TIM_CH1 TIM_CH2 TIM_CH3 TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化引脚

//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM2, ENABLE);

	//初始化TIM2
	TIM_TimeBaseInitStruct.TIM_Period = arr-1;//自动重装载寄存器的值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc-1;//TIMX预分频的值
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;//时钟分割
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);//根据以上功能对定时器进行初始化

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//选择定时器模式，TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出比较极性低

	TIM_OC1Init(TIM2, &TIM_OCInitStructure);//根据结构体信息进行初始化
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);//使能定时器TIM2在CCR2上的预装载值
	
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);//根据结构体信息进行初始化
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);//使能定时器TIM2在CCR2上的预装载值
	
//	TIM_OC3Init(TIM2, &TIM_OCInitStructure);//根据结构体信息进行初始化
//	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);//使能定时器TIM2在CCR2上的预装载值
//	
//	TIM_OC4Init(TIM2, &TIM_OCInitStructure);//根据结构体信息进行初始化
//	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);//使能定时器TIM2在CCR2上的预装载值
	//TIM_ARRPreloadConfig(TIM2,ENABLE);
	TIM_Cmd(TIM2, ENABLE);//使能定时器TIM2
}
#endif
#ifdef EN_TIM3
/**************************TIM3**********************************************************/
void TIM3_PWM_Init(u16 arr,u16 psc)//arr 自动重装载寄存器的值  psc TIMX预分频的值
{

	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体
	TIM_OCInitTypeDef TIM_OCInitStructure;//定义结构体
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;//定义初始化结构体

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);//使能GPIO外设和AFIO复用功能模块时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//使能定时器3时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //TIM_CH1 TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化引脚
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO , ENABLE );
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;//TIM_CH3 TIM_CH4
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);

	//初始化TIM3
	TIM_TimeBaseInitStruct.TIM_Period = arr-1;//自动重装载寄存器的值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc-1;//TIMX预分频的值
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;//时钟分割
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);//根据以上功能对定时器进行初始化

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//选择定时器模式，TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出比较极性低

	TIM_OC1Init(TIM3, &TIM_OCInitStructure);//根据结构体信息进行初始化
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//使能定时器TIM3在CCR2上的预装载值
	
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);//根据结构体信息进行初始化
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);//使能定时器TIM3在CCR2上的预装载值
	
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);//根据结构体信息进行初始化
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);//使能定时器TIM3在CCR2上的预装载值
	
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);//根据结构体信息进行初始化
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);//使能定时器TIM3在CCR2上的预装载值
	//TIM_ARRPreloadConfig(TIM3,ENABLE);
	TIM_Cmd(TIM3, ENABLE);//使能定时器TIM3
}
#endif
#ifdef EN_TIM4
/**************************TIM4**********************************************************/
void TIM4_PWM_Init(u16 arr,u16 psc)//arr 自动重装载寄存器的值  psc TIMX预分频的值
{

	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体
	TIM_OCInitTypeDef TIM_OCInitStructure;//定义结构体
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;//定义初始化结构体

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);//使能GPIO外设和AFIO复用功能模块时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//使能定时器3时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_9; //TIM_CH1 TIM_CH2 TIM_CH3 TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化引脚
	
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);

	//初始化TIM4
	TIM_TimeBaseInitStruct.TIM_Period = arr-1;//自动重装载寄存器的值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc-1;//TIMX预分频的值
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;//时钟分割
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);//根据以上功能对定时器进行初始化

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//选择定时器模式，TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出比较极性低

	TIM_OC1Init(TIM4, &TIM_OCInitStructure);//根据结构体信息进行初始化
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);//使能定时器TIM4在CCR2上的预装载值
	
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);//根据结构体信息进行初始化
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);//使能定时器TIM4在CCR2上的预装载值
	
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);//根据结构体信息进行初始化
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);//使能定时器TIM4在CCR2上的预装载值
	
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);//根据结构体信息进行初始化
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);//使能定时器TIM4在CCR2上的预装载值
	//TIM_ARRPreloadConfig(TIM3,ENABLE);
	TIM_Cmd(TIM4, ENABLE);//使能定时器TIM4
}
#endif
#ifdef EN_TIM5
/**************************TIM5**********************************************************/
/*与TIM2同时使用时（限于STM32F103RCTX）通道口发生变化，详见TIM2注释*/
void TIM5_PWM_Init(u16 arr,u16 psc)//arr 自动重装载寄存器的值  psc TIMX预分频的值
{

	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体
	TIM_OCInitTypeDef TIM_OCInitStructure;//定义结构体
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;//定义初始化结构体

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);//使能GPIO外设和AFIO复用功能模块时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//使能定时器1时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3; //TIM_CH1 TIM_CH2 TIM_CH3 TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化引脚

//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM5, ENABLE);

	//初始化TIM5
	TIM_TimeBaseInitStruct.TIM_Period = arr-1;//自动重装载寄存器的值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc-1;//TIMX预分频的值
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;//时钟分割
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStruct);//根据以上功能对定时器进行初始化

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//选择定时器模式，TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出比较极性低

	TIM_OC1Init(TIM5, &TIM_OCInitStructure);//根据结构体信息进行初始化
	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);//使能定时器TIM5在CCR2上的预装载值
	
	TIM_OC2Init(TIM5, &TIM_OCInitStructure);//根据结构体信息进行初始化
	TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);//使能定时器TIM5在CCR2上的预装载值
	
	TIM_OC3Init(TIM5, &TIM_OCInitStructure);//根据结构体信息进行初始化
	TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);//使能定时器TIM5在CCR2上的预装载值
	
	TIM_OC4Init(TIM5, &TIM_OCInitStructure);//根据结构体信息进行初始化
	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);//使能定时器TIM5在CCR2上的预装载值
	//TIM_ARRPreloadConfig(TIM5,ENABLE);
	TIM_Cmd(TIM5, ENABLE);//使能定时器TIM5
}
#endif
#ifdef EN_TIM8
/**************************TIM8**********************************************************/
void TIM8_PWM_Init(u16 arr,u16 psc)//arr 自动重装载寄存器的值  psc TIMX预分频的值
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	
 
   //设置该引脚为复用输出功能,输出TIM8 CH2的PWM脉冲波形	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM8
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM8 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	//TIM_OCInitStructure.TIM_Pulse=0;

	TIM_OC1Init(TIM8, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM8 OC2
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);  //使能TIM8在CCR2上的预装载寄存器

	TIM_OC2Init(TIM8, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM8 OC2
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);  //使能TIM8在CCR2上的预装载寄存器
	
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM8 OC2
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);  //使能TIM8在CCR2上的预装载寄存器
	
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM8 OC2
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable);  //使能TIM8在CCR2上的预装载寄存器
	
	TIM_CtrlPWMOutputs(TIM8,ENABLE);
	
	TIM_Cmd(TIM8, ENABLE);  //使能TIM8
}
#endif

