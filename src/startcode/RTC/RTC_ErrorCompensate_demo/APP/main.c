/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/23
*��  ��:  RTC��ʾ������ 
          RTC����demo,������ʵ��RTC�ⲿ�����������
		  ѡ��RTC0����1Hz�������ȡRTC���������������ֵ���ٽ��������� PA21-RTC0��
*��  ע:  ������ES8P508xоƬ
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main(void)
{
        SystemClockConfig();
        DeviceClockAllEnable();
	
        SCU_RegUnLock();
	SCU->SCLKEN1.XTAL_EN = 1;
	SCU->SCLKEN0.XTAL_LP = 0;
	while(SCU->SCLKEN1.XTAL_RDY == 0);  //�ȴ��ⲿʱ���ȶ�
	SCU_RegLock() ;
	
	MyRTC_Init();
	Error_Offset(247);                //�ڲ�ȡʵ�����ʱ��ע�ͱ�������������ʵ�⾧�����Ϊ-2.258s/d��
					 // ����õ���Ҫ�Ĳ���ֵΪ-9������Ϊ254�������Բ���������Ϊ0.087s/d */

    while (1)
    {

    }
}
