#ifndef __KEY_H
#define __KEY_H

#include "headfile.h"


#define KEY1_INT_GPIO_CLK           RCC_APB2Periph_GPIOA
#define KEY1_INT_GPIO_PORT          GPIOA
#define KEY1_INT_GPIO_PIN           GPIO_Pin_2

#define KEY2_INT_GPIO_CLK           RCC_APB2Periph_GPIOA
#define KEY2_INT_GPIO_PORT          GPIOA
#define KEY2_INT_GPIO_PIN           GPIO_Pin_3

#define KEY3_INT_GPIO_CLK           RCC_APB2Periph_GPIOA
#define KEY3_INT_GPIO_PORT          GPIOA
#define KEY3_INT_GPIO_PIN           GPIO_Pin_4

#define KEY4_INT_GPIO_CLK           RCC_APB2Periph_GPIOA
#define KEY4_INT_GPIO_PORT          GPIOA
#define KEY4_INT_GPIO_PIN           GPIO_Pin_5

#define GPIO_READ_KET1              GPIO_ReadInputDataBit(KEY1_INT_GPIO_PORT,KEY1_INT_GPIO_PIN)
#define GPIO_READ_KET2              GPIO_ReadInputDataBit(KEY2_INT_GPIO_PORT,KEY2_INT_GPIO_PIN)
#define GPIO_READ_KET3              GPIO_ReadInputDataBit(KEY3_INT_GPIO_PORT,KEY3_INT_GPIO_PIN)
#define GPIO_READ_KET4              GPIO_ReadInputDataBit(KEY4_INT_GPIO_PORT,KEY4_INT_GPIO_PIN)

#define Key1   1
#define Key2   3
#define Key3   4
#define Key4   2


void Key_Config(void);
uint8_t Key_Scan(uint8_t ctns);

#endif /* __KEY_H */
