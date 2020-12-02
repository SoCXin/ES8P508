/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/24
*��  ��:  ADC��ʾ������
          ADCʹ�õȴ�ת�����ת����
          ����10K�ĵ�λ����ͨ��4λ�������ʾADC�����12bits��
          ����K5�л�ADCͨ�����Ӱ�KINT��̽ӣ����ֱ��AIN1��AIN0���в���
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
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

        if (1 == g_200ms_flag)                          //���200ms��ȡ����ADC��ֵ
        {
            g_200ms_flag = 0;

            adc_data = ADCRead();
            DispHextoBcd(adc_data, g_led_buf);
        }

        if (1 == g_2ms_flag)                            //���2msˢ���������ʾ
        {
            g_2ms_flag = 0;

            LEDDisplayData(com, g_led_buf[com]);

            com++;

            if (com > 3)
            {
                com = 0;
            }
        }

        if (1 == g_10ms_flag)                           //���10msɨ�谴��
        {
            g_10ms_flag = 0;

            if (5 == KeyGetValue())
            {
                channel_flag = ~channel_flag;       //�л���ʾģʽ
            }
        }
    }
}


