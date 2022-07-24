

/*--------------------------------------------------------------------------
                ???????????
--------------------------------------------------------------------------*/
#ifndef __TCS34725_H
#define __TCS34725_H
#include "sys.h"
//
#define COLOR_ADDR_Device					0X52	//??????
#define COLOR_ADDR_ENABLE					0XA0
#define COLOR_ADDR_ATIME					0XA1
#define COLOR_ADDR_WTIME					0XA3
#define COLOR_ADDR_AILTL					0XA4
#define COLOR_ADDR_AILTH					0XA5
#define COLOR_ADDR_AIHTL					0XA6
#define COLOR_ADDR_AIHTH					0XA7
#define COLOR_ADDR_PERS						0XAC
#define COLOR_ADDR_CONFIG					0XAD
#define COLOR_ADDR_CONTROL				0XAF
#define COLOR_ADDR_ID							0XB2		
#define COLOR_ADDR_STATUS					0XB3
#define COLOR_ADDR_CDATAL					0XB4
#define COLOR_ADDR_CDATAH					0XB5
#define COLOR_ADDR_RDATAL					0XB6
#define COLOR_ADDR_RDATAH					0XB7
#define COLOR_ADDR_GDATAL					0XB8
#define COLOR_ADDR_GDATAH					0XB9
#define COLOR_ADDR_BDATAL					0XBA
#define COLOR_ADDR_BDATAH					0XBB
typedef struct
{
	float hue;
	float saturation;
	float luminance;
}_TCS3472_HSL;		//?????????????
typedef struct
{
	u16 Red;
	u16 Green;
	u16 Blue;
	u16 Clear;
}_TCS3472_RGBC;				//?????RGB?
typedef struct
{
	u16 Rgene;
	u16 Ggene;
	u16 Bgene;
	u16 Cgene;
}_WhiteBanlance_Gene;		//???ADC?
typedef struct
{
	u16 Red;
	u16 Green;
	u16 Blue;
	u16 Clear;
}_RGBC_V;							//?????ADC?
extern _TCS3472_RGBC RGB;									//???????RGB??
extern _WhiteBanlance_Gene GENE;					//???????3??
extern _RGBC_V RGB_V;											//?????RGB?ADC?
extern _TCS3472_HSL _TCS3472_HSL_DATA;		//????
//????
extern void Color_tcs34725_Init(void);		//???
extern u8 TCS34725_Read_addr(u8 Address);	//??????????
extern void TCS34725_Write_addr(u8 Address,u8 dat);	//???????
extern void White_Banlance_Init(void);							//????????
extern void Printf_ColorRGB(void);									//??????RGB????
void Capture_RGB(void);
#endif
