/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/24
*��  ��:  ADC��ʾ������ 
          ADCʹ�õȴ�ת�����ת����
          ����10K�ĵ�λ����ͨ��4λ�������ʾADC�����12bits��
          ����K5�л���ʾģʽ���ֱ���ʾADC��ֵ��ģ���ѹֵ
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
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

    while(1)
    {
        if(1 == g_200ms_flag)                           //���200ms��ȡ����ADC��ֵ
        {
            g_200ms_flag = 0;

            if (disp_mode_flag == 0xFF)                 //��ʾģʽ��ADC�Ĵ�������ֵ
            {
                adc_data = ADCRead();
                DispHextoBcd(adc_data,g_led_buf);
            }
            else                                        //��ʾģʽ��ת����ѹֵ
            {
                adc_data = ADCRead();
                adc_data = RATION * adc_data;
                DispHextoBcd(adc_data,g_led_buf);
            }
        }

        if(1 == g_2ms_flag)                             //���2msˢ���������ʾ
        {
            g_2ms_flag = 0;

            LEDDisplayData(com,g_led_buf[com]);
            if ((com == 0) && (disp_mode_flag == 0))    //��һ�����������ʾģʽΪ��ѹֵʱ����ʾС����
            {
                GPIOB_SetBit(GPIO_Pin_13);
            }
            com++;
            if(com > 3)
            {
                com = 0;
            }
        }

        if (1 == g_10ms_flag)                           //���10msɨ�谴��
        {
            g_10ms_flag = 0;

            if(5 == KeyGetValue())
            {
                disp_mode_flag = ~disp_mode_flag;       //�л���ʾģʽ
            }
        }
    }
}


