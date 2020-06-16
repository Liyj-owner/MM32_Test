#include "sys.h"
#include "delay.h"
#include "uart.h"
#include "led.h"
#include "eeprom.h"
#include "sflash.h"
#include "tim.h"
#include "key.h"
#include "beep.h"
#include	"adc.h"


u8 UART_Finish_FLAG=0;
void Led_Key_Test(void);
/********************************************************************************************************
**函数信息 ：UART2_IRQHandler(void)
**功能描述 ：UART2中断
**输入参数 ：无
**输出参数 ：无
********************************************************************************************************/
void UART2_IRQHandler(void)
{
		uint8_t i=0;
		if(UART_GetFlagStatus(UART2,UART_IT_RXIEN)==SET)
			{
				if(UART_ReceiveData(UART2)=='\n')
				{
					
						UART_Finish_FLAG=1;
						RecBuffer[sp]='\0';
						sp=0;	
				}
				else
				{
						if(sp==0)
						{
							for(i=0;i<REVBUFFSIZE;i++)
							{
							SendData[i]='\0';
							RecBuffer[i]='\0';
							}
						}
						RecBuffer[sp]=UART_ReceiveData(UART2);
						SendData[sp]=RecBuffer[sp];
						sp++;
				}
			}
		if(UART_GetITStatus(UART2,UART_IT_RXIEN)!=RESET)
		{
				UART_ClearITPendingBit(UART2,UART_IT_RXIEN);
		}
}

int main(void)
{

	u8 key_flag=0;
	u8 len;
    delay_init();	    	
    LED_Init();
		KEY_Init();
		uart_initwBaudRate(UART2,115200);
    TIM1_PWM_Init();
    TIM_SetCompare1(TIM1, 200);
		I2C_Initializes();
		ADC1_Init( ADC_Channel_5);
		Beep_init();
		delay_ms(1000);
		printf("\n  This is a MM32 Test Demo!!!\n");
		printf("\n	You can input the following command:\n");
		printf("\n1.BEEPON\n");
		printf("\n2.BEEPOFF\n");
		printf("\n3.GETADC\n");
		printf("\n4.TESTEEP\n");
		
    while(1)
    {
			Led_Key_Test();
			if(UART_Finish_FLAG)
			{
				len=strlen(RecBuffer)-1;
				if(!strncmp(RecBuffer,"BEEPON",len))
				{
					Beep_On();
					printf("BEEPON_OK \n");
				}
				else if(!strncmp(RecBuffer,"BEEPOFF",len))
				{
					Beep_Off();
					printf("BEEPOFF_OK \n");
				}
				else if(!strncmp(RecBuffer,"GETADC",len))
				{
					Get_AdcValue();
					printf("GETADC_OK \n");
				}
				else if(!strncmp(RecBuffer,"TESTEEP",len))
				{
		
					printf("TESTEEP_OK \n");
					ee_Test();
				}
				else 
				{
					printf("Input error!!!\n");
					printf("Please Input again!!!\n");
				}
				UART_Finish_FLAG=0;
			}
				
    }		
}
		
void Led_Key_Test(void)
{
	u8 status;
	status=KEY_Scan(0);
	switch(status)
        {
            case KEY1_PRES:
                LED1 = !LED1;
                break;
            case KEY2_PRES:
                LED2 = !LED2;
                break;
            case KEY3_PRES:
                LED3 = !LED3;
                break;
            case KEY4_PRES:
                LED4 = !LED4;
                break;
            default:
                delay_ms(10);
        }
}
