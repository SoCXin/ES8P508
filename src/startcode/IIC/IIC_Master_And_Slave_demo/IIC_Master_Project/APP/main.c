/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/24
*��  ��:  508�����ӻ�ͨ��demo��������Ϊ�������򣬸�����д�Ͷ�����ӻ�д��һ�����ݺ��ڶ���������
          �����ӻ���Ҫ����SCL��PA31����SDA��PA30������������
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/

#include "iic.h"

void delay(void)
{
	int i,j;
	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{;}
	}
}


char wbuf[8] = {1,2,3,4,5,6,7,8};
char rbuf[8] ;
int main()
{
	
    char i =0;
	SystemClockConfig();                                                //����ʱ��  
	DeviceClockAllEnable();                                             //����������ʱ��
	IICMasterInit();
		
	while(1)
	{
		for(i=0;i<8;i++)
		{
			wbuf[i]++;
		}
		IICWriteBuf(SLAVE_ADDR,wbuf,8);
		delay();
		IICReadBuf(SLAVE_ADDR,rbuf,8);
		delay();
	}
	
}

/***************************************************************
 ������: void I2C0_IRQHandler(void)
 ��  ����IIC�жϺ���
 ����ֵ����
 ���ֵ����
 ����ֵ����
***************************************************************/
char iic_buf = 0;
void I2C0_IRQHandler(void)
{
	
	
}




