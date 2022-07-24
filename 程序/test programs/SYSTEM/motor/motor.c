/**
* @owner        Sharkespeara
* @file         motor.c
* @brief        电机运动控制函数
* @details      
* @par History  见如下说明
*          
*/
#include "motor.h"
#include "sys.h"
#include "PWM.h"
#include "delay.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
#define  LeftMotor_Go()			{GPIO_SetBits(Motor_Port, Left_MotoA_Pin); GPIO_ResetBits(Motor_Port, Left_MotoB_Pin);}
#define  LeftMotor_Back()		{GPIO_ResetBits(Motor_Port, Left_MotoA_Pin); GPIO_SetBits(Motor_Port, Left_MotoB_Pin);}
#define  LeftMotor_Stop()		{GPIO_ResetBits(Motor_Port, Left_MotoA_Pin); GPIO_ResetBits(Motor_Port, Left_MotoB_Pin);}

#define  RightMotor_Go()		{GPIO_SetBits(Motor_Port, Right_MotoA_Pin); GPIO_ResetBits(Motor_Port, Right_MotoB_Pin);}
#define  RightMotor_Back()		{GPIO_ResetBits(Motor_Port, Right_MotoA_Pin); GPIO_SetBits(Motor_Port, Right_MotoB_Pin);}
#define  RightMotor_Stop()		{GPIO_ResetBits(Motor_Port, Right_MotoA_Pin); GPIO_ResetBits(Motor_Port, Right_MotoB_Pin);}
*/
#define  LeftMotorPWM(Speed)	TIM_SetCompare2(TIM2, Speed);
#define  RightMotorPWM(Speed)	TIM_SetCompare1(TIM2, Speed);		

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Car_Run(int Speed)
{
	LeftMotorPWM(Speed);
	RightMotorPWM(Speed);
}
void Car_Back(int Speed)
{
	LeftMotorPWM(Speed);
	RightMotorPWM(Speed);
}
void Car_Stop(void)
{	
	LeftMotorPWM(0);
	RightMotorPWM(0);
}
void Car_Left1(int Speed)
{	
	LeftMotorPWM(Speed);
	RightMotorPWM(Speed-250);
}
void Car_Right1(int Speed)
{
	LeftMotorPWM(Speed-250);
	RightMotorPWM(Speed);
}
void Car_Left2(int Speed)
{	
	LeftMotorPWM(Speed);
	RightMotorPWM(Speed-350);
}
void Car_Right2(int Speed)
{	
	LeftMotorPWM(Speed-350);
	RightMotorPWM(Speed);
}
void Car_Left3(int Speed)
{	
	LeftMotorPWM(Speed);
	RightMotorPWM(Speed-450);
}
void Car_Right3(int Speed)
{	
	LeftMotorPWM(Speed-450);
	RightMotorPWM(Speed);
}
void Car_Left4(void)
{	
	LeftMotorPWM(0);
	RightMotorPWM(600);
}
void Car_Right4(void)
{	
	LeftMotorPWM(600);
	RightMotorPWM(0);
}
void Car_RBack(void)
{
	LeftMotorPWM(300);
	RightMotorPWM(300);
	delay_ms(300);
}
void car_LBack(void)
{
	LeftMotorPWM(300);
	RightMotorPWM(300);
	delay_ms(300);
}


void motor1(void)//倒退
{
	//右轮
	PBout(1) = 1 ;
	PBout(0) = 0 ;
	//左轮
	PBout(2) = 1 ;
	PBout(10) = 0 ;
}
void motor2(void)//顺时针旋转
{
	//
	PBout(1) = 0 ;
	PBout(0) = 1 ;
	//
	PBout(2) = 1 ;
	PBout(10) = 0 ;
}
void motor3(void)//逆时针旋转
{
	//
	PBout(1) = 1 ;
	PBout(0) = 0 ;
	//
	PBout(2) = 0 ;
	PBout(10) = 1 ;
}
void motor4(void)//直走
{
	//
	PBout(1) = 0 ;
	PBout(0) = 1 ;
	//
	PBout(2) = 0 ;
	PBout(10) = 1 ;
}

