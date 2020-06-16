#include "softwarei2c.h"


/************************************************
�������� �� I2C_Delay
��    �� �� I2C��ʱ(�Ǳ�׼��ʱ,�����MCU�ٶ� ���ڴ�С)
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
static void I2C_Delay(void)
{
	uint8_t i;

	/*��
	 	�����ʱ����ͨ���߼������ǲ��Եõ��ġ�
    ����������CPU��Ƶ72MHz ��MDK���뻷����1���Ż�
  
		ѭ������Ϊ10ʱ��SCLƵ�� = 205KHz 
		ѭ������Ϊ7ʱ��SCLƵ�� = 347KHz�� SCL�ߵ�ƽʱ��1.5us��SCL�͵�ƽʱ��2.87us 
	 	ѭ������Ϊ5ʱ��SCLƵ�� = 421KHz�� SCL�ߵ�ƽʱ��1.25us��SCL�͵�ƽʱ��2.375us 
	*/
	for (i = 0; i < 10; i++);
}

/************************************************
�������� �� I2C_GPIO_Configuration
��    �� �� I2C��������(��©���)
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void I2C_GPIO_Configuration(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = PIN_I2C_SCL | PIN_I2C_SDA;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(PORT_I2C_SCL, &GPIO_InitStructure);
	//I2C_Stop();
}

/************************************************
�������� �� I2C_Initializes
��    �� �� I2C��ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void I2C_Initializes(void)
{
  I2C_GPIO_Configuration();

  I2C_SCL_HIGH;                                  //��λ״̬
  I2C_SDA_HIGH;
}

/************************************************
�������� �� I2C_SDA_SetOutput
��    �� �� I2C_SDA����Ϊ���
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void I2C_SDA_SetOutput(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin   = PIN_I2C_SDA;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_Init(PORT_I2C_SDA, &GPIO_InitStructure);
}

/************************************************
�������� �� I2C_SDA_SetInput
��    �� �� I2C_SDA����Ϊ����
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void I2C_SDA_SetInput(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin   = PIN_I2C_SDA;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
  GPIO_Init(PORT_I2C_SDA, &GPIO_InitStructure);
}

/************************************************
�������� �� I2C_Start
��    �� �� I2C��ʼ
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void I2C_Start(void)
{
  I2C_SCL_HIGH;                                  //SCL��

  I2C_SDA_HIGH;                                  //SDA�� -> ��
  I2C_Delay();
	
  I2C_SDA_LOW;                                   //SDA��
  I2C_Delay();

  I2C_SCL_LOW;                                   //SCL��(��д��ַ/����)
  I2C_Delay();
}

/************************************************
�������� �� I2C_Stop
��    �� �� I2Cֹͣ
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void I2C_Stop(void)
{
  I2C_SDA_LOW;                                   //SDA�� -> ��

  I2C_SCL_HIGH;                                  //SCL��
  I2C_Delay();

  I2C_SDA_HIGH;                                  //SDA��
  I2C_Delay();
}

/************************************************
�������� �� I2C_PutAck
��    �� �� I2C��������Ӧ��(���Ӧ��)λ
��    �� �� I2C_ACK ----- Ӧ��
            I2C_NOACK --- ��Ӧ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void I2C_PutAck(uint8_t Ack)
{

  if(I2C_ACK == Ack) //Ӧ��
	{
	 I2C_SDA_LOW;
	 I2C_Delay();
	 I2C_SCL_HIGH;                                  //SCL�� -> ��
   I2C_Delay();
	 I2C_SCL_LOW;                                   //SCL��
   I2C_Delay();
	 I2C_SDA_HIGH; 
	}
                                   
  else
	{
	 I2C_SDA_HIGH;                                //��Ӧ��
   I2C_Delay();
	 I2C_SCL_HIGH;                                  //SCL�� -> ��
   I2C_Delay();
	 I2C_SCL_LOW;                                   //SCL��
   I2C_Delay();
	}
}

/************************************************
�������� �� I2C_GetAck
��    �� �� I2C������ȡӦ��(���Ӧ��)λ
��    �� �� ��
�� �� ֵ �� I2C_ACK ----- Ӧ��
            I2C_NOACK --- ��Ӧ��
��    �� �� strongerHuang
*************************************************/
uint8_t I2C_GetAck(void)
{
  uint8_t ack;

//  I2C_SCL_LOW;                                   //SCL�� -> ��
//  I2C_Delay();
   I2C_SDA_HIGH;                                   //SCL�� -> ��
   I2C_Delay();
 // I2C_SDA_SetInput();                            //SDA����Ϊ����ģʽ(��©ģʽ���Բ����л�����)

  I2C_SCL_HIGH;                                  //SCL��(��ȡӦ��λ)
  I2C_Delay();

  if(I2C_SDA_READ)
    ack = I2C_NOACK;                             //��Ӧ��
  else
    ack = I2C_ACK;                               //Ӧ��

  I2C_SCL_LOW;                                   //SCL��
  I2C_Delay();
 // I2C_SDA_SetOutput();                           //SDA����Ϊ���ģʽ

  return ack;                                    //����Ӧ��λ
}

/************************************************
�������� �� I2C_WriteByte
��    �� �� I2Cдһ�ֽ�
��    �� �� Data -------- ����
�� �� ֵ �� I2C_ACK ----- Ӧ��
            I2C_NOACK --- ��Ӧ��
��    �� �� strongerHuang
*************************************************/
void I2C_WriteByte(uint8_t Data)
{
  uint8_t cnt;

  for(cnt=0; cnt<8; cnt++)
  {
    if(Data & 0x80)
      I2C_SDA_HIGH;                              //SDA��
    else
      I2C_SDA_LOW;                               //SDA��
    
    I2C_Delay();
    I2C_SCL_HIGH;                                //SCL��(��������)
    I2C_Delay();
		I2C_SCL_LOW;
		if(cnt==7)
		{
		I2C_SDA_HIGH; 
		}
		Data <<= 1;
		 I2C_Delay();
  }
  //return I2C_GetAck();                           //����Ӧ��λ
}

/************************************************
�������� �� I2C_ReadByte
��    �� �� I2C��һ�ֽ�
��    �� �� ack --------- ����Ӧ��(���߷�Ӧ��)λ
�� �� ֵ �� data -------- ��ȡ��һ�ֽ�����
��    �� �� strongerHuang
*************************************************/
uint8_t I2C_ReadByte()
{
  uint8_t cnt;
  uint8_t data=0;

  //I2C_SDA_SetInput();                            //SDA����Ϊ����ģʽ
  for(cnt=0; cnt<8; cnt++)
  {
		data <<= 1;
    I2C_SCL_HIGH;                                //SCL��(��ȡ����)
    I2C_Delay();
    
    if(I2C_SDA_READ)
      data |= 0x01;                              //SDAΪ��(������Ч)

    I2C_SCL_LOW;                                 //SCL��
    I2C_Delay();
  }

  return data;                                   //��������
}
uint8_t i2c_CheckDevice(uint8_t _Address)
{
	uint8_t ucAck;

	I2C_GPIO_Configuration();	/* ����GPIO */

	I2C_Start();		/* ���������ź� */

	/* �����豸��ַ+��д����bit��0 = w�� 1 = r) bit7 �ȴ� */
	I2C_WriteByte(_Address | EEPROM_I2C_WR);
	ucAck =I2C_GetAck();	/* ����豸��ACKӦ�� */

	I2C_Stop();			/* ����ֹͣ�ź� */

	return ucAck;
}

/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
