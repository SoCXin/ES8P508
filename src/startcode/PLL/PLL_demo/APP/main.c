/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  PLL例程
          PLL倍频到48M后，定时闪烁LD1-LD4指示灯，先调用PLLClock_Config()函数，可观测到系统时钟倍频至48MHz情况下LED灯的闪烁情况，屏蔽PLLClock_Config()函数，
      编译再下载后，系统时钟会更改为内部16MHz高速时钟，切记！！！此时应该应该硬件复位一下，如不硬件复位，系统
      时钟还会以48MHz倍频时钟去工作。
*备  注:  适用于HRSDK-GDB-ES8P508x
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"
#include "ES8P508x.h"

int main(void)
{
    uint8_t clock_cnt = 0;

    SystemInit();
    PLLClock_Config(ENABLE, SCU_PLL_HRC, SCU_PLL_48M, ENABLE);   //PLL使能，倍频到48M（可关闭打开分别观察指示灯闪烁差异）

    DeviceClockAllEnable();

    LightInit();
    T16N3Init();

    GPIOA_ResetBit(GPIO_Pin_14);
    GPIOA_ResetBit(GPIO_Pin_13);
    GPIOA_ResetBit(GPIO_Pin_12);
    GPIOA_ResetBit(GPIO_Pin_11);

    while (1)
    {
        if (1 == g_900ms_flag)
        {
            g_900ms_flag = 0;
            clock_cnt++;
        }

        if (clock_cnt % 2 == 1)
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
