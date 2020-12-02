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
函数名: void T16N0CAPInit(void)
描  述: T16N0定时器初始化 输入端口0,1上升沿，捕获16次
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void T16N0CAPInit(void)
{
    TIM_BaseInitStruType x;
    TIM_CapInitStruType y;
    GPIO_InitStruType z;

	z.GPIO_Signal = GPIO_Pin_Signal_Digital;
    z.GPIO_Func = GPIO_Func_1;
    z.GPIO_Direction = GPIO_Dir_In;
    z.GPIO_PUEN = GPIO_PUE_Input_Disable;
    z.GPIO_PDEN = GPIO_PDE_Input_Disable;
    z.GPIO_OD = GPIO_ODE_Output_Disable;
    z.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOB,GPIO_Pin_4,&z);
    GPIO_Init(GPIOB,GPIO_Pin_5,&z);

    x.TIM_ClkS = TIM_ClkS_PCLK;
    x.TIM_SYNC = DISABLE;
    x.TIM_EDGE = TIM_EDGE_Rise;
    x.TIM_Mode = TIM_Mode_CAP;
    T16Nx_BaseInit(T16N0,&x);

    T16Nx_MAT0ITConfig(T16N0,TIM_Go_No);                //MAT0匹配设置
    T16Nx_MAT2ITConfig(T16N0,TIM_Go_No);                //MAT2匹配设置

    y.TIM_CapFall = DISABLE;
    y.TIM_CapRise = ENABLE;
    y.TIM_CapIS0 = ENABLE;
    y.TIM_CapIS1 = ENABLE;
    y.TIM_CapTime = TIM_CapTime_16;                      //捕捉1次
    T16Nx_CapInit(T16N0,&y);

    T16Nx_ITConfig(T16N0,TIM_IT_CAP0,ENABLE);           //输入端口0捕捉中断
    T16Nx_ITConfig(T16N0,TIM_IT_CAP1,ENABLE);           //输入端口1捕捉中断
    NVIC_Init(NVIC_T16N0_IRQn,NVIC_Priority_1,ENABLE);  //中断设置
    T16N0_Enable();                                     //使能定时器

}
/*********************************************************
函数名: void T16N1CAPInit(void)
描  述: T16N1定时器初始化 输入端口0,1，下降沿，捕获2次
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void T16N1CAPInit(void)
{
    TIM_BaseInitStruType x;
    TIM_CapInitStruType y;
    GPIO_InitStruType z;
 
	z.GPIO_Signal = GPIO_Pin_Signal_Digital;
    z.GPIO_Func = GPIO_Func_1;
    z.GPIO_Direction = GPIO_Dir_In;
    z.GPIO_PUEN = GPIO_PUE_Input_Disable;
    z.GPIO_PDEN = GPIO_PDE_Input_Disable;
    z.GPIO_OD = GPIO_ODE_Output_Disable;
    z.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOB,GPIO_Pin_6,&z);
    GPIO_Init(GPIOB,GPIO_Pin_7,&z);

    x.TIM_ClkS = TIM_ClkS_PCLK;
    x.TIM_SYNC = DISABLE;
    x.TIM_EDGE = TIM_EDGE_Rise;
    x.TIM_Mode = TIM_Mode_CAP;
    T16Nx_BaseInit(T16N1,&x);

    T16Nx_MAT0ITConfig(T16N1,TIM_Go_No);                //MAT0匹配设置
    T16Nx_MAT2ITConfig(T16N1,TIM_Go_No);                //MAT2匹配设置

    y.TIM_CapRise = DISABLE;
    y.TIM_CapFall = ENABLE;
    y.TIM_CapIS0 = ENABLE;
    y.TIM_CapIS1 = ENABLE;
    y.TIM_CapTime = TIM_CapTime_2;                      //捕捉2次
    T16Nx_CapInit(T16N1,&y);

    T16Nx_ITConfig(T16N1,TIM_IT_CAP0,ENABLE);           //输入端口0捕捉中断
    T16Nx_ITConfig(T16N1,TIM_IT_CAP1,ENABLE);           //输入端口1捕捉中断
    NVIC_Init(NVIC_T16N1_IRQn,NVIC_Priority_1,ENABLE);  //中断设置
    T16N1_Enable();                                     //使能定时器
}

/*********************************************************
函数名: void T16N2CAPInit(void)
描  述: T16N2定时器初始化 输入端口0,1上升沿，捕获1次
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void T16N2CAPInit(void)
{
    TIM_BaseInitStruType x;
    TIM_CapInitStruType y;
    GPIO_InitStruType z;

	z.GPIO_Signal = GPIO_Pin_Signal_Digital;
    z.GPIO_Func = GPIO_Func_3;
    z.GPIO_Direction = GPIO_Dir_In;
    z.GPIO_PUEN = GPIO_PUE_Input_Disable;
    z.GPIO_PDEN = GPIO_PDE_Input_Disable;
    z.GPIO_OD = GPIO_ODE_Output_Disable;
    z.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOA,GPIO_Pin_28,&z);
    GPIO_Init(GPIOA,GPIO_Pin_29,&z);

    x.TIM_ClkS = TIM_ClkS_PCLK;
    x.TIM_SYNC = DISABLE;
    x.TIM_EDGE = TIM_EDGE_Rise;
    x.TIM_Mode = TIM_Mode_CAP;
    T16Nx_BaseInit(T16N2,&x);

    T16Nx_MAT0ITConfig(T16N2,TIM_Go_No);                //MAT0匹配设置
    T16Nx_MAT2ITConfig(T16N2,TIM_Go_No);                //MAT2匹配设置

    y.TIM_CapRise = ENABLE;
    y.TIM_CapFall = DISABLE;
    y.TIM_CapIS0 = ENABLE;
    y.TIM_CapIS1 = ENABLE;
    y.TIM_CapTime = TIM_CapTime_1;                      //捕捉1次
    T16Nx_CapInit(T16N2,&y);

    T16Nx_ITConfig(T16N2,TIM_IT_CAP0,ENABLE);           //输入端口0捕捉中断
    T16Nx_ITConfig(T16N2,TIM_IT_CAP1,ENABLE);           //输入端口1捕捉中断
    NVIC_Init(NVIC_T16N2_IRQn,NVIC_Priority_1,ENABLE);  //中断设置
    T16N2_Enable();                                     //使能定时器
}

/*********************************************************
函数名: void T16N3CAPInit(void)
描  述: T16N3定时器初始化 输入端口0,1，上升+下降沿，捕获8次
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void T16N3CAPInit(void)
{
    TIM_BaseInitStruType x;
    TIM_CapInitStruType y;
    GPIO_InitStruType z;

	z.GPIO_Signal = GPIO_Pin_Signal_Digital;
    z.GPIO_Func = GPIO_Func_3;
    z.GPIO_Direction = GPIO_Dir_In;
    z.GPIO_PUEN = GPIO_PUE_Input_Disable;
    z.GPIO_PDEN = GPIO_PDE_Input_Disable;
    z.GPIO_OD = GPIO_ODE_Output_Disable;
    z.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOB,GPIO_Pin_2,&z);
    GPIO_Init(GPIOB,GPIO_Pin_3,&z);

    x.TIM_ClkS = TIM_ClkS_PCLK;
    x.TIM_SYNC = DISABLE;
    x.TIM_EDGE = TIM_EDGE_Rise;
    x.TIM_Mode = TIM_Mode_CAP;
    T16Nx_BaseInit(T16N3,&x);

    T16Nx_MAT0ITConfig(T16N3,TIM_Go_No);                //MAT0匹配设置
    T16Nx_MAT2ITConfig(T16N3,TIM_Go_No);                //MAT2匹配设置

    y.TIM_CapRise = ENABLE;
    y.TIM_CapFall = ENABLE;
    y.TIM_CapIS0 = ENABLE;
    y.TIM_CapIS1 = ENABLE;
    y.TIM_CapTime = TIM_CapTime_8;                      //捕捉8次
    T16Nx_CapInit(T16N3,&y);

    T16Nx_ITConfig(T16N3,TIM_IT_CAP0,ENABLE);           //输入端口0捕捉中断
    T16Nx_ITConfig(T16N3,TIM_IT_CAP1,ENABLE);           //输入端口1捕捉中断
    NVIC_Init(NVIC_T16N3_IRQn,NVIC_Priority_1,ENABLE);  //中断设置
    T16N3_Enable();                                     //使能定时器
}
