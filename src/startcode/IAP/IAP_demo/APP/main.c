/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/25
*��  ��:  FLASH IAP��ʾ������ 
            FLASH��0x7Cҳд����0x12345678
            ��ȡ�ĵ�ַ�����Ƿ�д�룬д��ɹ����LD1��ʧ�ܵ��LD4
*��  ע:  ������HRSDK-GDB-ES8P508xоƬ
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
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

    SystemClockConfig();      //����ʱ��  
    DeviceClockAllEnable();   //����������ʱ��

    LEDInit();
    LightInit();

    GPIOA_SetBit(GPIO_Pin_11);   //Ϩ��LD4
    GPIOA_SetBit(GPIO_Pin_12);   //Ϩ��LD3
    GPIOA_SetBit(GPIO_Pin_13);   //Ϩ��LD2
    GPIOA_SetBit(GPIO_Pin_14);   //Ϩ��LD1

    /*ʹ������#if���ƣ�#if 1��ʹ��IAP�Ա��Ӳ���̻�ģ�����FLASHIAP������#if 0��ʹ��IAP�Ĵ���������ռ��SRAM��Դ��*/
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
    sta1 = FlashIap_ErasePage(PAGE_ADDR);                  //IAPҳ����
    sta2 = Flash_Read(&g_rbuf, START_ADDR, 1);             //����4���ֽ�����

    sta3 = FlashIap_WriteWord(0, PAGE_ADDR, data);         //д��4���ֽ�����
    sta4 = Flash_Read(&g_rbuf, START_ADDR, 1);             //����4���ֽ�����
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

