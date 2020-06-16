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
//    while((UART1->CSR & UART_IT_TXIEN) == 0); //循环发送,直到发送完毕
//    UART1->TDR = (ch & (uint16_t)0x00FF);
//    return ch;
//}

//#else
//#pragma import(__use_no_semihosting)
////标准库需要的支持函数
//struct __FILE
//{
//    int handle;

//};

//FILE __stdout;
////定义_sys_exit()以避免使用半主机模式
//_sys_exit(int x)
//{
//    x = x;
//}
//重定义fputc函数
int fputc(int ch, FILE *f)
{
    while((UART2->CSR & UART_IT_TXIEN) == 0); //循环发送,直到发送完毕
    UART2->TDR = (ch & (uint16_t)0x00FF);
    return ch;
}

void uart_initwBaudRate(UART_TypeDef* UARTx,u32 bound)
{
    //GPIO端口设置
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
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 推免复用输出
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;  //uart1_rx  pa10
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
        GPIO_Init(GPIOA, &GPIO_InitStructure);

    }
    if(UARTx == UART2)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;   //uart1_tx  pa2
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 推免复用输出
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;  //uart1_rx  pa3
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }
    if(UARTx == UART3)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;   //uart3_tx  pc10
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 推免复用输出
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;  //uart3_rx  pc11
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
		
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    /* Enable the UARTy_DMA1_IRQn Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel =UART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		
		    //UART 初始化设置
    UART_InitStructure.UART_BaudRate = bound;//串口波特率
    UART_InitStructure.UART_WordLength = UART_WordLength_8b;//字长为8位数据格式
    UART_InitStructure.UART_StopBits = UART_StopBits_1;//一个停止位
    UART_InitStructure.UART_Parity = UART_Parity_No;//无奇偶校验位
    UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_None;//无硬件数据流控制
    UART_InitStructure.UART_Mode = UART_Mode_Rx | UART_Mode_Tx;	//收发模式

    UART_Init(UARTx, &UART_InitStructure); //初始化串口1
    UART_ITConfig(UARTx, UART_IT_RXIEN, ENABLE);//开启串口接受中断
    UART_Cmd(UARTx, ENABLE);                    //使能串口1
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
