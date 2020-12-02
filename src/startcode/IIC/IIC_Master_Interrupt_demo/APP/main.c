/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/24
*��  ��:  IIC������ʾ������
          IIC�շ�����ʹ���жϷ�ʽ--EEPROM�ͺţ�24C01�����ʵ�ַ��Χ0x00~0x7F
          ����ѡ���ַ���д������LED��ʾ�����1�ֽڵ�ַ+1�ֽ����ݣ�
         ��1������K4����ַ�Ͱ��ֽ�+1��ͬʱ������ǰ����
         ��2������K3����ַ�߰��ֽ�+1��ͬʱ������ǰ����
         ��3������K2��д������=��ǰ��ַ
         ��4������K1��д������=0x00
         ��5������K5��ȫƬ����
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"
int main(void)
{
    uint8_t key;
    uint8_t com;
    uint8_t i;

    SystemClockConfig();                                                //����ʱ��  
    DeviceClockAllEnable();                                             //����������ʱ��

    SysTickInit();
    T16N3Init();
    LEDInit();
    KeyInit();
    IICMasterInit();

    memset(g_txbuf, 0, sizeof(g_txbuf));
    memset(g_rxbuf, 0, sizeof(g_rxbuf));

    g_tx_length = 0;                    //�������ݳ���
    g_tx_count = 0;                     //�����ֽڼ���
    g_rx_length = 0;                    //�������ݳ���
    g_rx_count = 0;                     //�����ֽڼ���

    com = 0;                                                            //��ʾλ�ĳ�ʼֵcom0

    g_addr_h = 0x00;                                                    //��ʼ����ַ
    g_addr_l = 0x00;
    g_addr = (g_addr_h << 4) + g_addr_l;
    g_data_h = 0x00;                                                    //��ʼ������
    g_data_l = 0x00;
    g_data = (g_data_h << 4) + g_data_l;

    IICMasterReadData(SLAVE_ADDR, g_addr, g_rbuf, 1);                   //����1���ֽ�EEPROM����

    while (1)
    {
        if (g_2ms_flag == 1)
        {
            g_2ms_flag = 0;
            LEDDisplayData(com, g_led_buf[com]);
            com++;
            if (com > 3)
                com = 0;
        }

        if (g_10ms_flag == 1)
        {
            g_10ms_flag = 0;

            key = KeyGetValue();
            switch (key)
            {
                    case 4:                                             //K4����ַ�Ͱ��ֽ�+1��ͬʱ������ǰ����
                    g_addr_l += 0x01;
                    if (g_addr_l > 0x0F)
                        g_addr_l = 0;
                    g_addr = (g_addr_h << 4) + g_addr_l;
                    IICMasterReadData(SLAVE_ADDR, g_addr, g_rbuf, 1);   //����1���ֽ�EEPROM����
                    break;
                    case 3:                                             //K3����ַ�߰��ֽ�+1��ͬʱ������ǰ����
                    g_addr_h += 0x01;
                    if (g_addr_h > 0x07)                                //����EEPROM��ַ��Χ0x00~0x7F
                        g_addr_h = 0;
                    g_addr = (g_addr_h << 4) + g_addr_l;
                    IICMasterReadData(SLAVE_ADDR, g_addr, g_rbuf, 1);   //����1���ֽ�EEPROM����
                    break;
                case 2:                                                 //K2��д������=��ǰ��ַ
                    g_wbuf[0] = g_addr;                        
                    IICMasterWriteData(SLAVE_ADDR, g_addr, g_wbuf, 1);  //д��1���ֽ�EEPROM����
                    Delay100us(100);
                    IICMasterReadData(SLAVE_ADDR, g_addr, g_rbuf, 1);   //����1���ֽ�EEPROM����
                    break;
                case 1:                                                 //K1��д������=0x00
                    g_wbuf[0] = 0x00;    
                    IICMasterWriteData(SLAVE_ADDR, g_addr, g_wbuf, 1);  //д��1���ֽ�EEPROM����
                    Delay100us(100);
                    IICMasterReadData(SLAVE_ADDR, g_addr, g_rbuf, 1);   //����1���ֽ�EEPROM����
                    break;
                case 5:                                                 //K5��ȫƬ����
                    g_addr = 0x00;
                    for (i=0; i<16; i++)                                //�ܹ�16ҳ
                    {
                        IICMasterErasePage(SLAVE_ADDR, g_addr);         //����128���ֽ�EEPROM�ռ䣬д0xFF
                        Delay100us(100);
                        g_addr += 8;
                    }
                    g_addr_h = 0x00;                                    //��ַ����
                    g_addr_l = 0x00;
                    g_addr = 0x00;
                    IICMasterReadData(SLAVE_ADDR, g_addr, g_rbuf, 1);   //����1���ֽ�EEPROM���ݣ�������ʾ
                    break;
                default:
                    break;
            }

            g_data_l = g_rbuf[0] & 0x0F;                                //���¶�������
            g_data_h = g_rbuf[0] >> 4;

            g_led_buf[0] = g_addr_h;                                    //������ʾ����
            g_led_buf[1] = g_addr_l;
            g_led_buf[2] = g_data_h;
            g_led_buf[3] = g_data_l;
        }
    }
}

