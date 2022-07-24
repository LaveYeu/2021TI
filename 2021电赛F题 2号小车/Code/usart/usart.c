#include "usart.h"
#include "led.h"

void Usart_Config(u32 baudrate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(USART_GPIO_CLK, ENABLE);
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_TX_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART_RX_GPIO_PORT, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USARTX, &USART_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(USARTX, USART_IT_RXNE, ENABLE);
	USART_Cmd(USARTX, ENABLE);	    
}

void USART_IRQHandler(void)
{
	static u8 res ;
	if(USART_GetITStatus(USARTX,USART_IT_RXNE)!=RESET)
	{
		res = USART_ReceiveData(USART1);
		if(res == 'A')
		{
			if(Solve==3)
			{
				//立个flag
				GPIO_ResetBits(LED1_GPIO_PORT, GPIO_Pin_14);
				LED1(0);
				SysTick_Delay_ms(5000);
				LED1(1);
				Set_Pwm(-MotorDuty, -MotorDuty);//倒车
						SysTick_Delay_ms(710);
						TurnLeft();
						Set_Pwm(MotorDuty, MotorDuty);//直行
			SysTick_Delay_ms(1400);
				Set_Pwm(0, -0);
				GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_15);
				while(1);
			}
			else
			{
				//立个flag
				GPIO_ResetBits(LED1_GPIO_PORT, GPIO_Pin_14);
				LED1(0);
				SysTick_Delay_ms(5100);
				LED1(1);
				Set_Pwm(-MotorDuty, -MotorDuty);//倒车
						SysTick_Delay_ms(750);
						TurnRight();
						Set_Pwm(MotorDuty, MotorDuty);//直行
			SysTick_Delay_ms(1100);
				Set_Pwm(0, -0);
				GPIO_SetBits(LED1_GPIO_PORT, GPIO_Pin_15);
				while(1);
			}
			
//			OLED_Show_Int(5,5,5,4,12);
			
		}
	}
}

//重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
	USART_SendData(USARTX, (uint8_t) ch);
	while (USART_GetFlagStatus(USARTX, USART_FLAG_TXE) == RESET);		
	return (ch);
}

//重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
	while (USART_GetFlagStatus(USARTX, USART_FLAG_RXNE) == RESET);
	return (int)USART_ReceiveData(USARTX);
}



