#include "loop.h"
#include "pwm.h" 
#include "TCS34725.h"
#include "TCS34725111.h"
#include "vl53l0x.h"
#include "vl53l0x_gen.h"

#include "systick.h"
u8 Step_X=0;
extern VL53L0X_Dev_t vl53l0x_dev;//设备I2C数据参数
u8 Flag_1=0, Flag_2=1, Flag_3=1, Flag_4=0;

u8 set_flag = 1;
u8 menu = 1, menu_ko = 1;
short temp;                //温度
float pitch, roll, yaw;    //欧拉角
short aacx, aacy, aacz;    //加速度传感器原始数据
short gyrox, gyroy, gyroz; //陀螺仪原始数据
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
	static char buf[VL53L0X_MAX_STRING_LENGTH];//测试模式字符串字符缓冲区
	VL53L0X_Error Status=VL53L0X_ERROR_NONE;//工作状态
	u8 mode=2; //0：默认；1：高精度；2：长距离；3：高速度
	u32 i;




//自己加入的变量
float TargetYaw = 0.0;
float YawErr    = 0.0;
int   TurnFlag	= 0; //   1为向左转90度，2位向右转90度
int   TurnHistory = 0;
int	  BlueTeethFlag = 0;	//另一小车蓝牙信号标志位
int	  LEDFLAG = 0;
int   ChooseSucces = 0; // 方案选择成功标志位
int   Solve = 0;   //重要参数！选择方案！ 
float   ChooseTimeDuration = 3.0;  //选择病房需要时间
int   DrugFlag = 0;        //药品放置标志位，为1时代表药品被放入
float   MoveTime = 0.0;//转弯，前行持续时间
int   MoveSuccess = 0;
int   MoveAsk = 0;


static void Duty_3ms(void)
{
//    if (mpu_dmp_get_data(&pitch, &roll, &yaw) == 0)
//    {
//        temp = MPU_Get_Temperature();               //得到温度值
//        MPU_Get_Accelerometer(&aacx, &aacy, &aacz); //得到加速度传感器数据
//        MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);  //得到陀螺仪数据
//    }
}

static void Duty_20ms(void)  // 专用定时线程
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
//	if(RGB_V.Red<745&&RGB_V1.Red<429)//同时检测，为十字路口
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
		ChooseTimeDuration-=0.1;//定时6s，每次减0.1减60次
		if(ChooseTimeDuration<0.5)LED1_TOGGLE;
	}
	else ChooseSucces = 1;//时间到，标记为置1，停止定时，并且记录标志，选择路径
	if(ChooseSucces==0)  //时间未到，保持测量
	{
	Status = vl53l0x_start_single_test(&vl53l0x_dev,&vl53l0x_data,buf);//执行一次测量
			if(Status==VL53L0X_ERROR_NONE)
			{
				printf("d: %4imm\r\n",Distance_data);//打印测量距离
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
	else//时间到，记录现在的数字与方案
	{
		LED1(1);
		
	}
			
	
//    OLED_Show_Float(50, 0, yaw, 3, 2, 12);
//    OLED_Show_Int(50, 1, RGB_V.Red, 5, 12);//右边模块
//	OLED_Show_Int(50, 2, RGB_V1.Red, 5, 12);//左边模块
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
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);// 设置中断优先级分组2
    Systime_Init(20);
	TIM1_PWM_Init(7199,0);
    Led_Config();
//    Key_Config();
    Usart_Config(115200);
    Usart1_Config(115200);
	Check_Medicine_Init();
    Motor_Init();
	
//	Set_Pwm(MotorDuty,MotorDuty);

	
	if(vl53l0x_init(&vl53l0x_dev))     //vl53l0x初始化
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
		 VL53L0X_RdByte(&vl53l0x_dev,0x51,&len);  //高四位没法读出来
		 printf("reg51 = 0x%x\n\r",len);
		 
		 Status = VL53L0X_WrWord(&vl53l0x_dev,0x62,0x9e12);
		 VL53L0X_RdWord(&vl53l0x_dev,0x62,&word);
		 printf("reg61 = 0x%x\n\r",word);
	 }
	
	if(vl53l0x_set_mode(&vl53l0x_dev,mode))   //配置测量模式
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
	
	
	
	Status = vl53l0x_start_single_test(&vl53l0x_dev,&vl53l0x_data,buf);//执行一次测量
			if(Status==VL53L0X_ERROR_NONE)
			{
				printf("d: %4imm\r\n",Distance_data);//打印测量距离
				OLED_Show_Int(6,6,Distance_data,4,2);
//				OLED_Num4(3,4,Distance_data);
			}
			else
			{
				printf("Measurement is Error!!!\r\n");
			}
}

//系统任务配置，创建不同执行周期的“线程”
static sched_task_t sched_tasks[] = 
{
    {Duty_3ms, 3, 0},
    {Duty_20ms, 20, 0},
    {Duty_8ms, 8, 0},
   
    {Duty_100ms, 100, 0}
};

//根据数组长度，判断线程数量
#define TASK_NUM (sizeof(sched_tasks) / sizeof(sched_task_t))

//函数无需放到main函数的while(1)中，可自行循环，不停判断是否有线程应该执行
void Loop_Run(void)
{
    static u8 index = 0; //线程 N
    static u32 tnow = 0; //系统当前时间
	
	if(MoveAsk==0)
	{
		while (ChooseSucces==0)
		{
			//循环判断所有线程，是否应该执行
			for (index = 0; index < TASK_NUM; index++)
			{
				//获取系统当前时间，单位MS
				tnow = time_count_ms;
				//进行判断，如果当前时间减去上一次执行的时间，大于等于该线程的执行周期，则执行线程
				if (tnow - sched_tasks[index].last_run >= sched_tasks[index].interval_ticks)
				{
					//更新线程的执行时间，用于下一次判断
					sched_tasks[index].last_run = tnow;
					//执行线程函数，使用的是函数指针
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
					//获取系统当前时间，单位MS
					tnow = time_count_ms;
					//进行判断，如果当前时间减去上一次执行的时间，大于等于该线程的执行周期，则执行线程
					if (tnow - sched_tasks[index].last_run >= sched_tasks[index].interval_ticks)
					{
						//更新线程的执行时间，用于下一次判断
						sched_tasks[index].last_run = tnow;
						//执行线程函数，使用的是函数指针
						sched_tasks[index].task_func();
					}
				}
		}
	}
	
}
