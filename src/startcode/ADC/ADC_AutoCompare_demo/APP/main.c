/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/24
*描  述:  ADC演示主程序 
          ADC自动转换比较：
          采用10K的电位器，通过4位数码管显示ADC结果
          （12bits）
          按键K5切换显示模式，分别显示ADC数值和模拟电压值
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main()
{
    uint8_t com = 0;
    uint16_t adc_data = 0;
    uint8_t disp_mode_flag = 0;
    uint8_t g_led_buf[4];

    SystemClockConfig();
    DeviceClockAllEnable();

    T16N3Init();
    LEDInit();
    KeyInit();
    ADC0_UserInit();
    ADCACPConfig();
    ADC_Start();

    while(1)
    {
        if(1 == g_adc_flag)                              //中断读取采样ADC数值
        {
            g_adc_flag = 0;

            if (disp_mode_flag == 0xFF)                 //显示模式：ADC寄存器采样值
            {
                adc_data = g_adc_data;
                DispHextoBcd(adc_data,g_led_buf);

                DispHextoBcd(g_adc_data,g_led_buf);
            }
            else                                        //显示模式：转换电压值
            {
                adc_data = g_adc_data;
                adc_data = (uint16_t)(RATION * (float)adc_data);
                DispHextoBcd(adc_data,g_led_buf);
            }
        }

        if(1 == g_2ms_flag)                             //间隔2ms刷新数码管显示
        {
            g_2ms_flag = 0;

            LEDDisplayData(com,g_led_buf[com]);
            if ((com == 0) && (disp_mode_flag == 0))    //第一个数码管在显示模式为电压值时，显示小数点
            {
                GPIOB_SetBit(GPIO_Pin_13);
            }
            com++;
            if(com > 3)
            {
                com = 0;
            }
        }

        if (1 == g_10ms_flag)                           //间隔10ms扫描按键
        {
            g_10ms_flag = 0;

            if(5 == KeyGetValue())
            {
                disp_mode_flag = ~disp_mode_flag;       //切换显示模式
            }
        }
    }
}





