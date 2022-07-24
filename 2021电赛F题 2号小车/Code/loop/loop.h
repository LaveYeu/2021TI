#ifndef __LOOP_H
#define __LOOP_H

#include "headfile.h"
#define PWMA   TIM1->CCR1  //PA8

#define AIN2   PBout(12)
#define AIN1   PBout(13)
#define BIN1   PBout(14)
#define BIN2   PBout(15)

#define PWMB   TIM1->CCR4  //PA11

typedef struct
{
	void (*task_func)(void);
	uint16_t interval_ticks;//执行时间间隔
	uint32_t last_run;//最后一次运行时间
}sched_task_t;


extern int16_t speed_set, turn_set;
extern int Solve;
extern int ChooseSucces;
extern int DrugFlag;
extern int MoveAsk;
extern int MoveSuccess;
extern float MoveTime;
extern float pitch, roll, yaw;
void Config(void);
void Loop_Run(void);
void ForWard(float time);
void TurnLeft(void);
void TurnRight(void);
void TurnAngle(int num);
#endif  //__LOOP_H


