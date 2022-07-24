/*
 * pid.c
 *
 *  Created on: 2021��3��30��
 *      Author: zhouw
 */

#include "pid.h"

void Pid_Init(PidObject* pid, float i, float KP, float KI, float KD, float Limit, float Max, float Min)
{
    pid->i = i;
    pid->error     = 0;
    pid->preverror = 0;
    pid->integ     = 0;
    pid->deriv     = 0;
    pid->kp = KP;
    pid->ki = KI;
    pid->kd = KD;
    pid->limit = Limit;
    pid->MaxValue = Max;
    pid->MinValue = Min;
}

float Pid_Out(PidObject* pid, float measure, float desired)
{
    pid->error = pid->i*(measure - desired);
    pid->integ += pid->error;
    pid->deriv = pid->error - pid->preverror;
    pid->preverror = pid->error;

    if(pid->integ > pid->limit)
    pid->integ = pid->limit;
    if(pid->integ < -pid->limit)
    pid->integ = -pid->limit;

    pid->out = (float)(pid->kp * pid->error + pid->ki * pid->integ +  pid->kd * pid->deriv);

    //����޷�
    if(pid->out > pid->MaxValue) pid->out = pid->MaxValue;
    if(pid->out < pid->MinValue) pid->out = pid->MinValue;

    return pid->out;
}



