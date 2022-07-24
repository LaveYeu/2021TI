/**
* @owner        Sharkespeara
* @file         motor.h
* @brief        电机控制头文件
* @details      
* @par History  见如下说明
*          
*/
#ifndef _MOTOR_H__
#define _MOTOR_H__

#include "stm32f10x.h"




void Car_Run(int Speed);
void Car_Back(int Speed);
void Car_Stop(void);

void Car_Left1(int Speed);
void Car_Right1(int Speed);

void Car_Left2(int Speed);
void Car_Right2(int Speed);

void Car_Left3(int Speed);
void Car_Right3(int Speed);

void Car_Left4(void);
void Car_Right4(void);

void Car_RBack(void);
void Car_LBack(void);


void motor1(void);
void motor2(void);
void motor3(void);
void motor4(void);

#endif
