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
������: void UART2_IRQHandler(void)
��  ��: UART�жϷ������
����ֵ: ��
���ֵ: ��
����ֵ: �� 
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

