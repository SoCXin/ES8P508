/*********************************************************
*Copyright (C), 2015, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2016/06/22
*��  ��:  PA21���������½��ط����źţ��źŷ�����������200Hz,������������100Hz����ʱ����ʼ�бȽ����Ե�Ч����
          T16N3����һ�η����жϴ�����LD1-LD4ָʾ�Ʒ�ת
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main()
{    
    SystemClockConfig();                //����ʱ��  
    DeviceClockAllEnable();             //����������ʱ��

    SysTickInit();
    LightInit();
    T16N3CNT_Init();                    //PA21���������ʹ��ʱ�����岻Ҫ�ϵ�

    GPIOA_SetBit(GPIO_Pin_11);          //Ϩ��LD4
    GPIOA_SetBit(GPIO_Pin_12);          //Ϩ��LD3
    GPIOA_SetBit(GPIO_Pin_13);          //Ϩ��LD2
    GPIOA_SetBit(GPIO_Pin_14);          //Ϩ��LD1

    while(1);
}
