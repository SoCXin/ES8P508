/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  蜂鸣器演示主程序
         （1）单击K4：演奏《两只老虎》
         （2）单击K3：演奏《新年好》
         （3）单击K2：演奏《粉刷匠》
         （4）单击K1：演奏《拔萝卜》
         （5）单击K5：演奏音符音阶
         注：需使用杜邦线将PA23与BUZ2连接，PB9与BUZ1连接 !
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{    
    uint8_t key; 
    const uint8_t *p_music;

    SystemClockConfig();       //配置时钟  
    DeviceClockAllEnable();    //打开所有外设时钟

    SysTickInit();             //系统滴答初始化
    KeyInit();                 //初始化按键
    Buzzer_Init();             //初始化蜂鸣器

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
