/**
 * 
* @owner        Sharkespeara
* @file         linewalking.h
* @brief        巡线模式头文件
* @details      
* @par History  见如下说明            
*/
#ifndef _LINEWALKING_H__
#define _LINEWALKING_H__	

#define PIN_1  PCin(1)//K
#define PIN_2  PCin(2)//K
#define PIN_3  PCin(3)//K
#define PIN_4  PCin(5)//K
#define PIN_5  PCin(7)//K
#define PIN_6  PCin(10)//K
#define PIN_7  PCin(11)//K

void LineWalking(void);
void LineWalking_1(void);
void LineWalking_2(void);
void tiaozheng(void);

void green_led(void);
void red_led(void);
void clips(void);
void dete_clips(void);
void reset_led(void);

void recive_signalP3(void);
void recive_signalP2(void);
void recive_signalP9_H(void);
void recive_signalP9_L(void);
void recive_signalP8(void);
void reset_classnumber(void);
void send_signal(void);

void cross_redline(void);
void return_store(void);
void choice_class0(void);
void choice_class1(void);
void choice_class2(void);

#endif
