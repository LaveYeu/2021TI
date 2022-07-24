

/*--------------------------------------------------------------------------
                主函数定义的全局变量等
--------------------------------------------------------------------------*/
#ifndef __TCS34725111_H
#define __TCS34725111_H
#include "sys.h"
#include "TCS34725.h"

extern _TCS3472_RGBC RGB1;									//存储转换过后的RGB数值
extern _WhiteBanlance_Gene GENE1;					//白平衡读取时的3色值
extern _RGBC_V RGB_V1;											//当前读取的RGB的ADC值
extern _RGBC_V RGB_V1;											//当前读取的RGB的ADC值
extern _TCS3472_HSL _TCS3472_HSL_DATA1;		//亮度数据
//函数声明
extern void Color_tcs34725_Init1(void);		//初始化
extern u8 TCS34725_Read_addr1(u8 Address);	//读取指定寄存器的数据
extern void TCS34725_Write_addr1(u8 Address,u8 dat);	//操作指定寄存器
extern void White_Banlance_Init1(void);							//白平衡初始化函数
extern void Printf_ColorRGB1(void);									//转换输出当前RGB及明亮值
extern void Capture_RGB1(void);

#endif
