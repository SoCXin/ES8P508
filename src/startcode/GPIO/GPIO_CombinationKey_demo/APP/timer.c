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
������: void T16N3Init(void)
��  ��: T16N3��ʱ����ʼ��
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void T16N3Init(void)
{
    TIM_BaseInitStruType x;

    x.TIM_ClkS = TIM_ClkS_PCLK;
    x.TIM_SYNC = DISABLE;
    x.TIM_EDGE = TIM_EDGE_Rise;
    x.TIM_Mode = TIM_Mode_TC0;
    T16Nx_BaseInit(T16N3, &x);

    T16Nx_SetPREMAT(T16N3, 1);
    T16Nx_SetMAT0(T16N3, 20000);
    T16Nx_MAT0ITConfig(T16N3, TIM_Clr_Int);
    T16Nx_ITConfig(T16N3, TIM_IT_MAT0, ENABLE);
    NVIC_Init(NVIC_T16N3_IRQn, NVIC_Priority_1, ENABLE);
    T16N3_Enable();
}

