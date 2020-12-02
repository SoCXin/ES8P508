/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/22
*描  述:  SysTick演示主程序
            Light灯闪烁，LD1，LD3和LD2，LD4间隔200ms分别闪烁，间隔时间使用SysTick定时器
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

    GPIOA_SetBit(GPIO_Pin_31);          //熄灭LD1
    GPIOA_SetBit(GPIO_Pin_2);          //熄灭LD2
    GPIOA_SetBit(GPIO_Pin_3);          //熄灭LD3
    GPIOA_SetBit(GPIO_Pin_4);          //熄灭LD4

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
