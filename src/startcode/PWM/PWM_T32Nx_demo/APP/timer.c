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
函数名: void PWM_Init(void)
描  述: pwm初始化
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void T32Nx_Init(void)
{
    TIM_BaseInitStruType x;
    GPIO_InitStruType y;
    y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_2;
    y.GPIO_Direction = GPIO_Dir_Out;
    y.GPIO_PUEN = GPIO_PUE_Input_Disable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOA,GPIO_Pin_2,&y);                     //PA2

    x.TIM_ClkS = TIM_ClkS_PCLK;                         //选择时钟：Pclk
    x.TIM_SYNC = DISABLE;
    x.TIM_EDGE = TIM_EDGE_Rise;
    x.TIM_Mode = TIM_Mode_PWM ;                         //设为PWM模式
    T32Nx_BaseInit(T32N0,&x);

    T32N0_PwmOut0_Enable();                             //使能端口输出0
    T32Nx_MAT0Out0Config(T32N0,TIM_Out_High);           //匹配2：输出高
    T32Nx_MAT1Out0Config(T32N0,TIM_Out_Low);            //匹配3：输出低

    T32Nx_SetPREMAT(T32N0,20);                          //预分频
    T32Nx_SetMAT0(T32N0,50);                            //控制占空比
    T32Nx_SetMAT1(T32N0,200);                           //控制频率200us

    T32Nx_MAT0ITConfig(T32N0,TIM_Go_Int);               //匹配2：继续计数
    T32Nx_MAT1ITConfig(T32N0,TIM_Clr_Int);              //匹配3：清0

    NVIC_Init(NVIC_T32N0_IRQn,NVIC_Priority_1,DISABLE);
    T32Nx_ITConfig(T32N0,TIM_IT_MAT0,DISABLE);          //可选择是否使能中断
    T32Nx_ITConfig(T32N0,TIM_IT_MAT1,DISABLE);
    T32N0_Enable();
}



