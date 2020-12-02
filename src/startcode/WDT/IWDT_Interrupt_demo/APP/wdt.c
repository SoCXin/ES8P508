
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
    IWDT_InitStruType x;

    IWDT_RegUnLock();
    x.WDT_Tms = 2000;           //ι������2s
    x.WDT_IE = ENABLE;
    x.WDT_Rst = ENABLE;
    x.WDT_Clock = WDT_CLOCK_PCLK;
    IWDT_Init(&x);
    IWDT_Enable();               //WDT���ڽ�������Enable
    IWDT_RegLock();

    NVIC_Init(NVIC_IWDT_IRQn, NVIC_Priority_0, ENABLE);
    IWDT_ITEnable();
}
