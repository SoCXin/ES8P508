/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  ��������ʾ������
         ��1������K4�����ࡶ��ֻ�ϻ���
         ��2������K3�����ࡶ����á�
         ��3������K2�����ࡶ��ˢ����
         ��4������K1�����ࡶ���ܲ���
         ��5������K5��������������
         ע����ʹ�öŰ��߽�PA23��BUZ2���ӣ�PB9��BUZ1���� !
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main(void)
{    
    uint8_t key; 
    const uint8_t *p_music;

    SystemClockConfig();       //����ʱ��  
    DeviceClockAllEnable();    //����������ʱ��

    SysTickInit();             //ϵͳ�δ��ʼ��
    KeyInit();                 //��ʼ������
    Buzzer_Init();             //��ʼ��������

    while(1)
    {
        key = KeyGetValue();
        switch (key)
        {
            case 4:
                p_music = Music4;
                PlayMusic(p_music);
                break;
            case 3:
                p_music = Music3;
                PlayMusic(p_music);
                break;
            case 2:
                p_music = Music2;
                PlayMusic(p_music);
                break;
            case 1:
                p_music = Music1;
                PlayMusic(p_music);
                break;
            case 5:
                PlayTone();
                break;
            default:
                break;
        }
    }
}
