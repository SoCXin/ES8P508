/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:    uart.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/29
*��  ��:    UARTģ������ж��շ���
*��  ע:    ������HRSDK-GDB-ES8P508x V1.0
            ����������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "uart.h"

/*********************************************************
������: void UARTInit(void)
��  ��: UART��ʼ���ӳ���
����ֵ: ��
���ֵ: ��
����ֵ: ��
**********************************************************/
void UARTInit(void)
{
    GPIO_InitStruType y;
    UART_InitStruType uart;

    y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_2;
    y.GPIO_Direction = GPIO_Dir_Out;
    y.GPIO_PUEN = GPIO_PUE_Input_Disable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Strong;
    GPIO_Init(GPIOA, GPIO_Pin_15, &y);               //PA15---TxD

    y.GPIO_Signal = GPIO_Pin_Signal_Digital;
    y.GPIO_Func = GPIO_Func_2;
    y.GPIO_Direction = GPIO_Dir_In;
    y.GPIO_PUEN = GPIO_PUE_Input_Enable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Strong;
    GPIO_Init(GPIOA, GPIO_Pin_16, &y);               //PA16---RxD

    uart.UART_StopBits = UART_StopBits_1;          //ֹͣλ��1
    uart.UART_TxMode = UART_DataMode_8;            //�������ݸ�ʽ��8λ����
    uart.UART_TxPolar = UART_Polar_Normal;         //���Ͷ˿ڼ��ԣ�����
    uart.UART_RxMode = UART_DataMode_8;            //�������ݸ�ʽ��8λ����
    uart.UART_RxPolar = UART_Polar_Normal;         //���ն˿ڼ��ԣ�����
    uart.UART_BaudRate = 9600;                     //������
    uart.UART_ClockSet = UART_Clock_1;             //ʱ��ѡ��Pclk
    UART_Init(UART2, &uart);

    UART_TBIMConfig(UART2, UART_TRBIM_Byte);
    UART_RBIMConfig(UART2, UART_TRBIM_Byte);
    UART_ITConfig(UART2, UART_IT_RB, ENABLE);
    NVIC_Init(NVIC_UART2_IRQn, NVIC_Priority_1, ENABLE);
    UART2_TxEnable();                               //UART2����ʹ��
    UART2_RxEnable();
}