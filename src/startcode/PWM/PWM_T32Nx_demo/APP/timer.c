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
������: void PWM_Init(void)
��  ��: pwm��ʼ��
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void T32Nx_Init(void)
{
    TIM_BaseInitStruType x;
    GPIO_InitStruType y;
    y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_2;
    y.GPIO_Direction = GPIO_Dir_Out;
    y.GPIO_PUEN = GPIO_PUE_Input_Disable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOA,GPIO_Pin_2,&y);                     //PA2

    x.TIM_ClkS = TIM_ClkS_PCLK;                         //ѡ��ʱ�ӣ�Pclk
    x.TIM_SYNC = DISABLE;
    x.TIM_EDGE = TIM_EDGE_Rise;
    x.TIM_Mode = TIM_Mode_PWM ;                         //��ΪPWMģʽ
    T32Nx_BaseInit(T32N0,&x);

    T32N0_PwmOut0_Enable();                             //ʹ�ܶ˿����0
    T32Nx_MAT0Out0Config(T32N0,TIM_Out_High);           //ƥ��2�������
    T32Nx_MAT1Out0Config(T32N0,TIM_Out_Low);            //ƥ��3�������

    T32Nx_SetPREMAT(T32N0,20);                          //Ԥ��Ƶ
    T32Nx_SetMAT0(T32N0,50);                            //����ռ�ձ�
    T32Nx_SetMAT1(T32N0,200);                           //����Ƶ��200us

    T32Nx_MAT0ITConfig(T32N0,TIM_Go_Int);               //ƥ��2����������
    T32Nx_MAT1ITConfig(T32N0,TIM_Clr_Int);              //ƥ��3����0

    NVIC_Init(NVIC_T32N0_IRQn,NVIC_Priority_1,DISABLE);
    T32Nx_ITConfig(T32N0,TIM_IT_MAT0,DISABLE);          //��ѡ���Ƿ�ʹ���ж�
    T32Nx_ITConfig(T32N0,TIM_IT_MAT1,DISABLE);
    T32N0_Enable();
}



