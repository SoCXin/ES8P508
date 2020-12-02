/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/23
*��  ��:  RTC��ʾ������ 
        �գ��ֱܷ���һ���жϣ����жϾ���������LD2-LD4������
        �������ж�δ��������LD2-LD4��˸��
*��  ע:  ������HRSDK-GDB-ES8P508xоƬ
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

    g_day_flag = 0;
    g_week_flag = 0;

    RTC_Init(RTC_LRC,RTC_HOUR24);

    RTC_WriteHour(15, 0);
    RTC_WriteMinute(24);
    RTC_WriteSecond(58);

    RTC_WriteDayAlarmHour(15, 0);
    RTC_WriteDayAlarmMinute(25);

    RTC_InterruptEnable(RTC_Interrupt_Source_DayALE);
    Delay1ms(3000);

    RTC_WriteWeek(4);
    RTC_WriteMonth(7);
    RTC_WriteDay(6);
    RTC_WriteHour(16, 0);
    RTC_WriteMinute(24);
    RTC_WriteSecond(58);

    RTC_WriteWeekAlarmWeek(4);
    RTC_WriteWeekAlarmHour(16, 0);
    RTC_WriteWeekAlarmMinute(25);

    RTC_InterruptEnable(RTC_Interrupt_Source_WeekALE);
    Delay1ms(3000);

    while (1)
    {
        if(g_day_flag == 1 && g_week_flag == 1)
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
