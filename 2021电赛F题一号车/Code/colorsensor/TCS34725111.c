
#include "TCS34725111.h"
#include "systick.h"
#include "usart.h"

//IO��������
#define SDA1_IN1()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}//����Ϊ����ģʽ
#define SDA1_OUT1() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}//����Ϊ���ģʽ


//IO��������	 
#define IIC1_SCL1    PBout(10) //SCL
#define IIC1_SDA1    PBout(11) //SDA	 
#define READ1_SDA1   PBin(11)  //����SDA 


#define  SDA_TCS34725_IN1     {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}  //SET  IN
#define  SDA_TCS34725_OUT1    {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;} //SET  OUT

#define Read_TCS34725_SDA1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)//��ȡ����ֵ

#define  SDA_H1        GPIO_SetBits  (GPIOB,GPIO_Pin_11)  //�á�1��
#define  SDA_L1         GPIO_ResetBits(GPIOB,GPIO_Pin_11)   //�塰0��
#define  SCL_H1         GPIO_SetBits  (GPIOB,GPIO_Pin_10)   //�á�1��
#define  SCL_L1         GPIO_ResetBits(GPIOB,GPIO_Pin_10)  //�塰0��
//��������
_TCS3472_HSL _TCS3472_HSL_DATA1;
//��������
void Color_tcs34725_Init1(void);
void TCS34725_Write_addr1(u8 Address, u8 dat);
u8 TCS34725_Read_addr1(u8 Address);
void Capture_RGB1(void);
void White_Banlance_Init1(void);
void Printf_ColorRGB1(void);
//�ڲ�����
void I2CStart1(void);
void I2Cask1(void);
void I2CStop1(void);
void I2CWrByte1(u8 oneByte);
void IIC_MASTERACK1(void);

/*************************************************
             I2C���ƺ���
*************************************************/
//������ʼ������
void Port_Init1(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PORTA,PORTEʱ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

void I2CStart1(void)//��ʼ�ź�
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
void I2CStop1(void) //ֹͣ�ź�
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

void I2Cask1(void) //ACK�ź�
{
    u8 timeout = 1;
    SDA_TCS34725_IN1;          //SDAת��Ϊ����
    SCL_L1;
    while((Read_TCS34725_SDA1) && (timeout <= 10)) //�ȴ�SDA���ء�0����ƽ
    {
        timeout++;
    }
    SCL_H1;
    SysTick_Delay_us(5);
    SCL_L1;
    SDA_TCS34725_OUT1;          //SDAת��Ϊ���
}
/*******************************************************************************
* �� �� ��         :IIC_MASTERACK()
* ��������         :MCUӦ���ź�        
* ��    ��         :��
* ��    ��         :��
*******************************************************************************/ 
void IIC_MASTERACK1(void)//��Ӧ�ź�
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
void I2CWrByte1(u8 oneByte) //дһ���ֽڸ�λ��ǰ����λ�ں�
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
u8 I2CReadByte1() //дһ���ֽڸ�λ��ǰ����λ�ں�
{
    u8 dat, i;
    dat = 0;
    SDA_TCS34725_IN1;          //SDAת��Ϊ����		
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
	TCS34725_Write_addr1(COLOR_ADDR_WTIME,0xFF);		//���õȴ�ʱ��2.4ms
	TCS34725_Write_addr1(COLOR_ADDR_ATIME,0xF6);		//���ü���ʱ��
	TCS34725_Write_addr1(COLOR_ADDR_CONTROL,0x02);	//RGBֵ���汶������	
	for(i=0;i<count;i++)
	{
		TCS34725_Write_addr1(COLOR_ADDR_ENABLE,0x0B);//�������ݲɼ�
		SysTick_Delay_ms(30);//��ʱ��Ҫ����
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
//��ƽ�����ݲɼ�
_WhiteBanlance_Gene GENE1={451,596,511,1570};		//��ʼֵ
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
	printf("\r\n��ɫ=%x����ɫ=%x,��ɫ=%x\r\n",RGB1.Red,RGB1.Green,RGB1.Blue);
	
}
void Color_tcs34725_Init1(void)
{
	Port_Init1();
	TCS34725_Write_addr1(COLOR_ADDR_WTIME,0xFF);		//���õȴ�ʱ��2.4ms
	TCS34725_Write_addr1(COLOR_ADDR_ATIME,0xF6);		//���ü���ʱ��24ms��������ֵ10240
	TCS34725_Write_addr1(COLOR_ADDR_CONTROL,0x02);	//RGBֵ���汶������
	TCS34725_Write_addr1(COLOR_ADDR_ENABLE,0x09);	//�رղɼ�ͨ��
}
