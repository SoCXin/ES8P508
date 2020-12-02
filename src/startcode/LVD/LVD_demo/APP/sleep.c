/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  sleep.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  
*备  注:  适用于HRSDK-GDB-HR8P296 V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "sleep.h"

/*********************************************************
函数名: void Sleep(uchar mode)
描  述: 进入待机模式子程序
输入值: mode - IDLE模式 
输出值: 无
返回值: 无 
**********************************************************/
void Sleep(uint8_t mode)
{
    if(1 == mode)
    {
        SCB_SystemLPConfig(SCB_LP_SleepDeep, ENABLE);   //配置为深度睡眠模式
    }
    //idle();
    //__asm { WFI } 
    __WFI();
}
