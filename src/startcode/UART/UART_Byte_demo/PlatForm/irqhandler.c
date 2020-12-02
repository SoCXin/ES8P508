#include "irqhandler.h"

__IO uint8_t g_rxbuf;

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
函数名: void UART2_IRQHandler(void)
描  述: UART中断服务程序
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void UART2_IRQHandler(void)
{
    if(UART_GetFlagStatus(UART2,UART_FLAG_RB) != RESET && UART_GetITStatus(UART2,UART_IT_RB) != RESET)
    {
        g_rxbuf = UART_RecByte(UART2);
        while(UART_GetFlagStatus(UART2,UART_FLAG_TB) == RESET);
        UART_SendByte(UART2,g_rxbuf);
    }
}

