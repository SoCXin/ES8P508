/*********************************************************
*Copyright (C), 2015, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��: Liut
*��  ��:  V1.00
*��  ��:  2017/06/23
*��  ��:  WDT��ʾ������ 
           LD1���200ms��˸�����Ź���ʱ2s��ι���򲻸�λ��LD1������˸����ι����λ��LD1���ֲ�������˸
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
    WdtInit();                          //WDT��ʼ��

    GPIOA_SetBit(GPIO_Pin_14);          //Ϩ��LD1
    GPIOA_SetBit(GPIO_Pin_13);          //Ϩ��LD2
    GPIOA_SetBit(GPIO_Pin_12);          //Ϩ��LD3
    GPIOA_SetBit(GPIO_Pin_11);          //Ϩ��LD4

    while(1)
    {
        IWDT_Clear();                    //ι���򲻸�λ����ι����λ

        Delay1ms(200);
        GPIOA_SetBit(GPIO_Pin_14);      //Ϩ��LD1
        Delay1ms(200);
        GPIOA_ResetBit(GPIO_Pin_14);    //Ϩ��LD1
    }
}
