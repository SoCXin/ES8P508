/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  定时器PWM输出演示主程序 
            PA10产生周期为200us，占空比为150/200的PWM波形
*备  注:  适用親RSDK-GDB-ES8P508x芯片
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{
    SystemClockConfig();            //配置时钟  
    DeviceClockAllEnable();         //打开所有外设时钟

    T16Nx_Init();

    while(1);
}

