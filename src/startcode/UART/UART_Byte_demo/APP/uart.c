/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:    uart.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/29
*描  述:    UART模块程序（中断收发）
*备  注:    适用于HRSDK-GDB-ES8P508x V1.0
            本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "uart.h"

/*********************************************************
函数名: void UARTInit(void)
描  述: UART初始化子程序
输入值: 无
输出值: 无
返回值: 无
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

    uart.UART_StopBits = UART_StopBits_1;          //停止位：1
    uart.UART_TxMode = UART_DataMode_8;            //发送数据格式：8位数据
    uart.UART_TxPolar = UART_Polar_Normal;         //发送端口极性：正常
    uart.UART_RxMode = UART_DataMode_8;            //接收数据格式：8位数据
    uart.UART_RxPolar = UART_Polar_Normal;         //接收端口极性：正常
    uart.UART_BaudRate = 9600;                     //波特率
    uart.UART_ClockSet = UART_Clock_1;             //时钟选择：Pclk
    UART_Init(UART2, &uart);

    UART_TBIMConfig(UART2, UART_TRBIM_Byte);
    UART_RBIMConfig(UART2, UART_TRBIM_Byte);
    UART_ITConfig(UART2, UART_IT_RB, ENABLE);
    NVIC_Init(NVIC_UART2_IRQn, NVIC_Priority_1, ENABLE);
    UART2_TxEnable();                               //UART2发送使能
    UART2_RxEnable();
}
