#include "irqhandler.h"

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
    }
    return;
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
//  if ((UART_GetITStatus(UART2, UART_IT_TB) != RESET)
//       && (UART_GetFlagStatus(UART2, UART_FLAG_TB) != RESET))//需要同时判断
//  {
//      UART_SendByte(UART2, g_txbuf[g_tx_count]);
//      g_tx_count++;

//      if (g_tx_count >= g_tx_length)
//      {
//          g_tx_count = 0;
//          UART_ITConfig(UART2, UART_IT_TB, DISABLE);
//      }
//  }

//  if ((UART_GetITStatus(UART2,UART_IT_RB) != RESET)
//       && (UART_GetFlagStatus(UART2, UART_FLAG_RB) != RESET))//需要同时判断
//  {
//      g_rxbuf[g_rx_count] = UART_RecByte(UART2);
//      g_rx_count++;

//      if (g_rx_count >= 6)            //按通信协议，至少包含6个字节
//          g_rx_start_flag = 1;        //置接收起始标志

//      g_rx_time = 0;                  //清零UART通讯计时，表明仍处于数据帧接收过程
//  }
}
