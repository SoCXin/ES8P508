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
������: void T32NxInit(void)
��  ��: T32Nx��ʱ����ʼ��
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void T32NxInit(void)
{
    TIM_BaseInitStruType x;

    x.TIM_ClkS = TIM_ClkS_PCLK;
    x.TIM_SYNC = DISABLE;
    x.TIM_EDGE = TIM_EDGE_Rise;
    x.TIM_Mode = TIM_Mode_TC0;
    T32Nx_BaseInit(T32N0,&x);

    T32Nx_SetPREMAT(T32N0,1);

    T32Nx_SetMAT0(T32N0,40000);

    NVIC_Init(NVIC_T32N0_IRQn,NVIC_Priority_1,ENABLE);

    T32Nx_MAT0ITConfig(T32N0,TIM_Clr_Int);

    T32Nx_ITConfig(T32N0,TIM_IT_MAT0,ENABLE);

    T32N0_Enable();
}
