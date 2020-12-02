/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/25
*��  ��:  SPI���ӻ�ͨ�ų��򣬱�����Ϊ�ӻ����򣬸�������������������ݣ��������������´���������ʱ�򣬷��ͱ�������ݡ�
          �������ӣ�PA26-SCK(SPI_CLK),PA27-NSS(SPI_CS),PA25-SDI(SPI_DI),PA24-SDO(SPI_DO) !!!!!!!!!!!!
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"
uint8_t spi_buf[9] ={0,0,0,0,0,0,0,0,0};
uint8_t spi_count =0;

int main(void)
{
    SystemClockConfig();                                    //����ʱ��  
    DeviceClockAllEnable();                                 //����������ʱ��
    
    SPI_GPIO_Init();

    while (1)
    {
        
    }
}

/***************************************************************
 ������: void SPI_IRQHandler(void)
 ��  ����IIC�жϺ���
 ����ֵ����
 ���ֵ����
 ����ֵ����
***************************************************************/

void SPI0_IRQHandler(void)
{
    if(SPI_GetITStatus(SPI_IT_NSS) == SET)
    { 
        SPI_ClearITPendingBit(SPI_Clr_NSS);
        SPI_RX_CLR();
        SPI_TX_CLR();
        spi_count = 0;
        if(SPI_GetFlagStatus(SPI_Flag_NSS) == SET)      //Ƭѡδѡ��
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
            if(spi_buf[0] == (Slave_Addr | 0x01))    //������
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
