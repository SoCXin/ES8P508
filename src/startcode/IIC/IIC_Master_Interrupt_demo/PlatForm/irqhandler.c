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

/***************************************************************
 函数名: void T16N3_IRQHandler(void)
 描  述：T16N3定时中断函数
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
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
    }
}
/***************************************************************
 函数名: void I2C0_IRQHandler(void)
 描  述：IIC中断函数
 输入值：无
 输出值：无
 返回值：无
***************************************************************/
void I2C0_IRQHandler(void)
{
    if((I2C_GetTBStatus() != RESET) && I2C_GetITStatus(I2C_IT_TB) == SET)
    {
        I2C_SendByte(g_txbuf[g_tx_count]);
        g_tx_count++;
        if(g_tx_count >= g_tx_length)
        {
            g_tx_count = 0;
            I2C_ITConfig(I2C_IT_TB,DISABLE);
        }
    }

    if(I2C_GetFlagStatus(I2C_Flag_RB) != RESET && I2C_GetITStatus(I2C_IT_RB) == SET)
    {
        g_rxbuf[g_rx_count] = I2C_RecByte();
        g_rx_count++;
    }
}





