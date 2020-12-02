/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/24
*��  ��:  IIC������ʾ������
          IIC�շ�����ʹ��ɨ�跽ʽ--EEPROM�ͺţ�24C01�����ʵ�ַ��Χ0x00~0x7F
          ����ѡ���ַ���д������LED��ʾ�����1�ֽڵ�ַ+1�ֽ����ݣ�
          ÿ�ε���K5����ַ+1������+1��д����ȡ����ʾ��LED�ϣ�
          ����ַ����0x0F�󣬲���ȫƬ

*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main(void)
{
    uint8_t key;
    uint8_t com;
    uint8_t i;

    SystemClockConfig();                                   //����ʱ��  
    DeviceClockAllEnable();                                //����������ʱ��

    SysTickInit();
    T16N3Init();
    LEDInit();
    KeyInit();
    IICMasterInit();

    com = 0;                                               //��ʾλ�ĳ�ʼֵcom0

    g_addr_h = 0x00;                                       //��ʼ����ַ
    g_addr_l = 0x00;
    g_addr = (g_addr_h << 4) + g_addr_l;    
    g_data_h = 0x00;                                       //��ʼ������
    g_data_l = 0x00;
    g_data = (g_data_h << 4) + g_data_l;

    g_wbuf[0] = 0x00;
    IICMasterWriteData(SLAVE_ADDR, g_addr, g_wbuf, 1);     //д��1���ֽ�EEPROM����
    Delay100us(100);
    IICMasterReadData(SLAVE_ADDR, g_addr, g_rbuf, 1);      //����1���ֽ�EEPROM����

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

            if(key == 5)
            {
                g_wbuf[0]++;
                g_addr_l += 0x01;
                if (g_addr_l > 0x0F)
                    g_addr_l = 0;
                g_addr = (g_addr_h << 4) + g_addr_l;
                IICMasterWriteData(SLAVE_ADDR, g_addr, g_wbuf, 1);                  //д��1���ֽ�EEPROM����
                Delay100us(100);
                IICMasterReadData(SLAVE_ADDR, g_addr, g_rbuf, 1);                   //����1���ֽ�EEPROM����
            }

            if(g_wbuf[0] > 0x0F)
            {
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
                g_wbuf[0] = 0;
            }
            g_data_l = g_rbuf[0] & 0x0F;        //���¶�������
            g_data_h = g_rbuf[0] >> 4;

            g_led_buf[0] = g_addr_h;           //������ʾ����
            g_led_buf[1] = g_addr_l;
            g_led_buf[2] = g_data_h;
            g_led_buf[3] = g_data_l;
        }
    }
}
