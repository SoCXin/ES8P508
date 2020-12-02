/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  light.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/25
*��  ��:  LIGHTָʾ��ģ�麯��
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "light.h"

/***************************************************************
 ��  ����LIGHTָʾ�Ƴ�ʼ��
 ����ֵ����
 ����ֵ����
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

