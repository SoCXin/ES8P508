/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  timer.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/25
*描  述:  T32N模块程序
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "timer.h"

/*********************************************************
函数名: void T32NxInit(void)
描  述: T32Nx定时器初始化
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void T32NxInit(void)
{
    TIM_BaseInitStruType x;

    x.TIM_ClkS = TIM_ClkS_PCLK;
    x.TIM_SYNC = DISABLE;
    x.TIM_EDGE = TIM_EDGE_Rise;
    x.TIM_Mode = TIM_Mode_TC0;
    T32Nx_BaseInit(T32N0,&x);

    T32Nx_SetPREMAT(T32N0,1);

    T32Nx_SetMAT0(T32N0,40000);

    NVIC_Init(NVIC_T32N0_IRQn,NVIC_Priority_1,ENABLE);

    T32Nx_MAT0ITConfig(T32N0,TIM_Clr_Int);

    T32Nx_ITConfig(T32N0,TIM_IT_MAT0,ENABLE);

    T32N0_Enable();
}
