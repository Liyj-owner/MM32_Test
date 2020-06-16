/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef _I2C_H
#define _I2C_H

/* 包含的头文件 --------------------------------------------------------------*/
#include "HAL_device.h"
#include "sys.h"
#define EEPROM_I2C_WR	0		/* 写控制bit */
#define EEPROM_I2C_RD	1		/* 读控制bit */

/* 宏定义 --------------------------------------------------------------------*/
#define PORT_I2C_SCL              GPIOB
#define PORT_I2C_SDA              GPIOB

#define PIN_I2C_SCL               GPIO_Pin_6
#define PIN_I2C_SDA               GPIO_Pin_7

#define I2C_SCL_LOW               (PORT_I2C_SCL->BRR  = PIN_I2C_SCL)
#define I2C_SCL_HIGH              (PORT_I2C_SCL->BSRR = PIN_I2C_SCL)
#define I2C_SDA_LOW               (PORT_I2C_SDA->BRR  = PIN_I2C_SDA)
#define I2C_SDA_HIGH              (PORT_I2C_SDA->BSRR = PIN_I2C_SDA)

#define I2C_SDA_READ              ((PORT_I2C_SDA->IDR &  PIN_I2C_SDA ) != 0)

#define I2C_ACK                   0                        //应答
#define I2C_NOACK                 1                        //非应答

/* 函数申明 ------------------------------------------------------------------*/
void I2C_Initializes(void);
void I2C_SDA_SetOutput(void);
void I2C_SDA_SetInput(void);

void I2C_Start(void);
void I2C_Stop(void);
void I2C_PutAck(uint8_t Ack);
uint8_t I2C_GetAck(void);

void I2C_WriteByte(uint8_t Data);
uint8_t I2C_ReadByte();
uint8_t i2c_CheckDevice(uint8_t _Address);

#endif /* _I2C_H */