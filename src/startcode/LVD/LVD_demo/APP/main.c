/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/23
*描  述:  LVD程序：拨码开关由5V切换到3.3V时，LVD检测低于3.9V电压，再切换回5V后，则点亮LED1-LED4
*备  注:  适用于HRSDK-GDB-ES8P508x V1.1
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{
    SystemClockConfig();                //配置时钟  
    DeviceClockAllEnable();             //打开所有外设时钟

    SysTickInit();                      //系统滴答初始化
    LightInit();

    GPIOA_SetBit(GPIO_Pin_14);          //熄灭LD1
    GPIOA_SetBit(GPIO_Pin_13);          //熄灭LD2
    GPIOA_SetBit(GPIO_Pin_12);          //熄灭LD3
    GPIOA_SetBit(GPIO_Pin_11);          //熄灭LD4

    SCU_RegUnLock();
    SCU_LVDVS_3V9();
    SCU_LVDIFS_Fall();
    SCU_LVDFLT_Enable();
    NVIC_Init(NVIC_LVD_IRQn,NVIC_Priority_0,ENABLE);  //中断设置
    SCU_LVD_Enable();
    SCU_LVDIT_Enable();
    SCU_RegLock();

    while(1);
}
