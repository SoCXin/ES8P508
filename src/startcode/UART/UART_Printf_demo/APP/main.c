/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  UART模块例程 
          可调用标准库使用，需要以下三个步骤
		  1、keil勾选Use MicroLIB ，2、main.c #include "stdio.h"，3、keil #define __PRINTF_USE_UART2__
*备  注:  适用于ES8P508x芯片
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"
#include "stdio.h"

int main(void)
{
    uint8_t cnt = 245;
    unsigned char buf[] = {'E', 'a', 's', 't', 's', 'o', 'f', 't', '!','\0'};

    SystemClockConfig();                //配置时钟  
    DeviceClockAllEnable();             //打开所有外设时钟

    SysTickInit();
    UARTInit();                         //UART初始化(9600,8,NO,1)

    while(1)
    {
        Delay1ms(2000);
        printf(" Hello word! \r\n");       //打印字符串
        Delay1ms(2000);
        printf(" cnt = %d \r\n", cnt);     //打印10进制数值
        Delay1ms(2000);
        printf(" %s \r\n", buf);           //打印字符
    }
}

