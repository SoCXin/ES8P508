/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  AE
*版  本:  V1.00
*日  期:  2017/06/24
*描  述:  AES演示程序
          写入密钥key和数据data，获得加密密文res0和解密明文res1
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main()
{
    AES_InitStruType x;
    uint32_t key[4] = {0x2b7e1516, 0x28aed2a6, 0xabf71588, 0x09cf4f3c};
    uint32_t data[4] = {0x3243F6A8, 0x885A308D, 0x313198A2, 0xE0370734};

    uint32_t res0[4] = {0};
    uint32_t res1[4] = {0};

    SystemClockConfig();
    DeviceClockAllEnable();


    /* 加密 */
    x.MODE = AES_MODE_ENCRYPT;
    AES_Init(&x);

    AES_WriteKey(key);
    AES_WriteData(data);
    AES_Enable();

    while (AES_GetDoneStatus() == AES_DONE_NO);

    AES_ReadData(res0);

    /* 解密 */
    x.MODE = AES_MODE_DECRYPT;
    AES_Init(&x);
    AES_WriteKey(key);
    AES_WriteData(res0);
    AES_Enable();

    while (AES_GetDoneStatus() == AES_DONE_NO);

    AES_ReadData(res1);

    while (1);
}





