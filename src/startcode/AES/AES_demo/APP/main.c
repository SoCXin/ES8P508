/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  AE
*��  ��:  V1.00
*��  ��:  2017/06/24
*��  ��:  AES��ʾ����
          д����Կkey������data����ü�������res0�ͽ�������res1
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
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


    /* ���� */
    x.MODE = AES_MODE_ENCRYPT;
    AES_Init(&x);

    AES_WriteKey(key);
    AES_WriteData(data);
    AES_Enable();

    while (AES_GetDoneStatus() == AES_DONE_NO);

    AES_ReadData(res0);

    /* ���� */
    x.MODE = AES_MODE_DECRYPT;
    AES_Init(&x);
    AES_WriteKey(key);
    AES_WriteData(res0);
    AES_Enable();

    while (AES_GetDoneStatus() == AES_DONE_NO);

    AES_ReadData(res1);

    while (1);
}





