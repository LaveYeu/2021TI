/*
 * pid.h
 *
 *  Created on: 2021年3月30日
 *      Author: zhouw
 */

#ifndef CODE_PID_H_
#define CODE_PID_H_

#include "headfile.h"

typedef struct
{
    float i;            //反馈系数
    float kp;           //比例系数
    float ki;           //积分系数
    float kd;           //微分系数
    float error;        //误差
    float preverror;    //前一个误差
    float integ;        //误差积分
    float deriv;        //误差微分
    float limit;        //积分限幅
    float MaxValue;     //输出最大值
    float MinValue;     //输出最小值
    float out;          //输出值
} PidObject;

void Pid_Init(PidObject* pid, float i, float KP, float KI, float KD, float Limit, float Max, float Min);
float Pid_Out(PidObject* pid, float measure, float desired);

#endif /* CODE_PID_H_ */
