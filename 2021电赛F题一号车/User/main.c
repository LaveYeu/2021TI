#include "headfile.h"


u8 ii = 0;
int main(void)
{
    //��ʼ��
    Config();


	//ѡ�񷽰�
	Loop_Run();

	
	SysTick_Delay_ms(200);
	while(ii==0)
		{
			ii = Check_Medicine(GPIOA,GPIO_Pin_4);//ʱ�̼��ҩƷָʾ���ȴ�����
		}
		LED1(0);
		SysTick_Delay_ms(1000);
		LED1(1);
	if(Solve==1)
	{
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(2450);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
	
		TurnLeft();//��ת90��
		
		Set_Pwm(0, 0);
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(1500);
		Set_Pwm(0, 0);
		
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_14);//���Ƶȴ�жҩƷ
		ii = Check_Medicine(GPIOA,GPIO_Pin_4);
		while(ii==1)
		{
			ii = Check_Medicine(GPIOA,GPIO_Pin_4);//ʱ�̼��ҩƷָʾ���ȴ�����
//			USART_SendByte(USART1,'A');
		}
		LED1(0);
		SysTick_Delay_ms(1000);
		LED1(1);
		USART_SendByte(USART1,'A');
//		USART_SendByte(USART1,'A');
//		USART_SendByte(USART1,'A');
		GPIO_ResetBits(LED1_GPIO_PORT, GPIO_Pin_14);
		
		//���� 
		Set_Pwm(-MotorDuty, -MotorDuty);//����
		SysTick_Delay_ms(1500);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnLeft();
		
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(2200);
		Set_Pwm(0, 0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_15);//���̵�
	}
	
	
	if(Solve==2)
	{
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(2400);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnRight();
		Set_Pwm(0, 0);
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(1500);
		Set_Pwm(0, -0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_14);//���Ƶȴ�жҩƷ
		ii = Check_Medicine(GPIOA,GPIO_Pin_4);
		while(ii==1)
		{
			
			ii = Check_Medicine(GPIOA,GPIO_Pin_4);//ʱ�̼��ҩƷָʾ���ȴ�����
		}
		LED1(0);
		SysTick_Delay_ms(1000);
		LED1(1);
		USART_SendByte(USART1,'A');
		GPIO_ResetBits(LED1_GPIO_PORT, GPIO_Pin_14);
		//����     
		Set_Pwm(-MotorDuty, -MotorDuty);//����
		SysTick_Delay_ms(1500);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnRight();
		
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(2200);
		Set_Pwm(0, 0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_15);//���̵�
	}
	
	if(Solve==3)
	{
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(5200);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnNum(87.5);
		Set_Pwm(0, 0);
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(1500);
		Set_Pwm(0, -0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_14);//���Ƶȴ�жҩƷ
		ii = Check_Medicine(GPIOA,GPIO_Pin_4);
		while(ii==1)
		{
			ii = Check_Medicine(GPIOA,GPIO_Pin_4);//ʱ�̼��ҩƷָʾ���ȴ�����
		}
		LED1(0);
		SysTick_Delay_ms(1000);
		LED1(1);
		USART_SendByte(USART1,'A');
		SysTick_Delay_ms(500);
//		USART_SendByte(USART1,'A');
//		SysTick_Delay_ms(500);
		
		GPIO_ResetBits(LED1_GPIO_PORT, GPIO_Pin_14);
		//���� 
		Set_Pwm(-MotorDuty, -MotorDuty);//����
		SysTick_Delay_ms(1600);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnNum(89);//�����Ҹ�
		Set_Pwm(0, -0);
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(4500);
		Set_Pwm(0, 0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_15);//���̵�
	}
	
	
	if(Solve==4)//D����
	{
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(5100);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnRight();
		Set_Pwm(0, 0);
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(1500);
		Set_Pwm(0, -0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_14);//���Ƶȴ�жҩƷ
		ii = Check_Medicine(GPIOA,GPIO_Pin_4);
		while(ii==1)
		{
			ii = Check_Medicine(GPIOA,GPIO_Pin_4);//ʱ�̼��ҩƷָʾ���ȴ�����
		}
		LED1(0);
		SysTick_Delay_ms(1000);
		LED1(1);
		USART_SendByte(USART1,'A');
		GPIO_ResetBits(LED1_GPIO_PORT, GPIO_Pin_14);
//		USART_SendByte(USART1,'A');
		//���� 
		Set_Pwm(-MotorDuty, -MotorDuty);//����
		SysTick_Delay_ms(1500);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnRight();
		Set_Pwm(0, -0);
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(4500);
		Set_Pwm(0, 0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_15);//���̵�
	}
	//���߳����У�������ѭ����
	if(Solve==5)//E����
	{
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(7700);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnRight();
		Set_Pwm(0, 0);
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(2570);
		Set_Pwm(0, -0);
		TurnNum(-84);
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(1500);
		Set_Pwm(0, -0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_14);//���Ƶȴ�жҩƷ
		ii = Check_Medicine(GPIOA,GPIO_Pin_4);
		while(ii==1)
		{
			ii = Check_Medicine(GPIOA,GPIO_Pin_4);//ʱ�̼��ҩƷָʾ���ȴ�����
		}
		LED1(0);
		SysTick_Delay_ms(1000);
		LED1(1);
		GPIO_ResetBits(LED1_GPIO_PORT, GPIO_Pin_14);
		//���� 
		Set_Pwm(-MotorDuty, -MotorDuty);//����
		SysTick_Delay_ms(1600);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
//		TurnRight();
		TurnLeft80();
//		TurnLeft();
		Set_Pwm(0, -0);
		Set_Pwm(-MotorDuty, -MotorDuty);//ֱ��
		SysTick_Delay_ms(2600);
		TurnLeft();
		Set_Pwm(-MotorDuty, -MotorDuty);//ֱ��
		SysTick_Delay_ms(7250);
		Set_Pwm(0, 0);
		
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_15);//���̵�
	}
	
	if(Solve==6)//F����
	{
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(7700);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnRight();
		Set_Pwm(0, 0);
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(2620);
		Set_Pwm(0, -0);
		TurnNum(84);
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(1500);
		Set_Pwm(0, -0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_14);//���Ƶȴ�жҩƷ
		ii = Check_Medicine(GPIOA,GPIO_Pin_4);
		while(ii==1)
		{
			ii = Check_Medicine(GPIOA,GPIO_Pin_4);//ʱ�̼��ҩƷָʾ���ȴ�����
		}
		LED1(0);
		SysTick_Delay_ms(1000);
		LED1(1);
		GPIO_ResetBits(LED1_GPIO_PORT, GPIO_Pin_14);
		//���� 
		Set_Pwm(-MotorDuty, -MotorDuty);//����
		SysTick_Delay_ms(1650);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
//		TurnRight();
		TurnLeft();
//		TurnLeft();
		Set_Pwm(0, -0);
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(2250);
		TurnLeft();
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(7250);
		Set_Pwm(0, 0);
		
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_15);//���̵�
	}
	
	if(Solve==7)//G����
	{
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(7800);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnNum(88);
		Set_Pwm(0, 0);
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(2620);
		Set_Pwm(0, -0);
		TurnRight();
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(1500);
		Set_Pwm(0, -0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_14);//���Ƶȴ�жҩƷ
		ii = Check_Medicine(GPIOA,GPIO_Pin_4);
		while(ii==1)
		{
			ii = Check_Medicine(GPIOA,GPIO_Pin_4);//ʱ�̼��ҩƷָʾ���ȴ�����
		}
		LED1(0);
		SysTick_Delay_ms(1000);
		LED1(1);
		GPIO_ResetBits(LED1_GPIO_PORT, GPIO_Pin_14);
		//���� 
		Set_Pwm(-MotorDuty, -MotorDuty);//����
		SysTick_Delay_ms(1450);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnRight();
//		TurnLeft();
//		TurnLeft();
		Set_Pwm(0, -0);
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(2250);
		TurnRight();
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(7250);
		Set_Pwm(0, 0);
		
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_15);//���̵�
	}
	
	if(Solve==8)//H����
	{
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(7800);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnNum(88);
		Set_Pwm(0, 0);
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(2620);
		Set_Pwm(0, -0);
		TurnNum(88);
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(1200);
		Set_Pwm(0, -0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_14);//���Ƶȴ�жҩƷ
		ii = Check_Medicine(GPIOA,GPIO_Pin_4);
		while(ii==1)
		{
			ii = Check_Medicine(GPIOA,GPIO_Pin_4);//ʱ�̼��ҩƷָʾ���ȴ�����
		}
		LED1(0);
		SysTick_Delay_ms(1000);
		LED1(1);
		GPIO_ResetBits(LED1_GPIO_PORT, GPIO_Pin_14);
		//���� 
		Set_Pwm(-MotorDuty, -MotorDuty);//����
		SysTick_Delay_ms(1500);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnRight();
//		TurnLeft();
//		TurnLeft();
		Set_Pwm(0, -0);
		Set_Pwm(-MotorDuty, -MotorDuty);//ֱ��
		SysTick_Delay_ms(2450);
		TurnLeft();
		Set_Pwm(MotorDuty, MotorDuty);//ֱ��
		SysTick_Delay_ms(7150);
		Set_Pwm(0, 0);
		
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_15);//���̵�
	}
    
    
}



