/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H
#define __UART_H
#include "stdio.h"
#include "sys.h"
//´®¿Ú1³õÊ¼»¯

#define SendData SendBuffer

extern uint8_t sp;
extern  uint8_t Rx_Len;
extern uint8_t USART_Finish_FLAG;

#define REVBUFFSIZE  100
#define SENDBUFFSIZE 100

extern  char SendBuffer[SENDBUFFSIZE];
extern  char RecBuffer [REVBUFFSIZE];

void uart_initwBaudRate(UART_TypeDef* UARTx,u32 bound);
#endif

/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2019 MindMotion ----------------------*/
