/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/25
*描  述:  SPI主机从机通信demo，本程序为主机程序，负责发起写和读。向从机写入一个数据后，在读回主机。
          引脚连接A26-SCK(SPI_CLK),PA27-NSS(SPI_CS),PA25-SDI(SPI_DI),PA24-SDO(SPI_DO) !!!!!!!!!!!!
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
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
    SystemClockConfig();                                    //配置时钟  
    DeviceClockAllEnable();                                 //打开所有外设时钟
    
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
