#include "irqhandler.h"
#include "lib_wdt.h"
#include "SysTick.h"

void NMI_IRQHandler(void)
{
    
}

void HardFault_IRQHandler(void)
{
    while(1)
    {
    }
}

void SVC_IRQHandler(void)
{
    
}

void PendSV_IRQHandler(void)
{
    
}

void SysTick_IRQHandler(void)
{
    TimingDelay_Decrement();
}

uint32_t count0 = 0;
uint32_t count1 = 0;
uint32_t count2 = 0;
uint32_t count3 = 0;
/*********************************************************
������: void T16N0_IRQHandler(void)
��  ��: T16N0��ʱ�жϺ���
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void T16N0_IRQHandler(void)
{
    if(T16Nx_GetFlagStatus(T16N0,TIM_IF_MAT0) != RESET)
    {
        T16Nx_ClearIFPendingBit(T16N0,TIM_IF_MAT0);
        count0++;
        if ((count0 % 100) < 50)                /* ��ʱ50�ε���LED */
            GPIOA_SetBit(GPIO_Pin_14);
        else
            GPIOA_ResetBit(GPIO_Pin_14);

        count0 = count0 % 100;
    }
}
/*********************************************************
������: void T16N1_IRQHandler(void)
��  ��: T16N1��ʱ�жϺ���
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void T16N1_IRQHandler(void)
{
    if(T16Nx_GetFlagStatus(T16N1,TIM_IF_MAT0) != RESET)
    {
        T16Nx_ClearIFPendingBit(T16N1,TIM_IF_MAT0);
        count1++;
        if ((count1 % 200) < 100)                /* ��ʱ100�ε���LED */
            GPIOA_SetBit(GPIO_Pin_13);
        else
            GPIOA_ResetBit(GPIO_Pin_13);

        count1 = count1 % 200;
    }
}
/*********************************************************
������: void T16N2_IRQHandler(void)
��  ��: T16N2��ʱ�жϺ���
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void T16N2_IRQHandler(void)
{
    if(T16Nx_GetFlagStatus(T16N2,TIM_IF_MAT0) != RESET)
    {
        T16Nx_ClearIFPendingBit(T16N2,TIM_IF_MAT0);
        count2++;
        if ((count2 % 300) < 150)                /* ��ʱ150�ε���LED */
            GPIOA_SetBit(GPIO_Pin_12);
        else
            GPIOA_ResetBit(GPIO_Pin_12);

        count2 = count2 % 300;
    }
}
/*********************************************************
������: void T16N3_IRQHandler(void)
��  ��: T16N3��ʱ�жϺ���
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void T16N3_IRQHandler(void)
{
    if(T16Nx_GetFlagStatus(T16N3,TIM_IF_MAT0) != RESET)
    {
        T16Nx_ClearIFPendingBit(T16N3,TIM_IF_MAT0);
        count3++;
        if ((count3 % 400) < 200)                /* ��ʱ200�ε���LED */
            GPIOA_SetBit(GPIO_Pin_11);
        else
            GPIOA_ResetBit(GPIO_Pin_11);

        count3 = count3 % 400;
    }
}


