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
函数名: void T16N0_IRQHandler(void)
描  述: T16N0定时中断函数
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void T16N0_IRQHandler(void)
{
    if(T16Nx_GetFlagStatus(T16N0,TIM_IF_MAT0) != RESET)
    {
        T16Nx_ClearIFPendingBit(T16N0,TIM_IF_MAT0);
        count0++;
        if ((count0 % 100) < 50)                /* 超时50次点亮LED */
            GPIOA_SetBit(GPIO_Pin_14);
        else
            GPIOA_ResetBit(GPIO_Pin_14);

        count0 = count0 % 100;
    }
}
/*********************************************************
函数名: void T16N1_IRQHandler(void)
描  述: T16N1定时中断函数
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void T16N1_IRQHandler(void)
{
    if(T16Nx_GetFlagStatus(T16N1,TIM_IF_MAT0) != RESET)
    {
        T16Nx_ClearIFPendingBit(T16N1,TIM_IF_MAT0);
        count1++;
        if ((count1 % 200) < 100)                /* 超时100次点亮LED */
            GPIOA_SetBit(GPIO_Pin_13);
        else
            GPIOA_ResetBit(GPIO_Pin_13);

        count1 = count1 % 200;
    }
}
/*********************************************************
函数名: void T16N2_IRQHandler(void)
描  述: T16N2定时中断函数
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void T16N2_IRQHandler(void)
{
    if(T16Nx_GetFlagStatus(T16N2,TIM_IF_MAT0) != RESET)
    {
        T16Nx_ClearIFPendingBit(T16N2,TIM_IF_MAT0);
        count2++;
        if ((count2 % 300) < 150)                /* 超时150次点亮LED */
            GPIOA_SetBit(GPIO_Pin_12);
        else
            GPIOA_ResetBit(GPIO_Pin_12);

        count2 = count2 % 300;
    }
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
        count3++;
        if ((count3 % 400) < 200)                /* 超时200次点亮LED */
            GPIOA_SetBit(GPIO_Pin_11);
        else
            GPIOA_ResetBit(GPIO_Pin_11);

        count3 = count3 % 400;
    }
}


