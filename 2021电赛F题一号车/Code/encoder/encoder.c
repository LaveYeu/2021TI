#include "encoder.h"

void Encoder1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;

    RCC_APB2PeriphClockCmd(ENCODER1_GPIO_CLK, ENABLE);
    DEBUG_ENCODER1_APBxClkCmd(DEBUG_ENCODER1_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin = ENCODER1_GPIO1_PIN | ENCODER1_GPIO2_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;     //浮空输入
    GPIO_Init(ENCODER1_GPIO_PORT, &GPIO_InitStructure); //根据设定参数初始化GPIOB

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 0x0;                  // 预分频器
    TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;      //设定计数器自动重装值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //选择时钟分频：不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; ////TIM向上计数
    TIM_TimeBaseInit(ENCODER1_TIMX, &TIM_TimeBaseStructure);
    TIM_EncoderInterfaceConfig(ENCODER1_TIMX, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 10;
    TIM_ICInit(ENCODER1_TIMX, &TIM_ICInitStructure);
    TIM_ClearFlag(ENCODER1_TIMX, TIM_FLAG_Update); //清除TIM的更新标志位
    TIM_ITConfig(ENCODER1_TIMX, TIM_IT_Update, ENABLE);
    //Reset counter
    TIM_SetCounter(ENCODER1_TIMX, 0);
    TIM_Cmd(ENCODER1_TIMX, ENABLE);
}

void Encoder2_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;

    RCC_APB2PeriphClockCmd(ENCODER2_GPIO_CLK, ENABLE);
    DEBUG_ENCODER2_APBxClkCmd(DEBUG_ENCODER2_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin = ENCODER2_GPIO1_PIN | ENCODER2_GPIO2_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;     //浮空输入
    GPIO_Init(ENCODER2_GPIO_PORT, &GPIO_InitStructure); //根据设定参数初始化GPIOB

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 0x0;                  // 预分频器
    TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;      //设定计数器自动重装值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //选择时钟分频：不分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; ////TIM向上计数
    TIM_TimeBaseInit(ENCODER2_TIMX, &TIM_TimeBaseStructure);
    TIM_EncoderInterfaceConfig(ENCODER2_TIMX, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 10;
    TIM_ICInit(ENCODER2_TIMX, &TIM_ICInitStructure);
    TIM_ClearFlag(ENCODER2_TIMX, TIM_FLAG_Update); //清除TIM的更新标志位
    TIM_ITConfig(ENCODER2_TIMX, TIM_IT_Update, ENABLE);
    //Reset counter
    TIM_SetCounter(ENCODER2_TIMX, 0);
    TIM_Cmd(ENCODER2_TIMX, ENABLE);
}

int Read_Encoder(u8 TIMX)
{
    int Encoder_TIM;
    switch (TIMX)
    {
    case 2:
        Encoder_TIM = (short)TIM2->CNT;
        TIM2->CNT = 0;
        break;
    case 3:
        Encoder_TIM = (short)TIM3->CNT;
        TIM3->CNT = 0;
        break;
    case 4:
        Encoder_TIM = (short)TIM4->CNT;
        TIM4->CNT = 0;
        break;
    default:
        Encoder_TIM = 0;
    }
    return Encoder_TIM;
}

void TIM4_IRQHandler(void)
{
    if (TIM4->SR & 0X0001) //溢出中断
    {
    }
    TIM4->SR &= ~(1 << 0); //清除中断标志位
}

void TIM2_IRQHandler(void)
{
    if (TIM2->SR & 0X0001) //溢出中断
    {
    }
    TIM2->SR &= ~(1 << 0); //清除中断标志位
}
