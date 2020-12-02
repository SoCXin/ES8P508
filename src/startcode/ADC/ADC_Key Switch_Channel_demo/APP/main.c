/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/24
*描  述:  ADC演示主程序
          ADC使用等待转换完成转换：
          采用10K的电位器，通过4位数码管显示ADC结果（12bits）
          按键K5切换ADC通道（子板KINT需短接），分别对AIN1和AIN0进行采样
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main()
{
    uint8_t com = 0;
    uint16_t adc_data = 0;
    uint8_t channel_flag = 0;
    uint8_t g_led_buf[4];

    SystemClockConfig();
    DeviceClockAllEnable();

    T16N3Init();
    LEDInit();
    KeyInit();
    ADC0_UserInit();

    while (1)
    {
        if (channel_flag == 0)
        {
            ADC_Set_CH(ADC_CHS_AIN1);
        }
        else
        {
            ADC_Set_CH(ADC_CHS_AIN0);
        }

        if (1 == g_200ms_flag)                          //间隔200ms读取采样ADC数值
        {
            g_200ms_flag = 0;

            adc_data = ADCRead();
            DispHextoBcd(adc_data, g_led_buf);
        }

        if (1 == g_2ms_flag)                            //间隔2ms刷新数码管显示
        {
            g_2ms_flag = 0;

            LEDDisplayData(com, g_led_buf[com]);

            com++;

            if (com > 3)
            {
                com = 0;
            }
        }

        if (1 == g_10ms_flag)                           //间隔10ms扫描按键
        {
            g_10ms_flag = 0;

            if (5 == KeyGetValue())
            {
                channel_flag = ~channel_flag;       //切换显示模式
            }
        }
    }
}


