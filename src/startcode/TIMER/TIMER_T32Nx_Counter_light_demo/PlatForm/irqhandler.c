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
函数名: void T32N0_IRQHandler(void)
描  述: T32N0
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void T32N0_IRQHandler(void)
{
    if(T32Nx_GetFlagStatus(T32N0,TIM_IF_MAT0) != RESET)
    {
        T32Nx_ClearIFPendingBit(T32N0,TIM_IF_MAT0);

        count3++;
        if ((count3 % 2) == 1)
        {
            GPIOA_SetBit(GPIO_Pin_11);
            GPIOA_SetBit(GPIO_Pin_12);
            GPIOA_SetBit(GPIO_Pin_13);
            GPIOA_SetBit(GPIO_Pin_14);
        }
        else
        {
            GPIOA_ResetBit(GPIO_Pin_11);
            GPIOA_ResetBit(GPIO_Pin_12);
            GPIOA_ResetBit(GPIO_Pin_13);
            GPIOA_ResetBit(GPIO_Pin_14);
        }
    }
}


