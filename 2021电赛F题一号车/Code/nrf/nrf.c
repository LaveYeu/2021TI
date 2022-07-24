#include "nrf.h"

const char *ErrorString = "NRF24L01 NO FIND";

/**
  * @brief :NRF24L01���Ĵ���
  * @param :
           @Addr:�Ĵ�����ַ
  * @note  :��ַ���豸����Ч
  * @retval:��ȡ������
  */
uint8_t NRF24L01_Read_Reg(uint8_t RegAddr)
{
  uint8_t btmp;

  SPI_NSS_SET(0); //Ƭѡ

  Spi_Read_Write_Byte(NRF_READ_REG | RegAddr); //������ ��ַ
  btmp = Spi_Read_Write_Byte(0xFF);            //������

  SPI_NSS_SET(1); //ȡ��Ƭѡ

  return btmp;
}

/**
  * @brief :NRF24L01��ָ�����ȵ�����
  * @param :
  *			@reg:��ַ
  *			@pBuf:���ݴ�ŵ�ַ
  *			@len:���ݳ���
  * @note  :���ݳ��Ȳ�����255����ַ���豸����Ч
  * @retval:��ȡ״̬
  */
void NRF24L01_Read_Buf(uint8_t RegAddr, uint8_t *pBuf, uint8_t len)
{
  uint8_t btmp;

  SPI_NSS_SET(0); //Ƭѡ

  Spi_Read_Write_Byte(NRF_READ_REG | RegAddr); //������ ��ַ
  for (btmp = 0; btmp < len; btmp++)
  {
    *(pBuf + btmp) = Spi_Read_Write_Byte(0xFF); //������
  }
  SPI_NSS_SET(1); //ȡ��Ƭѡ
}

/**
  * @brief :NRF24L01д�Ĵ���
  * @param :��
  * @note  :��ַ���豸����Ч
  * @retval:��д״̬
  */
void NRF24L01_Write_Reg(uint8_t RegAddr, uint8_t Value)
{
  SPI_NSS_SET(0); //Ƭѡ

  Spi_Read_Write_Byte(NRF_WRITE_REG | RegAddr); //д���� ��ַ
  Spi_Read_Write_Byte(Value);                   //д����

  SPI_NSS_SET(1); //ȡ��Ƭѡ
}

/**
  * @brief :NRF24L01дָ�����ȵ�����
  * @param :
  *			@reg:��ַ
  *			@pBuf:д������ݵ�ַ
  *			@len:���ݳ���
  * @note  :���ݳ��Ȳ�����255����ַ���豸����Ч
  * @retval:д״̬
  */
void NRF24L01_Write_Buf(uint8_t RegAddr, uint8_t *pBuf, uint8_t len)
{
  uint8_t i;

  SPI_NSS_SET(0); //Ƭѡ

  Spi_Read_Write_Byte(NRF_WRITE_REG | RegAddr); //д���� ��ַ
  for (i = 0; i < len; i++)
  {
    Spi_Read_Write_Byte(*(pBuf + i)); //д����
  }

  SPI_NSS_SET(1); //ȡ��Ƭѡ
}

/**
  * @brief :���TX������
  * @param :��
  * @note  :��
  * @retval:��
  */
void NRF24L01_Flush_Tx_Fifo(void)
{
  SPI_NSS_SET(0); //Ƭѡ

  Spi_Read_Write_Byte(FLUSH_TX); //��TX FIFO����

  SPI_NSS_SET(1); //ȡ��Ƭѡ
}

/**
  * @brief :���RX������
  * @param :��
  * @note  :��
  * @retval:��
  */
void NRF24L01_Flush_Rx_Fifo(void)
{
  SPI_NSS_SET(0); //Ƭѡ

  Spi_Read_Write_Byte(FLUSH_RX); //��RX FIFO����

  SPI_NSS_SET(1); //ȡ��Ƭѡ
}

/**
  * @brief :����ʹ����һ������
  * @param :��
  * @note  :��
  * @retval:��
  */
void NRF24L01_Reuse_Tx_Payload(void)
{
  SPI_NSS_SET(0); //Ƭѡ

  Spi_Read_Write_Byte(REUSE_TX_PL); //����ʹ����һ������

  SPI_NSS_SET(1); //ȡ��Ƭѡ
}

/**
  * @brief :NRF24L01�ղ���
  * @param :��
  * @note  :��
  * @retval:��
  */
void NRF24L01_Nop(void)
{
  SPI_NSS_SET(0); //Ƭѡ

  Spi_Read_Write_Byte(NOP); //�ղ�������

  SPI_NSS_SET(1); //ȡ��Ƭѡ
}

/**
  * @brief :NRF24L01��״̬�Ĵ���
  * @param :��
  * @note  :��
  * @retval:NRF24L01״̬
  */
uint8_t NRF24L01_Read_Status_Register(void)
{
  uint8_t Status;

  SPI_NSS_SET(0); //Ƭѡ

  Status = Spi_Read_Write_Byte(NRF_READ_REG + STATUS); //��״̬�Ĵ���

  SPI_NSS_SET(1); //ȡ��Ƭѡ

  return Status;
}

/**
  * @brief :NRF24L01���ж�
  * @param :
           @IRQ_Source:�ж�Դ
  * @note  :��
  * @retval:�����״̬�Ĵ�����ֵ
  */
uint8_t NRF24L01_Clear_IRQ_Flag(uint8_t IRQ_Source)
{
  uint8_t btmp = 0;

  IRQ_Source &= (1 << RX_DR) | (1 << TX_DS) | (1 << MAX_RT); //�жϱ�־����
  btmp = NRF24L01_Read_Status_Register();                    //��״̬�Ĵ���

  SPI_NSS_SET(0);                              //Ƭѡ
  Spi_Read_Write_Byte(NRF_WRITE_REG + STATUS); //д״̬�Ĵ�������
  Spi_Read_Write_Byte(IRQ_Source | btmp);      //����Ӧ�жϱ�־
  SPI_NSS_SET(1);                              //ȡ��Ƭѡ

  return (NRF24L01_Read_Status_Register()); //����״̬�Ĵ���״̬
}

/**
  * @brief :��NRF24L01�ж�״̬
  * @param :��
  * @note  :��
  * @retval:�ж�״̬
  */
uint8_t NRF24L01_Read_IRQ_Status(void)
{
  return (NRF24L01_Read_Status_Register() & ((1 << RX_DR) | (1 << TX_DS) | (1 << MAX_RT))); //�����ж�״̬
}

/**
  * @brief :��FIFO�����ݿ��
  * @param :��
  * @note  :��
  * @retval:���ݿ��
  */
uint8_t NRF24L01_Read_Top_Fifo_Width(void)
{
  uint8_t btmp;

  SPI_NSS_SET(0); //Ƭѡ

  Spi_Read_Write_Byte(R_RX_PL_WID); //��FIFO�����ݿ������
  btmp = Spi_Read_Write_Byte(0xFF); //������

  SPI_NSS_SET(1); //ȡ��Ƭѡ

  return btmp;
}

/**
  * @brief :�����յ�������
  * @param :��
  * @note  :��
  * @retval:
           @pRxBuf:���ݴ�ŵ�ַ�׵�ַ
  */
uint8_t NRF24L01_Read_Rx_Payload(uint8_t *pRxBuf)
{
  uint8_t Width, PipeNum;

  PipeNum = (NRF24L01_Read_Reg(STATUS) >> 1) & 0x07; //������״̬
  Width = NRF24L01_Read_Top_Fifo_Width();            //���������ݸ���

  SPI_NSS_SET(0);                   //Ƭѡ
  Spi_Read_Write_Byte(RD_RX_PLOAD); //����Ч��������

  for (PipeNum = 0; PipeNum < Width; PipeNum++)
  {
    *(pRxBuf + PipeNum) = Spi_Read_Write_Byte(0xFF); //������
  }
  SPI_NSS_SET(1);           //ȡ��Ƭѡ
  NRF24L01_Flush_Rx_Fifo(); //���RX FIFO

  return Width;
}

/**
  * @brief :�������ݣ���Ӧ��
  * @param :
  *			@pTxBuf:�������ݵ�ַ
  *			@len:����
  * @note  :һ�β�����32���ֽ�
  * @retval:��
  */
void NRF24L01_Write_Tx_Payload_Ack(uint8_t *pTxBuf, uint8_t len)
{
  uint8_t btmp;
  uint8_t length = (len > 32) ? 32 : len; //���ݳ����Լ32 ��ֻ����32��

  NRF24L01_Flush_Tx_Fifo(); //��TX FIFO

  SPI_NSS_SET(0);                   //Ƭѡ
  Spi_Read_Write_Byte(WR_TX_PLOAD); //��������

  for (btmp = 0; btmp < length; btmp++)
  {
    Spi_Read_Write_Byte(*(pTxBuf + btmp)); //��������
  }
  SPI_NSS_SET(1); //ȡ��Ƭѡ
}

/**
  * @brief :�������ݣ�����Ӧ��
  * @param :
  *			@pTxBuf:�������ݵ�ַ
  *			@len:����
  * @note  :һ�β�����32���ֽ�
  * @retval:��
  */
void NRF24L01_Write_Tx_Payload_NoAck(uint8_t *pTxBuf, uint8_t len)
{
  if (len > 32 || len == 0)
  {
    return; //���ݳ��ȴ���32 ���ߵ���0 ��ִ��
  }

  SPI_NSS_SET(0);                        //Ƭѡ
  Spi_Read_Write_Byte(WR_TX_PLOAD_NACK); //��������
  while (len--)
  {
    Spi_Read_Write_Byte(*pTxBuf); //��������
    pTxBuf++;
  }
  SPI_NSS_SET(1); //ȡ��Ƭѡ
}

/**
  * @brief :�ڽ���ģʽ����TX FIFOд����(��ACK)
  * @param :
  *			@pData:���ݵ�ַ
  *			@len:����
  * @note  :һ�β�����32���ֽ�
  * @retval:��
  */
void NRF24L01_Write_Tx_Payload_InAck(uint8_t *pData, uint8_t len)
{
  uint8_t btmp;

  len = (len > 32) ? 32 : len; //���ݳ��ȴ���32����ֻд32���ֽ�

  SPI_NSS_SET(0);                   //Ƭѡ
  Spi_Read_Write_Byte(W_ACK_PLOAD); //����
  for (btmp = 0; btmp < len; btmp++)
  {
    Spi_Read_Write_Byte(*(pData + btmp)); //д����
  }
  SPI_NSS_SET(1); //ȡ��Ƭѡ
}

/**
  * @brief :���÷��͵�ַ
  * @param :
  *			@pAddr:��ַ��ŵ�ַ
  *			@len:����
  * @note  :��
  * @retval:��
  */
void NRF24L01_Set_TxAddr(uint8_t *pAddr, uint8_t len)
{
  len = (len > 5) ? 5 : len;               //��ַ���ܴ���5���ֽ�
  NRF24L01_Write_Buf(TX_ADDR, pAddr, len); //д��ַ
}

/**
  * @brief :���ý���ͨ����ַ
  * @param :
  *			@PipeNum:ͨ��
  *			@pAddr:��ַ����ŵ�ַ
  *			@Len:����
  * @note  :ͨ��������5 ��ַ���Ȳ�����5���ֽ�
  * @retval:��
  */
void NRF24L01_Set_RxAddr(uint8_t PipeNum, uint8_t *pAddr, uint8_t Len)
{
  Len = (Len > 5) ? 5 : Len;
  PipeNum = (PipeNum > 5) ? 5 : PipeNum; //ͨ��������5 ��ַ���Ȳ�����5���ֽ�

  NRF24L01_Write_Buf(RX_ADDR_P0 + PipeNum, pAddr, Len); //д���ַ
}

/**
  * @brief :����ͨ���ٶ�
  * @param :
  *			@Speed:�ٶ�
  * @note  :��
  * @retval:��
  */
void NRF24L01_Set_Speed(nRf24l01SpeedType Speed)
{
  uint8_t btmp = 0;

  btmp = NRF24L01_Read_Reg(RF_SETUP);
  btmp &= ~((1 << 5) | (1 << 3));

  if (Speed == SPEED_250K) //250K
  {
    btmp |= (1 << 5);
  }
  else if (Speed == SPEED_1M) //1M
  {
    btmp &= ~((1 << 5) | (1 << 3));
  }
  else if (Speed == SPEED_2M) //2M
  {
    btmp |= (1 << 3);
  }

  NRF24L01_Write_Reg(RF_SETUP, btmp);
}

/**
  * @brief :���ù���
  * @param :
  *			@Speed:�ٶ�
  * @note  :��
  * @retval:��
  */
void NRF24L01_Set_Power(nRf24l01PowerType Power)
{
  uint8_t btmp;

  btmp = NRF24L01_Read_Reg(RF_SETUP) & ~0x07;
  switch (Power)
  {
  case POWER_F18DBM:
    btmp |= PWR_18DB;
    break;
  case POWER_F12DBM:
    btmp |= PWR_12DB;
    break;
  case POWER_F6DBM:
    btmp |= PWR_6DB;
    break;
  case POWER_0DBM:
    btmp |= PWR_0DB;
    break;
  default:
    break;
  }
  NRF24L01_Write_Reg(RF_SETUP, btmp);
}

/**
  * @brief :����Ƶ��
  * @param :
  *			@FreqPoint:Ƶ�����ò���
  * @note  :ֵ������127
  * @retval:��
  */
void RF24LL01_Write_Hopping_Point(uint8_t FreqPoint)
{
  NRF24L01_Write_Reg(RF_CH, FreqPoint & 0x7F);
}

/**
  * @brief :NRF24L01���
  * @param :��
  * @note  :��
  * @retval:��
  */
void NRF24L01_Check(void)
{
  uint8_t i;
  uint8_t buf[5] = {0XA5, 0XA5, 0XA5, 0XA5, 0XA5};
  uint8_t read_buf[5] = {0};

  while (1)
  {
    NRF24L01_Write_Buf(TX_ADDR, buf, 5);     //д��5���ֽڵĵ�ַ
    NRF24L01_Read_Buf(TX_ADDR, read_buf, 5); //����д��ĵ�ַ
    for (i = 0; i < 5; i++)
    {
      if (buf[i] != read_buf[i])
      {
        break;
      }
    }

    if (5 == i)
    {
      break;
    }
    else
    {
      OLED_Show_String(0,3,(uint8_t *)ErrorString,12);
    }
    Delay_ms(1500);
  }
}

/**
  * @brief :����ģʽ
  * @param :
  *			@Mode:ģʽ����ģʽ�����ģʽ
  * @note  :��
  * @retval:��
  */
void NRF24L01_Set_Mode(nRf24l01ModeType Mode)
{
  uint8_t controlreg = 0;
  controlreg = NRF24L01_Read_Reg(CONFIG);

  if (Mode == MODE_TX)
  {
    controlreg &= ~(1 << PRIM_RX);
  }
  else
  {
    if (Mode == MODE_RX)
    {
      controlreg |= (1 << PRIM_RX);
    }
  }

  NRF24L01_Write_Reg(CONFIG, controlreg);
}

/**
  * @brief :NRF24L01����һ������
  * @param :
  *			@txbuf:�����������׵�ַ
  *			@Length:�������ݳ���
  * @note  :��
  * @retval:
  *			MAX_TX���ﵽ����ط�����
  *			TX_OK���������
  *			0xFF:����ԭ��
  */
uint8_t NRF24L01_TxPacket(uint8_t *txbuf, uint8_t Length)
{
  uint8_t Status = 0;
  uint16_t MsTimes = 0;

  SPI_NSS_SET(0); //Ƭѡ
  Spi_Read_Write_Byte(FLUSH_TX);
  SPI_NSS_SET(1);

  NRF_CE_SET(0);
  NRF24L01_Write_Buf(WR_TX_PLOAD, txbuf, Length); //д���ݵ�TX BUF 32�ֽ�  TX_PLOAD_WIDTH
  NRF_CE_SET(1);                                  //��������
  while (0 != NRF_IRQ_STATUS())
  {
    Delay_ms(1);
    if (500 == MsTimes++) //500ms��û�з��ͳɹ������³�ʼ���豸
    {
      NRF24L01_Config();
      NRF24L01_Init();
      NRF24L01_Set_Mode(MODE_TX);
      break;
    }
  }
  Status = NRF24L01_Read_Reg(STATUS); //��״̬�Ĵ���
  NRF24L01_Write_Reg(STATUS, Status); //���TX_DS��MAX_RT�жϱ�־

  if (Status & MAX_TX) //�ﵽ����ط�����
  {
    NRF24L01_Write_Reg(FLUSH_TX, 0xff); //���TX FIFO�Ĵ���
    return MAX_TX;
  }
  if (Status & TX_OK) //�������
  {
    return TX_OK;
  }

  return 0xFF; //����ԭ����ʧ��
}

/**
  * @brief :NRF24L01��������
  * @param :
  *			@rxbuf:�������ݴ�ŵ�ַ
  * @note  :��
  * @retval:���յ����ݸ���
  */
uint8_t NRF24L01_RxPacket(uint8_t *rxbuf)
{
  uint8_t Status = 0, RxLength = 0, Times100Ms = 0;

  SPI_NSS_SET(0); //Ƭѡ
  Spi_Read_Write_Byte(FLUSH_RX);
  SPI_NSS_SET(1);

  while (0 != NRF_IRQ_STATUS())
  {
    Delay_ms(100);

    if (30 == Times100Ms++) //3sû���չ����ݣ����³�ʼ��ģ��
    {
      NRF24L01_Config();
      NRF24L01_Init();
      NRF24L01_Set_Mode(MODE_RX);
      break;
    }
  }

  Status = NRF24L01_Read_Reg(STATUS); //��״̬�Ĵ���
  NRF24L01_Write_Reg(STATUS, Status); //���жϱ�־
  if (Status & RX_OK)                 //���յ�����
  {
    RxLength = NRF24L01_Read_Reg(R_RX_PL_WID);       //��ȡ���յ������ݸ���
    NRF24L01_Read_Buf(RD_RX_PLOAD, rxbuf, RxLength); //���յ�����
    NRF24L01_Write_Reg(FLUSH_RX, 0xff);                //���RX FIFO
    return RxLength;
  }

  return 0; //û���յ�����
}

/**
  * @brief :NRF24L01���ų�ʼ��
  * @param :��
  * @note  :��
  * @retval:��
  */
void NRF24L01_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  RCC_APB2PeriphClockCmd(NRF_GPIO_CLK, ENABLE);

  GPIO_InitStruct.GPIO_Pin = NRF_CE_GPIO_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(NRF_CE_GPIO_PORT, &GPIO_InitStruct);
  GPIO_SetBits(NRF_CE_GPIO_PORT, NRF_CE_GPIO_PIN);

  GPIO_InitStruct.GPIO_Pin = NRF_IRQ_GPIO_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(NRF_IRQ_GPIO_PORT, &GPIO_InitStruct);

  NRF_CE_SET(0);  //??24L01
  SPI_NSS_SET(1); //??SPI??
}

/**
  * @brief :NRF24L01ģ���ʼ��
  * @param :��
  * @note  :��
  * @retval:��
  */
void NRF24L01_Init(void)
{
  uint8_t addr[5] = {INIT_ADDR};

  NRF_CE_SET(1);
  NRF24L01_Clear_IRQ_Flag(IRQ_ALL);
#if DYNAMIC_PACKET == 1

  NRF24L01_Write_Reg(DYNPD, (1 << 0)); //ʹ��ͨ��1��̬���ݳ���
  NRF24L01_Write_Reg(FEATRUE, 0x07);
  NRF24L01_Read_Reg(DYNPD);
  NRF24L01_Read_Reg(FEATRUE);

#elif DYNAMIC_PACKET == 0

  L01_WriteSingleReg(L01REG_RX_PW_P0, FIXED_PACKET_LEN); //�̶����ݳ���

#endif //DYNAMIC_PACKET

  NRF24L01_Write_Reg(CONFIG, /*( 1<<MASK_RX_DR ) |*/ //�����ж�
                                 (1 << EN_CRC) |     //ʹ��CRC 1���ֽ�
                                 (1 << PWR_UP));     //�����豸
  NRF24L01_Write_Reg(EN_AA, (1 << ENAA_P0));         //ͨ��0�Զ�Ӧ��
  NRF24L01_Write_Reg(EN_RXADDR, (1 << ERX_P0));      //ͨ��0����
  NRF24L01_Write_Reg(SETUP_AW, AW_5BYTES);           //��ַ��� 5���ֽ�
  NRF24L01_Write_Reg(SETUP_RETR, ARD_4000US |
                                     (REPEAT_CNT & 0x0F)); //�ظ��ȴ�ʱ�� 250us
  NRF24L01_Write_Reg(RF_CH, 60);                           //��ʼ��ͨ��
  NRF24L01_Write_Reg(RF_SETUP, 0x26);

  NRF24L01_Set_TxAddr(&addr[0], 5);    //����TX��ַ
  NRF24L01_Set_RxAddr(0, &addr[0], 5); //����RX��ַ
}

