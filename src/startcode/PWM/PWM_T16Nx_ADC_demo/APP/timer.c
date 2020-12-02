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
������: void PWM_Init(void)
��  ��: pwm��ʼ��
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void T16Nx_Init(void)
{
    TIM_BaseInitStruType x;
    GPIO_InitStruType y;
    T16Nx_PWMInitStruType z;

	  y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_3;
    y.GPIO_Direction = GPIO_Dir_Out;
    y.GPIO_PUEN = GPIO_PUE_Input_Disable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Normal;

    GPIO_Init(GPIOA,GPIO_Pin_28,&y);                     //PA28

    x.TIM_ClkS = TIM_ClkS_PCLK;                         //ѡ��ʱ�ӣ�Pclk
    x.TIM_SYNC = DISABLE;
    x.TIM_EDGE = TIM_EDGE_Rise;
    x.TIM_Mode = TIM_Mode_PWM ;                         //��ΪPWMģʽ
    T16Nx_BaseInit(T16N2,&x);

    T16N2_PwmOut0_Enable();                             //ʹ�ܶ˿����0
    T16Nx_MAT0Out0Config(T16N2,TIM_Out_High);           //ƥ��2�������
    T16Nx_MAT1Out0Config(T16N2,TIM_Out_Low);            //ƥ��3�������

    z.T16Nx_MOE0 = ENABLE;
    z.T16Nx_MOE1 = ENABLE;
    z.T16Nx_POL0 = POSITIVE;
    z.T16Nx_POL1 = POSITIVE;
    T16Nx_PWMOutConfig(T16N2,&z);                       //�������

    T16Nx_SetPREMAT(T16N2,20);                          //Ԥ��Ƶ
    T16Nx_SetMAT0(T16N2,30000);                         //����ռ�ձ�
    T16Nx_SetMAT1(T16N2,60000);                         //����Ƶ��

    T16Nx_TRG_Config(T16N2,T16Nx_MAT0,ENABLE);          //ƥ��MAT0����ADC

    T16Nx_MAT0ITConfig(T16N2,TIM_Go_Int);               //ƥ��2����������
    T16Nx_MAT1ITConfig(T16N2,TIM_Clr_Int);              //ƥ��3����0

    T16Nx_ITConfig(T16N2,TIM_IT_MAT0,DISABLE);          //��ѡ���Ƿ�ʹ���ж�
    T16Nx_ITConfig(T16N2,TIM_IT_MAT1,DISABLE);

    NVIC_Init(NVIC_T16N2_IRQn,NVIC_Priority_1,DISABLE);
    T16N2_Enable();
}
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
    T16Nx_BaseInit(T16N3,&x);

    T16Nx_SetPREMAT(T16N3,1);
    T16Nx_SetMAT0(T16N3,20000);
    T16Nx_MAT0ITConfig(T16N3,TIM_Clr_Int);
    T16Nx_ITConfig(T16N3,TIM_IT_MAT0,ENABLE);
    NVIC_Init(NVIC_T16N3_IRQn,NVIC_Priority_1,ENABLE);
    T16N3_Enable();
}



