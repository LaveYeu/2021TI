#include "loop.h"
#include "pwm.h" 
#include "TCS34725.h"
#include "TCS34725111.h"
#include "vl53l0x.h"
#include "vl53l0x_gen.h"

#include "systick.h"
u8 Step_X=0;
extern VL53L0X_Dev_t vl53l0x_dev;//�豸I2C���ݲ���
u8 Flag_1=0, Flag_2=1, Flag_3=1, Flag_4=0;

u8 set_flag = 1;
u8 menu = 1, menu_ko = 1;
short temp;                //�¶�
float pitch, roll, yaw;    //ŷ����
short aacx, aacy, aacz;    //���ٶȴ�����ԭʼ����
short gyrox, gyroy, gyroz; //������ԭʼ����
float left_set, right_set;
int16_t turn_set = 0;
int16_t pwm_l = 0, pwm_r = 0;
int16_t speed_l = 0, speed_r = 0;
int16_t speed_set = 0, speed_mea = 0;

PidObject spe_pid, tur_pid, *menu_pid;
float spe_kp = 0, spe_ki = 0, spe_kd = 0;
float tur_kp = 0, tur_ki = 0, tur_kd = 0;
int16_t   bal_out = 0, spe_out = 0, tur_out = 0;



uint8_t data;
	uint8_t len;
	uint16_t word;
	uint8_t data1;
	static char buf[VL53L0X_MAX_STRING_LENGTH];//����ģʽ�ַ����ַ�������
	VL53L0X_Error Status=VL53L0X_ERROR_NONE;//����״̬
	u8 mode=2; //0��Ĭ�ϣ�1���߾��ȣ�2�������룻3�����ٶ�
	u32 i;




//�Լ�����ı���
float TargetYaw = 0.0;
float YawErr    = 0.0;
int   TurnFlag	= 0; //   1Ϊ����ת90�ȣ�2λ����ת90��
int   TurnHistory = 0;
int	  BlueTeethFlag = 0;	//��һС�������źű�־λ
int	  LEDFLAG = 0;
int   ChooseSucces = 0; // ����ѡ��ɹ���־λ
int   Solve = 0;   //��Ҫ������ѡ�񷽰��� 
float   ChooseTimeDuration = 3.0;  //ѡ�񲡷���Ҫʱ��
int   DrugFlag = 0;        //ҩƷ���ñ�־λ��Ϊ1ʱ����ҩƷ������
float   MoveTime = 0.0;//ת�䣬ǰ�г���ʱ��
int   MoveSuccess = 0;
int   MoveAsk = 0;


static void Duty_3ms(void)
{
//    if (mpu_dmp_get_data(&pitch, &roll, &yaw) == 0)
//    {
//        temp = MPU_Get_Temperature();               //�õ��¶�ֵ
//        MPU_Get_Accelerometer(&aacx, &aacy, &aacz); //�õ����ٶȴ���������
//        MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);  //�õ�����������
//    }
}

static void Duty_20ms(void)  // ר�ö�ʱ�߳�
{
	if(MoveSuccess==0&&MoveAsk==1)
	{
		MoveTime-=0.01;
	}
	if(MoveTime<0)MoveSuccess = 1;
//    Set_Pwm(-2000, 3000);
}

static void Duty_8ms(void)
{
//	Capture_RGB();
//	Capture_RGB1();
//	if(RGB_V.Red<745&&RGB_V1.Red<429)//ͬʱ��⣬Ϊʮ��·��
//	{
//		Set_Pwm(0, 0);
//		LEDFLAG = 1;
////		LED1(1);
//	}
//	if(LEDFLAG==1)
//	{
//		LED1(0);
//	}
}



static void Duty_100ms(void)
{
//	OLED_Clear();
//	OLED_Show_String(0, 0, "Yaw:", 12);
//    OLED_Show_String(0, 1, "RED:", 12);
//    LED1_TOGGLE;
	if(ChooseTimeDuration>0)
	{
		ChooseTimeDuration-=0.1;//��ʱ6s��ÿ�μ�0.1��60��
		if(ChooseTimeDuration<0.5)LED1_TOGGLE;
	}
	else ChooseSucces = 1;//ʱ�䵽�����Ϊ��1��ֹͣ��ʱ�����Ҽ�¼��־��ѡ��·��
	if(ChooseSucces==0)  //ʱ��δ�������ֲ���
	{
	Status = vl53l0x_start_single_test(&vl53l0x_dev,&vl53l0x_data,buf);//ִ��һ�β���
			if(Status==VL53L0X_ERROR_NONE)
			{
				printf("d: %4imm\r\n",Distance_data);//��ӡ��������
				OLED_Show_Uint(6,6,Distance_data,7,16);
//				if(Distance_data>60&&Distance_data<85)
//				{
//					Solve = 1;
//				}
//				else if(Distance_data>85&&Distance_data<100)
//				{
//					Solve = 2;
//				}
				if(Distance_data>60&&Distance_data<115)
				{
					Solve = 3;
				}
				else if(Distance_data>115&&Distance_data<180)
				{
					Solve = 4;
				}
//				else if(Distance_data>130&&Distance_data<145)
//				{
//					Solve = 5;
//				}
//				else if(Distance_data>145&&Distance_data<160)
//				{
//					Solve = 6;
//				}
//				else if(Distance_data>160&&Distance_data<175)
//				{
//					Solve = 7;
//				}
//				else if(Distance_data>175&&Distance_data<200)
//				{
//					Solve = 8;
//				}
				
				if(Solve == 1)	   OLED_Show_String(0, 3, "A", 12);
				else if(Solve == 2)OLED_Show_String(0, 3, "B", 12);
				else if(Solve == 3)OLED_Show_String(0, 3, "C", 12);
				else if(Solve == 4)OLED_Show_String(0, 3, "D", 12);
				else if(Solve == 5)OLED_Show_String(0, 3, "E", 12);
				else if(Solve == 6)OLED_Show_String(0, 3, "F", 12);
				else if(Solve == 7)OLED_Show_String(0, 3, "G", 12);
				else if(Solve == 8)OLED_Show_String(0, 3, "H", 12);
				OLED_Show_Float(2,2,ChooseTimeDuration,2,2,12);
				
			}
			else
			{
				OLED_Show_Uint(7,6,666,5,2);
				printf("Measurement is Error!!!\r\n");
//				OLED_Num4(3,4,4);
			}
	}
	else//ʱ�䵽����¼���ڵ������뷽��
	{
		LED1(1);
		
	}
			
	
//    OLED_Show_Float(50, 0, yaw, 3, 2, 12);
//    OLED_Show_Int(50, 1, RGB_V.Red, 5, 12);//�ұ�ģ��
//	OLED_Show_Int(50, 2, RGB_V1.Red, 5, 12);//���ģ��
//	OLED_Show_Int(50, 3, LEDFLAG, 5, 12);//LEDFLAG
//    OLED_Show_Float(0, 6, left_set, 3, 2, 12);
//    OLED_Show_Float(60, 6, right_set, 3, 2, 12);
//    OLED_Show_Int(0, 7, pwm_l, 3, 12);
//    OLED_Show_Int(60, 7, pwm_r, 3, 12);
//    User_Tx(-201, 101);
    // SysTick_Delay_ms(1000);
	 
}
void ForWard(float time)
{
	MoveTime = time;
	MoveAsk = 1;
	Set_Pwm(MotorDuty, MotorDuty);
	Loop_Run();
	
	MoveAsk = 0;
//	Set_Pwm(0,0);
}


void TurnLeft(void)
{
	if (mpu_dmp_get_data(&pitch, &roll, &yaw) == 0);
	TargetYaw = yaw +90;
	float temp = 0.0;
	while(myabs(TargetYaw-yaw)>1.0)
	{
		if (mpu_dmp_get_data(&pitch, &roll, &yaw) == 0);
		temp = TargetYaw-yaw;
		if(temp>0.0)Set_Pwm(TurnDuty, -TurnDuty);
		if(temp<0.0)Set_Pwm(-TurnDuty, TurnDuty);
		OLED_Show_Float(50, 0, yaw, 3, 2, 12);
	}
	Set_Pwm(0, 0);
	
}

void TurnAngle(int num)
{
	if (mpu_dmp_get_data(&pitch, &roll, &yaw) == 0);
	TargetYaw = yaw +num;
	float temp = 0.0;
	while(myabs(TargetYaw-yaw)>1.0)
	{
		if (mpu_dmp_get_data(&pitch, &roll, &yaw) == 0);
		temp = TargetYaw-yaw;
		if(temp>0.0)Set_Pwm(TurnDuty, -TurnDuty);
		if(temp<0.0)Set_Pwm(-TurnDuty, TurnDuty);
		OLED_Show_Float(50, 0, yaw, 3, 2, 12);
	}
	Set_Pwm(0, 0);
	
}


void TurnRight(void)
{
	if (mpu_dmp_get_data(&pitch, &roll, &yaw) == 0);
	TargetYaw = yaw -90;
	float temp = 0.0;
	while(myabs(TargetYaw-yaw)>1.0)
	{
		if (mpu_dmp_get_data(&pitch, &roll, &yaw) == 0);
		temp = TargetYaw-yaw;
		if(temp>0.0)Set_Pwm(TurnDuty, -TurnDuty);
		if(temp<0.0)Set_Pwm(-TurnDuty, TurnDuty);
		OLED_Show_Float(50, 0, yaw, 3, 2, 12);
	}
	Set_Pwm(0, 0);
	
}

void Config(void)
{
    SysTick_Delay_ms(1000);
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);// �����ж����ȼ�����2
    Systime_Init(20);
	TIM1_PWM_Init(7199,0);
    Led_Config();
//    Key_Config();
    Usart_Config(115200);
    Usart1_Config(115200);
	Check_Medicine_Init();
    Motor_Init();
	
//	Set_Pwm(MotorDuty,MotorDuty);

	
	if(vl53l0x_init(&vl53l0x_dev))     //vl53l0x��ʼ��
	 {
		printf("VL53L0X_Init Error!!!\r\n");
		SysTick_Delay_ms(200);
	 }
	 else
	 {
		 printf("VL53L0X_Init OK\r\n");
		 
		 VL53L0X_RdByte(&vl53l0x_dev,0xC0,&data);
		 printf("regc0 = 0x%x\n\r",data);
		
		 VL53L0X_RdByte(&vl53l0x_dev,0xC1,&data1);
		 printf("regc1 = 0x%x\n\r",data1);
		 
		 VL53L0X_RdByte(&vl53l0x_dev,0xC2,&len);
		 printf("regc2 = 0x%x\n\r",len); 
		 
		 Status = VL53L0X_WrByte(&vl53l0x_dev,0x51,0x12);
		 VL53L0X_RdByte(&vl53l0x_dev,0x51,&len);  //����λû��������
		 printf("reg51 = 0x%x\n\r",len);
		 
		 Status = VL53L0X_WrWord(&vl53l0x_dev,0x62,0x9e12);
		 VL53L0X_RdWord(&vl53l0x_dev,0x62,&word);
		 printf("reg61 = 0x%x\n\r",word);
	 }
	
	if(vl53l0x_set_mode(&vl53l0x_dev,mode))   //���ò���ģʽ
		{
			printf("Mode Set Error!!!\r\n");
			
//			OLED_ShowString(0,0,"Pitch:",12);
		}
	else
		printf("Mode Set OK!!!\r\n");
//    Encoder1_Init();
//    Encoder2_Init();
    OLED_Init();
    OLED_Clear();
//	Color_tcs34725_Init();
//	Color_tcs34725_Init1();
//	Capture_RGB();
//	Capture_RGB1();
//	OLED_Show_Int(5,5,RGB_V.Red,3,2);
//	OLED_Show_Int(6,6,RGB_V1.Red,3,2);
    MPU_Init();
    while (mpu_dmp_init())
    {
        OLED_Show_String(0, 0, "MPU6050 ERROR", 12);
        SysTick_Delay_ms(200);
        OLED_Clear();
    }
	OLED_Clear();
    OLED_Show_String(0, 0, "Yaw:", 12);
//    OLED_Show_String(0, 1, "RED:", 12);
	
	
	
	Status = vl53l0x_start_single_test(&vl53l0x_dev,&vl53l0x_data,buf);//ִ��һ�β���
			if(Status==VL53L0X_ERROR_NONE)
			{
				printf("d: %4imm\r\n",Distance_data);//��ӡ��������
				OLED_Show_Int(6,6,Distance_data,4,2);
//				OLED_Num4(3,4,Distance_data);
			}
			else
			{
				printf("Measurement is Error!!!\r\n");
			}
}

//ϵͳ�������ã�������ִͬ�����ڵġ��̡߳�
static sched_task_t sched_tasks[] = 
{
    {Duty_3ms, 3, 0},
    {Duty_20ms, 20, 0},
    {Duty_8ms, 8, 0},
   
    {Duty_100ms, 100, 0}
};

//�������鳤�ȣ��ж��߳�����
#define TASK_NUM (sizeof(sched_tasks) / sizeof(sched_task_t))

//��������ŵ�main������while(1)�У�������ѭ������ͣ�ж��Ƿ����߳�Ӧ��ִ��
void Loop_Run(void)
{
    static u8 index = 0; //�߳� N
    static u32 tnow = 0; //ϵͳ��ǰʱ��
	
	if(MoveAsk==0)
	{
		while (ChooseSucces==0)
		{
			//ѭ���ж������̣߳��Ƿ�Ӧ��ִ��
			for (index = 0; index < TASK_NUM; index++)
			{
				//��ȡϵͳ��ǰʱ�䣬��λMS
				tnow = time_count_ms;
				//�����жϣ������ǰʱ���ȥ��һ��ִ�е�ʱ�䣬���ڵ��ڸ��̵߳�ִ�����ڣ���ִ���߳�
				if (tnow - sched_tasks[index].last_run >= sched_tasks[index].interval_ticks)
				{
					//�����̵߳�ִ��ʱ�䣬������һ���ж�
					sched_tasks[index].last_run = tnow;
					//ִ���̺߳�����ʹ�õ��Ǻ���ָ��
					sched_tasks[index].task_func();
				}
			}
		}
	}
	if(MoveAsk==1)
	{
		while(MoveSuccess==0)
		{
			for (index = 0; index < TASK_NUM; index++)
				{
					//��ȡϵͳ��ǰʱ�䣬��λMS
					tnow = time_count_ms;
					//�����жϣ������ǰʱ���ȥ��һ��ִ�е�ʱ�䣬���ڵ��ڸ��̵߳�ִ�����ڣ���ִ���߳�
					if (tnow - sched_tasks[index].last_run >= sched_tasks[index].interval_ticks)
					{
						//�����̵߳�ִ��ʱ�䣬������һ���ж�
						sched_tasks[index].last_run = tnow;
						//ִ���̺߳�����ʹ�õ��Ǻ���ָ��
						sched_tasks[index].task_func();
					}
				}
		}
	}
	
}
