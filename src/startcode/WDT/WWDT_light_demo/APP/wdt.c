/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  wdt.h
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/29
*描  述:  WDT函数文件
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "wdt.h"

/***************************************************************
 描  述：WDT初始化初始化
 输入值：无
 返回值：无
***************************************************************/
void WdtInit(void)
{
    WWDT_InitStruType x;

    WWDT_RegUnLock();

    x.WDT_Tms = 2000;           //喂狗周期2s
    x.WDT_IE = ENABLE;
    x.WDT_Rst = ENABLE;
    x.WDT_Clock = WDT_CLOCK_PCLK;
    x.WDT_Win = WDT_WIN_50;
    WWDT_Init(&x);
    WWDT_Enable();
    WWDT_RegLock();

    NVIC_Init(NVIC_WWDT_IRQn,NVIC_Priority_1,ENABLE);
}
