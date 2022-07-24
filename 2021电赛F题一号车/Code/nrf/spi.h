#ifndef __SPI_H
#define __SPI_H

#include "headfile.h"

#define  DEBUG_SPI_APBxClkCmd     RCC_APB1PeriphClockCmd
#define  DEBUG_SPI_CLK            RCC_APB1Periph_SPI2
#define  SPI_GPIO_CLK             RCC_APB2Periph_GPIOA

#define  SPIX					  SPI2
#define  SPI_CLK_GPIO_PORT		  GPIOB
#define  SPI_CLK_GPIO_PIN		  GPIO_Pin_13
#define  SPI_MISO_GPIO_PORT		  GPIOB
#define  SPI_MISO_GPIO_PIN		  GPIO_Pin_14
#define  SPI_MOSI_GPIO_PORT		  GPIOB
#define  SPI_MOSI_GPIO_PIN		  GPIO_Pin_15
#define  SPI_NSS_GPIO_PORT	      GPIOB
#define  SPI_NSS_GPIO_PIN		  GPIO_Pin_12

#define  SPI_NSS_SET(a)    if(a) GPIO_SetBits(SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN);\
                           else  GPIO_ResetBits(SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN)	

#define SPI_WAIT_TIMEOUT			((uint16_t)0xFFFF)


void Spi_Config(void);
uint8_t Spi_Read_Write_Byte(uint8_t TxByte);
void Spi_Read_Write_String(uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length);



#endif  //__SPI_H


