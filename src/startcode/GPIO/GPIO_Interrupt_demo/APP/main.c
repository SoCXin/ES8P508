/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/22
*描  述:  LED演示主程序
          循环计数0000-9999，每隔1s计数一次，按键K5按下清零(按键使用中断模式输入)
*备  注:  适用于HRSDK-GDB-ES8P508x V1.1
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{
    uint8_t com = 0;
    uint16_t disp_data = 0; 
    KINT_InitSettingType y; 
    GPIO_InitStruType x;	

    SystemClockConfig();                           //配置时钟  
    DeviceClockAllEnable();                        //打开所有外设时钟

    T16N3Init();                                   //T16N定时器初始化               
    LEDInit();                                     //数码管初始化
	
    x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_In;
    x.GPIO_PUEN = GPIO_PUE_Input_Enable;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOA,GPIO_Pin_20,&x);               //初始化KINT按键
	
    y.IE_Set = KINT_IE_Set_Enable;
    y.Trigger_Style = KINT_Trigger_Trailing_Edge;
    KINT_Init(GPIOA,GPIO_Pin_20, &y);              //初始化按键中断PA20

    DispHextoBcd(com, g_led_buf);
	
    while(1)
    {
        if(1 == g_2ms_flag)                        //显示数值
        {
            g_2ms_flag = 0;
            LEDDisplayData(com,g_led_buf[com]);
            com++;
            if(com > 3)
                com = 0;
        }

        if(1 == g_1s_flag)                         //秒数增加
        {
             g_1s_flag = 0;
             DispHextoBcd(disp_data,g_led_buf);
             disp_data++;
             if(disp_data > 9999)
                disp_data = 0;
        }
		if(1 == g_key_flag_4)                      //按键中断
        {
            g_key_flag_4 = 0;
            disp_data = 0;
        }
    }
}
