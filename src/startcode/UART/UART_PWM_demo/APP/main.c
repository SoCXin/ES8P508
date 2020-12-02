/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  UARTģ������
          ʹ��UART0��PB1���ͣ�ʹ��38KPWM���ƣ������շ�����������0X55,�����жϺ󣬽����յ�0x55���ͣ����ָʾ
*��  ע:  ������ES8P508xоƬ
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"
#include "systick.h"


extern uint8_t g_rx_buf;

int main(void)
{
    SystemInit();                //����ʱ��
    DeviceClockAllEnable();      //����������ʱ��

    SysTickInit();
    LightInit();
    UARTInit();                         //UART��ʼ��(1200,8,NO,1)

    g_recv_flag = 0;

    GPIOA_SetBit(GPIO_Pin_11);
    GPIOA_SetBit(GPIO_Pin_12);
    GPIOA_SetBit(GPIO_Pin_13);
    GPIOA_SetBit(GPIO_Pin_14);

    UART_SendByte(UART0, 0x55);

    while (1)
    {
        if (1 == g_recv_flag)
        {
            g_recv_flag = 0;
            g_rx_buf = 0;
            UART_SendByte(UART0, 0x55);
            GPIOA_ResetBit(GPIO_Pin_14);
            Delay100us(500);
        }
    }
}
