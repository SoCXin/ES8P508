/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  timer.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/25
*描  述:  T16N模块程序
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "timer.h"

/*********************************************************
函数名: void T16N3Init(void)
描  述: T16N3定时器初始化
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void T16N3Init(void)
{
    TIM_BaseInitStruType x;

    x.TIM_ClkS = TIM_ClkS_PCLK;
    x.TIM_SYNC = DISABLE;
    x.TIM_EDGE = TIM_EDGE_Rise;
    x.TIM_Mode = TIM_Mode_TC0;
    T16Nx_BaseInit(T16N3, &x);

    T16Nx_SetPREMAT(T16N3, 1);
    T16Nx_SetMAT0(T16N3, 20000);
    T16Nx_MAT0ITConfig(T16N3, TIM_Clr_Int);
    T16Nx_ITConfig(T16N3, TIM_IT_MAT0, ENABLE);
    NVIC_Init(NVIC_T16N3_IRQn, NVIC_Priority_1, ENABLE);
    T16N3_Enable();
}

