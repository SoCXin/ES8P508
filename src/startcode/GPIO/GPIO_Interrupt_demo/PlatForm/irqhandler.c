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
   // TimingDelay_Decrement();
}
/*********************************************************
函数名: void T16N3_IRQHandler(void)
描  述: T16N3定时中断函数
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void T16N3_IRQHandler(void)
{
    if(T16Nx_GetFlagStatus(T16N3,TIM_IF_MAT0) != RESET)
    {
        T16Nx_ClearIFPendingBit(T16N3,TIM_IF_MAT0);
        g_2ms_flag = 1;
        g_10ms_cnt++;
        if(g_10ms_cnt >= 5)
        {
            g_10ms_cnt = 0;
            g_10ms_flag = 1;
        }
        g_1s_cnt++;
        if(g_1s_cnt >= 500)
        {
            g_1s_cnt = 0;
            g_1s_flag = 1;
        }
    }
}

/*********************************************************
函数名: void KINT4_IRQHandler(void)
描  述: 中断函数
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
/*********************************************************
函数名: void Interrupt_KINT_Handler(void)
描  述: 按键中断处理函数
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void KINT_IRQHandler(void)
{
    if (KINT_GetITFlag(GPIOA,GPIO_Pin_20) != RESET)
    {
        KINT_ClearITFlag(GPIOA,GPIO_Pin_20);      // 清除按键中断标志位
        g_key_flag_4 = 1;
    }
}


