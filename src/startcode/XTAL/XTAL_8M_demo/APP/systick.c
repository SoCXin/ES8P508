/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  systick.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/25
*��  ��:  SysTickģ�����
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "systick.h"

__IO uint32_t TimingDelay;

/***************************************************************
 ��������void SysTickInit(void)
 ��  ����ϵͳ�δ��ʼ����100us
 ����ֵ����
 ���ֵ����
 ����ֵ����
***************************************************************/
void SysTickInit(void)
{
    SYSTICK_InitStruType x;

    x.SysTick_Value = SystemCoreClock / 10000;  //100us
    x.SysTick_ClkSource = SysTick_ClkS_Cpu;
    x.SysTick_ITEnable = ENABLE;                //�ж�ʹ��
    SysTick_Init(&x);

    SysTick_Disable();                          //ʹ��ʱ�ſ���
}

/***************************************************************
 ��������void Delay100us(__IO uint32_t nTime)
 ��  ����ϵͳ�δ�100us��ʱ
 ����ֵ����ʱ100us����
 ���ֵ����
 ����ֵ����
***************************************************************/
void Delay100us(__IO uint32_t nTime)
{
    TimingDelay = nTime;
    SysTick_Enable();
    while(TimingDelay != 0);
    SysTick_Disable();
}

/***************************************************************
 ��������void Delay1ms(__IO uint32_t nTime)
 ��  ������ʱ����
 ����ֵ����ʱ1ms�ĸ���
 ���ֵ����
 ����ֵ����
***************************************************************/
void Delay1ms(__IO uint32_t nTime)
{
    uint32_t i;

    for(i=0;i<nTime;i++)
        Delay100us(10);
}

/***************************************************************
 ��������void TimingDelay_Decrement(void)
 ��  ����ϵͳ�δ��жϵ���
 ����ֵ����
 ���ֵ����
 ����ֵ����
***************************************************************/
void TimingDelay_Decrement(void)
{
    if(TimingDelay != 0)
        TimingDelay --;
}
