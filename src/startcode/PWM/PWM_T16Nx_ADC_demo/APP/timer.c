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
函数名: void PWM_Init(void)
描  述: pwm初始化
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void T16Nx_Init(void)
{
    TIM_BaseInitStruType x;
    GPIO_InitStruType y;
    T16Nx_PWMInitStruType z;

	  y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_3;
    y.GPIO_Direction = GPIO_Dir_Out;
    y.GPIO_PUEN = GPIO_PUE_Input_Disable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Normal;

    GPIO_Init(GPIOA,GPIO_Pin_28,&y);                     //PA28

    x.TIM_ClkS = TIM_ClkS_PCLK;                         //选择时钟：Pclk
    x.TIM_SYNC = DISABLE;
    x.TIM_EDGE = TIM_EDGE_Rise;
    x.TIM_Mode = TIM_Mode_PWM ;                         //设为PWM模式
    T16Nx_BaseInit(T16N2,&x);

    T16N2_PwmOut0_Enable();                             //使能端口输出0
    T16Nx_MAT0Out0Config(T16N2,TIM_Out_High);           //匹配2：输出高
    T16Nx_MAT1Out0Config(T16N2,TIM_Out_Low);            //匹配3：输出低

    z.T16Nx_MOE0 = ENABLE;
    z.T16Nx_MOE1 = ENABLE;
    z.T16Nx_POL0 = POSITIVE;
    z.T16Nx_POL1 = POSITIVE;
    T16Nx_PWMOutConfig(T16N2,&z);                       //配置输出

    T16Nx_SetPREMAT(T16N2,20);                          //预分频
    T16Nx_SetMAT0(T16N2,30000);                         //控制占空比
    T16Nx_SetMAT1(T16N2,60000);                         //控制频率

    T16Nx_TRG_Config(T16N2,T16Nx_MAT0,ENABLE);          //匹配MAT0触发ADC

    T16Nx_MAT0ITConfig(T16N2,TIM_Go_Int);               //匹配2：继续计数
    T16Nx_MAT1ITConfig(T16N2,TIM_Clr_Int);              //匹配3：清0

    T16Nx_ITConfig(T16N2,TIM_IT_MAT0,DISABLE);          //可选择是否使能中断
    T16Nx_ITConfig(T16N2,TIM_IT_MAT1,DISABLE);

    NVIC_Init(NVIC_T16N2_IRQn,NVIC_Priority_1,DISABLE);
    T16N2_Enable();
}
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
    T16Nx_BaseInit(T16N3,&x);

    T16Nx_SetPREMAT(T16N3,1);
    T16Nx_SetMAT0(T16N3,20000);
    T16Nx_MAT0ITConfig(T16N3,TIM_Clr_Int);
    T16Nx_ITConfig(T16N3,TIM_IT_MAT0,ENABLE);
    NVIC_Init(NVIC_T16N3_IRQn,NVIC_Priority_1,ENABLE);
    T16N3_Enable();
}



