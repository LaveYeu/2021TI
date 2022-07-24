#include "spi.h"




void Spi_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	SPI_InitTypeDef	SPI_InitStruct;
	
	RCC_APB2PeriphClockCmd(SPI_GPIO_CLK, ENABLE);
	DEBUG_SPI_APBxClkCmd(DEBUG_SPI_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = SPI_CLK_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_CLK_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = SPI_MOSI_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_MOSI_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = SPI_MISO_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_MISO_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = SPI_NSS_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_NSS_GPIO_PORT, &GPIO_InitStruct);

	GPIO_SetBits(SPI_CLK_GPIO_PORT, SPI_CLK_GPIO_PIN);
	GPIO_SetBits(SPI_MOSI_GPIO_PORT, SPI_MOSI_GPIO_PIN);
	GPIO_SetBits(SPI_MISO_GPIO_PORT, SPI_MISO_GPIO_PIN);
	GPIO_SetBits(SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN);

	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	//双线全双工
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;                      //主SPI模式
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;							//空闲状态为低电平 
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;						//第一个边沿采集数据
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_16b;					//8位数据
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;							//从机软件管理
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;//32分频
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;					//最高位先发送
	SPI_InitStruct.SPI_CRCPolynomial = 7;							//CRC多项式,默认不使用SPI自带CRC	 
	SPI_Init(SPIX, &SPI_InitStruct);

	SPI_Cmd(SPIX, ENABLE);       //使能SPI外设
	Spi_Read_Write_Byte(0XFF);    //启动传输
}

/**
  * @brief :SPI收发一个字节
  * @param :
  *			@TxByte: 发送的数据字节
  * @note  :非堵塞式，一旦等待超时，函数会自动退出
  * @retval:接收到的字节
  */
uint8_t Spi_Read_Write_Byte(uint8_t TxByte)
{
	uint8_t Data = 0;
	uint16_t WaitTime = 0;
	
	while(RESET == SPI_I2S_GetFlagStatus(SPIX, SPI_I2S_FLAG_TXE))		//等待发送缓冲区为空
	{
		if(SPI_WAIT_TIMEOUT == ++WaitTime)
		{
			break;			//如果等待超时则退出
		}
	}

	SPI_I2S_SendData(SPIX, TxByte); //通过外设SPI发送一个数据
	WaitTime = 0;		//重新设置接收等待时间(因为SPI的速度很快，正常情况下在发送完成之后会立即收到数据，等待时间不需要过长)
	
	while(RESET == SPI_I2S_GetFlagStatus(SPIX, SPI_I2S_FLAG_RXNE))		//等待接收缓冲区非空
	{
		if(SPI_WAIT_TIMEOUT == ++WaitTime)
		{
			break;			//如果等待超时则退出
		}
	}
	
	Data = SPI_I2S_ReceiveData(SPIX);		//读取接收数据
	
	return Data;		//返回
}

/**
  * @brief :SPI收发字符串
  * @param :
  *			@ReadBuffer: 接收数据缓冲区地址
  *			@WriteBuffer:发送字节缓冲区地址
  *			@Length:字节长度
  * @note  :非堵塞式，一旦等待超时，函数会自动退出
  * @retval:无
  */
void Spi_Read_Write_String(uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length)
{
	GPIO_ResetBits(SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN);			//拉低片选
	while(Length--)
	{
		*ReadBuffer = Spi_Read_Write_Byte(*WriteBuffer);		//收发数据
		ReadBuffer++;
		WriteBuffer++;				//读写地址加1
	}
	GPIO_SetBits(SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN);				//拉高片选
}



