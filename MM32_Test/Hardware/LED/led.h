/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H
#define __LED_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////
//开发板
//LED驱动代码
//////////////////////////////////////////////////////////////////////////////////
#define LED1 PAout(15)	// PA15
#define LED2 PCout(10)	// PC10
#define LED3 PCout(11)	// PC11
#define LED4 PCout(12)	// PC12

#endif /*__LED_H*/
void LED_Init(void);//初始化
