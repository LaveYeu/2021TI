#ifndef __OLED_H
#define __OLED_H

#include "headfile.h"


#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64

#define OLED_CMD     0	      //写命令
#define OLED_DATA    1	      //写数据

//OLED IIC端口定义
#define  OLED_GPIO_CLK           RCC_APB2Periph_GPIOB
#define  OLED_SCL_GPIO_PORT      GPIOB
#define  OLED_SCL_GPIO_PIN       GPIO_Pin_1
#define  OLED_SDA_GPIO_PORT      GPIOB
#define  OLED_SDA_GPIO_PIN       GPIO_Pin_0

#define OLED_IIC_SCL(a)     if(a) GPIO_SetBits(OLED_SCL_GPIO_PORT,OLED_SCL_GPIO_PIN);\
                            else  GPIO_ResetBits(OLED_SCL_GPIO_PORT,OLED_SCL_GPIO_PIN)

#define OLED_IIC_SDA(a)     if(a) GPIO_SetBits(OLED_SDA_GPIO_PORT,OLED_SDA_GPIO_PIN);\
                            else  GPIO_ResetBits(OLED_SDA_GPIO_PORT,OLED_SDA_GPIO_PIN)



//坐标设置
void OLED_Set_Pos(unsigned char x, unsigned char y);
//开启OLED显示    
void OLED_Display_On(void);
//关闭OLED显示     
void OLED_Display_Off(void);
//清屏函数,清完屏,整个屏幕是黑色的!
void OLED_Clear(void);
//更新显示
void OLED_On(void);
//OLED初始化
void OLED_Init(void);
//在指定位置显示一个字符
void OLED_Show_Char(u8 x, u8 y, u8 chr, u8 size);
//在指定位置显示一个字符串
void OLED_Show_String(u8 x, u8 y, u8 *chr, u8 size);
//在指定位置显示几位整数(有符号)
void OLED_Show_Int(u8 x, u8 y, int32_t num, u8 len, u8 size);
//在指定位置显示几位整数(无符号)
void OLED_Show_Uint(u8 x, u8 y, u32 num, u8 len, u8 size);
//在指定位置显示几位浮点数
void OLED_Show_Float(u8 x, u8 y, double num, u8 len1, u8 len2, u8 size);



#endif  
	 



