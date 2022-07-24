#include "stm32f10x.h"
#include "delay.h"
#include "GPIO.h"
#include "PWM.h"
#include "PID.h"
#include "linewalking.h"
#include "PID_Motor.h"
#include "sys.h"
#include "encoder.h"

u8 flag_Stop=1;     //停止标志位
int Encoder;        //编码器的脉冲计数
int moto;           //电机PWM变量
unsigned char Send_Count;//串口需要发送的数据个数
unsigned char COUNT;          //计数变量
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
extern  __IO int encoderDelta1, encoderDelta2, encoderDelta3;
extern  __IO int encoder1, encoder2, encoder3;
extern  __IO int Delta;
extern  float RES_PWM1,RES_PWM2,RES_PWM3;
extern int LAST2,LAST3,LAST4;
extern PID pid1;
extern PID pid2;
extern PID pid3;
extern int speed1,speed2,speed3;
extern int LAST2_SS,LAST3_SS,LAST4_SS;
extern int speedd1,speedd2,speedd3,speedd4;
extern int class_number;
//////////////////////////////////////////////////////////////////////////

int main(void)
{
	GPIO_SITEA();
	GPIO_SITEB();
	GPIO_SITEC();
	
	delay_init();
	
	TIM1_PWM_Init(999,71);
	
	Encoder_TIM2_Init();
  Encoder_TIM3_Init();

	PID_TIM4_Init(49,7199);//5ms中断一次
	
	PID_param1_init(); //PID结构体初始化
	PID_param2_init();
	
	TIM2->CNT = 32768;  //TIM2 CNT值初始化
	TIM3->CNT = 32768;  //TIM3 CNT值初始化
	
	delay_ms(200);
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_10);
	GPIO_ResetBits(GPIOC,GPIO_Pin_1);
	GPIO_ResetBits(GPIOC,GPIO_Pin_2);
	GPIO_ResetBits(GPIOC,GPIO_Pin_3);
	GPIO_ResetBits(GPIOC,GPIO_Pin_11);
	GPIO_ResetBits(GPIOC,GPIO_Pin_5);
	GPIO_ResetBits(GPIOC,GPIO_Pin_7);
	GPIO_ResetBits(GPIOC,GPIO_Pin_9);
//	GPIO_SetBits(GPIOB,GPIO_Pin_3);
//	clips(); 
//	while(1)
//	{
//		LineWalking_1();
//		while(1)
//		{
//			CAR_stop();
//			delay_ms(1864);
//			break;
//		}
//		LineWalking_2();
//		while(1)
//		{
//			CAR_stop();
//			delay_ms(1864);
//			break;
//		}
//		CAR_left(1000);
//		LineWalking_1();
//		LineWalking_2();
//		while(1)
//		{
//			CAR_stop();
//		}
//		
//	}
	
	while(1)
	{
		//近端
		reset_led();
		recive_signalP9_L();        //收到高电平信号--开始出发
		clips();
		CAR_run(7);
		LineWalking_1();            //开始循迹
		LineWalking_2();
		while(1)
		{
			CAR_stop();
			delay_ms(10);
			break;
		}
		recive_signalP9_L();        //收到低电平信号--准备转弯
		choice_class0();             //选择病房并进入
		reset_led();
		while(1)
		{
			green_led();
			CAR_stop();
			break;
		}

		
//中端
		reset_led();
		recive_signalP9_L();        //收到高电平信号--开始出发
		clips();
		LineWalking_1();            //开始循迹
		cross_redline();
		LineWalking_1();
		while(1)
		{
			send_signal();
			CAR_stop();
			recive_signalP9_L();
			break;
		}
		LineWalking_2();
//		recive_signalP9_L();        //收到低电平信号--准备转弯
		choice_class1();             //选择病房并进入
		while(1)
		{
			CAR_stop();
//			recive_signalP9_L();
			break;
		}

		//远端
		clips();
		LineWalking_1();
		LineWalking_2();
		LineWalking_1();
		LineWalking_2();
		LineWalking_1();
		LineWalking_2();
		CAR_left(700);
		cross_redline();
		LineWalking_2();
		CAR_left(700);
		LineWalking_2();
		while(1)
		{
			red_led();
			CAR_stop();
			break;
		}
		dete_clips();
		return_1();
		reset_led();
		LineWalking_2();
		CAR_right(700);
		cross_redline();
		LineWalking_2();
		CAR_right(700);
		cross_redline();
		LineWalking_1();
		LineWalking_2();
		LineWalking_1();
		LineWalking_2();
		LineWalking_1();
		LineWalking_2();
		green_led();
		
	}
}

