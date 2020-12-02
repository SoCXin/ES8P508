/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  定时器CAP演示主程序 
      T16Nx对应引脚输入方波信号（信号发生器，低于200Hz），T16Nx根据捕获状态和捕获次数发生一次中断，LD1指示灯翻转
      注！！！！！！！！！！！！！！此例程PB4，PB5两端口同时复用为我司学习母板AMCU模块的通讯端口，母板上对于这两个
      IO进行了硬件弱上拉处理，所以此处的现象不对，用户请特别注意，可通过PB6,PB7、PA28,PA29、PB2,PB3三组的定时器复
      用配置进行学习、验正。我司学习子板自带LD1的指示灯，所以学习子板不配合母板的情况下PB4，PB5两端口输入捕获的功
      能正常。
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
    T16N0CAPInit();                     //PB4,PB5输入捕获！！！！！！！！请看头文件说明
    T16N1CAPInit();                     //PB6,PB7输入捕获
    T16N2CAPInit();                     //PA28,PA29输入捕获
    T16N3CAPInit();                     //PB2,PB3输入捕获

    GPIOA_SetBit(GPIO_Pin_14);          //使用LD1指示捕获状态
    GPIOA_SetBit(GPIO_Pin_13);
    GPIOA_SetBit(GPIO_Pin_12);      
    GPIOA_SetBit(GPIO_Pin_11);
    while(1);
}

