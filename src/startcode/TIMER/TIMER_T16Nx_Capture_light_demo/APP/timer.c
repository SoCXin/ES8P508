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
������: void T16N0CAPInit(void)
��  ��: T16N0��ʱ����ʼ�� ����˿�0,1�����أ�����16��
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void T16N0CAPInit(void)
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
    GPIO_Init(GPIOB,GPIO_Pin_4,&z);
    GPIO_Init(GPIOB,GPIO_Pin_5,&z);

    x.TIM_ClkS = TIM_ClkS_PCLK;
    x.TIM_SYNC = DISABLE;
    x.TIM_EDGE = TIM_EDGE_Rise;
    x.TIM_Mode = TIM_Mode_CAP;
    T16Nx_BaseInit(T16N0,&x);

    T16Nx_MAT0ITConfig(T16N0,TIM_Go_No);                //MAT0ƥ������
    T16Nx_MAT2ITConfig(T16N0,TIM_Go_No);                //MAT2ƥ������

    y.TIM_CapFall = DISABLE;
    y.TIM_CapRise = ENABLE;
    y.TIM_CapIS0 = ENABLE;
    y.TIM_CapIS1 = ENABLE;
    y.TIM_CapTime = TIM_CapTime_16;                      //��׽1��
    T16Nx_CapInit(T16N0,&y);

    T16Nx_ITConfig(T16N0,TIM_IT_CAP0,ENABLE);           //����˿�0��׽�ж�
    T16Nx_ITConfig(T16N0,TIM_IT_CAP1,ENABLE);           //����˿�1��׽�ж�
    NVIC_Init(NVIC_T16N0_IRQn,NVIC_Priority_1,ENABLE);  //�ж�����
    T16N0_Enable();                                     //ʹ�ܶ�ʱ��

}
/*********************************************************
������: void T16N1CAPInit(void)
��  ��: T16N1��ʱ����ʼ�� ����˿�0,1���½��أ�����2��
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void T16N1CAPInit(void)
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
    GPIO_Init(GPIOB,GPIO_Pin_6,&z);
    GPIO_Init(GPIOB,GPIO_Pin_7,&z);

    x.TIM_ClkS = TIM_ClkS_PCLK;
    x.TIM_SYNC = DISABLE;
    x.TIM_EDGE = TIM_EDGE_Rise;
    x.TIM_Mode = TIM_Mode_CAP;
    T16Nx_BaseInit(T16N1,&x);

    T16Nx_MAT0ITConfig(T16N1,TIM_Go_No);                //MAT0ƥ������
    T16Nx_MAT2ITConfig(T16N1,TIM_Go_No);                //MAT2ƥ������

    y.TIM_CapRise = DISABLE;
    y.TIM_CapFall = ENABLE;
    y.TIM_CapIS0 = ENABLE;
    y.TIM_CapIS1 = ENABLE;
    y.TIM_CapTime = TIM_CapTime_2;                      //��׽2��
    T16Nx_CapInit(T16N1,&y);

    T16Nx_ITConfig(T16N1,TIM_IT_CAP0,ENABLE);           //����˿�0��׽�ж�
    T16Nx_ITConfig(T16N1,TIM_IT_CAP1,ENABLE);           //����˿�1��׽�ж�
    NVIC_Init(NVIC_T16N1_IRQn,NVIC_Priority_1,ENABLE);  //�ж�����
    T16N1_Enable();                                     //ʹ�ܶ�ʱ��
}

/*********************************************************
������: void T16N2CAPInit(void)
��  ��: T16N2��ʱ����ʼ�� ����˿�0,1�����أ�����1��
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void T16N2CAPInit(void)
{
    TIM_BaseInitStruType x;
    TIM_CapInitStruType y;
    GPIO_InitStruType z;

	z.GPIO_Signal = GPIO_Pin_Signal_Digital;
    z.GPIO_Func = GPIO_Func_3;
    z.GPIO_Direction = GPIO_Dir_In;
    z.GPIO_PUEN = GPIO_PUE_Input_Disable;
    z.GPIO_PDEN = GPIO_PDE_Input_Disable;
    z.GPIO_OD = GPIO_ODE_Output_Disable;
    z.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOA,GPIO_Pin_28,&z);
    GPIO_Init(GPIOA,GPIO_Pin_29,&z);

    x.TIM_ClkS = TIM_ClkS_PCLK;
    x.TIM_SYNC = DISABLE;
    x.TIM_EDGE = TIM_EDGE_Rise;
    x.TIM_Mode = TIM_Mode_CAP;
    T16Nx_BaseInit(T16N2,&x);

    T16Nx_MAT0ITConfig(T16N2,TIM_Go_No);                //MAT0ƥ������
    T16Nx_MAT2ITConfig(T16N2,TIM_Go_No);                //MAT2ƥ������

    y.TIM_CapRise = ENABLE;
    y.TIM_CapFall = DISABLE;
    y.TIM_CapIS0 = ENABLE;
    y.TIM_CapIS1 = ENABLE;
    y.TIM_CapTime = TIM_CapTime_1;                      //��׽1��
    T16Nx_CapInit(T16N2,&y);

    T16Nx_ITConfig(T16N2,TIM_IT_CAP0,ENABLE);           //����˿�0��׽�ж�
    T16Nx_ITConfig(T16N2,TIM_IT_CAP1,ENABLE);           //����˿�1��׽�ж�
    NVIC_Init(NVIC_T16N2_IRQn,NVIC_Priority_1,ENABLE);  //�ж�����
    T16N2_Enable();                                     //ʹ�ܶ�ʱ��
}

/*********************************************************
������: void T16N3CAPInit(void)
��  ��: T16N3��ʱ����ʼ�� ����˿�0,1������+�½��أ�����8��
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void T16N3CAPInit(void)
{
    TIM_BaseInitStruType x;
    TIM_CapInitStruType y;
    GPIO_InitStruType z;

	z.GPIO_Signal = GPIO_Pin_Signal_Digital;
    z.GPIO_Func = GPIO_Func_3;
    z.GPIO_Direction = GPIO_Dir_In;
    z.GPIO_PUEN = GPIO_PUE_Input_Disable;
    z.GPIO_PDEN = GPIO_PDE_Input_Disable;
    z.GPIO_OD = GPIO_ODE_Output_Disable;
    z.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOB,GPIO_Pin_2,&z);
    GPIO_Init(GPIOB,GPIO_Pin_3,&z);

    x.TIM_ClkS = TIM_ClkS_PCLK;
    x.TIM_SYNC = DISABLE;
    x.TIM_EDGE = TIM_EDGE_Rise;
    x.TIM_Mode = TIM_Mode_CAP;
    T16Nx_BaseInit(T16N3,&x);

    T16Nx_MAT0ITConfig(T16N3,TIM_Go_No);                //MAT0ƥ������
    T16Nx_MAT2ITConfig(T16N3,TIM_Go_No);                //MAT2ƥ������

    y.TIM_CapRise = ENABLE;
    y.TIM_CapFall = ENABLE;
    y.TIM_CapIS0 = ENABLE;
    y.TIM_CapIS1 = ENABLE;
    y.TIM_CapTime = TIM_CapTime_8;                      //��׽8��
    T16Nx_CapInit(T16N3,&y);

    T16Nx_ITConfig(T16N3,TIM_IT_CAP0,ENABLE);           //����˿�0��׽�ж�
    T16Nx_ITConfig(T16N3,TIM_IT_CAP1,ENABLE);           //����˿�1��׽�ж�
    NVIC_Init(NVIC_T16N3_IRQn,NVIC_Priority_1,ENABLE);  //�ж�����
    T16N3_Enable();                                     //ʹ�ܶ�ʱ��
}
