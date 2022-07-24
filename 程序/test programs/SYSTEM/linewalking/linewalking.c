/**
* @owner        Sharkespeara
* @file         linewalking.c
* @brief        巡线模式运动函数
* @details      
* @par History  见如下说明
*          
*/


#include "linewalking.h"
#include "sys.h"
#include "PID_motor.h"
#include "delay.h"
#include "stdlib.h"
#include "GPIO.h"
#include "PID.h"

extern PID pid1;
extern PID pid2;
extern PID pid3;
extern int speed1,speed2;
int class_number = 0;

#define val  700
#define val1 150
#define val2 200
#define val3 400
#define linespeed 7


//亮红灯(未检测到)为0
//灭红灯(检测到)为1

void LineWalking_1(void)
{
	while(1)
	{
		if(PIN_7 == 1)
		{
		  break;
		}
		else if(PIN_6 == 1)
		{
			break;
			
		}
	  else if(PIN_3 == 1)
		{
		 pid1.tracking_val = val1;
	   pid2.tracking_val = -1*val1;
		 delay_ms(100);
		 pid1.tracking_val = 0;
		 pid2.tracking_val = 0;//循迹偏移量重置为0
		} 
		else if(PIN_4 == 1)
		{
		 pid1.tracking_val = -1*val1;
	   pid2.tracking_val = val1;
		 delay_ms(100);
		 pid1.tracking_val = 0;
		 pid2.tracking_val = 0;//循迹偏移量重置为0
		}
	  else if(PIN_2 == 1)
		{
		 pid1.tracking_val = val3;
	   pid2.tracking_val = -1*val3;
		 delay_ms(100);
		 pid1.tracking_val = 0;
		 pid2.tracking_val = 0;//循迹偏移量重置为0
		} 
		else if(PIN_5 == 1)
		{
		 pid1.tracking_val = -1*val3;
	   pid2.tracking_val = val3;
		 delay_ms(100);
		 pid1.tracking_val = 0;
		 pid2.tracking_val = 0;//循迹偏移量重置为0
		}
		
		
		else
		{
			speed1 = linespeed;
			speed2 = linespeed;
		}
	}
}
///////////////////////////////////////////////////////
void LineWalking_2(void)
{
		while(1)
	{
		if((PIN_3 == 1 && PIN_4 == 1)||(PIN_2 == 1 && PIN_5 == 1))
		{
		  break;
		}
	  else if(PIN_3 == 1)
		{
		 pid1.tracking_val = val1;
	   pid2.tracking_val = -1*val1;
		 delay_ms(100);
		 pid1.tracking_val = 0;
		 pid2.tracking_val = 0;//循迹偏移量重置为0
		} 
		else if(PIN_4 == 1)
		{
		 pid1.tracking_val = -1*val1;
	   pid2.tracking_val = val1;
		 delay_ms(100);
		 pid1.tracking_val = 0;
		 pid2.tracking_val = 0;//循迹偏移量重置为0
		}
		else if(PIN_2 == 1)
		{
		 pid1.tracking_val = -1*val3;
	   pid2.tracking_val = val3;
		 delay_ms(100);
		 pid1.tracking_val = 0;
		 pid2.tracking_val = 0;//循迹偏移量重置为0
		} 
		else if(PIN_5 == 1)
		{
		 pid1.tracking_val = val3;
	   pid2.tracking_val = -1*val3;
		 delay_ms(100);
		 pid1.tracking_val = 0;
		 pid2.tracking_val = 0;//循迹偏移量重置为0
		}
		else
		{
			speed1 = 4;
			speed2 = 4;
		}
	}
}
///////////////////////////////////////////////////////
void tiaozheng(void)
{
	do
	{
		speed1 = 2;
	}
	while(PIN_4 == 0);
		do
	{
		speed2 = 2;
	}
	while(PIN_3 == 0);
}
///////////////////////////////////////////////////////
void red_led(void)
{
	PCout(4) = 1;
}
void green_led(void)
{
	PAout(12) = 1;
}
void reset_led(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_12);
}
////////////////////////////////////////////////////////
void dete_clips(void)
{
	while(1)
	{
	 if(PCin(6) == 0)
	 {
		 green_led();
		 delay_ms(200);
		 break;
	 }
  }
}
////////////////////////////////////////////////////////
void clips(void)
{
	while(1)
	{
		if(PCin(6) == 0)
		{
			delay_ms(50);
			if(PCin(6) == 0)
			{
				delay_ms(1000);
				break;
			}
		}
	}
}
////////////////////////////////////////////////////////
void choice_class0(void)  //1为左//2为右   
{
	while(1)
	{
	 if(PAin(2)== 1)
	 {
		 send_signal();
			CAR_left(1000);    //小车左转
			cross_redline();
			LineWalking_2();   //循迹至病房门口
		  red_led();
			PCin(6) = 1 ;
			dete_clips();      //检测药物是否被取下
			return_1();        //掉头
		  reset_led();
	    LineWalking_2();
		  CAR_right(800);
		  LineWalking_2();
			break;
	 }
	 if(PAin(3)== 1)
	 {
		 send_signal();
			CAR_right(800);
		 cross_redline();
			LineWalking_2();
		 red_led();
			PCin(6) = 1 ;
			dete_clips();
		 reset_led();
			return_1();        //掉头
			LineWalking_2();
		  CAR_left(800);
		  LineWalking_2();
			break;
	 }
 }
}
///////////////////////////////////////////////////////
void choice_class1(void)  //1为左//2为右   //中端
{
	while(1)
	{
	 if(PAin(2)== 1)
	 {
		 send_signal();
			CAR_left(700);    //小车左转
			cross_redline();
			LineWalking_2();   //循迹至病房门口
			PCin(6) = 1 ;
			dete_clips();      //检测药物是否被取下
			return_1();        //掉头
	    LineWalking_2();
		  CAR_right(800);
		  LineWalking_1();
		cross_redline();
		LineWalking_1();
		LineWalking_2();
			break;
	 }
	 if(PAin(3)== 1)
	 {
		 send_signal();
			CAR_right(700);
			cross_redline();
			LineWalking_2();
			PCin(6) = 1 ;
			dete_clips();
			return_1();        //掉头
		 reset_led();
			LineWalking_2();
		  CAR_left(800);
		  LineWalking_1();
		cross_redline();
		LineWalking_1();
		LineWalking_2();
			break;
	 }
 }
}
///////////////////////////////////////////////////////
void choice_class2(void)  //远端
{
	while(1)
	{
	 if(PAin(2)== 1)
	 {
		 send_signal();
			CAR_left(700);    //小车左转
			cross_redline();
			LineWalking_2();   //循迹至病房门口
			PCin(6) = 1 ;
			dete_clips();      //检测药物是否被取下
			return_1();        //掉头
	    LineWalking_2();
		  CAR_right(800);
		  LineWalking_1();
		cross_redline();
		LineWalking_1();
		LineWalking_2();
			break;
	 }
	 if(PAin(3)== 1)
	 {
			CAR_right(700);
			cross_redline();
			LineWalking_1();
			PCin(6) = 1 ;
			dete_clips();
			return_1();        //掉头
			LineWalking_1();
			CAR_left(500);
		  LineWalking_1();
		  CAR_right(500);
			break;
	 }
  }
}
///////////////////////////////////////////////////////
void return_store(void)
{
	while(1)
	{
	 if(class_number == 1)  //小车从左边循迹返回到中心线
	 {
		 CAR_right(500);
		 LineWalking_1();
		 break;
	 }
	 if(class_number == 2)  //小车从右边循迹返回到中心线
	 {
		 CAR_left(500);
		 LineWalking_1();
		 break;
	 }
  }
}
//////////////////////////////////////////
void reset_classnumber(void)
{
	class_number = 0;
}
//////////////////////////////////////////
void cross_redline(void)
{
	CAR_run(5);
	delay_ms(500);
}
//////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
void send_signal(void)
{
	PAout(5) = 1;
	delay_ms(500);
	PAout(5) = 0;
}

void recive_signalP8(void)
{
	while(1)
	{
			if(PAin(8) == 1)
			{
				break;
			}
	}
}

void recive_signalP9_H(void)
{
	while(1)
	{
			if(PCin(9) == 1)
			{
				break;
			}
	}
}
void recive_signalP9_L(void)
{
	while(1)
	{
			if(PCin(9) == 0)
			{
				break;
			}
	}
}

