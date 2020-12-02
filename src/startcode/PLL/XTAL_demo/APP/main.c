/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  PLL���� 
              ѡ��ϵͳʹ���ⲿ20M����XTALʱ���ȵ���PLLClock_Config()�������ɹ۲⵽ϵͳʱ�ӱ�Ƶ��48MHz�����LED�Ƶ���˸�����
          ����PLLClock_Config()������ ���������غ� ϵͳʱ�ӻ����Ϊ�ⲿ20MHz����ʱ�ӣ��мǣ�������ʱӦ��Ӧ��Ӳ����λһ�£��粻Ӳ����λ��ϵͳ
		  ʱ�ӻ�����48MHz��Ƶʱ��ȥ������
*��  ע:  ������HRSDK-GDB-ES8P508
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"
#include "ES8P508x.h"

int main(void)
{
    uint8_t clock_cnt = 0;

    SystemClockSelect(CLK_SEL_XTAL);     //ѡ��XTAL
    PLLClock_Config(ENABLE, SCU_PLL_XTAL_20M, SCU_PLL_48M, ENABLE);    //PLLʹ�ܣ���Ƶ��48M���ɹرմ򿪷ֱ�۲�ָʾ����˸���죩
    DeviceClockAllEnable();

    LightInit();
    T16N3Init();

    GPIOA_ResetBit(GPIO_Pin_14);
    GPIOA_ResetBit(GPIO_Pin_13);
    GPIOA_ResetBit(GPIO_Pin_12);
    GPIOA_ResetBit(GPIO_Pin_11);

    while(1)
    {
        if(1 == g_900ms_flag)
        {
            g_900ms_flag = 0;
            clock_cnt++;
        }

        if(clock_cnt%2 == 1)
        {
	    GPIOA_ResetBit(GPIO_Pin_14);
	    GPIOA_ResetBit(GPIO_Pin_13);
	    GPIOA_ResetBit(GPIO_Pin_12);
	    GPIOA_ResetBit(GPIO_Pin_11);
        }
        else
        {
            GPIOA_SetBit(GPIO_Pin_14);
            GPIOA_SetBit(GPIO_Pin_13);
            GPIOA_SetBit(GPIO_Pin_12);
            GPIOA_SetBit(GPIO_Pin_11);
        }
    }
}
