#include "systime.h"

//计数变量
uint16_t time_count_20us=0;
uint16_t time_count_ms=0;
uint16_t time_count_s=0;
uint16_t time_count_min=0;
uint16_t time_count_h=0;

//系统时钟初始化
void Systime_Init(uint32_t time_us)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	DEBUG_SYSTIME_APBxClkCmd(DEBUG_SYSTIME_CLK, ENABLE);
    
	TIM_TimeBaseInitStruct.TIM_Period = time_us;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 71;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(SYSTIME_TIMX,&TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(SYSTIME_TIMX,TIM_IT_Update,ENABLE);
	TIM_ClearITPendingBit(SYSTIME_TIMX,TIM_IT_Update);
	
	NVIC_InitStructure.NVIC_IRQChannel = SYSTIME_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	
	TIM_Cmd(SYSTIME_TIMX,ENABLE);
}

//20us计数
static void Count_Time_20us(void)
{
	time_count_20us++;
	if(time_count_20us>=50)
	{
		time_count_20us=0;
		time_count_ms++;
		if(time_count_ms>=1000)
		{
			time_count_ms=0;
			time_count_s++;
			if(time_count_s>=60)
			{
				time_count_s=0;
				time_count_min++;
				if(time_count_min>=60)
				{
					time_count_min=0;
					time_count_h++;
					if(time_count_h>=24)time_count_h=0;
				}
			}
		}
	}
}

//系统时钟中断
void SYSTIME_IRQHandler(void)
{
	if(TIM_GetITStatus(SYSTIME_TIMX,TIM_IT_Update))
	{
		Count_Time_20us();
	}
	TIM_ClearITPendingBit(SYSTIME_TIMX,TIM_IT_Update);	
}

uint32_t Get_Time_us(void)
{
	uint32_t this_time=0;
	if(time_count_20us)
	{
		this_time+=time_count_20us*20;
	}
	if(time_count_ms)
	{
		this_time+=time_count_ms*1000;
	}
	if(time_count_s)
	{
		this_time+=time_count_s*1000000;
	}
	if(time_count_min)
	{
		this_time+=time_count_min*60*1000000;
	}
	if(time_count_h)
	{
		this_time+=time_count_h*60*60*1000000;
	}
	return this_time;
}

uint32_t Get_Time_ms(void)
{
	 uint32_t this_time=0;
	 if(time_count_ms)
	 {
		 this_time+=time_count_ms;
	 }
	 if(time_count_s)
	 {
		  this_time+=time_count_s*1000;
	 }
	 if(time_count_min)
	 {
		 this_time+=time_count_min*60*1000;
	 }
	 if(time_count_h)
	 {
		 this_time+=time_count_h*60*60*1000;
	 }
	 return this_time;
}

uint32_t Get_Time_s(void)
{
	uint32_t this_time=0;
	if(time_count_ms>500)
	{
		this_time+=1;
	}
	if(time_count_s)
	{
		this_time+=time_count_s;
	}
	if(time_count_min)
	{
		this_time+=time_count_min*60;
	}
	if(time_count_h)
	{
		this_time+=time_count_h*60*60;
	}
	return this_time;
}

uint32_t Get_Time_min(void)
{
	uint32_t this_time=0;
	if(time_count_s>30)
	{
		this_time+=1;
	}
	if(time_count_min)
	{
		this_time+=time_count_min;
	}
	if(time_count_h)
	{
		this_time+=time_count_h*60;
	}
	return this_time;
}

uint32_t Get_Time_h(void)
{
	uint32_t this_time=0;
	if(time_count_min>30)
	{
		this_time+=1;
	}
	if(time_count_h)
	{
		this_time+=time_count_h;
	}
	return this_time;
}





















