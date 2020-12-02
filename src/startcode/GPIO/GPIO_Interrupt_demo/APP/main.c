/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/22
*��  ��:  LED��ʾ������
          ѭ������0000-9999��ÿ��1s����һ�Σ�����K5��������(����ʹ���ж�ģʽ����)
*��  ע:  ������HRSDK-GDB-ES8P508x V1.1
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main(void)
{
    uint8_t com = 0;
    uint16_t disp_data = 0; 
    KINT_InitSettingType y; 
    GPIO_InitStruType x;	

    SystemClockConfig();                           //����ʱ��  
    DeviceClockAllEnable();                        //����������ʱ��

    T16N3Init();                                   //T16N��ʱ����ʼ��               
    LEDInit();                                     //����ܳ�ʼ��
	
    x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_In;
    x.GPIO_PUEN = GPIO_PUE_Input_Enable;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOA,GPIO_Pin_20,&x);               //��ʼ��KINT����
	
    y.IE_Set = KINT_IE_Set_Enable;
    y.Trigger_Style = KINT_Trigger_Trailing_Edge;
    KINT_Init(GPIOA,GPIO_Pin_20, &y);              //��ʼ�������ж�PA20

    DispHextoBcd(com, g_led_buf);
	
    while(1)
    {
        if(1 == g_2ms_flag)                        //��ʾ��ֵ
        {
            g_2ms_flag = 0;
            LEDDisplayData(com,g_led_buf[com]);
            com++;
            if(com > 3)
                com = 0;
        }

        if(1 == g_1s_flag)                         //��������
        {
             g_1s_flag = 0;
             DispHextoBcd(disp_data,g_led_buf);
             disp_data++;
             if(disp_data > 9999)
                disp_data = 0;
        }
		if(1 == g_key_flag_4)                      //�����ж�
        {
            g_key_flag_4 = 0;
            disp_data = 0;
        }
    }
}
