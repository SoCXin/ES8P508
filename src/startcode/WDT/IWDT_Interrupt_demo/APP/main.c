/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者: Liut
*版  本:  V1.00
*日  期:  2017/06/23
*描  述:  WDT演示主程序 
           看门狗定时2s，在看门狗中断函数中，喂狗则不复位，LD1点亮200ms，不喂狗则复位，LD1不正常闪烁
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main()
{    
    SystemClockConfig();                //配置时钟  
    DeviceClockAllEnable();             //打开所有外设时钟

    SysTickInit();                      //初始化系统滴答定时器
    LightInit();                        //指示灯初始化
    WdtInit();                          //WDT初始化

    GPIOA_SetBit(GPIO_Pin_11);          //熄灭LD4
    GPIOA_SetBit(GPIO_Pin_12);          //熄灭LD3
    GPIOA_SetBit(GPIO_Pin_13);          //熄灭LD2
    GPIOA_SetBit(GPIO_Pin_14);          //熄灭LD1

    g_wdt_inte_flag = 0;                //看门狗中断是否产生标志

    while(1)
    {   
        if(1 == g_wdt_inte_flag)
        {
            g_wdt_inte_flag = 0;
            GPIOA_ResetBit(GPIO_Pin_14);    //点亮LD1
            Delay1ms(200);
        }
        else
        {
            GPIOA_SetBit(GPIO_Pin_14);      //熄灭LD1
        }
    }
}
