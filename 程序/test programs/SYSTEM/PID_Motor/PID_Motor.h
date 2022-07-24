#ifndef  _MOTOR_H
#define  _MOTOR_H

#include "sys.h" 


#define Ain1  PBout(0)
#define Ain2  PBout(1)

#define Bin1  PBout(2)
#define Bin2  PBout(10)


void Motor_Init(void);/*【5】*/
int Limit(float PWM_INPUT);
int GFP_abs(int p);

void Load1(int moto1);
void Load2(int moto2);
void Load3(int moto3);

void go_1(int speedd1);
void go_2(int speedd2);
void go_3(int speedd3);

void CAR_run(int speedd1);
void CAR_stop(void);
void CAR_right(int timee);
void CAR_left(int timee);

void return_1(void);

void return_right(void);
void return_left(void);
void class_1(void);
void class_2(void);

void time(int timee);
#endif

