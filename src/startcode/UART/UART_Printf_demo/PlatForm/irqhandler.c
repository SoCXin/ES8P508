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
������: void T16N3_IRQHandler(void)
��  ��: T16N3��ʱ�жϺ���
����ֵ: ��
���ֵ: ��
����ֵ: �� 
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
������: void UART2_IRQHandler(void)
��  ��: UART�жϷ������
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void UART2_IRQHandler(void)
{
//  if ((UART_GetITStatus(UART2, UART_IT_TB) != RESET)
//       && (UART_GetFlagStatus(UART2, UART_FLAG_TB) != RESET))//��Ҫͬʱ�ж�
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
//       && (UART_GetFlagStatus(UART2, UART_FLAG_RB) != RESET))//��Ҫͬʱ�ж�
//  {
//      g_rxbuf[g_rx_count] = UART_RecByte(UART2);
//      g_rx_count++;

//      if (g_rx_count >= 6)            //��ͨ��Э�飬���ٰ���6���ֽ�
//          g_rx_start_flag = 1;        //�ý�����ʼ��־

//      g_rx_time = 0;                  //����UARTͨѶ��ʱ�������Դ�������֡���չ���
//  }
}
