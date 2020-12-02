/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/22
*描  述:  PB6引脚输入下降沿方波信号，LED显示输入方波频率，最大显示支持9999Hz
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

uint32_t count = 0;

int main()
{
    uint8_t g_led_buf[4];
    uint8_t com = 0;

    SystemClockConfig();                //配置时钟  
    DeviceClockAllEnable();             //打开所有外设时钟

    SysTickInit();
    LightInit();
    LEDInit();
    T16N1CNT_Init();                    //PB6输入计数
    T16N2Init();

    GPIOA_SetBit(GPIO_Pin_11);         //熄灭LD4
    GPIOA_SetBit(GPIO_Pin_12);          //熄灭LD3
    GPIOA_SetBit(GPIO_Pin_13);          //熄灭LD2
    GPIOA_SetBit(GPIO_Pin_14);          //熄灭LD1

    memset(g_led_buf, 0,sizeof(g_led_buf));

    while(1)
    {
        if(g_1s_flag == 1)
        {
            g_1s_flag = 0;
            DispHextoBcd(count * 2,g_led_buf);
            count = 0;
        }

        if(g_2ms_flag == 1)
        {
            g_2ms_flag = 0;
            LEDDisplayData(com,g_led_buf[com]);
            com++;
            if(com > 3)
                com = 0;
        }
    }
}
