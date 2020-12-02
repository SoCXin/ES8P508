/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  timer.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/25
*��  ��:  T32Nģ�����
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "timer.h"

/*********************************************************
������: void T32N0CNT_Init(void)
��  ��: T32Nx��ʼ��
����ֵ: ��
���ֵ: ��
����ֵ: �� 
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

    x.TIM_ClkS = TIM_ClkS_CK0;              //�ⲿʱ��CK0
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
