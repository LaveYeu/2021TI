#include "key.h"


void Key_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK, ENABLE);	
	GPIO_InitStruct.GPIO_Pin = KEY1_INT_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;		
	GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStruct);
	
	RCC_APB2PeriphClockCmd(KEY2_INT_GPIO_CLK, ENABLE);	
	GPIO_InitStruct.GPIO_Pin = KEY2_INT_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;		
	GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStruct);
	
	RCC_APB2PeriphClockCmd(KEY3_INT_GPIO_CLK, ENABLE);	
	GPIO_InitStruct.GPIO_Pin = KEY3_INT_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;		
	GPIO_Init(KEY3_INT_GPIO_PORT, &GPIO_InitStruct);
	
	RCC_APB2PeriphClockCmd(KEY4_INT_GPIO_CLK, ENABLE);	
	GPIO_InitStruct.GPIO_Pin = KEY4_INT_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;		
	GPIO_Init(KEY4_INT_GPIO_PORT, &GPIO_InitStruct);
}

uint8_t Key_Scan(uint8_t ctns)
{
    static u8 key = 1;

    if( (GPIO_READ_KET1==0 | GPIO_READ_KET2==0 | GPIO_READ_KET3==0 | GPIO_READ_KET4==0) && key==1 )
    {
        Delay_ms(10);
        key = 0;
        
        if (GPIO_READ_KET1 == 0)
        return Key1;
        if (GPIO_READ_KET2 == 0)
        return Key2;
        if (GPIO_READ_KET3 == 0)
        return Key3;
        if (GPIO_READ_KET4 == 0)
        return Key4;
    }
    
    if((GPIO_READ_KET1==1 && GPIO_READ_KET2==1 && GPIO_READ_KET3==1 && GPIO_READ_KET4==1) | ctns==1)
    key = 1;
    return 0;
}






