/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  定时器PWM输出演示主程序 
            PA28引脚输出PWM波形，使用PWM调制模式触发ADC，采用10K的电位器，通过4位数码管显示ADC结果（12bits）
*备  注:  适用于ES8P508x芯片
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{
    uint8_t com = 0;
    uint16_t adc_data = 0;
    uint8_t disp_mode_flag = 0;
    uint8_t g_led_buf[4];

    SystemClockConfig();            //配置时钟  
    DeviceClockAllEnable();         //打开所有外设时钟

    T16N3Init();
    LEDInit();
    T16Nx_Init();
    ADC0_UserInit();

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
            ADC_Start();                                //开始下一次ADC转换
        }

        if(1 == g_2ms_flag)                             //间隔2ms刷新数码管显示
        {
            g_2ms_flag = 0;

            LEDDisplayData(com,g_led_buf[com]);
            if ((com == 0) && (disp_mode_flag == 0))    //第一个数码管在显示模式为电压值时，显示小数点
            {
                GPIOB_SetBit(GPIO_Pin_1);
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

