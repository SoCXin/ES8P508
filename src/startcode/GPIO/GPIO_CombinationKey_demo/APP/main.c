/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*作 者:  Liut
*版 本:  V1.00
*日 期:  2017/06/22
*描 述： 按键检测演示程序
*备 注:  适用于HRSDK-GDB-ES8P508x
         单击K1(按下有效),LED1点亮
         单击K2(释放有效),LED2翻转
         单击K3(按下有效),LED1-LED4流水点亮
         单击K4(按下有效),LED4-LED1流水点亮
         单击K5(按下有效),所有LED熄灭
     本软件仅供学习和演示使用，对用户直接引用代码所带来的风险和后果不承担任何法律责任
**********************************************************/
#include "main.h"
#include "led.h"

int main()
{
    SystemClockConfig();                //系统时钟配置
    DeviceClockAllEnable();             //外部时钟使能
    SysTickInit();

    LEDInit();
    T16N3Init();
    LightInit();                        //Light初始化
    KeyInit();                          //按键初始化

    GPIOA_SetBit(GPIO_Pin_11);          //熄灭LD4
    GPIOA_SetBit(GPIO_Pin_12);          //熄灭LD3
    GPIOA_SetBit(GPIO_Pin_13);          //熄灭LD2
    GPIOA_SetBit(GPIO_Pin_14);          //熄灭LD1

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




