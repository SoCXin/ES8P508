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
函数名: void T32N0CNT_Init(void)
描  述: T32Nx初始化
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void T32N0CNT_Init(void)
{
    TIM_BaseInitStruType x;
    GPIO_InitStruType y;

	  y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_1;
    y.GPIO_Direction = GPIO_Dir_In;
    y.GPIO_PUEN = GPIO_PUE_Input_Disable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOA,GPIO_Pin_21,&y);

    x.TIM_ClkS = TIM_ClkS_CK0;              //外部时钟CK0
    x.TIM_SYNC = DISABLE;
    x.TIM_EDGE = TIM_EDGE_Fall;
    x.TIM_Mode = TIM_Mode_TC0;
    T32Nx_BaseInit(T32N0,&x);

    T32Nx_MAT0ITConfig(T32N0,TIM_Clr_Int);
    T32Nx_SetPREMAT(T32N0,0);
    T32Nx_SetCNT(T32N0,0);
    T32Nx_SetMAT0(T32N0,1);

    T32Nx_ITConfig(T32N0,TIM_IT_MAT0,ENABLE);
    NVIC_Init(NVIC_T32N0_IRQn,NVIC_Priority_1,ENABLE);
    T32N0_Enable();
}
