/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�� ��:  Liut
*�� ��:  V1.00
*�� ��:  2017/06/22
*�� ���� ���������ʾ����
*�� ע:  ������HRSDK-GDB-ES8P508x
         ����K1(������Ч),LED1����
         ����K2(�ͷ���Ч),LED2��ת
         ����K3(������Ч),LED1-LED4��ˮ����
         ����K4(������Ч),LED4-LED1��ˮ����
         ����K5(������Ч),����LEDϨ��
     ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��պͺ�����е��κη�������
**********************************************************/
#include "main.h"
#include "led.h"

int main()
{
    SystemClockConfig();                //ϵͳʱ������
    DeviceClockAllEnable();             //�ⲿʱ��ʹ��
    SysTickInit();

    LEDInit();
    T16N3Init();
    LightInit();                        //Light��ʼ��
    KeyInit();                          //������ʼ��

    GPIOA_SetBit(GPIO_Pin_11);          //Ϩ��LD4
    GPIOA_SetBit(GPIO_Pin_12);          //Ϩ��LD3
    GPIOA_SetBit(GPIO_Pin_13);          //Ϩ��LD2
    GPIOA_SetBit(GPIO_Pin_14);          //Ϩ��LD1

    g_10ms_flag = 0;
    g_200ms_flag = 0;
    g_200ms_cnt = 0;
    g_key_cmd = 0;
    flag = 0;

    while (1)
    {
        if (g_10ms_flag == 1)
        {
            g_10ms_flag = 0;
            g_key_cmd = KeyGetValue();

            switch (g_key_cmd)
            {
                case 1:
                    GPIOA_ResetBit(GPIO_Pin_14);
                    break;

                case 2:
                    if (flag == 1)
                    {
                        flag = 0;
                        GPIOA_SetBit(GPIO_Pin_13);
                    }
                    else
                    {
                        flag = 1;
                        GPIOA_ResetBit(GPIO_Pin_13);
                    }

                    break;

                case 3:
                    GPIOA_SetBit(GPIO_Pin_11);
                    GPIOA_SetBit(GPIO_Pin_12);
                    GPIOA_SetBit(GPIO_Pin_13);
                    GPIOA_SetBit(GPIO_Pin_14);

                    GPIOA_ResetBit(GPIO_Pin_14);
                    Delay1ms(500);
                    GPIOA_ResetBit(GPIO_Pin_13);
                    Delay1ms(500);
                    GPIOA_ResetBit(GPIO_Pin_12);
                    Delay1ms(500);
                    GPIOA_ResetBit(GPIO_Pin_11);
                    Delay1ms(500);

                    GPIOA_SetBit(GPIO_Pin_11);
                    GPIOA_SetBit(GPIO_Pin_12);
                    GPIOA_SetBit(GPIO_Pin_13);
                    GPIOA_SetBit(GPIO_Pin_14);
                    break;

                case 4:
                    GPIOA_SetBit(GPIO_Pin_11);
                    GPIOA_SetBit(GPIO_Pin_12);
                    GPIOA_SetBit(GPIO_Pin_13);
                    GPIOA_SetBit(GPIO_Pin_14);

                    GPIOA_ResetBit(GPIO_Pin_11);
                    Delay1ms(500);
                    GPIOA_ResetBit(GPIO_Pin_12);
                    Delay1ms(500);
                    GPIOA_ResetBit(GPIO_Pin_13);
                    Delay1ms(500);
                    GPIOA_ResetBit(GPIO_Pin_14);
                    Delay1ms(500);

                    GPIOA_SetBit(GPIO_Pin_11);
                    GPIOA_SetBit(GPIO_Pin_12);
                    GPIOA_SetBit(GPIO_Pin_13);
                    GPIOA_SetBit(GPIO_Pin_14);
                    break;

                case 5:
                    GPIOA_SetBit(GPIO_Pin_11);
                    GPIOA_SetBit(GPIO_Pin_12);
                    GPIOA_SetBit(GPIO_Pin_13);
                    GPIOA_SetBit(GPIO_Pin_14);
                    break;

                default:
                    g_key_cmd = 0;
                    GPIOA_SetBit(GPIO_Pin_14);
                    GPIOA_SetBit(GPIO_Pin_12);
                    break;
            }
        }
    }
}




