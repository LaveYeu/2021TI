#include "headfile.h"


u8 ii = 0;
int main(void)
{
//	int16_t dd,ff;
    //初始化
    Config();

	//选择方案
	Loop_Run();

	int blueteeth = 0;
	static u8 res1 ;
	
	
	while(ii==0)
		{
			ii = Check_Medicine(GPIOA,GPIO_Pin_4);//时刻检测药品指示，等待发车
		}
		LED1(0);
		SysTick_Delay_ms(1000);
		LED1(1);
	SysTick_Delay_ms(200);
	
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
		}
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
		SysTick_Delay_ms(5600);
		Set_Pwm(0, 0);
		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_14);
		SysTick_Delay_ms(100);
		
		while(blueteeth==0)
		{
			if(USART_GetITStatus(USARTX,USART_IT_RXNE)!=RESET)
			{
//				OLED_Show_String(0, 0, "SUCCESS ERROR", 12);
//				LED1(0);
//					SysTick_Delay_ms(1000);
//					LED1(1);
//				break;
//				blueteeth = 1;
//				blueteeth = 1;
//				res1 = USART_ReceiveData(USART1);
//				if(res1 == 'A')
//				{
					
					//立个flag
//					LED1(0);
//					SysTick_Delay_ms(1000);
//					LED1(1);
//					OLED_Show_String(0, 0, "MPU6050 ERROR", 12);
//					break;
//					SysTick_Delay_ms(4000);
//					Set_Pwm(-MotorDuty, -MotorDuty);//倒车
//					SysTick_Delay_ms(1500);
//					TurnLeft();
//					Set_Pwm(MotorDuty, MotorDuty);//直行
//		SysTick_Delay_ms(1800);
////					OLED_Show_Int(5,5,5,4,12);
//					
//				}
				LED1(0);
					SysTick_Delay_ms(1000);
					LED1(1);
			}
			OLED_Show_String(0, 0, "WAIT BLUE", 12);
		}
//		LED1(0);
//					SysTick_Delay_ms(1000);
//					LED1(1);
////		TurnLeft();
//		Set_Pwm(0, 0);
//		Set_Pwm(MotorDuty, MotorDuty);//直行
//		SysTick_Delay_ms(1500);
//		Set_Pwm(0, -0);
//		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_14);//点红灯等待卸药品
//		ii = Check_Medicine(GPIOA,GPIO_Pin_4);
//		while(ii==1)
//		{
//			ii = Check_Medicine(GPIOA,GPIO_Pin_4);//时刻检测药品指示，等待发车
//		}
//		GPIO_ResetBits(LED1_GPIO_PORT, GPIO_Pin_14);
//		//返回 
//		Set_Pwm(-MotorDuty, -MotorDuty);//倒车
//		SysTick_Delay_ms(1500);
//		Set_Pwm(0, 0);
//		SysTick_Delay_ms(100);
//		TurnLeft();
//		Set_Pwm(0, -0);
//		Set_Pwm(MotorDuty, MotorDuty);//直行
//		SysTick_Delay_ms(4500);
//		Set_Pwm(0, 0);
//		GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_15);//点绿灯
	}
	
	
	if(Solve==4)//D病房
	{
		Set_Pwm(MotorDuty, MotorDuty);//直行
		SysTick_Delay_ms(5600);
		Set_Pwm(0, 0);
		SysTick_Delay_ms(100);
		while(blueteeth==0)
		{
			if(USART_GetITStatus(USARTX,USART_IT_RXNE)!=RESET)
			{
				OLED_Show_String(0, 0, "SUCCESS ERROR", 12);
				LED1(0);
					SysTick_Delay_ms(1000);
					LED1(1);
				break;
				blueteeth = 1;
				blueteeth = 1;
				res1 = USART_ReceiveData(USART1);
				if(res1 == 'A')
				{
//					
//					//立个flag
//					LED1(0);
//					SysTick_Delay_ms(1000);
//					LED1(1);
//					OLED_Show_String(0, 0, "MPU6050 ERROR", 12);
//					break;
//					SysTick_Delay_ms(4000);
//					Set_Pwm(-MotorDuty, -MotorDuty);//倒车
//					SysTick_Delay_ms(1500);
//					TurnLeft();
//					Set_Pwm(MotorDuty, MotorDuty);//直行
//		SysTick_Delay_ms(1800);
////					OLED_Show_Int(5,5,5,4,12);
					
				}
				LED1(0);
					SysTick_Delay_ms(1000);
					LED1(1);
			}
			OLED_Show_String(0, 0, "WAIT BLUE", 12);
		}
	}
    
    
}



