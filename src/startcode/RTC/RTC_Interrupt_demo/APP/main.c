/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/23
*描  述:  RTC演示主程序 
            RTC间隔1s发生一次中断，计数，LD1奇数秒时点亮，偶数秒时关闭；
            月，日，时，分，秒分别发生一次中断，若中断均产生，则LD2-LD4常亮；
            若任意中断未产生，则LD2-LD4闪烁；
*备  注:  适用于ES8P508x芯片
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{
    SystemClockConfig();
    DeviceClockAllEnable();

    SysTickInit();
    LightInit();

    GPIOA_SetBit(GPIO_Pin_14);          //熄灭LD1
    GPIOA_SetBit(GPIO_Pin_13);          //熄灭LD2
    GPIOA_SetBit(GPIO_Pin_12);          //熄灭LD3
    GPIOA_SetBit(GPIO_Pin_11);          //熄灭LD4

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
