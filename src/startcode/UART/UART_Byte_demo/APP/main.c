/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/22
*��  ��:  UART��ʾ������ 
          �ϵ緢�� "Hello word!"�󣬵ȴ����ڽ��գ�������ͬByte
*��  ע:  ������ES8P508xоƬ
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main(void)
{

    uint8_t i;
    uint8_t buf[] = {"Hello word!"};    //�������ݻ���

    SystemClockConfig();                //����ʱ��  
    DeviceClockAllEnable();             //����������ʱ��

    SysTickInit();
    UARTInit();                         //UART��ʼ��(9600,8,NO,1)

    for(i=0; i<sizeof(buf); i++)
    {
        while(UART_GetFlagStatus(UART2, UART_FLAG_TB) == RESET);
        UART_SendByte(UART2, buf[i]);
    }

    while(1);
}

