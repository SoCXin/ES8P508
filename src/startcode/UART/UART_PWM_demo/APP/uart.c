/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  uart.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "uart.h"
#include "lib_timer.h"

/*********************************************************
������: void UARTInit(void)
��  ��: UART��ʼ���ӳ���
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void UARTInit(void)
{
    GPIO_InitStruType x;
    UART_InitStruType y;

    x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Direction = GPIO_Dir_Out;
    x.GPIO_Func   = GPIO_Func_2;
    x.GPIO_OD     = GPIO_ODE_Output_Disable;
    x.GPIO_DS     = GPIO_DS_Output_Strong;
    x.GPIO_PUEN   = GPIO_PUE_Input_Disable;
    x.GPIO_PDEN   = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIOB, GPIO_Pin_1, &x);       //TXD - PB1

    x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func   = GPIO_Func_2;
    x.GPIO_Direction = GPIO_Dir_In;
    x.GPIO_OD     = GPIO_ODE_Output_Disable;
    x.GPIO_DS     = GPIO_DS_Output_Strong;
    x.GPIO_PUEN   = GPIO_PUE_Input_Enable;
    x.GPIO_PDEN   = GPIO_PDE_Input_Disable;
    GPIO_Init(GPIOB, GPIO_Pin_0, &x);        //RXD - PB0

    y.UART_StopBits = UART_StopBits_1;       //ֹͣλ��1
    y.UART_TxMode   = UART_DataMode_8Odd;    //�������ݸ�ʽ��8λ����+��У��
    y.UART_TxPolar  = UART_Polar_Normal;     //���Ͷ˿ڼ��ԣ�����
    y.UART_RxMode   = UART_DataMode_8;       //�������ݸ�ʽ��8λ����
    y.UART_RxPolar  = UART_Polar_Normal;     //���ն˿ڼ��ԣ�����
    y.UART_BaudRate = 1200;                  //������
    y.UART_ClockSet = UART_Clock_1;          //ʱ��ѡ��Pclk
    UART_Init(UART0, &y);

    GPIO_TX0Config(UART_TXPLV_Low, UART_TX0PS_BUZ, UART_TYPE_TXD0);
    BUZC_Frequence(38000, ENABLE);           //BUZ���38k

    UART_TBIMConfig(UART0, UART_TRBIM_Byte);
    UART_RBIMConfig(UART0, UART_TRBIM_Byte);
    UART_ITConfig(UART0, UART_IT_RB, ENABLE);
    NVIC_Init(NVIC_UART0_IRQn, NVIC_Priority_1, ENABLE);

    UART0_TxEnable();
    UART0_RxEnable();
}
