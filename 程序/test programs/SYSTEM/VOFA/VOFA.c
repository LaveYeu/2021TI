/**
* @owner        Sharkespeara
* @file         VOFA+.c
* @brief        VOFA上位机发送函数
* @details      
* @par History  见如下说明
*          
*/
#include "VOFA.h"


u8 byte[4]={0};    //定义数组
u8 t_test=0;
typedef union
{
	float fdata;
	unsigned long ldata;
}FloatLongType;

void Float_to_Byte(float f,unsigned char byte[])
{
	FloatLongType fl;
	fl.fdata=f;
	byte[0]=(unsigned char)fl.ldata;
	byte[1]=(unsigned char)(fl.ldata>>8);
	byte[2]=(unsigned char)(fl.ldata>>16);
	byte[3]=(unsigned char)(fl.ldata>>24);
}

void vofa1(float one)
{
	unsigned char tail[4] = {0x00,0x00,0x80,0x7f};	

	Float_to_Byte(one*1.0,byte);
	
		for(t_test=0;t_test<4;t_test++)
		{
			USART_SendData(USART1, byte[t_test]);         //向串口1发送数据
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
		}
		USART_SendData(USART1,tail[0]);
	  delay_ms(1);
		USART_SendData(USART1,tail[1]);
	  delay_ms(1);
		USART_SendData(USART1,tail[2]);
	  delay_ms(1);
		USART_SendData(USART1,tail[3]);
	  delay_ms(1);
}

void vofa2(float one,float two)
{
	unsigned char tail[4] = {0x00,0x00,0x80,0x7f};	

	Float_to_Byte(one*1.0,byte);
	
		for(t_test=0;t_test<4;t_test++)
		{
			USART_SendData(USART1, byte[t_test]);         //向串口1发送数据
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
		}
	Float_to_Byte(two*1.0,byte);
		for(t_test=0;t_test<4;t_test++)
		{
			USART_SendData(USART1, byte[t_test]);         //向串口1发送数据
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
		}		
		USART_SendData(USART1,tail[0]);
	  delay_ms(1);
		USART_SendData(USART1,tail[1]);
	  delay_ms(1);
		USART_SendData(USART1,tail[2]);
	  delay_ms(1);
		USART_SendData(USART1,tail[3]);
	  delay_ms(1);
}

void vofa3(float one,float two,float three)
{
	unsigned char tail[4] = {0x00,0x00,0x80,0x7f};	

	Float_to_Byte(one*1.0,byte);
	
		for(t_test=0;t_test<4;t_test++)
		{
			USART_SendData(USART1, byte[t_test]);         //向串口1发送数据
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
		}
	Float_to_Byte(two*1.0,byte);
		for(t_test=0;t_test<4;t_test++)
		{
			USART_SendData(USART1, byte[t_test]);         //向串口1发送数据
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
		}		
	Float_to_Byte(three*1.0,byte);
		for(t_test=0;t_test<4;t_test++)
		{
			USART_SendData(USART1, byte[t_test]);         //向串口1发送数据
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
		}	
		USART_SendData(USART1,tail[0]);
	  delay_ms(1);
		USART_SendData(USART1,tail[1]);
	  delay_ms(1);
		USART_SendData(USART1,tail[2]);
	  delay_ms(1);
		USART_SendData(USART1,tail[3]);
	  delay_ms(1);
}

void vofa4(float one,float two,float three,float four)
{
	unsigned char tail[4] = {0x00,0x00,0x80,0x7f};	

	Float_to_Byte(one*1.0,byte);
	
		for(t_test=0;t_test<4;t_test++)
		{
			USART_SendData(USART1, byte[t_test]);         //向串口1发送数据
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
		}
	Float_to_Byte(two*1.0,byte);
		for(t_test=0;t_test<4;t_test++)
		{
			USART_SendData(USART1, byte[t_test]);         //向串口1发送数据
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
		}		
	Float_to_Byte(three*1.0,byte);
		for(t_test=0;t_test<4;t_test++)
		{
			USART_SendData(USART1, byte[t_test]);         //向串口1发送数据
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
		}	
	Float_to_Byte(four*1.0,byte);
		for(t_test=0;t_test<4;t_test++)
		{
			USART_SendData(USART1, byte[t_test]);         //向串口1发送数据
			while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
		}	
		USART_SendData(USART1,tail[0]);
	  delay_ms(1);
		USART_SendData(USART1,tail[1]);
	  delay_ms(1);
		USART_SendData(USART1,tail[2]);
	  delay_ms(1);
		USART_SendData(USART1,tail[3]);
	  delay_ms(1);
}	






	
	
