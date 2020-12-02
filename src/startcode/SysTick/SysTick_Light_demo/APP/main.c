/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/22
*��  ��:  SysTick��ʾ������
            Light����˸��LD1��LD3��LD2��LD4���200ms�ֱ���˸�����ʱ��ʹ��SysTick��ʱ��
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

    GPIOA_SetBit(GPIO_Pin_31);          //Ϩ��LD1
    GPIOA_SetBit(GPIO_Pin_2);          //Ϩ��LD2
    GPIOA_SetBit(GPIO_Pin_3);          //Ϩ��LD3
    GPIOA_SetBit(GPIO_Pin_4);          //Ϩ��LD4

    while(1)
    {
        Delay1ms(200);
        GPIOA_ResetBit(GPIO_Pin_14);
        GPIOA_ResetBit(GPIO_Pin_12);
        Delay1ms(200);
        GPIOA_SetBit(GPIO_Pin_14);
        GPIOA_SetBit(GPIO_Pin_12);

        Delay1ms(200);
        GPIOA_ResetBit(GPIO_Pin_13);
        GPIOA_ResetBit(GPIO_Pin_11);
        Delay1ms(200);
        GPIOA_SetBit(GPIO_Pin_13);
        GPIOA_SetBit(GPIO_Pin_11);
    }
}
