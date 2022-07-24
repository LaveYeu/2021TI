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

	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	//˫��ȫ˫��
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;                      //��SPIģʽ
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;							//����״̬Ϊ�͵�ƽ 
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;						//��һ�����زɼ�����
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_16b;					//8λ����
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;							//�ӻ��������
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;//32��Ƶ
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;					//���λ�ȷ���
	SPI_InitStruct.SPI_CRCPolynomial = 7;							//CRC����ʽ,Ĭ�ϲ�ʹ��SPI�Դ�CRC	 
	SPI_Init(SPIX, &SPI_InitStruct);

	SPI_Cmd(SPIX, ENABLE);       //ʹ��SPI����
	Spi_Read_Write_Byte(0XFF);    //��������
}

/**
  * @brief :SPI�շ�һ���ֽ�
  * @param :
  *			@TxByte: ���͵������ֽ�
  * @note  :�Ƕ���ʽ��һ���ȴ���ʱ���������Զ��˳�
  * @retval:���յ����ֽ�
  */
uint8_t Spi_Read_Write_Byte(uint8_t TxByte)
{
	uint8_t Data = 0;
	uint16_t WaitTime = 0;
	
	while(RESET == SPI_I2S_GetFlagStatus(SPIX, SPI_I2S_FLAG_TXE))		//�ȴ����ͻ�����Ϊ��
	{
		if(SPI_WAIT_TIMEOUT == ++WaitTime)
		{
			break;			//����ȴ���ʱ���˳�
		}
	}

	SPI_I2S_SendData(SPIX, TxByte); //ͨ������SPI����һ������
	WaitTime = 0;		//�������ý��յȴ�ʱ��(��ΪSPI���ٶȺܿ죬����������ڷ������֮��������յ����ݣ��ȴ�ʱ�䲻��Ҫ����)
	
	while(RESET == SPI_I2S_GetFlagStatus(SPIX, SPI_I2S_FLAG_RXNE))		//�ȴ����ջ������ǿ�
	{
		if(SPI_WAIT_TIMEOUT == ++WaitTime)
		{
			break;			//����ȴ���ʱ���˳�
		}
	}
	
	Data = SPI_I2S_ReceiveData(SPIX);		//��ȡ��������
	
	return Data;		//����
}

/**
  * @brief :SPI�շ��ַ���
  * @param :
  *			@ReadBuffer: �������ݻ�������ַ
  *			@WriteBuffer:�����ֽڻ�������ַ
  *			@Length:�ֽڳ���
  * @note  :�Ƕ���ʽ��һ���ȴ���ʱ���������Զ��˳�
  * @retval:��
  */
void Spi_Read_Write_String(uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length)
{
	GPIO_ResetBits(SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN);			//����Ƭѡ
	while(Length--)
	{
		*ReadBuffer = Spi_Read_Write_Byte(*WriteBuffer);		//�շ�����
		ReadBuffer++;
		WriteBuffer++;				//��д��ַ��1
	}
	GPIO_SetBits(SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN);				//����Ƭѡ
}



