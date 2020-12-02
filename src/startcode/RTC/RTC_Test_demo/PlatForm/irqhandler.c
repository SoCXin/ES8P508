#include "irqhandler.h"
#include "lib_wdt.h"
#include "SysTick.h"
#include "lib_rtc.h"

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

        g_1s_cnt++;
        if(g_1s_cnt >= 500)
        {
            g_1s_cnt = 0;
            g_1s_flag = 1;
        } 
    }
}

/*********************************************************
函数名: void RTC_IRQHandler(void)
描  述: 实时时钟中断处理函数
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void RTC_IRQHandler(void)
{
    if (RTC_GetFlagStatus(RTC_Interrupt_Source_Second) != RESET
        && RTC_GetITStatus(RTC_Interrupt_Source_Second) != RESET)
    {
        RTC_ClearITPendingBit(RTC_Interrupt_Source_Second);    //清中断标识
        SecondCount++;
        if ((SecondCount & 0x01) == 0x01)
            GPIOA_SetBit(GPIO_Pin_20);      //熄灭LD1
        else
            GPIOA_ResetBit(GPIO_Pin_20);    //点亮LD1
    }

    if (RTC_GetFlagStatus(RTC_Interrupt_Source_Minute) != RESET
        && RTC_GetITStatus(RTC_Interrupt_Source_Minute) != RESET)
    {
        RTC_ClearITPendingBit(RTC_Interrupt_Source_Minute);    //清中断标识
        MinuteCount++;
        if ((MinuteCount & 0x01) == 0x01)
            GPIOA_SetBit(GPIO_Pin_21);      //熄灭LD2
        else
            GPIOA_ResetBit(GPIO_Pin_21);    //点亮LD2
    }

}
