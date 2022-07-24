#include "pwm.h" 


int MotorDuty = 3000;
int TurnDuty = 2300;
/*--------------------------------------------
 * 功能：  初始化药物检测
 * 参数：  无
 * 返回值：无
-------------------------------------------*/
void Check_Medicine_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	/* 打开GPIO时钟 */

	GPIO_InitStructure.GPIO_Pin = 4;							/* GPIO引脚号 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  	/* 浮空输入 */
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
  * 功能：检测是否有药物
  * @param  GPIOx: where x can be (A..G) to select the GPIO peripheral.
  * @param  GPIO_Pin:  specifies the port bit to read.
*/
u8 Check_Medicine(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin))
	{
		return 0;
	}
	else 
	{
		return 1;
	}
}

void Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PB端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	//端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;      //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //50MHZ
	GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB 
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
	AIN1=0,AIN2=0;
	BIN1=0,BIN1=0;
}


/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：左轮PWM、右轮PWM
返回  值：无
**************************************************************************/
void Set_Pwm(int moto1,int moto2)
{
	if(moto1<0)			AIN2=1,			AIN1=0;
		else 	        AIN2=0,			AIN1=1;
		PWMA=myabs(moto1);
		if(moto2<0)	BIN1=0,			BIN2=1;
		else        BIN1=1,			BIN2=0;
		PWMB=myabs(moto2);	
}

//void Rotation(int num)
//{
//	
//	
//}



/**************************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
目    的：经过直立环和速度环以及转向环计算出来的PWM有可能为负值
					而只能赋给定时器PWM寄存器只能是正值。故需要对PWM进行绝对值处理
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

float FloatMyabs(float a)
{ 		   
	  float temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}


void Limit(int *motoA,int *motoB)
{
	if(*motoA>10000)*motoA=10000; 
	if(*motoA<-10000)*motoA=-10000;
	
	if(*motoB>10000)*motoB=10000;
	if(*motoB<-10000)*motoB=-10000;
}



void TIM1_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //使能GPIO外设时钟使能
	//设置该引脚为复用输出功能,输出TIM1 CH1 CH4的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11; //TIM_CH1 //TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;                            //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx

	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE 主输出使能	

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1预装载使能	 
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH4预装载使能	 
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_Cmd(TIM1, ENABLE);  //使能TIM1
}

