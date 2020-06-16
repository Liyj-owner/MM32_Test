#include "sys.h"
#include "uart.h"

 uint8_t sp = 0;
 uint8_t USART_Finish_FLAG = 0;
 uint8_t Rx_Len;
 char SendBuffer[SENDBUFFSIZE]="";
 char RecBuffer[REVBUFFSIZE]="";
 
//////////////////////////////////////////////////////////////////
//#ifdef __GNUC__

//#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
//#else
//#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

//#endif

#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f);
//#ifdef USE_IAR
//PUTCHAR_PROTOTYPE
//{
//    while((UART1->CSR & UART_IT_TXIEN) == 0); //ѭ������,ֱ���������
//    UART1->TDR = (ch & (uint16_t)0x00FF);
//    return ch;
//}

//#else
//#pragma import(__use_no_semihosting)
////��׼����Ҫ��֧�ֺ���
//struct __FILE
//{
//    int handle;

//};

//FILE __stdout;
////����_sys_exit()�Ա���ʹ�ð�����ģʽ
//_sys_exit(int x)
//{
//    x = x;
//}
//�ض���fputc����
int fputc(int ch, FILE *f)
{
    while((UART2->CSR & UART_IT_TXIEN) == 0); //ѭ������,ֱ���������
    UART2->TDR = (ch & (uint16_t)0x00FF);
    return ch;
}

void uart_initwBaudRate(UART_TypeDef* UARTx,u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    UART_InitTypeDef UART_InitStructure;
		NVIC_InitTypeDef  NVIC_InitStructure;
    if(UARTx == UART1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_UART1, ENABLE);
    }
    else if(UARTx == UART2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART2, ENABLE);
    }
    else if(UARTx == UART3)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART3, ENABLE);
    }

    if(UARTx == UART1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;   //uart1_tx  pa9
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // ���⸴�����
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;  //uart1_rx  pa10
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //��������
        GPIO_Init(GPIOA, &GPIO_InitStructure);

    }
    if(UARTx == UART2)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;   //uart1_tx  pa2
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // ���⸴�����
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;  //uart1_rx  pa3
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //��������
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
    if(UARTx == UART3)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;   //uart3_tx  pc10
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // ���⸴�����
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;  //uart3_rx  pc11
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //��������
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
		
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    /* Enable the UARTy_DMA1_IRQn Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel =UART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		
		    //UART ��ʼ������
    UART_InitStructure.UART_BaudRate = bound;//���ڲ�����
    UART_InitStructure.UART_WordLength = UART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    UART_InitStructure.UART_StopBits = UART_StopBits_1;//һ��ֹͣλ
    UART_InitStructure.UART_Parity = UART_Parity_No;//����żУ��λ
    UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_None;//��Ӳ������������
    UART_InitStructure.UART_Mode = UART_Mode_Rx | UART_Mode_Tx;	//�շ�ģʽ

    UART_Init(UARTx, &UART_InitStructure); //��ʼ������1
    UART_ITConfig(UARTx, UART_IT_RXIEN, ENABLE);//�������ڽ����ж�
    UART_Cmd(UARTx, ENABLE);                    //ʹ�ܴ���1
}

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
