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
������: void T16N2_IRQHandler(void)
��  ��: T16N2��ʱ�жϺ���
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
//void T16N0_IRQHandler(void)
//{
//   if(T16Nx_GetFlagStatus(T16N0,TIM_IF_CAP0) != RESET)
//    {
//        T16Nx_ClearIFPendingBit(T16N0,TIM_IF_CAP0);

//        count++;
//        if ((count & 0x01) == 0x01)
//        {
//            GPIOA_ResetBit(GPIO_Pin_14);
//        }
//        else
//        {
//            GPIOA_SetBit(GPIO_Pin_14);
//        }
//    }

//   if(T16Nx_GetFlagStatus(T16N0,TIM_IF_CAP1) != RESET)
//    {
//        T16Nx_ClearIFPendingBit(T16N0,TIM_IF_CAP1);

//        count++;
//        if ((count & 0x01) == 0x01)
//        {
//            GPIOA_ResetBit(GPIO_Pin_14);
//        }
//        else
//        {
//            GPIOA_SetBit(GPIO_Pin_14);
//        }
//    }
//}
void T16N0_IRQHandler(void)
{
   if(T16Nx_GetFlagStatus(T16N0,TIM_IF_CAP0) != RESET)
    {
        T16Nx_ClearIFPendingBit(T16N0,TIM_IF_CAP0);

        count++;
        if ((count & 0x01) == 0x01)
        {
            GPIOA_ResetBit(GPIO_Pin_14);
        }
        else
        {
            GPIOA_SetBit(GPIO_Pin_14);
        }
    }

   if(T16Nx_GetFlagStatus(T16N0,TIM_IF_CAP1) != RESET)
    {
        T16Nx_ClearIFPendingBit(T16N0,TIM_IF_CAP1);

        count++;
        if ((count & 0x01) == 0x01)
        {
            GPIOA_ResetBit(GPIO_Pin_14);
        }
        else
        {
            GPIOA_SetBit(GPIO_Pin_14);
        }
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
   if(T16Nx_GetFlagStatus(T16N1,TIM_IF_CAP0) != RESET)
    {
        T16Nx_ClearIFPendingBit(T16N1,TIM_IF_CAP0);

        count++;
        if ((count & 0x01) == 0x01)
        {
            GPIOA_ResetBit(GPIO_Pin_14);
        }
        else
        {
            GPIOA_SetBit(GPIO_Pin_14);
        }
    }

   if(T16Nx_GetFlagStatus(T16N1,TIM_IF_CAP1) != RESET)
    {
        T16Nx_ClearIFPendingBit(T16N1,TIM_IF_CAP1);

        count++;
        if ((count & 0x01) == 0x01)
        {
            GPIOA_ResetBit(GPIO_Pin_14);
        }
        else
        {
            GPIOA_SetBit(GPIO_Pin_14);
        }
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
   if(T16Nx_GetFlagStatus(T16N2,TIM_IF_CAP0) != RESET)
    {
        T16Nx_ClearIFPendingBit(T16N2,TIM_IF_CAP0);

        count++;
        if ((count & 0x01) == 0x01)
        {
            GPIOA_ResetBit(GPIO_Pin_14);
        }
        else
        {
            GPIOA_SetBit(GPIO_Pin_14);
        }
    }

   if(T16Nx_GetFlagStatus(T16N2,TIM_IF_CAP1) != RESET)
    {
        T16Nx_ClearIFPendingBit(T16N2,TIM_IF_CAP1);

        count++;
        if ((count & 0x01) == 0x01)
        {
            GPIOA_ResetBit(GPIO_Pin_14);
        }
        else
        {
            GPIOA_SetBit(GPIO_Pin_14);
        }
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
   if(T16Nx_GetFlagStatus(T16N3,TIM_IF_CAP0) != RESET)
    {
        T16Nx_ClearIFPendingBit(T16N3,TIM_IF_CAP0);

        count++;
        if ((count & 0x01) == 0x01)
        {
            GPIOA_ResetBit(GPIO_Pin_14);
        }
        else
        {
            GPIOA_SetBit(GPIO_Pin_14);
        }
    }

   if(T16Nx_GetFlagStatus(T16N3,TIM_IF_CAP1) != RESET)
    {
        T16Nx_ClearIFPendingBit(T16N3,TIM_IF_CAP1);

        count++;
        if ((count & 0x01) == 0x01)
        {
            GPIOA_ResetBit(GPIO_Pin_14);
        }
        else
        {
            GPIOA_SetBit(GPIO_Pin_14);
        }
    }
}

