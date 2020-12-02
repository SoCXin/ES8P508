/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/25
*��  ��:  SPI�����ӻ�ͨ��demo��������Ϊ�������򣬸�����д�Ͷ�����ӻ�д��һ�����ݺ��ڶ���������
          �������ӣPA26-SCK(SPI_CLK),PA27-NSS(SPI_CS),PA25-SDI(SPI_DI),PA24-SDO(SPI_DO) !!!!!!!!!!!!
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

uint8_t wbuf[8] = {1,2,3,4,5,6,7,8};
uint8_t rbuf[8] ; 

void delay(void)
{
	int i,j;
	for(i=0;i<200;i++)
	{
		for(j=0;j<200;j++)
		{;}
	}
}

int main(void)
{
    uint8_t i;
    SystemClockConfig();                                    //����ʱ��  
    DeviceClockAllEnable();                                 //����������ʱ��
    
    SPI_GPIO_Init();
    
    while (1)
    {
        for(i = 0; i < 8; i ++)
        {
            wbuf[i] ++;
        }
        
        SPIWriteData(wbuf, 8);  
        delay();
        SPIReadData(rbuf, 8);  
        delay();
        
    }
}
