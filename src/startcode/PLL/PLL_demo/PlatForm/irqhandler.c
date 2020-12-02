#include "irqhandler.h"
#include "lib_wdt.h"
#include "lib_config.h"

void NMI_IRQHandler(void)
{
    
}

void HardFault_IRQHandler(void)
{
    while(1);
}

void SVC_IRQHandler(void)
{
    
}

void PendSV_IRQHandler(void)
{
    
}

void SysTick_IRQHandler(void)
{

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
    if (T16Nx_GetFlagStatus(T16N3,TIM_IF_MAT0 )!= RESET)
    {
        T16Nx_ClearIFPendingBit(T16N3,TIM_IF_MAT0);
        g_2ms_flag = 1;

        g_10ms_cnt++;
        if(g_10ms_cnt >= 5)
        {
            g_10ms_cnt = 0;
            g_10ms_flag = 1;
        }

        g_900ms_cnt++;
        if(g_900ms_cnt >= 250)
        {
            g_900ms_cnt = 0;
            g_900ms_flag = 1;
        }
    }

    return;
}
