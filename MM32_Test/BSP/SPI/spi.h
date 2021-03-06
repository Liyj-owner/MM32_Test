/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef _SPI_H
#define _SPI_H

/* 包含的头文件 --------------------------------------------------------------*/
#include "HAL_device.h"
#include "sys.h"

/* 宏定义 --------------------------------------------------------------------*/
#define PORT_SPI_CS               GPIOB
#define PORT_SPI_SCK              GPIOB
#define PORT_SPI_MISO             GPIOB
#define PORT_SPI_MOSI             GPIOB

#define PIN_SPI_CS                GPIO_Pin_12
#define PIN_SPI_SCK               GPIO_Pin_13
#define PIN_SPI_MISO              GPIO_Pin_14
#define PIN_SPI_MOSI              GPIO_Pin_15


#define SPI_CS_ENABLE             (PORT_SPI_CS->BRR  = PIN_SPI_CS)
#define SPI_CS_DISABLE            (PORT_SPI_CS->BSRR = PIN_SPI_CS)

#define SPI_SCK_LOW               (PORT_SPI_SCK->BRR  = PIN_SPI_SCK)
#define SPI_SCK_HIGH              (PORT_SPI_SCK->BSRR = PIN_SPI_SCK)

#define SPI_MISO_READ             (PORT_SPI_MISO->IDR & PIN_SPI_MISO)

#define SPI_MOSI_LOW              (PORT_SPI_MOSI->BRR  = PIN_SPI_MOSI)
#define SPI_MOSI_HIGH             (PORT_SPI_MOSI->BSRR = PIN_SPI_MOSI)


/* 函数申明 ------------------------------------------------------------------*/
void SPI_Initializes(void);
void SPI_WriteByte(uint8_t TxData);
uint8_t SPI_ReadByte(void);


#endif /* _SPI_H */

/**** Copyright (C)2016 strongerHuang. All Rights Reserved **** END OF FILE ****/
