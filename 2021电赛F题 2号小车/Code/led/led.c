#include "led.h"

void Led_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(LED1_GPIO_CLK, ENABLE);

	GPIO_InitStruct.GPIO_Pin = LED1_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);
	GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
	GPIO_ResetBits(LED1_GPIO_PORT, GPIO_Pin_14);
}

