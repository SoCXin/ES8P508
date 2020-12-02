/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  ��ʱ��CAP��ʾ������ 
            T32Nx��Ӧ�������뷽���ź�(�źŷ�����������200Hz)��T32Nx���ݲ���״̬�Ͳ����������һ���жϣ�LD1ָʾ�Ʒ�ת
*��  ע:  ������ES8P508xоƬ
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

uint32_t count = 0;

int main(void)
{
    SystemClockConfig();                //����ʱ��  
    DeviceClockAllEnable();             //����������ʱ��

    LightInit();
    T32N0CAPInit();                     //PA21,PA22���벶��

    GPIOA_SetBit(GPIO_Pin_14);        //ʹ��LD1ָʾ����״̬
    GPIOA_SetBit(GPIO_Pin_12);
    GPIOA_SetBit(GPIO_Pin_13);
    GPIOA_SetBit(GPIO_Pin_11);

    while(1);
}

