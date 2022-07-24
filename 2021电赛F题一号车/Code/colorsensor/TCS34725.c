
#include "TCS34725.h"
//#include "delay.h"
#include "usart.h"
#include "systick.h"

//IO????
#define SDA1_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=8<<28;}//???????
#define SDA1_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=3<<28;}//???????


//IO????	 
#define IIC1_SCL    PBout(6) //SCL
#define IIC1_SDA    PBout(7) //SDA	 
#define READ1_SDA   PBin(7)  //??SDA 


#define  SDA_TCS34725_IN     {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(uint32_t)8<<28;}  //SET  IN
#define  SDA_TCS34725_OUT    {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(uint32_t)3<<28;} //SET  OUT

#define Read_TCS34725_SDA  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)//?????

#define  SDA_H         GPIO_SetBits  (GPIOB,GPIO_Pin_7)  //?“1”
#define  SDA_L         GPIO_ResetBits(GPIOB,GPIO_Pin_7)   //?“0”
#define  SCL_H         GPIO_SetBits  (GPIOB,GPIO_Pin_6)   //?“1”
#define  SCL_L         GPIO_ResetBits(GPIOB,GPIO_Pin_6)  //?“0”
//????
_TCS3472_HSL _TCS3472_HSL_DATA;
//????
void Color_tcs34725_Init(void);
void TCS34725_Write_addr(u8 Address, u8 dat);
u8 TCS34725_Read_addr(u8 Address);
void Capture_RGB(void);
void White_Banlance_Init(void);
void Printf_ColorRGB(void);
//????
void I2CStart(void);
void I2Cask(void);
void I2CStop(void);
void I2CWrByte(u8 oneByte);
void IIC_MASTERACK (void);

/*************************************************
             I2C????
*************************************************/
//???????
void Port_Init(void) //IO???
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOB,ENABLE);//??PORTA,PORTE??
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

void I2CStart(void)//????
{
		SDA_TCS34725_OUT;
    SCL_H;
    SysTick_Delay_us(5);
    SDA_H;
    SysTick_Delay_us(5);
    SDA_L;
    SysTick_Delay_us(5);
    SCL_L;
}
void I2CStop(void) //????
{
		SDA_TCS34725_OUT;
    SDA_L;
    SysTick_Delay_us(5);
    SCL_H;
    SysTick_Delay_us(5);
    SDA_H;
    SysTick_Delay_us(5);
    SCL_L;
    SysTick_Delay_us(5);
    SDA_L;
    SysTick_Delay_us(5);
}

void I2Cask(void) //ACK??
{
    u8 timeout = 1;
    SDA_TCS34725_IN;          //SDA?????
    SCL_L;
    while((Read_TCS34725_SDA) && (timeout <= 10)) //??SDA??‘0’??
    {
        timeout++;
    }
    SCL_H;
    SysTick_Delay_us(5);
    SCL_L;
    SDA_TCS34725_OUT;          //SDA?????
}
/*******************************************************************************
* ? ? ?         :IIC_MASTERACK()
* ????         :MCU????        
* ?    ?         :?
* ?    ?         :?
*******************************************************************************/ 
void IIC_MASTERACK (void)//????
{
  
		SDA_TCS34725_OUT;    
    SCL_L;
    SysTick_Delay_us(5);
    SDA_L;
    SysTick_Delay_us(5);
    SCL_H;
    SysTick_Delay_us(5);
    SCL_L;
    SysTick_Delay_us(5);      
}
void I2CWrByte(u8 oneByte) //?????????,????
{
    u8 i;
		SDA_TCS34725_OUT;
    SCL_L;
    for(i = 0; i < 8; i++)
    {
        if(oneByte & 0x80)
            SDA_H;
        else
            SDA_L;

        SysTick_Delay_us(5);
        SCL_H;
        SysTick_Delay_us(5);
        SCL_L;
        oneByte <<= 1;
    }
}
u8 I2CReadByte() //?????????,????
{
    u8 dat, i;
    dat = 0;
    SDA_TCS34725_IN;          //SDA?????		
    SCL_L;
    for(i = 0; i < 8; i++)
    {
        SCL_H;
        dat = dat << 1;
        if(Read_TCS34725_SDA)
        {
            dat++;
        }
        SysTick_Delay_us(5);
        SCL_L;
        SysTick_Delay_us(5);
    }
		SDA_TCS34725_OUT;
    return dat ;
}

void TCS34725_Write_addr(u8 Address,u8 dat) //
{
    I2CStart();
    I2CWrByte(COLOR_ADDR_Device); 
    I2Cask();
    I2CWrByte(Address);	
    I2Cask();
    I2CWrByte(dat);
    I2Cask();
    I2CStop();
}

u8 TCS34725_Read_addr(u8 Address)  //
{
		u8 rev;

    I2CStart();
    I2CWrByte(COLOR_ADDR_Device);
    I2Cask();
		I2CWrByte(Address);
		I2Cask();
		I2CStart();
		I2CWrByte(COLOR_ADDR_Device|0x01);	
    I2Cask();
		rev = I2CReadByte();
    I2CStop();
    return(rev);
}

_RGBC_V RGB_V;
void Capture_RGB(void)
{
	u8 i,count=3;
	u8 status;
	u16 tt[4];
	u32 r=0,g=0,b=0,c=0;
	TCS34725_Write_addr(COLOR_ADDR_WTIME,0xFF);		//??????2.4ms
	TCS34725_Write_addr(COLOR_ADDR_ATIME,0xF6);		//??????
	TCS34725_Write_addr(COLOR_ADDR_CONTROL,0x02);	//RGB???????	
	for(i=0;i<count;i++)
	{
		TCS34725_Write_addr(COLOR_ADDR_ENABLE,0x0B);//??????
		SysTick_Delay_ms(30);//??????
		status = TCS34725_Read_addr(COLOR_ADDR_ENABLE) & ~0x02;
		TCS34725_Write_addr(COLOR_ADDR_ENABLE,status);
		
    I2CStart();
    I2CWrByte(COLOR_ADDR_Device);
    I2Cask();
		I2CWrByte(COLOR_ADDR_CDATAL);
		I2Cask();
		I2CStart();
		I2CWrByte(COLOR_ADDR_Device|0x01);	
		I2Cask();
		tt[0] = I2CReadByte();
		IIC_MASTERACK();
		tt[0] |= I2CReadByte()<<8;
		IIC_MASTERACK();
		tt[1] = I2CReadByte();
		IIC_MASTERACK();
		tt[1] |= I2CReadByte()<<8;
		IIC_MASTERACK();
		tt[2] = I2CReadByte();
		IIC_MASTERACK();
		tt[2] |= I2CReadByte()<<8;
		IIC_MASTERACK();
		tt[3] = I2CReadByte();
		IIC_MASTERACK();
		tt[3] |= I2CReadByte()<<8;
		I2CStop();

		c += tt[0];
		r += tt[1];
		g += tt[2];
		b += tt[3];
	}
	RGB_V.Green = g/count;	
	RGB_V.Blue = b/count;
	RGB_V.Red = r/count;
	RGB_V.Clear = c/count;	
}
//???????
_WhiteBanlance_Gene GENE={451,596,511,1570};		//???
void White_Banlance_Init(void)
{
	Capture_RGB();
	GENE.Rgene = RGB_V.Red;
	GENE.Ggene = RGB_V.Green;
	GENE.Bgene = RGB_V.Blue;
	GENE.Cgene = RGB_V.Clear;
}

_TCS3472_RGBC RGB;
void Printf_ColorRGB(void)
{
	Capture_RGB();
	RGB.Red = RGB_V.Red*255/GENE.Rgene;
	RGB.Green = RGB_V.Green*255/GENE.Ggene;
	RGB.Blue = RGB_V.Blue*255/GENE.Bgene;
	
	if(RGB.Red>255)		RGB.Red = 255;
	if(RGB.Green>255)	RGB.Green = 255;
	if(RGB.Blue>255)	RGB.Blue = 255;	
//	printf("\r\n??=%x,??=%x,??=%x\r\n",RGB.Red,RGB.Green,RGB.Blue);
	
}
void Color_tcs34725_Init(void)
{
	Port_Init();
	TCS34725_Write_addr(COLOR_ADDR_WTIME,0xFF);		//??????2.4ms
	TCS34725_Write_addr(COLOR_ADDR_ATIME,0xF6);		//??????24ms,?????10240
	TCS34725_Write_addr(COLOR_ADDR_CONTROL,0x02);	//RGB???????
	TCS34725_Write_addr(COLOR_ADDR_ENABLE,0x09);	//??????
}
