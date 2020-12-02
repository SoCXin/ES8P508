/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/25
*描  述:  SPI主从机通信程序，本程序为从机程序，负责接收主机发来的数据，并保存起来。下次主机读的时候，发送保存的数据。
          引脚连接：PA26-SCK(SPI_CLK),PA27-NSS(SPI_CS),PA25-SDI(SPI_DI),PA24-SDO(SPI_DO) !!!!!!!!!!!!
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"
uint8_t spi_buf[9] ={0,0,0,0,0,0,0,0,0};
uint8_t spi_count =0;

int main(void)
{
    SystemClockConfig();                                    //配置时钟  
    DeviceClockAllEnable();                                 //打开所有外设时钟
    
    SPI_GPIO_Init();

    while (1)
    {
        
    }
}

/***************************************************************
 函数名: void SPI_IRQHandler(void)
 描  述：IIC中断函数
 输入值：无
 输出值：无
 返回值：无
***************************************************************/

void SPI0_IRQHandler(void)
{
    if(SPI_GetITStatus(SPI_IT_NSS) == SET)
    { 
        SPI_ClearITPendingBit(SPI_Clr_NSS);
        SPI_RX_CLR();
        SPI_TX_CLR();
        spi_count = 0;
        if(SPI_GetFlagStatus(SPI_Flag_NSS) == SET)      //片选未选中
        {
            SPI_ITConfig(SPI_IT_TB, DISABLE);
        }
        else
        {
            SPI_ITConfig(SPI_IT_RB, ENABLE);
            SPI_RBIMConfig(SPI_IType_BYTE);
        }
    }
    if(SPI_GetITStatus(SPI_IT_RB) == SET)
    {
        spi_buf[spi_count] = SPI_RecByte();
        spi_count ++;
        if(spi_count == 1)
        {
            if(spi_buf[0] == (Slave_Addr | 0x01))    //主机读
            {
                SPI_SendByte(spi_buf[spi_count]);
                spi_count ++;
                
                SPI_ITConfig(SPI_IT_TB, ENABLE);
                SPI_ITConfig(SPI_IT_RB, DISABLE);
                SPI_TBIMConfig(SPI_IType_BYTE);
                
                
            }
            else
            {
                SPI_TX_CLR();
                SPI_ITConfig(SPI_IT_TB, DISABLE);
            }
        }
    }
    if(SPI_GetITStatus(SPI_IT_TB) == SET)
    {

        SPI_SendByte(spi_buf[spi_count]);
        spi_count ++;
    }
}
