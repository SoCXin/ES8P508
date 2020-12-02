/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  定时器CAP演示主程序 
            T32Nx对应引脚输入方波信号(信号发生器，低于200Hz)，T32Nx根据捕获状态和捕获次数发生一次中断，LD1指示灯翻转
*备  注:  适用于ES8P508x芯片
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

uint32_t count = 0;

int main(void)
{
    SystemClockConfig();                //配置时钟  
    DeviceClockAllEnable();             //打开所有外设时钟

    LightInit();
    T32N0CAPInit();                     //PA21,PA22输入捕获

    GPIOA_SetBit(GPIO_Pin_14);        //使用LD1指示捕获状态
    GPIOA_SetBit(GPIO_Pin_12);
    GPIOA_SetBit(GPIO_Pin_13);
    GPIOA_SetBit(GPIO_Pin_11);

    while(1);
}

