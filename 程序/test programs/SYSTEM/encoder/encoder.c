/**
* @owner        Sharkespeara
* @file         encoder.c
* @brief        编码器初始化函数
* @details      
* @par History  见如下说明
*          
*/

#include "encoder.h"

void Encoder_TIM2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;//初始化GPIO--PA0、PA1
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
		
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);//初始化定时器。
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInitStruct.TIM_Period=65535; //设定计数器自动重装值
	TIM_TimeBaseInitStruct.TIM_Prescaler=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//配置编码器模式
	
	TIM_ICStructInit(&TIM_ICInitStruct);//初始化输入捕获
	TIM_ICInitStruct.TIM_ICFilter=10;//滤波器
	TIM_ICInit(TIM2,&TIM_ICInitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;   //使能外部中断通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;   //使能外部中断通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;    //响应优先级3
	NVIC_Init(&NVIC_InitStruct);
	
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//配置溢出更新中断标志位//使能定时器中断
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);//清除TIM的更新标志位

	TIM_SetCounter(TIM2,0);//清零定时器计数值
	
	TIM_Cmd(TIM2,ENABLE);//开启定时器
}

void Encoder_TIM3_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义一个引脚初始化的结构体  
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;//定义一个定时器初始化的结构体
  TIM_ICInitTypeDef TIM_ICInitStructure; //定义一个定时器编码器模式初始化的结构体
	NVIC_InitTypeDef NVIC_InitStruct;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 
 
  GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_TimeBaseStructure.TIM_Period = 65535; //设定计数器自动重装值
	TIM_TimeBaseStructure.TIM_Prescaler = 0; // 预分频器 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //选择时钟分频：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3：CH1、CH2同时计数，四分频
	TIM_ICStructInit(&TIM_ICInitStructure); //把TIM_ICInitStruct 中的每一个参数按缺省值填入
	TIM_ICInitStructure.TIM_ICFilter = 10;  //设置滤波器长度
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;   //使能外部中断通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;   //使能外部中断通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; //抢占优先级1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;    //响应优先级3
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);//清除TIM的更新标志位
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);//使能定时器中断

	TIM_Cmd(TIM3, ENABLE);
}


//void Encoder_TIM4_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStruct;
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
//	TIM_ICInitTypeDef TIM_ICInitStruct;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
//	
//	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
//	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6 |GPIO_Pin_7;
//	GPIO_Init(GPIOB,&GPIO_InitStruct);
//	
//	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
//	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
//	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
//	TIM_TimeBaseInitStruct.TIM_Period=65535;
//	TIM_TimeBaseInitStruct.TIM_Prescaler=0;
//	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
//	
//	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
//	
//	TIM_ICStructInit(&TIM_ICInitStruct);
//	TIM_ICInitStruct.TIM_ICFilter=10;
//	TIM_ICInit(TIM4,&TIM_ICInitStruct);
//	
//	TIM_ClearFlag(TIM4,TIM_FLAG_Update);
//	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
//	
//	TIM_SetCounter(TIM4,0);

//	TIM_Cmd(TIM4,ENABLE);
//}

/**********************
编码器
速度读取函数
入口参数：定时器
**********************/
int Read_Speed(int TIMx)
{
	int value_1;
	switch(TIMx)
	{
		case 2:value_1=(short)TIM_GetCounter(TIM2);
				TIM_SetCounter(TIM2,0);
				break;
		//IF是定时器2，1.采集编码器的计数值并保存。2.将定时器的计数值清零。
		case 5:value_1=(short)TIM_GetCounter(TIM4);
				TIM_SetCounter(TIM5,0);
				break;
		default:value_1=0;
	}
	return value_1;
}

int Read_Encoder_TIM2(void)
{
	int Encoder_TIM;
	Encoder_TIM=TIM2->CNT; //读取计数
	if(Encoder_TIM>0xefff)Encoder_TIM=Encoder_TIM-0xffff; //转化计数值为有方向的值，大于0正转，小于0反转。
	TIM2->CNT=0; //读取完后计数清零
	return Encoder_TIM; //返回值
}

