/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��: Liut
*��  ��:  V1.00
*��  ��:  2017/06/23
*��  ��:  WDT��ʾ������ 
           ���Ź���ʱ2s���ڿ��Ź��жϺ����У�ι���򲻸�λ��LD1����200ms����ι����λ��LD1��������˸
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

    GPIOA_SetBit(GPIO_Pin_11);          //Ϩ��LD4
    GPIOA_SetBit(GPIO_Pin_12);          //Ϩ��LD3
    GPIOA_SetBit(GPIO_Pin_13);          //Ϩ��LD2
    GPIOA_SetBit(GPIO_Pin_14);          //Ϩ��LD1

    g_wdt_inte_flag = 0;                //���Ź��ж��Ƿ������־

    while(1)
    {   
        if(1 == g_wdt_inte_flag)
        {
            g_wdt_inte_flag = 0;
            GPIOA_ResetBit(GPIO_Pin_14);    //����LD1
            Delay1ms(200);
        }
        else
        {
            GPIOA_SetBit(GPIO_Pin_14);      //Ϩ��LD1
        }
    }
}
