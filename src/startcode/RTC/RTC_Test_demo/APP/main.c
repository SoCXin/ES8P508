/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/23
*��  ��:  RTC��ʾ������ 
            RTCдһ���̶�ʱ�䣬����ʱ���Ƿ���д��ʱ��һ�£���һ����LD1-LD4�Ƽ����˸��һ����LD1-LD4������
*��  ע:  ������ES8P508xоƬ
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

/*********************************************************
������: uint32_t RTC_Test(void)
��  ��: ʵʱʱ��API����
����ֵ: ��
���ֵ: ��
����ֵ: SUCCESS: ���Գɹ�
        ERROR: ����ʧ��
**********************************************************/
ErrorStatus RTC_Test(void)
{
    uint32_t sec, min, hour, day, month, year, week;
    uint32_t meridiem, mode;
    uint32_t wa_min, wa_hour, wa_week;
    uint32_t da_min, da_hour;

    RTC_Init(RTC_LRC,RTC_HOUR24);

    /* ��ȡ�ϵ�Ĭ��ֵ */
    mode = RTC_ReadHourmode();
    sec = RTC_ReadSecond();
    min = RTC_ReadMinute();
    hour = RTC_ReadHour(&meridiem);
    day = RTC_ReadDay();
    month = RTC_ReadMonth();
    year = RTC_ReadYear();
    week = RTC_ReadWeek();
    wa_min = RTC_ReadWeekAlarmMinute();
    wa_hour = RTC_ReadWeekAlarmHour(&meridiem);
    wa_week = RTC_ReadWeekAlarmWeek();
    da_min = RTC_ReadDayAlarmMinute();
    da_hour = RTC_ReadDayAlarmHour(&meridiem);

    /* д���µ�ֵ */
    RTC_WriteWeekAlarmMinute(25);
    wa_min = RTC_ReadWeekAlarmMinute();

    RTC_WriteWeekAlarmHour(21, 0);
    wa_hour = RTC_ReadWeekAlarmHour(&meridiem);

    RTC_WriteWeekAlarmWeek(6);
    wa_week = RTC_ReadWeekAlarmWeek();

    RTC_WriteDayAlarmMinute(30);
    da_min = RTC_ReadDayAlarmMinute();

    RTC_WriteDayAlarmHour(7, 1);
    da_hour = RTC_ReadDayAlarmHour(&meridiem);

    RTC_WriteWeek(3);
    week = RTC_ReadWeek();

    RTC_WriteYear(2017);
    year = RTC_ReadYear();
   
    RTC_WriteMonth(6);
    month = RTC_ReadMonth();

    RTC_WriteDay(29);
    day = RTC_ReadDay();

    RTC_WriteHour(14, 1);
    hour = RTC_ReadHour(&meridiem);

    RTC_WriteMinute(58);
    min = RTC_ReadMinute();

    RTC_WriteSecond(30);
    sec = RTC_ReadSecond();

    /* ��ȡ��ֵ */
    if ((mode != RTC_HOUR24)
        || (sec != 30) || (min != 58) || (hour != 14) || (day != 29) || (month != 6) || (year != 2017) || (week != 3)
        || (wa_min != 25)|| (wa_hour != 21)|| (wa_week != 6)
        || (da_min != 30)|| (da_hour != 7))
        return ERROR;

    return SUCCESS;
}

/*********************************************************
������: int main(void)
��  ��: 
����ֵ: ��
���ֵ: ��
����ֵ: 
**********************************************************/
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

    while (1)
    {
        if(ERROR == RTC_Test())                                   //RTC��дʱ��
        {
            GPIOA_ResetBit(GPIO_Pin_14);
            GPIOA_ResetBit(GPIO_Pin_13);
            GPIOA_ResetBit(GPIO_Pin_12);
            GPIOA_ResetBit(GPIO_Pin_11);
            Delay1ms(500);
            GPIOA_SetBit(GPIO_Pin_14);
            GPIOA_SetBit(GPIO_Pin_13);
            GPIOA_SetBit(GPIO_Pin_12);
            GPIOA_SetBit(GPIO_Pin_11);
            Delay1ms(500);
        }
        else
        {
            GPIOA_ResetBit(GPIO_Pin_14);
            GPIOA_ResetBit(GPIO_Pin_13);
            GPIOA_ResetBit(GPIO_Pin_12);
            GPIOA_ResetBit(GPIO_Pin_11);
        }
    }
}
