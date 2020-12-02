/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  PLL���� 
             ѡ��ϵͳʹ���ⲿ8M����XTALʱ��
*��  ע:  ������HRSDK-GDB-ES8P508x
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"
#include "ES8P508x.h"

//ע���˴�������Ҫ����8M���񣬲�Ҫʹ��ĸ�壨ĸ��������·��Ծ������Ӱ�죩��ֻ��Ҫʹ���Ӱ弴��

int main(void)
{
    SystemClockSelect(CLK_SEL_XTAL);       //ѡ��XTAL
    SystemCoreClock = 8000000;                              //����������ڴ˴��޸ļ���
    DeviceClockAllEnable();

    SysTickInit();
    LightInit();

    GPIOA_ResetBit(GPIO_Pin_14);

    while(1)
    {
        GPIOA_ResetBit(GPIO_Pin_14);
        Delay100us(10000);
        GPIOA_SetBit(GPIO_Pin_14);
        Delay100us(10000);
    }
}
