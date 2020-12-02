/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.01
*日  期:  2017/06/29
*描  述:  PLL例程 
             选择系统使用外部8M晶振XTAL时钟
*备  注:  适用于HRSDK-GDB-ES8P508x
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"
#include "ES8P508x.h"

//注：此处测试需要焊接8M晶振，不要使用母板（母板连接线路会对晶振产生影响），只需要使用子板即可

int main(void)
{
    SystemClockSelect(CLK_SEL_XTAL);       //选择XTAL
    SystemCoreClock = 8000000;                              //其他规格晶振在此处修改即可
    DeviceClockAllEnable();

    SysTickInit();
    LightInit();

    GPIOA_ResetBit(GPIO_Pin_14);

    while(1)
    {
        GPIOA_ResetBit(GPIO_Pin_14);
        Delay100us(10000);
        GPIOA_SetBit(GPIO_Pin_14);
        Delay100us(10000);
    }
}
