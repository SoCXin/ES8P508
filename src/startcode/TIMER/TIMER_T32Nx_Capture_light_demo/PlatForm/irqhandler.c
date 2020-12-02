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

extern uint32_t count;
/*********************************************************
������: void T32N0_IRQHandler(void)
��  ��: T32N0��ʱ�жϺ���
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void T32N0_IRQHandler(void)
{
   if(T32Nx_GetFlagStatus(T32N0,TIM_IF_CAP0) != RESET)
    {
        T32Nx_ClearIFPendingBit(T32N0,TIM_IF_CAP0);

        count++;
//        if ((count & 0x01) == 0x01)
			  if ((count % 100) < 50)
        {
            GPIOA_ResetBit(GPIO_Pin_14);
        }
        else
        {
            GPIOA_SetBit(GPIO_Pin_14);
        }
    }

   if(T32Nx_GetFlagStatus(T32N0,TIM_IF_CAP1) != RESET)
    {
        T32Nx_ClearIFPendingBit(T32N0,TIM_IF_CAP1);

        count++;
//        if ((count & 0x01) == 0x01)
			  if ((count % 100) < 50)
        {
            GPIOA_ResetBit(GPIO_Pin_14);
        }
        else
        {
            GPIOA_SetBit(GPIO_Pin_14);
        }
    }
}

