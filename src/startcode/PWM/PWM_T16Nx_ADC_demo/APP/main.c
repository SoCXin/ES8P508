/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  ��ʱ��PWM�����ʾ������ 
            PA28�������PWM���Σ�ʹ��PWM����ģʽ����ADC������10K�ĵ�λ����ͨ��4λ�������ʾADC�����12bits��
*��  ע:  ������ES8P508xоƬ
          ����������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main(void)
{
    uint8_t com = 0;
    uint16_t adc_data = 0;
    uint8_t disp_mode_flag = 0;
    uint8_t g_led_buf[4];

    SystemClockConfig();            //����ʱ��  
    DeviceClockAllEnable();         //����������ʱ��

    T16N3Init();
    LEDInit();
    T16Nx_Init();
    ADC0_UserInit();

    while(1)
    {
        if(1 == g_adc_flag)                              //�ж϶�ȡ����ADC��ֵ
        {
            g_adc_flag = 0;

            if (disp_mode_flag == 0xFF)                 //��ʾģʽ��ADC�Ĵ�������ֵ
            {
                adc_data = g_adc_data;
                DispHextoBcd(adc_data,g_led_buf);
                DispHextoBcd(g_adc_data,g_led_buf);
            }
            else                                        //��ʾģʽ��ת����ѹֵ
            {
                adc_data = g_adc_data;
                adc_data = (uint16_t)(RATION * (float)adc_data);
                DispHextoBcd(adc_data,g_led_buf);
            }
            ADC_Start();                                //��ʼ��һ��ADCת��
        }

        if(1 == g_2ms_flag)                             //���2msˢ���������ʾ
        {
            g_2ms_flag = 0;

            LEDDisplayData(com,g_led_buf[com]);
            if ((com == 0) && (disp_mode_flag == 0))    //��һ�����������ʾģʽΪ��ѹֵʱ����ʾС����
            {
                GPIOB_SetBit(GPIO_Pin_1);
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
