#ifndef __HEADFILE_H
#define __HEADFILE_H


#include "math.h"
#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "dmpKey.h"
#include "dmpmap.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

//官方头文件
#include "stm32f10x.h"

//本人头文件
#include "pid.h"
#include "led.h"
#include "key.h"
#include "trx.h"
#include "pwm.h"
#include "loop.h"
#include "oled.h"
#include "usart.h"
#include "usart1.h"
//#include "encoder.h"
#include "systick.h"
#include "systime.h"
#include "mpu_i2c.h"
#include "mpu6050.h"


#define Delay_ms   SysTick_Delay_ms
#define Delay_us   SysTick_Delay_us

#define Limit(x,max,min)   x>max?max:(x<min?min:x)

#endif  //__HEADFILE_H

