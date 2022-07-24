#include "stm32f10x.h"
#include "delay.h"
#include "GPIO.h"
#include "PWM.h"
#include "PID.h"
#include "linewalking.h"
#include "PID_Motor.h"
#include "sys.h"
#include "encoder.h"

u8 flag_Stop=1;     //ֹͣ��־λ
int Encoder;        //���������������
int moto;           //���PWM����
unsigned char Send_Count;//������Ҫ���͵����ݸ���
unsigned char COUNT;          //��������
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

	PID_TIM4_Init(49,7199);//5ms�ж�һ��
	
	PID_param1_init(); //PID�ṹ���ʼ��
	PID_param2_init();
	
	TIM2->CNT = 32768;  //TIM2 CNTֵ��ʼ��
	TIM3->CNT = 32768;  //TIM3 CNTֵ��ʼ��
	
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
		//����
		reset_led();
		recive_signalP9_L();        //�յ��ߵ�ƽ�ź�--��ʼ����
		clips();
		CAR_run(7);
		LineWalking_1();            //��ʼѭ��
		LineWalking_2();
		while(1)
		{
			CAR_stop();
			delay_ms(10);
			break;
		}
		recive_signalP9_L();        //�յ��͵�ƽ�ź�--׼��ת��
		choice_class0();             //ѡ�񲡷�������
		reset_led();
		while(1)
		{
			green_led();
			CAR_stop();
			break;
		}

		
//�ж�
		reset_led();
		recive_signalP9_L();        //�յ��ߵ�ƽ�ź�--��ʼ����
		clips();
		LineWalking_1();            //��ʼѭ��
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
//		recive_signalP9_L();        //�յ��͵�ƽ�ź�--׼��ת��
		choice_class1();             //ѡ�񲡷�������
		while(1)
		{
			CAR_stop();
//			recive_signalP9_L();
			break;
		}

		//Զ��
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

