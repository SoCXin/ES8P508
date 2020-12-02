/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/22
*描  述: PA21引脚输入下降沿方波信号（信号发生器，低于200Hz,此例程在输入100Hz方波时，开始有比较明显的效果）,
				 T32N0计数一次发生中断触发，LD1-LD4指示灯翻转
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main()
{    
    SystemClockConfig();                //配置时钟  
    DeviceClockAllEnable();             //打开所有外设时钟

    SysTickInit();
    LightInit();
    T32N0CNT_Init();                    //PA21输入计数

    GPIOA_SetBit(GPIO_Pin_14);          //熄灭LD1
    GPIOA_SetBit(GPIO_Pin_11);
    GPIOA_SetBit(GPIO_Pin_12);
    GPIOA_SetBit(GPIO_Pin_13);

    while(1);
}
