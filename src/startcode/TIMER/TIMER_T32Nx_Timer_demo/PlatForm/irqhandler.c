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
/*********************************************************
������: void T32N0_IRQHandler(void)
��  ��: T32N0��ʱ�жϺ���
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void T32N0_IRQHandler(void)
{
    if(T32Nx_GetFlagStatus(T32N0,TIM_IF_MAT0) != RESET)
    {
        T32Nx_ClearIFPendingBit(T32N0,TIM_IF_MAT0);
        count0++;
        if ((count0 % 100) < 50)                /* ��ʱ50�ε���LED */
            GPIOA_SetBit(GPIO_Pin_14);
        else
            GPIOA_ResetBit(GPIO_Pin_14);

        count0 = count0 % 100;
    }
}


