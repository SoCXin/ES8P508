/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/22
*描  述:  UART演示主程序 
          上电发送 "Hello word!"后，等待串口接收，发送相同Byte
*备  注:  适用于ES8P508x芯片
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{

    uint8_t i;
    uint8_t buf[] = {"Hello word!"};    //发送数据缓存

    SystemClockConfig();                //配置时钟  
    DeviceClockAllEnable();             //打开所有外设时钟

    SysTickInit();
    UARTInit();                         //UART初始化(9600,8,NO,1)

    for(i=0; i<sizeof(buf); i++)
    {
        while(UART_GetFlagStatus(UART2, UART_FLAG_TB) == RESET);
        UART_SendByte(UART2, buf[i]);
    }

    while(1);
}

