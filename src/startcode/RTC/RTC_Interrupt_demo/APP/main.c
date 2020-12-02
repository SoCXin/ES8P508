/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/23
*��  ��:  RTC��ʾ������ 
            RTC���1s����һ���жϣ�������LD1������ʱ������ż����ʱ�رգ�
            �£��գ�ʱ���֣���ֱ���һ���жϣ����жϾ���������LD2-LD4������
            �������ж�δ��������LD2-LD4��˸��
*��  ע:  ������ES8P508xоƬ
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main(void)
{
    SystemClockConfig();
    DeviceClockAllEnable();

    SysTickInit();
    LightInit();

    GPIOA_SetBit(GPIO_Pin_14);          //Ϩ��LD1
    GPIOA_SetBit(GPIO_Pin_13);          //Ϩ��LD2
    GPIOA_SetBit(GPIO_Pin_12);          //Ϩ��LD3
    GPIOA_SetBit(GPIO_Pin_11);          //Ϩ��LD4

    g_sec_flag = 0;
    g_min_flag = 0;
    g_hour_flag = 0;
    g_day_flag = 0;
    g_month_flag = 0;

    RTC_Init(RTC_LOSC,RTC_HOUR24);      //RTC_LRC,RTC_LOSC

    RTC_WriteSecond(30);
    RTC_InterruptEnable(RTC_Interrupt_Source_Second);
    Delay1ms(3000);

    RTC_WriteMinute(30);
    RTC_WriteSecond(58);
    RTC_InterruptEnable(RTC_Interrupt_Source_Minute);
    Delay1ms(3000);

    RTC_WriteHour(14, 1);
    RTC_WriteMinute(59);
    RTC_WriteSecond(58);
    RTC_InterruptEnable(RTC_Interrupt_Source_Hour);
    Delay1ms(3000);

    RTC_WriteDay(25);
    RTC_WriteHour(23, 1);
    RTC_WriteMinute(59);
    RTC_WriteSecond(58);
    RTC_InterruptEnable(RTC_Interrupt_Source_Day);
    Delay1ms(3000);

    RTC_WriteMonth(6);
    RTC_WriteDay(30);
    RTC_WriteHour(23, 1);
    RTC_WriteMinute(59);
    RTC_WriteSecond(58);
    RTC_InterruptEnable(RTC_Interrupt_Source_Month);
    Delay1ms(3000);

    while (1)
    {
        if(g_sec_flag == 1
           && g_min_flag == 1
           && g_hour_flag == 1
           && g_day_flag == 1
           && g_month_flag == 1)
        {
            GPIOA_ResetBit(GPIO_Pin_13);
            GPIOA_ResetBit(GPIO_Pin_12);
            GPIOA_ResetBit(GPIO_Pin_11);
        }
        else
        {
            GPIOA_ResetBit(GPIO_Pin_13);
            GPIOA_ResetBit(GPIO_Pin_12);
            GPIOA_ResetBit(GPIO_Pin_11);
            Delay1ms(500);
            GPIOA_SetBit(GPIO_Pin_13);
            GPIOA_SetBit(GPIO_Pin_12);
            GPIOA_SetBit(GPIO_Pin_11);
            Delay1ms(500);
        }
    }
}
