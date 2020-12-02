/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  timer.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/25
*��  ��:  T16Nģ�����
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "timer.h"

/*********************************************************
������: void T16N3CNT_Init(void)
��  ��: T16Nx��ʼ��
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void T16N3CNT_Init(void)
{
    TIM_BaseInitStruType x;
    GPIO_InitStruType y;

    y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_3;
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
    T16Nx_BaseInit(T16N3,&x);

    T16Nx_MAT0ITConfig(T16N3,TIM_Clr_Int);
    T16Nx_SetPREMAT(T16N3,0);
    T16Nx_SetCNT(T16N3,0);
    T16Nx_SetMAT0(T16N3,1);

    T16Nx_ITConfig(T16N3,TIM_IT_MAT0,ENABLE);
    NVIC_Init(NVIC_T16N3_IRQn,NVIC_Priority_1,ENABLE);
    T16N3_Enable();
}
