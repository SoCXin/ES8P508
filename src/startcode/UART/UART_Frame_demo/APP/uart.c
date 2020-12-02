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
    GPIO_Init(GPIOA,GPIO_Pin_15,&y);                 //PA15---TxD

    y.GPIO_Signal = GPIO_Pin_Signal_Digital;
	  y.GPIO_Func = GPIO_Func_2;
    y.GPIO_Direction = GPIO_Dir_In;
    y.GPIO_PUEN = GPIO_PUE_Input_Enable;
    y.GPIO_PDEN = GPIO_PDE_Input_Disable;
    y.GPIO_OD = GPIO_ODE_Output_Disable;
    y.GPIO_DS = GPIO_DS_Output_Strong;
    GPIO_Init(GPIOA,GPIO_Pin_16,&y);                 //PA16---RxD

    uart.UART_StopBits = UART_StopBits_1;          //停止位：1
    uart.UART_TxMode = UART_DataMode_8;            //发送数据格式：8位数据
    uart.UART_TxPolar = UART_Polar_Normal;         //发送端口极性：正常
    uart.UART_RxMode = UART_DataMode_8;            //接收数据格式：8位数据
    uart.UART_RxPolar = UART_Polar_Normal;         //接收端口极性：正常
    uart.UART_BaudRate = 9600;                     //波特率
    uart.UART_ClockSet = UART_Clock_1;             //时钟选择：Pclk
    UART_Init(UART2,&uart);

    UART_TBIMConfig(UART2,UART_TRBIM_Byte);
    UART_RBIMConfig(UART2, UART_TRBIM_Byte);
    UART_ITConfig(UART2,UART_IT_RB,ENABLE);
    NVIC_Init(NVIC_UART2_IRQn,NVIC_Priority_1,ENABLE);
    UART2_TxEnable();                               //UART2发送使能
    UART2_RxEnable();
}
/*********************************************************
函数名: void UARTTxData(uint8_t *buf, uint8_t n)
描  述: UART发送数据整帧打包
输入值: buf—发送数据缓存
        n—发送数据个数
输出值: 无
返回值: 无
**********************************************************/
void UARTTxData(uint8_t *buf, uint8_t n)
{
    uint8_t i, check_sum;

    buf[0] = HEAD1;             //帧头0x55
    buf[1] = HEAD2;             //帧头0xAA
    buf[2] = SLAVE_ADDR;        //设备地址

    check_sum = 0;

    for (i=0; i<n-3; i++)
        check_sum ^= buf[i];    //计算所有字节（包括帧头）的异或和

    buf[n-3] = check_sum;       //赋值校验和
    buf[n-2] = TAIL1;           //帧尾0x5A
    buf[n-1] = TAIL2;           //帧尾0xA5
    UART_ITConfig(UART2, UART_IT_TB, ENABLE);    //使能发送中断，在中断判断并结束发送数据帧
}

/*********************************************************
函数名: uint8_t UARTRxData(uint8_t *buf, uint8_t n)
描  述: UART接收数据整帧解包
输入值: 无
输出值: buf—接收数据缓存
        n—接收数据个数
返回值: 无
**********************************************************/
uint8_t UARTRxData(uint8_t *buf, uint8_t n)
{
    uint8_t i, check_sum;

    if ((buf[0] != HEAD1)
         || (buf[1] != HEAD2)
         || (buf[n-2] != TAIL1)
         || (buf[n-1] != TAIL2))      //判断帧头及帧尾有误
        return 1;

    if (buf[2] != SLAVE_ADDR)       //判断从机地址不匹配
        return 1;

    check_sum = 0;
    for (i = 0; i < n-3; i++)    
        check_sum ^= buf[i];        //计算所有字节（包括帧头）的异或和

    if (buf[n-3] != check_sum)      //判断校验和错误
        return 1;

    return 0;                       //正确解包本帧数据
}

