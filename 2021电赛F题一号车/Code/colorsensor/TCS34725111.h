

/*--------------------------------------------------------------------------
                �����������ȫ�ֱ�����
--------------------------------------------------------------------------*/
#ifndef __TCS34725111_H
#define __TCS34725111_H
#include "sys.h"
#include "TCS34725.h"

extern _TCS3472_RGBC RGB1;									//�洢ת�������RGB��ֵ
extern _WhiteBanlance_Gene GENE1;					//��ƽ���ȡʱ��3ɫֵ
extern _RGBC_V RGB_V1;											//��ǰ��ȡ��RGB��ADCֵ
extern _RGBC_V RGB_V1;											//��ǰ��ȡ��RGB��ADCֵ
extern _TCS3472_HSL _TCS3472_HSL_DATA1;		//��������
//��������
extern void Color_tcs34725_Init1(void);		//��ʼ��
extern u8 TCS34725_Read_addr1(u8 Address);	//��ȡָ���Ĵ���������
extern void TCS34725_Write_addr1(u8 Address,u8 dat);	//����ָ���Ĵ���
extern void White_Banlance_Init1(void);							//��ƽ���ʼ������
extern void Printf_ColorRGB1(void);									//ת�������ǰRGB������ֵ
extern void Capture_RGB1(void);

#endif
