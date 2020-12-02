/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/22
*��  ��:  PB6���������½��ط����źţ�LED��ʾ���뷽��Ƶ�ʣ������ʾ֧��9999Hz
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

uint32_t count = 0;

int main()
{
    uint8_t g_led_buf[4];
    uint8_t com = 0;

    SystemClockConfig();                //����ʱ��  
    DeviceClockAllEnable();             //����������ʱ��

    SysTickInit();
    LightInit();
    LEDInit();
    T16N1CNT_Init();                    //PB6�������
    T16N2Init();

    GPIOA_SetBit(GPIO_Pin_11);         //Ϩ��LD4
    GPIOA_SetBit(GPIO_Pin_12);          //Ϩ��LD3
    GPIOA_SetBit(GPIO_Pin_13);          //Ϩ��LD2
    GPIOA_SetBit(GPIO_Pin_14);          //Ϩ��LD1

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
