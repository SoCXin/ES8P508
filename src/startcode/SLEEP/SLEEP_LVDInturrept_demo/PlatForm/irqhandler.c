#include "irqhandler.h"
#include "lib_wdt.h"
#include "SysTick.h"
#include "main.h"

extern uint8_t g_sleep_flag;

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
函数名: void PINT3_IRQHandler(void)
描  述: 按键中断程序
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void PINT4_IRQHandler(void)
{
    PINT_ClearITPendingBit(PINT_IT_PINT4);            //清零KINT中断标志
}

void LVD_IRQHandler(void)
{
    if(SCU_GetLVDFlagStatus(SCU_LVDFlag_IF) != RESET)
    {
        SCU_RegUnLock();
        SCU_LVDClearIFBit();
        SCU_RegLock();
        g_sleep_flag = 1;
    }
}


