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
������: void T32N0CAPInit(void)
��  ��: T32N0��ʱ����ʼ�� ����˿�0,1�����أ�����1��
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void T32N0CAPInit(void)
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
    GPIO_Init(GPIOA,GPIO_Pin_21,&z);
    GPIO_Init(GPIOA,GPIO_Pin_22,&z);

    x.TIM_ClkS = TIM_ClkS_PCLK;
    x.TIM_SYNC = DISABLE;
    x.TIM_EDGE = TIM_EDGE_Rise;
    x.TIM_Mode = TIM_Mode_CAP;
    T32Nx_BaseInit(T32N0,&x);

    T32Nx_MAT0ITConfig(T32N0,TIM_Go_No);                //MAT0ƥ������
    T32Nx_MAT2ITConfig(T32N0,TIM_Go_No);                //MAT2ƥ������

    y.TIM_CapRise = ENABLE;
    y.TIM_CapFall = DISABLE;
    y.TIM_CapIS0 = ENABLE;
    y.TIM_CapIS1 = ENABLE;
    y.TIM_CapTime = TIM_CapTime_1;                      //��׽1��
    T32Nx_CapInit(T32N0,&y);

    T32Nx_ITConfig(T32N0,TIM_IT_CAP0,ENABLE);           //����˿�0��׽�ж�
    T32Nx_ITConfig(T32N0,TIM_IT_CAP1,ENABLE);           //����˿�1��׽�ж�
    NVIC_Init(NVIC_T32N0_IRQn,NVIC_Priority_1,ENABLE);  //�ж�����
    T32N0_Enable();                                     //ʹ�ܶ�ʱ��
}
