#include "beep.h"

void Beep_init(void)
{
	TIM1_PWM_Init();
}

void Beep_On(void)
{
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void Beep_Off(void)
{
	TIM_CtrlPWMOutputs(TIM1, DISABLE);
}