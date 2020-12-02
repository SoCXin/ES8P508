/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/23
*描  述:  RTC演示主程序 
          RTC误差补偿demo,本例程实现RTC外部晶振的误差补偿。
		  选择RTC0引脚1Hz输出，测取RTC误差，由误差计算出补偿值，再进行误差补偿。 PA21-RTC0脚
*备  注:  适用于ES8P508x芯片
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{
        SystemClockConfig();
        DeviceClockAllEnable();
	
        SCU_RegUnLock();
	SCU->SCLKEN1.XTAL_EN = 1;
	SCU->SCLKEN0.XTAL_LP = 0;
	while(SCU->SCLKEN1.XTAL_RDY == 0);  //等待外部时钟稳定
	SCU_RegLock() ;
	
	MyRTC_Init();
	Error_Offset(247);                //在测取实际误差时请注释本函数。本例中实测晶振误差为-2.258s/d，
					 // 计算得到需要的补偿值为-9，补码为254，经测试补偿后的误差为0.087s/d */

    while (1)
    {

    }
}
