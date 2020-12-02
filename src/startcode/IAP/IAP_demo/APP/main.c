/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/25
*描  述:  FLASH IAP演示主程序 
            FLASH的0x7C页写数据0x12345678
            读取改地址数据是否写入，写入成功点灯LD1，失败点灯LD4
*备  注:  适用于HRSDK-GDB-ES8P508x芯片
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{
    uint32_t g_rbuf = 0;
    uint32_t data = 0x12345678;
    uint32_t sta1 = 0;
    uint32_t sta2 = 0;
    uint32_t sta3 = 0;
    uint32_t sta4 = 0;

    SystemClockConfig();      //配置时钟  
    DeviceClockAllEnable();   //打开所有外设时钟

    LEDInit();
    LightInit();

    GPIOA_SetBit(GPIO_Pin_11);   //熄灭LD4
    GPIOA_SetBit(GPIO_Pin_12);   //熄灭LD3
    GPIOA_SetBit(GPIO_Pin_13);   //熄灭LD2
    GPIOA_SetBit(GPIO_Pin_14);   //熄灭LD1

    /*使用下面#if控制，#if 1则使用IAP自编程硬件固化模块进行FLASHIAP操作；#if 0则使用IAP寄存器操作（占用SRAM资源）*/
#if 1
    FlashIAP_RegUnLock();
    FlashIAP_Enable();
    FlashIap_CloseAll_WPROT();

    sta1 = IAP_PageErase(START_ADDR);
    sta2 = IAPRead(&g_rbuf, START_ADDR, 1);
    sta3 = IAP_WordProgram(START_ADDR, data);
    sta4 = IAPRead(&g_rbuf, START_ADDR, 1);

    FlashIAP_RegLock();
    FlashIAP_Disable();
    FlashIap_OpenAll_WPROT();
#else
    sta1 = FlashIap_ErasePage(PAGE_ADDR);                  //IAP页擦除
    sta2 = Flash_Read(&g_rbuf, START_ADDR, 1);             //读出4个字节数据

    sta3 = FlashIap_WriteWord(0, PAGE_ADDR, data);         //写入4个字节数据
    sta4 = Flash_Read(&g_rbuf, START_ADDR, 1);             //读出4个字节数据
#endif
    while(1)
    {
        if(g_rbuf == 0x12345678
            && sta1 == SUCCESS
            && sta2 == SUCCESS
            && sta3 == SUCCESS
            && sta4 == SUCCESS)
        {
            GPIOA_ResetBit(GPIO_Pin_14);
        }
        else
        {
            GPIOA_ResetBit(GPIO_Pin_11);
        }
    }
}

