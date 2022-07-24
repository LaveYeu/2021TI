/**
* @owner        Sharkespeara
* @file         VOFA.H
* @brief        VOFA上位机头文件
* @details      
* @par History  见如下说明
*          
*/

#ifndef __VOFA_H
#define __VOFA_H
 #include "sys.h"
 
extern unsigned char tail[4];

	
void fasong(float lk);
void vofa1(float one);
void vofa2(float one,float two);
void vofa3(float one,float two,float three);
void vofa4(float one,float two,float three,float four);
 
#endif 



