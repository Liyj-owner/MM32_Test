#include "key.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////
//������
//�������� ��������
//////////////////////////////////////////////////////////////////////////////////

//������ʼ������
void KEY_Init(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ��GPIOBʱ��


    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//PB1,K1��WK_UP��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó���������
		GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB1

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_10 | GPIO_Pin_11; //PB2,PB10,PB11,K2,K3,K4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB.2,10,11
}
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//����ֵ��
//0��û���κΰ�������
//KEY1_PRES��KEY1����
//KEY2_PRES��KEY2����
//KEY3_PRES��KEY3����
//KEY4_PRES��KEY4����
u8 KEY_Scan(u8 mode)
{
    static u8 key_up = 1; //�������ɿ���־
    if(mode)key_up = 1; //֧������
    if(key_up && (KEY1 == 1 || KEY2 == 0 || KEY3 == 0 || KEY4 == 0))
    {
        delay_ms(10);//ȥ����
        key_up = 0;
        if(KEY1 == 1)return KEY1_PRES;
        else if(KEY2 == 0)return KEY2_PRES;
        else if(KEY3 == 0)return KEY3_PRES;
        else if(KEY4 == 0)return KEY4_PRES;
    }
    else if(KEY1 == 0 && KEY3 == 1 && KEY4 == 1 && KEY2 == 1)key_up = 1;
    return 0;// �ް�������
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





