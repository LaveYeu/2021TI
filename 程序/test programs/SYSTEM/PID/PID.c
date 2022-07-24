/**
* @owner        Sharkespeara
* @file         PID.c
* @brief        PID控制函数
* @details      
* @par History  见如下说明
*          
*/

#include "PID.h"
#include "PID_Motor.h"
#include "Linewalking.h"

float RES_PWM1,RES_PWM2;//定义PWM输出

int speed1=0,speed2=0;

int LAST1 = 0,LAST2 = 0;

void PID_TIM4_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_Period = arr;     //重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;  //预分频系数
	TIM_TimeBaseInitStruct.TIM_ClockDivision =0; //时钟分割
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);  //使能定时器中断
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01; 
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
  NVIC_Init(&NVIC_InitStructure);
 
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);//清除TIM的更新标志位
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);//使能定时器中断

	TIM_Cmd(TIM4,ENABLE);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************
PID1值初始化
入口：下列
出口：见电机PID
****************************/
PID pid1;
void PID_param1_init(void)
 {
     /* 初始化参数 */
     pid1.target_val = 0;        //目标值
     pid1.actual_val = 0.0;         //实际值
     pid1.err        = 0;           //定义偏差值
  	 pid1.output_val = 0;   
     pid1.err_last   = 0.0;         //定义上一个偏差值
     pid1.integral   = 0.0;         //定义积分值
     pid1.Kp         = 150;
     pid1.Ki         = 0;
     pid1.Kd         = 50;
	   pid1.tracking_val  = 0;  //循迹偏移量

 }
 
 /*********************************
***********************************/
void PID_TARGET_1(float temp1_val)
{
	pid1.target_val = temp1_val;    // 设置当前的目标值
	RES_PWM1 = PID_realize1(LAST1);//通过PID计算所需PWM值
  Load1(RES_PWM1);                //装载PWM值
}
/****************************************************
电机PID

入口：目标速度
出口：实际速度
**************************/
float PID_realize1(float actual1_val)
{
     /*计算目标值与实际值的误差*/
    pid1.err = pid1.target_val - actual1_val;
     /*误差累积*/
    pid1.integral += pid1.err;
     /*PID算法实现*/
    pid1.output_val = (pid1.Kp*pid1.err  + pid1.tracking_val)+
										 pid1.Ki*pid1.integral+
										 pid1.Kd*(pid1.err-pid1.err_last);
     /*误差传递*/
    pid1.err_last = pid1.err;
     /*返回当前实际值*/
    return pid1.output_val;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/**************************
PID2值初始化
入口：下列
出口：见电机PID
****************************/
PID pid2;
void PID_param2_init(void)
 {
     /* 初始化参数 */
     pid2.target_val = 0;        //目标值
     pid2.actual_val = 0.0;         //实际值
     pid2.err        = 0;           //定义偏差值
  	 pid2.output_val = 0;   
     pid2.err_last   = 0.0;         //定义上一个偏差值
     pid2.integral   = 0.0;         //定义积分值
     pid2.Kp         = 150;
     pid2.Ki         = 0;
     pid2.Kd         = 50;
	   pid2.tracking_val  = 0;      //循迹偏移量
 }
void PID_TARGET_2(float temp2_val)
{
	pid2.target_val = temp2_val;    // 设置当前的目标值
	RES_PWM2 = PID_realize2(LAST2); //通过PID计算所需PWM值
  Load2(RES_PWM2);                 //装载PWM值
}
/*****************************************************/
/*************************
电机PID

入口：目标速度
出口：实际速度
**************************/
/////////////////////////////////////////////////////////////////
float PID_realize2(float actual2_val)
{
     /*计算目标值与实际值的误差*/
    pid2.err = pid2.target_val - actual2_val;
     /*误差累积*/
    pid2.integral += pid2.err;
     /*PID算法实现*/
    pid2.output_val = (pid2.Kp*pid2.err+pid2.tracking_val)+
										 pid2.Ki*pid2.integral+
										 pid2.Kd*(pid2.err-pid2.err_last);
     /*误差传递*/
    pid2.err_last = pid2.err;
     /*返回当前实际值*/
    return pid2.output_val;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
///**************************
//PID值初始化
//入口：下列
//出口：见电机PID
//****************************/
//PID pid3;
//void PID_param3_init(void)
// {
//     /* 初始化参数 */
//     pid3.target_val = 0;        //目标值
//     pid3.actual_val = 0.0;         //实际值
//     pid3.err        = 0;           //定义偏差值
//  	 pid3.output_val = 0;   
//     pid3.err_last   = 0.0;         //定义上一个偏差值
//     pid3.integral   = 0.0;         //定义积分值
//     pid3.Kp         = 0;
//     pid3.Ki         = 0;
//     pid3.Kd         = 0;
//     pid3.tracking  = 0;         //循迹偏移量
// }
//void PID_TARGET_3(float temp3_val)
//{
//	pid3.target_val = temp3_val;    // 设置当前的目标
//	RES_PWM3 = PID_realize3(LAST4);
//  Load3(RES_PWM3);
//}

///***************************************************
//电机PID

//入口：目标速度
//出口：实际速度
//**************************/
//////////////////////////////////////////////////////////////////////
//float PID_realize3(float actual3_val)
//{
//     /*计算目标值与实际值的误差*/
//    pid3.err = pid3.target_val - actual3_val;
//     /*误差累积*/
//    pid3.integral += pid3.err;
//     /*PID算法实现*/
//    pid3.output_val = (pid3.Kp*pid3.err+pid3.tracking)+
//										 pid3.Ki*pid3.integral+
//										 pid3.Kd*(pid3.err-pid3.err_last);
//     /*误差传递*/
//    pid3.err_last = pid3.err;
//     /*返回当前实际值*/
//    return pid3.output_val;
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TIM4_IRQHandler(void) //PID中断输入引脚
{
	 
	if(TIM_GetFlagStatus(TIM4,TIM_FLAG_Update)==SET)//一级判定
	{
		  LAST1 = TIM2->CNT - 32768; //瞬时速度值
			LAST2 = TIM3->CNT - 32768;
		
			TIM2->CNT = 32768;         //CNT值复位
			TIM3->CNT = 32768;
		
			PID_TARGET_1(speed1);     //设置PID速度
			PID_TARGET_2(speed2);
	} 
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//清除中断标志位
	
	return 0;
}




