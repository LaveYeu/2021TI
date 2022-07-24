
#include "TCS34725111.h"
#include "systick.h"
#include "usart.h"

//IO方向设置
#define SDA1_IN1()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}//配置为输入模式
#define SDA1_OUT1() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}//配置为输出模式


//IO操作函数	 
#define IIC1_SCL1    PBout(10) //SCL
#define IIC1_SDA1    PBout(11) //SDA	 
#define READ1_SDA1   PBin(11)  //输入SDA 


#define  SDA_TCS34725_IN1     {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}  //SET  IN
#define  SDA_TCS34725_OUT1    {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;} //SET  OUT

#define Read_TCS34725_SDA1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)//读取数据值

#define  SDA_H1        GPIO_SetBits  (GPIOB,GPIO_Pin_11)  //置“1”
#define  SDA_L1         GPIO_ResetBits(GPIOB,GPIO_Pin_11)   //清“0”
#define  SCL_H1         GPIO_SetBits  (GPIOB,GPIO_Pin_10)   //置“1”
#define  SCL_L1         GPIO_ResetBits(GPIOB,GPIO_Pin_10)  //清“0”
//参数定义
_TCS3472_HSL _TCS3472_HSL_DATA1;
//函数声明
void Color_tcs34725_Init1(void);
void TCS34725_Write_addr1(u8 Address, u8 dat);
u8 TCS34725_Read_addr1(u8 Address);
void Capture_RGB1(void);
void White_Banlance_Init1(void);
void Printf_ColorRGB1(void);
//内部函数
void I2CStart1(void);
void I2Cask1(void);
void I2CStop1(void);
void I2CWrByte1(u8 oneByte);
void IIC_MASTERACK1(void);

/*************************************************
             I2C控制函数
*************************************************/
//按键初始化函数
void Port_Init1(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOB,ENABLE);//使能PORTA,PORTE时钟
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

void I2CStart1(void)//开始信号
{
		SDA_TCS34725_OUT1;
    SCL_H1;
    SysTick_Delay_us(5);
    SDA_H1;
    SysTick_Delay_us(5);
    SDA_L1;
    SysTick_Delay_us(5);
    SCL_L1;
}
void I2CStop1(void) //停止信号
{
		SDA_TCS34725_OUT1;
    SDA_L1;
    SysTick_Delay_us(5);
    SCL_H1;
    SysTick_Delay_us(5);
    SDA_H1;
    SysTick_Delay_us(5);
    SCL_L1;
    SysTick_Delay_us(5);
    SDA_L1;
    SysTick_Delay_us(5);
}

void I2Cask1(void) //ACK信号
{
    u8 timeout = 1;
    SDA_TCS34725_IN1;          //SDA转换为输入
    SCL_L1;
    while((Read_TCS34725_SDA1) && (timeout <= 10)) //等待SDA返回‘0’电平
    {
        timeout++;
    }
    SCL_H1;
    SysTick_Delay_us(5);
    SCL_L1;
    SDA_TCS34725_OUT1;          //SDA转换为输出
}
/*******************************************************************************
* 函 数 名         :IIC_MASTERACK()
* 函数功能         :MCU应答信号        
* 输    入         :无
* 输    出         :无
*******************************************************************************/ 
void IIC_MASTERACK1(void)//答应信号
{
  
		SDA_TCS34725_OUT1;    
    SCL_L1;
    SysTick_Delay_us(5);
    SDA_L1;
    SysTick_Delay_us(5);
    SCL_H1;
    SysTick_Delay_us(5);
    SCL_L1;
    SysTick_Delay_us(5);      
}
void I2CWrByte1(u8 oneByte) //写一个字节高位在前，低位在后
{
    u8 i;
		SDA_TCS34725_OUT1;
    SCL_L1;
    for(i = 0; i < 8; i++)
    {
        if(oneByte & 0x80)
            SDA_H1;
        else
            SDA_L1;

        SysTick_Delay_us(5);
        SCL_H1;
        SysTick_Delay_us(5);
        SCL_L1;
        oneByte <<= 1;
    }
}
u8 I2CReadByte1() //写一个字节高位在前，低位在后
{
    u8 dat, i;
    dat = 0;
    SDA_TCS34725_IN1;          //SDA转换为输入		
    SCL_L1;
    for(i = 0; i < 8; i++)
    {
        SCL_H1;
        dat = dat << 1;
        if(Read_TCS34725_SDA1)
        {
            dat++;
        }
        SysTick_Delay_us(5);
        SCL_L1;
        SysTick_Delay_us(5);
    }
		SDA_TCS34725_OUT1;
    return dat ;
}

void TCS34725_Write_addr1(u8 Address,u8 dat) //
{
    I2CStart1();
    I2CWrByte1(COLOR_ADDR_Device); 
    I2Cask1();
    I2CWrByte1(Address);	
    I2Cask1();
    I2CWrByte1(dat);
    I2Cask1();
    I2CStop1();
}

u8 TCS34725_Read_addr1(u8 Address)  //
{
		u8 rev;

    I2CStart1();
    I2CWrByte1(COLOR_ADDR_Device);
    I2Cask1();
		I2CWrByte1(Address);
		I2Cask1();
		I2CStart1();
		I2CWrByte1(COLOR_ADDR_Device|0x01);	
    I2Cask1();
		rev = I2CReadByte1();
    I2CStop1();
    return(rev);
}

_RGBC_V RGB_V1;
void Capture_RGB1(void)
{
	u8 i,count=3;
	u8 status;
	u16 tt[4];
	u32 r=0,g=0,b=0,c=0;
	TCS34725_Write_addr1(COLOR_ADDR_WTIME,0xFF);		//设置等待时间2.4ms
	TCS34725_Write_addr1(COLOR_ADDR_ATIME,0xF6);		//设置计数时间
	TCS34725_Write_addr1(COLOR_ADDR_CONTROL,0x02);	//RGB值增益倍数设置	
	for(i=0;i<count;i++)
	{
		TCS34725_Write_addr1(COLOR_ADDR_ENABLE,0x0B);//开启数据采集
		SysTick_Delay_ms(30);//延时需要加上
		status = TCS34725_Read_addr1(COLOR_ADDR_ENABLE) & ~0x02;
		TCS34725_Write_addr1(COLOR_ADDR_ENABLE,status);
		
    I2CStart1();
    I2CWrByte1(COLOR_ADDR_Device);
    I2Cask1();
		I2CWrByte1(COLOR_ADDR_CDATAL);
		I2Cask1();
		I2CStart1();
		I2CWrByte1(COLOR_ADDR_Device|0x01);	
		I2Cask1();
		tt[0] = I2CReadByte1();
		IIC_MASTERACK1();
		tt[0] |= I2CReadByte1()<<8;
		IIC_MASTERACK1();
		tt[1] = I2CReadByte1();
		IIC_MASTERACK1();
		tt[1] |= I2CReadByte1()<<8;
		IIC_MASTERACK1();
		tt[2] = I2CReadByte1();
		IIC_MASTERACK1();
		tt[2] |= I2CReadByte1()<<8;
		IIC_MASTERACK1();
		tt[3] = I2CReadByte1();
		IIC_MASTERACK1();
		tt[3] |= I2CReadByte1()<<8;
		I2CStop1();

		c += tt[0];
		r += tt[1];
		g += tt[2];
		b += tt[3];
	}
	RGB_V1.Green = g/count;	
	RGB_V1.Blue = b/count;
	RGB_V1.Red = r/count;
	RGB_V1.Clear = c/count;	
}
//白平衡数据采集
_WhiteBanlance_Gene GENE1={451,596,511,1570};		//初始值
void White_Banlance_Init1(void)
{
	Capture_RGB1();
	GENE1.Rgene = RGB_V1.Red;
	GENE1.Ggene = RGB_V1.Green;
	GENE1.Bgene = RGB_V1.Blue;
	GENE1.Cgene = RGB_V1.Clear;
}

_TCS3472_RGBC RGB1;
void Printf_ColorRGB1(void)
{
	Capture_RGB1();
	RGB1.Red = RGB_V1.Red*255/GENE.Rgene;
	RGB1.Green = RGB_V1.Green*255/GENE.Ggene;
	RGB1.Blue = RGB_V1.Blue*255/GENE.Bgene;
	
	if(RGB1.Red>255)		RGB1.Red = 255;
	if(RGB1.Green>255)	RGB1.Green = 255;
	if(RGB1.Blue>255)	RGB1.Blue = 255;	
	printf("\r\n红色=%x，绿色=%x,蓝色=%x\r\n",RGB1.Red,RGB1.Green,RGB1.Blue);
	
}
void Color_tcs34725_Init1(void)
{
	Port_Init1();
	TCS34725_Write_addr1(COLOR_ADDR_WTIME,0xFF);		//设置等待时间2.4ms
	TCS34725_Write_addr1(COLOR_ADDR_ATIME,0xF6);		//设置计数时间24ms，最大计数值10240
	TCS34725_Write_addr1(COLOR_ADDR_CONTROL,0x02);	//RGB值增益倍数设置
	TCS34725_Write_addr1(COLOR_ADDR_ENABLE,0x09);	//关闭采集通道
}
