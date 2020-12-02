/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/25
*��  ��:  SPI������ʾ������
          EEPROM�ͺţ�93AA46�����ʵ�ַ��Χ0x00~0x7F
          ��ַ���д������LED��ʾ�����1�ֽڵ�ַ+1�ֽ����ݣ�
          ��ַ+1��0x00-0x0F��������+1��0x00-0x0F����д��EEPROM��Ȼ�����������ʾ��LED�ϣ����0x0F�����ȫƬ
          ע���������ӣ�PA26-SCK(SPI_CLK),PA27-NSS(SPI_CS),PA25-SDI(SPI_MISO),PA24-SDO(SPI_MOSI) !!!!!!!!!!!!
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"

int main(void)
{
    uint8_t com;

    SystemClockConfig();               //����ʱ��  
    DeviceClockAllEnable();            //����������ʱ��

    SysTickInit();                     //ϵͳ�δ��ʼ��
    T16N3Init();
    LEDInit();
    KeyInit();
    SPI_GPIO_Init();

    com = 0;                           //��ʾλ�ĳ�ʼֵcom0

    g_addr_h = 0x00;                         //��ʼ����ַ
    g_addr_l = 0x00;
    g_addr = (g_addr_h << 4) + g_addr_l;
    g_data_h = 0x00;                         //��ʼ������
    g_data_l = 0x00;
    g_data = (g_data_h << 4) + g_data_l;

    g_wbuf[0] = 0x00;
    SPIWriteData(g_addr, g_wbuf, 1);        //д��1���ֽ�EEPROM����
    Delay1ms(100);
    SPIReadData(g_addr, g_rbuf, 1);         //����1���ֽ�EEPROM����

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

        if(g_1s_flag == 1)
        {
            g_1s_flag = 0;

            g_wbuf[0]++;
            g_addr_l += 0x01;
            if (g_addr_l > 0x0F)
                g_addr_l = 0;
            g_addr = (g_addr_h << 4) + g_addr_l;

            SPIWriteData(g_addr, g_wbuf, 1);        //д��1���ֽ�EEPROM����
            Delay1ms(100);
            SPIReadData(g_addr, g_rbuf, 1);         //����1���ֽ�EEPROM����

            if(g_wbuf[0] > 0x0F)
            {
                SPIEraseAll();                          //����ȫƬ
                g_addr_h = 0x00;                        //��ַ����
                g_addr_l = 0x00;
                g_addr = 0x00;
                SPIReadData(g_addr, g_rbuf, 1);         //����1���ֽ�EEPROM����
                g_wbuf[0] = 0;
            }
        }

        if (g_10ms_flag == 1)
        {
            g_10ms_flag = 0;

            g_data_l = g_rbuf[0] & 0x0F;                    //���¶�������
            g_data_h = g_rbuf[0] >> 4;

            g_led_buf[0] = g_addr_h;                        //������ʾ����
            g_led_buf[1] = g_addr_l;
            g_led_buf[2] = g_data_h;
            g_led_buf[3] = g_data_l;
        }
    }
}
