/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  light.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/25
*描  述:  LIGHT指示灯模块函数
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "light.h"

/***************************************************************
 描  述：LIGHT指示灯初始化
 输入值：无
 返回值：无
***************************************************************/
void LightInit(void)
{
    GPIO_InitStruType x;

    x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_Out;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;

    GPIO_Init(GPIOA,GPIO_Pin_14,&x);    //LD1
    GPIO_Init(GPIOA,GPIO_Pin_13,&x);     //LD2
    GPIO_Init(GPIOA,GPIO_Pin_12,&x);     //LD3
    GPIO_Init(GPIOA,GPIO_Pin_11,&x);     //LD4
}

