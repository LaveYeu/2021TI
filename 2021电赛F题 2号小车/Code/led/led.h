#ifndef __LED_H
#define __LED_H

#include "headfile.h"

#define LED1_GPIO_PIN              GPIO_Pin_13
#define LED1_GPIO_PORT             GPIOC
#define LED1_GPIO_CLK              RCC_APB2Periph_GPIOC



#define   LED1(a)   if(a) GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PIN); \
                    else  GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN)

#define   LED1_TOGGLE     {LED1_GPIO_PORT->ODR ^= LED1_GPIO_PIN;}

void Led_Config(void);

#endif // __LED_H

