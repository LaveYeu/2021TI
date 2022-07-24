#include "usart1.h"

void Usart1_Config(u32 baudrate)
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
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1X_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(USARTX, USART_IT_RXNE, ENABLE);
	USART_Cmd(USARTX, ENABLE);	    
}

void USART1X_IRQHandler(void)
{
	if(USART_GetITStatus(USART1X,USART_IT_RXNE)!=RESET)
	{
	}
}

////重定向c库函数printf到串口，重定向后可使用printf函数
//int fputc(int ch, FILE *f)
//{
//	USART_SendData(USARTX, (uint8_t) ch);
//	while (USART_GetFlagStatus(USART1X, USART_FLAG_TXE) == RESET);		
//	return (ch);
//}

////重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
//int fgetc(FILE *f)
//{
//	while (USART_GetFlagStatus(USART1X, USART_FLAG_RXNE) == RESET);
//	return (int)USART_ReceiveData(USART1X);
//}



