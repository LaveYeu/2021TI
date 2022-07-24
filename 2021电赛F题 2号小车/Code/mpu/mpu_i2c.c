#include "mpu_i2c.h"




static void MPU_IIC_Delay(void)
{
	Delay_us(2);
}

void MPU_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(MPU_GPIO_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = MPU_SCL_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(MPU_SCL_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(MPU_SCL_GPIO_PORT, MPU_SCL_GPIO_PIN);

	GPIO_InitStructure.GPIO_Pin = MPU_SDA_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(MPU_SDA_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(MPU_SDA_GPIO_PORT, MPU_SDA_GPIO_PIN);
}

void MPU_IIC_Start(void)
{
	/* 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 */
	MPU_SDA_OUT();
	MPU_IIC_SDA(1);
	MPU_IIC_SCL(1);
	MPU_IIC_Delay();
	MPU_IIC_SDA(0);
	MPU_IIC_Delay();
	MPU_IIC_SCL(0);
	MPU_IIC_Delay();
}

void MPU_IIC_Stop(void)
{
	/* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */
	MPU_SDA_OUT();
	MPU_IIC_SCL(0);
	MPU_IIC_SDA(0);
	MPU_IIC_Delay();
	MPU_IIC_SCL(1);
	MPU_IIC_SDA(1);
	MPU_IIC_Delay();
}

void MPU_IIC_Ack(void)
{
	MPU_IIC_SCL(0);
	MPU_SDA_OUT();
	MPU_IIC_SDA(0);	/* CPU驱动SDA = 0 */
	MPU_IIC_Delay();
	MPU_IIC_SCL(1);	/* CPU产生1个时钟 */
	MPU_IIC_Delay();
	MPU_IIC_SCL(0);
	MPU_IIC_Delay();
}

void MPU_IIC_NAck(void)
{
	MPU_IIC_SCL(0);
	MPU_SDA_OUT();
	MPU_IIC_SDA(1);	/* CPU驱动SDA = 1 */
	MPU_IIC_Delay();
	MPU_IIC_SCL(1);	/* CPU产生1个时钟 */
	MPU_IIC_Delay();
	MPU_IIC_SCL(0);
	MPU_IIC_Delay();	
}

void MPU_IIC_SendByte(u8 _ucByte)
{
	u8 i;

	MPU_SDA_OUT();
	MPU_IIC_SCL(0);

	/* 先发送字节的高位bit7 */
	for (i = 0; i < 8; i++)
	{		
		if (_ucByte & 0x80)
		{
			MPU_IIC_SDA(1);
		}
		else
		{
			MPU_IIC_SDA(0);
		}
		MPU_IIC_Delay();
		MPU_IIC_SCL(1);
		MPU_IIC_Delay();	
		MPU_IIC_SCL(0);
		if (i == 7)
		{
			 MPU_IIC_SDA(1); // 释放总线
		}
		_ucByte <<= 1;	/* 左移一个bit */
		MPU_IIC_Delay();
	}
}

u8 MPU_IIC_ReadByte(u8 ack)
{
	u8 i;
	u8 value = 0;

	MPU_SDA_IN();

	/* 读到第1个bit为数据的bit7 */
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		MPU_IIC_SCL(0);
		MPU_IIC_Delay();
		MPU_IIC_SCL(1);
		MPU_IIC_Delay();
		if (MPU_IIC_SDA_READ())
		{
			value++;
		}
		MPU_IIC_SCL(0);
		MPU_IIC_Delay();
	}
	if(ack==0)
		MPU_IIC_NAck();
	else
		MPU_IIC_Ack();
	return value;
}

u8 MPU_IIC_WaitAck(void)
{
	u8 re;

	MPU_SDA_IN();

	MPU_IIC_SDA(1);	/* CPU释放SDA总线 */
	MPU_IIC_Delay();
	MPU_IIC_SCL(1);	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	MPU_IIC_Delay();
	if (MPU_IIC_SDA_READ())	/* CPU读取SDA口线状态 */
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
	MPU_IIC_SCL(0);
	MPU_IIC_Delay();
	return re;
}


//IIC写一个字节 
//reg:寄存器地址 data:数据 返回值:0,正常 其他,错误
u8 MPU_Write_Byte(u8 reg,u8 data) 				 
{ 
    MPU_IIC_Start(); 
	MPU_IIC_SendByte((MPU_ADDR<<1)|0);//发送器件地址+写命令	
	if(MPU_IIC_WaitAck())	//等待应答
	{
		MPU_IIC_Stop();		 
		return 1;		
	}
    MPU_IIC_SendByte(reg);	//写寄存器地址
    MPU_IIC_WaitAck();		//等待应答 
	MPU_IIC_SendByte(data);//发送数据
	if(MPU_IIC_WaitAck())	//等待ACK
	{
		MPU_IIC_Stop();	 
		return 1;		 
	}		 
    MPU_IIC_Stop();	 
	return 0;
}
//IIC读一个字节 
//reg:寄存器地址 返回值:读到的数据
u8 MPU_Read_Byte(u8 reg)
{
	u8 res;
    MPU_IIC_Start(); 
	MPU_IIC_SendByte((MPU_ADDR<<1)|0);//发送器件地址+写命令	
	MPU_IIC_WaitAck();		//等待应答 
    MPU_IIC_SendByte(reg);	//写寄存器地址
    MPU_IIC_WaitAck();		//等待应答
    MPU_IIC_Start();
	MPU_IIC_SendByte((MPU_ADDR<<1)|1);//发送器件地址+读命令	
    MPU_IIC_WaitAck();		//等待应答 
	res=MPU_IIC_ReadByte(0);//读取数据,发送nACK 
    MPU_IIC_Stop();			//产生一个停止条件 
	return res;		
}
//IIC连续写
//addr:器件地址 reg:寄存器地址 len:写入长度 buf:数据区 返回值:0,正常 其他,错误
u8 MPU_Write_Len(u8 addr, u8 reg, u8 len, u8 *buf)
{
	u8 i; 
    MPU_IIC_Start(); 
	MPU_IIC_SendByte((addr<<1)|0);//发送器件地址+写命令	
	if(MPU_IIC_WaitAck())	//等待应答
	{
		MPU_IIC_Stop();		 
		return 1;		
	}
    MPU_IIC_SendByte(reg);	//写寄存器地址
    MPU_IIC_WaitAck();		//等待应答
	for(i=0;i<len;i++)
	{
		MPU_IIC_SendByte(buf[i]);	//发送数据
		if(MPU_IIC_WaitAck())		//等待ACK
		{
			MPU_IIC_Stop();	 
			return 1;		 
		}		
	}    
    MPU_IIC_Stop();	 
	return 0;	
} 
//IIC连续读
//addr:器件地址 reg:寄存器地址 len:读取长度 buf:数据区 返回值:0,正常 其他,错误
u8 MPU_Read_Len(u8 addr, u8 reg, u8 len, u8 *buf)
{ 
 	MPU_IIC_Start(); 
	MPU_IIC_SendByte((addr<<1)|0);//发送器件地址+写命令	
	if(MPU_IIC_WaitAck())	//等待应答
	{
		MPU_IIC_Stop();		 
		return 1;		
	}
    MPU_IIC_SendByte(reg);	//写寄存器地址
    MPU_IIC_WaitAck();		//等待应答
    MPU_IIC_Start();
	MPU_IIC_SendByte((addr<<1)|1);//发送器件地址+读命令	
    MPU_IIC_WaitAck();		//等待应答 
	while(len)
	{
		if(len==1)
		*buf=MPU_IIC_ReadByte(0);   //读数据,发送nACK 
		else 
		*buf=MPU_IIC_ReadByte(1);   //读数据,发送ACK  
		len--;
		buf++; 
	}    
    MPU_IIC_Stop();	//产生一个停止条件 
	return 0;	
}






