/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  light.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/25
*描  述:  LIGHT指示灯模块函数
*备  注:  适用于HRSDK-GDB-ES8P508 V1.0
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

    x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_Out;
    x.GPIO_PUEN = DISABLE;
    x.GPIO_PDEN = ENABLE;
    x.GPIO_OD = DISABLE;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    x.GPIO_INEB = GPIO_INEB_DISABLE;

    GPIO_Init(GPIOA,GPIO_Pin_31,&x);    //LD1
    GPIO_Init(GPIOA,GPIO_Pin_2,&x);     //LD2
    GPIO_Init(GPIOA,GPIO_Pin_3,&x);     //LD3
    GPIO_Init(GPIOA,GPIO_Pin_4,&x);     //LD4
}

