/**
* @owner        Sharkespeara
* @file         PID.c
* @brief        PID���ƺ���
* @details      
* @par History  ������˵��
*          
*/

#include "PID.h"
#include "PID_Motor.h"
#include "Linewalking.h"

float RES_PWM1,RES_PWM2;//����PWM���

int speed1=0,speed2=0;

int LAST1 = 0,LAST2 = 0;

void PID_TIM4_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_Period = arr;     //��װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;  //Ԥ��Ƶϵ��
	TIM_TimeBaseInitStruct.TIM_ClockDivision =0; //ʱ�ӷָ�
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);  //ʹ�ܶ�ʱ���ж�
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01; 
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
  NVIC_Init(&NVIC_InitStructure);
 
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);//���TIM�ĸ��±�־λ
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);//ʹ�ܶ�ʱ���ж�

	TIM_Cmd(TIM4,ENABLE);	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************
PID1ֵ��ʼ��
��ڣ�����
���ڣ������PID
****************************/
PID pid1;
void PID_param1_init(void)
 {
     /* ��ʼ������ */
     pid1.target_val = 0;        //Ŀ��ֵ
     pid1.actual_val = 0.0;         //ʵ��ֵ
     pid1.err        = 0;           //����ƫ��ֵ
  	 pid1.output_val = 0;   
     pid1.err_last   = 0.0;         //������һ��ƫ��ֵ
     pid1.integral   = 0.0;         //�������ֵ
     pid1.Kp         = 150;
     pid1.Ki         = 0;
     pid1.Kd         = 50;
	   pid1.tracking_val  = 0;  //ѭ��ƫ����

 }
 
 /*********************************
***********************************/
void PID_TARGET_1(float temp1_val)
{
	pid1.target_val = temp1_val;    // ���õ�ǰ��Ŀ��ֵ
	RES_PWM1 = PID_realize1(LAST1);//ͨ��PID��������PWMֵ
  Load1(RES_PWM1);                //װ��PWMֵ
}
/****************************************************
���PID

��ڣ�Ŀ���ٶ�
���ڣ�ʵ���ٶ�
**************************/
float PID_realize1(float actual1_val)
{
     /*����Ŀ��ֵ��ʵ��ֵ�����*/
    pid1.err = pid1.target_val - actual1_val;
     /*����ۻ�*/
    pid1.integral += pid1.err;
     /*PID�㷨ʵ��*/
    pid1.output_val = (pid1.Kp*pid1.err  + pid1.tracking_val)+
										 pid1.Ki*pid1.integral+
										 pid1.Kd*(pid1.err-pid1.err_last);
     /*����*/
    pid1.err_last = pid1.err;
     /*���ص�ǰʵ��ֵ*/
    return pid1.output_val;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/**************************
PID2ֵ��ʼ��
��ڣ�����
���ڣ������PID
****************************/
PID pid2;
void PID_param2_init(void)
 {
     /* ��ʼ������ */
     pid2.target_val = 0;        //Ŀ��ֵ
     pid2.actual_val = 0.0;         //ʵ��ֵ
     pid2.err        = 0;           //����ƫ��ֵ
  	 pid2.output_val = 0;   
     pid2.err_last   = 0.0;         //������һ��ƫ��ֵ
     pid2.integral   = 0.0;         //�������ֵ
     pid2.Kp         = 150;
     pid2.Ki         = 0;
     pid2.Kd         = 50;
	   pid2.tracking_val  = 0;      //ѭ��ƫ����
 }
void PID_TARGET_2(float temp2_val)
{
	pid2.target_val = temp2_val;    // ���õ�ǰ��Ŀ��ֵ
	RES_PWM2 = PID_realize2(LAST2); //ͨ��PID��������PWMֵ
  Load2(RES_PWM2);                 //װ��PWMֵ
}
/*****************************************************/
/*************************
���PID

��ڣ�Ŀ���ٶ�
���ڣ�ʵ���ٶ�
**************************/
/////////////////////////////////////////////////////////////////
float PID_realize2(float actual2_val)
{
     /*����Ŀ��ֵ��ʵ��ֵ�����*/
    pid2.err = pid2.target_val - actual2_val;
     /*����ۻ�*/
    pid2.integral += pid2.err;
     /*PID�㷨ʵ��*/
    pid2.output_val = (pid2.Kp*pid2.err+pid2.tracking_val)+
										 pid2.Ki*pid2.integral+
										 pid2.Kd*(pid2.err-pid2.err_last);
     /*����*/
    pid2.err_last = pid2.err;
     /*���ص�ǰʵ��ֵ*/
    return pid2.output_val;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
///**************************
//PIDֵ��ʼ��
//��ڣ�����
//���ڣ������PID
//****************************/
//PID pid3;
//void PID_param3_init(void)
// {
//     /* ��ʼ������ */
//     pid3.target_val = 0;        //Ŀ��ֵ
//     pid3.actual_val = 0.0;         //ʵ��ֵ
//     pid3.err        = 0;           //����ƫ��ֵ
//  	 pid3.output_val = 0;   
//     pid3.err_last   = 0.0;         //������һ��ƫ��ֵ
//     pid3.integral   = 0.0;         //�������ֵ
//     pid3.Kp         = 0;
//     pid3.Ki         = 0;
//     pid3.Kd         = 0;
//     pid3.tracking  = 0;         //ѭ��ƫ����
// }
//void PID_TARGET_3(float temp3_val)
//{
//	pid3.target_val = temp3_val;    // ���õ�ǰ��Ŀ��
//	RES_PWM3 = PID_realize3(LAST4);
//  Load3(RES_PWM3);
//}

///***************************************************
//���PID

//��ڣ�Ŀ���ٶ�
//���ڣ�ʵ���ٶ�
//**************************/
//////////////////////////////////////////////////////////////////////
//float PID_realize3(float actual3_val)
//{
//     /*����Ŀ��ֵ��ʵ��ֵ�����*/
//    pid3.err = pid3.target_val - actual3_val;
//     /*����ۻ�*/
//    pid3.integral += pid3.err;
//     /*PID�㷨ʵ��*/
//    pid3.output_val = (pid3.Kp*pid3.err+pid3.tracking)+
//										 pid3.Ki*pid3.integral+
//										 pid3.Kd*(pid3.err-pid3.err_last);
//     /*����*/
//    pid3.err_last = pid3.err;
//     /*���ص�ǰʵ��ֵ*/
//    return pid3.output_val;
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TIM4_IRQHandler(void) //PID�ж���������
{
	 
	if(TIM_GetFlagStatus(TIM4,TIM_FLAG_Update)==SET)//һ���ж�
	{
		  LAST1 = TIM2->CNT - 32768; //˲ʱ�ٶ�ֵ
			LAST2 = TIM3->CNT - 32768;
		
			TIM2->CNT = 32768;         //CNTֵ��λ
			TIM3->CNT = 32768;
		
			PID_TARGET_1(speed1);     //����PID�ٶ�
			PID_TARGET_2(speed2);
	} 
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//����жϱ�־λ
	
	return 0;
}




