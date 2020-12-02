/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/22
*��  ��:  LED��ʾ������
          ѭ������0000-9999��ÿ��1s����һ�Σ�����K5�������㣨����ʹ��ɨ�跽ʽ���룩
*��  ע:  ������HRSDK-GDB-ES8P508x V1.1
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main(void)
{
    uint8_t com = 0;
    uint16_t disp_data = 0; 

    SystemClockConfig();            //����ʱ��  
    DeviceClockAllEnable();         //����������ʱ��

    T16N3Init();                    //T16N��ʱ����ʼ��
    KeyInit();                      //K5��ʼ��
    LEDInit();                      //����ܳ�ʼ��

    while(1)
    {
        if(1 == g_2ms_flag)                             //��ʾ��ֵ
        {
            g_2ms_flag = 0;
            LEDDisplayData(com,g_led_buf[com]);
            com++;
            if(com > 3)
                com = 0;
        }

        if(1 == g_1s_flag)                              //��������
        {
             g_1s_flag = 0;
             DispHextoBcd(disp_data,g_led_buf);
             disp_data += 1;
             if(disp_data > 9999)
                disp_data = 0;
        }

        if (1 == g_10ms_flag)                           //ɨ�谴��
        {
            g_10ms_flag = 0;

            if(5 == KeyGetValue())
            {
                disp_data = 0;
            }
        }
    }
}
