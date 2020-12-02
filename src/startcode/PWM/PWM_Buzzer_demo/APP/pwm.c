/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  pwm.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  PWMģ�����
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "pwm.h"

/*********************************************************
������: void User_T16N2_PWMInit(void)
��  ��: T16N2��ʱ����ʼ����PWM���
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void User_T16N2_PWMInit(void)
{
    TIM_BaseInitStruType x;

    x.TIM_ClkS = TIM_ClkS_PCLK;                 //ѡ��ʱ�ӣ�Pclk
    x.TIM_SYNC = DISABLE;
    x.TIM_EDGE = TIM_EDGE_Rise;
    x.TIM_Mode = TIM_Mode_PWM ;                 //��ΪPWMģʽ
    T16Nx_BaseInit(T16N2,&x);

    T16N2_PwmOut1_Enable();                     //ʹ�ܶ˿����1
    T16Nx_MAT2Out1Config(T16N2,TIM_Out_High);   //ƥ��2�������
    T16Nx_MAT3Out1Config(T16N2,TIM_Out_Low);    //ƥ��3�������

    T16Nx_SetPREMAT(T16N2,5);                   //Ԥ��Ƶ
    T16Nx_SetMAT2(T16N2,3000);                  //����ռ�ձ�
    T16Nx_SetMAT3(T16N2,6000);                  //����Ƶ��

    T16Nx_MAT2ITConfig(T16N2,TIM_Go_Int);       //ƥ��2����������
    T16Nx_MAT3ITConfig(T16N2,TIM_Clr_Int);      //ƥ��3����0

    T16Nx_ITConfig(T16N2,TIM_IT_MAT2,DISABLE);    //��ѡ���Ƿ�ʹ���ж�
    T16Nx_ITConfig(T16N2,TIM_IT_MAT3,DISABLE);
    NVIC_Init(NVIC_T16N2_IRQn,NVIC_Priority_1,DISABLE);       //�򿪻�ر����ж�
    T16N2_Enable();                             //ʹ�ܶ�ʱ�� 
}    

/*********************************************************
������: void PWMOutput(uint32_t temp)
��  ��: T16N2 PWM�������Ƶ�ʣ�ռ�ձȹ̶�Ϊ50%������������ʹ��
����ֵ: ����Ƶ����ֵ
���ֵ: ��
����ֵ: �� 
**********************************************************/
void PWMOutput(uint16_t temp)
{
    T16Nx_SetMAT2(T16N2,temp/2);    //�͵�ƽʱ��
    T16Nx_SetMAT3(T16N2,temp);      //��ʱ��
    T16Nx_SetCNT(T16N2,0);          //���ú�һ��Ҫ���CNT���������¼���������
}
