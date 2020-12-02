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
        g_200ms_cnt++;
        if(g_200ms_cnt >= 100)
        {
            g_200ms_cnt = 0;
            g_200ms_flag = 1;
        }
    }
}
/*********************************************************
函数名: void ADC_IRQHandler(void)
描  述: ADC定时中断函数
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void ADC_IRQHandler(void)
{
    if(ADC_GetFlagStatus(ADC_IF) != RESET && ADC_GetITStatus(ADC_IE) != RESET)
    {
        ADC_ClearIFStatus(ADC_IF);

        while(ADC_GetConvStatus() == SET);
        g_adc_data = ADC_GetConvValue();
        g_adc_flag = 1;
    }

    if(ADC_GetFlagStatus(ADC_IF_ACPOVER) == SET && ADC_GetITStatus(ADC_IE_ACPOVER) != RESET)
    {
        g_adc_data = ADC_GetACPMeanValue();
        g_adc_flag = 1;
        ADC_ClearIFStatus(ADC_IF_ACPOVER);
    }

    if(ADC_GetFlagStatus(ADC_IF_ACPMIN) == SET && ADC_GetITStatus(ADC_IE_ACPMIN) != RESET)
    {
        g_adc_data = ADC_GetACPMeanValue();
        g_adc_flag = 1;
        ADC_ClearIFStatus(ADC_IF_ACPMIN);
    }

    if(ADC_GetFlagStatus(ADC_IF_ACPMAX) == SET && ADC_GetITStatus(ADC_IE_ACPMAX) != RESET)
    {
        g_adc_data = ADC_GetACPMeanValue();
        g_adc_flag = 1;
        ADC_ClearIFStatus(ADC_IF_ACPMAX);
    }
}


