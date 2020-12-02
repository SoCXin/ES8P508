/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  wdt.h
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/29
*��  ��:  WDT�����ļ�
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "wdt.h"

/***************************************************************
 ��  ����WDT��ʼ����ʼ��
 ����ֵ����
 ����ֵ����
***************************************************************/
void WdtInit(void)
{
    WWDT_InitStruType x;

    WWDT_RegUnLock();

    x.WDT_Tms = 2000;           //ι������2s
    x.WDT_IE = ENABLE;
    x.WDT_Rst = ENABLE;
    x.WDT_Clock = WDT_CLOCK_PCLK;
    x.WDT_Win = WDT_WIN_50;
    WWDT_Init(&x);
    WWDT_Enable();
    WWDT_RegLock();

    NVIC_Init(NVIC_WWDT_IRQn,NVIC_Priority_1,ENABLE);
}
