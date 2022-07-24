/*
 * pid.h
 *
 *  Created on: 2021��3��30��
 *      Author: zhouw
 */

#ifndef CODE_PID_H_
#define CODE_PID_H_

#include "headfile.h"

typedef struct
{
    float i;            //����ϵ��
    float kp;           //����ϵ��
    float ki;           //����ϵ��
    float kd;           //΢��ϵ��
    float error;        //���
    float preverror;    //ǰһ�����
    float integ;        //������
    float deriv;        //���΢��
    float limit;        //�����޷�
    float MaxValue;     //������ֵ
    float MinValue;     //�����Сֵ
    float out;          //���ֵ
} PidObject;

void Pid_Init(PidObject* pid, float i, float KP, float KI, float KD, float Limit, float Max, float Min);
float Pid_Out(PidObject* pid, float measure, float desired);

#endif /* CODE_PID_H_ */
