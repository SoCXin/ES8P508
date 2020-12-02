/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/22
*��  ��:  TN32N0��ʱ����˸LD1ָʾ��
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main()
{    
    SystemClockConfig();                //����ʱ��  
    DeviceClockAllEnable();             //����������ʱ��

    SysTickInit();                      //��ʼ��ϵͳ�δ�ʱ��
    LightInit();                        //ָʾ�Ƴ�ʼ��
    T32NxInit();

    GPIOA_SetBit(GPIO_Pin_11);          //Ϩ��LD4
    GPIOA_SetBit(GPIO_Pin_12);          //Ϩ��LD3
    GPIOA_SetBit(GPIO_Pin_13);          //Ϩ��LD2
    GPIOA_SetBit(GPIO_Pin_14);          //Ϩ��LD1

    while(1);
}
