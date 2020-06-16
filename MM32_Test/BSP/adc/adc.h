#ifndef __ADC_H_
#define __ADC_H_
#include "HAL_device.h"
#include	"uart.h"

void ADC1_Init(uint8_t ADC_Channel_x);
u16 ADC1_SingleChannel_Get(uint8_t ADC_Channel_x);
u16 Get_Adc_Average(uint8_t ADC_Channel_x, uint8_t times);
void Get_AdcValue(void);
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
