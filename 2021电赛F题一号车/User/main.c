#include "headfile.h"


u8 ii = 0;
int main(void)
{
    //初始化
    Config();


	//选择方案
	Loop_Run();

	
	SysTick_Delay_ms(200);
	while(ii==0)
		{
			ii = Check_Medicine(GPIOA,GPIO_Pin_4);//时刻检测药品指示，等待发车
		}
		LED1(0);
		SysTick_Delay_ms(1000);
		LED1(1);
	if(Solve==1)
	{
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(2450);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
	
		TurnLeft();//左转90度
		
		Set_Pwm(0, 0);
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(1500);
		Set_Pwm(0, 0);
		
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_14);//点红灯等待卸药品
		ii = Check_Medicine(GPIOA,GPIO_Pin_4);
		while(ii==1)
		{
			ii = Check_Medicine(GPIOA,GPIO_Pin_4);//时刻检测药品指示，等待发车
//			USART_SendByte(USART1,'A');
		}
		LED1(0);
		SysTick_Delay_ms(1000);
		LED1(1);
		USART_SendByte(USART1,'A');
//		USART_SendByte(USART1,'A');
//		USART_SendByte(USART1,'A');
		GPIO_ResetBits(LED1_GPIO_PORT, GPIO_Pin_14);
		
		//返回 
		Set_Pwm(-MotorDuty, -MotorDuty);//倒车
		SysTick_Delay_ms(1500);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnLeft();
		
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(2200);
		Set_Pwm(0, 0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_15);//点绿灯
	}
	
	
	if(Solve==2)
	{
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(2400);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnRight();
		Set_Pwm(0, 0);
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(1500);
		Set_Pwm(0, -0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_14);//点红灯等待卸药品
		ii = Check_Medicine(GPIOA,GPIO_Pin_4);
		while(ii==1)
		{
			
			ii = Check_Medicine(GPIOA,GPIO_Pin_4);//时刻检测药品指示，等待发车
		}
		LED1(0);
		SysTick_Delay_ms(1000);
		LED1(1);
		USART_SendByte(USART1,'A');
		GPIO_ResetBits(LED1_GPIO_PORT, GPIO_Pin_14);
		//返回     
		Set_Pwm(-MotorDuty, -MotorDuty);//倒车
		SysTick_Delay_ms(1500);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnRight();
		
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(2200);
		Set_Pwm(0, 0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_15);//点绿灯
	}
	
	if(Solve==3)
	{
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(5200);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnNum(87.5);
		Set_Pwm(0, 0);
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(1500);
		Set_Pwm(0, -0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_14);//点红灯等待卸药品
		ii = Check_Medicine(GPIOA,GPIO_Pin_4);
		while(ii==1)
		{
			ii = Check_Medicine(GPIOA,GPIO_Pin_4);//时刻检测药品指示，等待发车
		}
		LED1(0);
		SysTick_Delay_ms(1000);
		LED1(1);
		USART_SendByte(USART1,'A');
		SysTick_Delay_ms(500);
//		USART_SendByte(USART1,'A');
//		SysTick_Delay_ms(500);
		
		GPIO_ResetBits(LED1_GPIO_PORT, GPIO_Pin_14);
		//返回 
		Set_Pwm(-MotorDuty, -MotorDuty);//倒车
		SysTick_Delay_ms(1600);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnNum(89);//左正右负
		Set_Pwm(0, -0);
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(4500);
		Set_Pwm(0, 0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_15);//点绿灯
	}
	
	
	if(Solve==4)//D病房
	{
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(5100);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnRight();
		Set_Pwm(0, 0);
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(1500);
		Set_Pwm(0, -0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_14);//点红灯等待卸药品
		ii = Check_Medicine(GPIOA,GPIO_Pin_4);
		while(ii==1)
		{
			ii = Check_Medicine(GPIOA,GPIO_Pin_4);//时刻检测药品指示，等待发车
		}
		LED1(0);
		SysTick_Delay_ms(1000);
		LED1(1);
		USART_SendByte(USART1,'A');
		GPIO_ResetBits(LED1_GPIO_PORT, GPIO_Pin_14);
//		USART_SendByte(USART1,'A');
		//返回 
		Set_Pwm(-MotorDuty, -MotorDuty);//倒车
		SysTick_Delay_ms(1500);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnRight();
		Set_Pwm(0, -0);
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(4500);
		Set_Pwm(0, 0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_15);//点绿灯
	}
	//多线程运行（可自行循环）
	if(Solve==5)//E病房
	{
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(7700);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnRight();
		Set_Pwm(0, 0);
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(2570);
		Set_Pwm(0, -0);
		TurnNum(-84);
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(1500);
		Set_Pwm(0, -0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_14);//点红灯等待卸药品
		ii = Check_Medicine(GPIOA,GPIO_Pin_4);
		while(ii==1)
		{
			ii = Check_Medicine(GPIOA,GPIO_Pin_4);//时刻检测药品指示，等待发车
		}
		LED1(0);
		SysTick_Delay_ms(1000);
		LED1(1);
		GPIO_ResetBits(LED1_GPIO_PORT, GPIO_Pin_14);
		//返回 
		Set_Pwm(-MotorDuty, -MotorDuty);//倒车
		SysTick_Delay_ms(1600);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
//		TurnRight();
		TurnLeft80();
//		TurnLeft();
		Set_Pwm(0, -0);
		Set_Pwm(-MotorDuty, -MotorDuty);//直行
		SysTick_Delay_ms(2600);
		TurnLeft();
		Set_Pwm(-MotorDuty, -MotorDuty);//直行
		SysTick_Delay_ms(7250);
		Set_Pwm(0, 0);
		
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_15);//点绿灯
	}
	
	if(Solve==6)//F病房
	{
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(7700);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnRight();
		Set_Pwm(0, 0);
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(2620);
		Set_Pwm(0, -0);
		TurnNum(84);
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(1500);
		Set_Pwm(0, -0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_14);//点红灯等待卸药品
		ii = Check_Medicine(GPIOA,GPIO_Pin_4);
		while(ii==1)
		{
			ii = Check_Medicine(GPIOA,GPIO_Pin_4);//时刻检测药品指示，等待发车
		}
		LED1(0);
		SysTick_Delay_ms(1000);
		LED1(1);
		GPIO_ResetBits(LED1_GPIO_PORT, GPIO_Pin_14);
		//返回 
		Set_Pwm(-MotorDuty, -MotorDuty);//倒车
		SysTick_Delay_ms(1650);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
//		TurnRight();
		TurnLeft();
//		TurnLeft();
		Set_Pwm(0, -0);
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(2250);
		TurnLeft();
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(7250);
		Set_Pwm(0, 0);
		
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_15);//点绿灯
	}
	
	if(Solve==7)//G病房
	{
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(7800);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnNum(88);
		Set_Pwm(0, 0);
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(2620);
		Set_Pwm(0, -0);
		TurnRight();
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(1500);
		Set_Pwm(0, -0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_14);//点红灯等待卸药品
		ii = Check_Medicine(GPIOA,GPIO_Pin_4);
		while(ii==1)
		{
			ii = Check_Medicine(GPIOA,GPIO_Pin_4);//时刻检测药品指示，等待发车
		}
		LED1(0);
		SysTick_Delay_ms(1000);
		LED1(1);
		GPIO_ResetBits(LED1_GPIO_PORT, GPIO_Pin_14);
		//返回 
		Set_Pwm(-MotorDuty, -MotorDuty);//倒车
		SysTick_Delay_ms(1450);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnRight();
//		TurnLeft();
//		TurnLeft();
		Set_Pwm(0, -0);
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(2250);
		TurnRight();
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(7250);
		Set_Pwm(0, 0);
		
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_15);//点绿灯
	}
	
	if(Solve==8)//H病房
	{
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(7800);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnNum(88);
		Set_Pwm(0, 0);
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(2620);
		Set_Pwm(0, -0);
		TurnNum(88);
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(1200);
		Set_Pwm(0, -0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_14);//点红灯等待卸药品
		ii = Check_Medicine(GPIOA,GPIO_Pin_4);
		while(ii==1)
		{
			ii = Check_Medicine(GPIOA,GPIO_Pin_4);//时刻检测药品指示，等待发车
		}
		LED1(0);
		SysTick_Delay_ms(1000);
		LED1(1);
		GPIO_ResetBits(LED1_GPIO_PORT, GPIO_Pin_14);
		//返回 
		Set_Pwm(-MotorDuty, -MotorDuty);//倒车
		SysTick_Delay_ms(1500);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		TurnRight();
//		TurnLeft();
//		TurnLeft();
		Set_Pwm(0, -0);
		Set_Pwm(-MotorDuty, -MotorDuty);//直行
		SysTick_Delay_ms(2450);
		TurnLeft();
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(7150);
		Set_Pwm(0, 0);
		
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_15);//点绿灯
	}
    
    
}



