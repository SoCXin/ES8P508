#include "irqhandler.h"
//#include "lib_wdt.h"
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

/*********************************************************
函数名: void LVD_IRQHandler(void)
描  述: LVD中断程序
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void LVD_IRQHandler(void)
{
    if(SCU_GetLVDFlagStatus(SCU_LVDFlag_IF) != RESET)
    {
        GPIOA_ResetBit(GPIO_Pin_14);
        GPIOA_ResetBit(GPIO_Pin_13);
        GPIOA_ResetBit(GPIO_Pin_12);
        GPIOA_ResetBit(GPIO_Pin_11);
    }
}


