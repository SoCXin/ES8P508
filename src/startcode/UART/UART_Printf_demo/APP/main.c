/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  UARTģ������ 
          �ɵ��ñ�׼��ʹ�ã���Ҫ������������
		  1��keil��ѡUse MicroLIB ��2��main.c #include "stdio.h"��3��keil #define __PRINTF_USE_UART2__
*��  ע:  ������ES8P508xоƬ
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"
#include "stdio.h"

int main(void)
{
    uint8_t cnt = 245;
    unsigned char buf[] = {'E', 'a', 's', 't', 's', 'o', 'f', 't', '!','\0'};

    SystemClockConfig();                //����ʱ��  
    DeviceClockAllEnable();             //����������ʱ��

    SysTickInit();
    UARTInit();                         //UART��ʼ��(9600,8,NO,1)

    while(1)
    {
        Delay1ms(2000);
        printf(" Hello word! \r\n");       //��ӡ�ַ���
        Delay1ms(2000);
        printf(" cnt = %d \r\n", cnt);     //��ӡ10������ֵ
        Delay1ms(2000);
        printf(" %s \r\n", buf);           //��ӡ�ַ�
    }
}

