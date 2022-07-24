/**
* @owner        Sharkespeara
* @file         PID.h
* @brief        PID函数
* @details      
* @par History  见如下说明
*          
*/
#ifndef  _CONTROL_H
#define  _CONTROL_H

#include "sys.h" 

typedef struct 
 {
     float target_val;               		//目标值1
     float actual_val;                  //实际值1
	   float output_val;                  //输出值
     float err;                         //定义偏差值
     float err_last;                    //定义上一个偏差值
     float Kp,Ki,Kd;                    //定义比例、积分、微分系数
     float integral;                    //定义积分值
	   float tracking_val;                   //循迹偏移量1
}PID;

int Vertical(float Med,float Angle,float gyro_Y);
int Velocity(int encoder_left,int encoder_right);

int Turn(int gyro_Z);
void EXTI2_IRQHandler(void);

void PID_TIM4_Init(u16 arr,u16 psc);

void PID_param1_init(void);
void PID_param2_init(void);
void PID_param3_init(void);

float PID_realize1(float actual1_val);
float PID_realize2(float actual2_val);
float PID_realize3(float actual3_val);

//float PID_realize1(void);
void PID_TARGET_1(float temp1_val);
void PID_TARGET_2(float temp2_val);
void PID_TARGET_3(float temp3_val);

#endif

