/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/24
*描  述:  IIC主机演示主程序
          IIC收发数据使用扫描方式--EEPROM型号：24C01，访问地址范围0x00~0x7F
          按键选择地址或读写操作，LED显示结果（1字节地址+1字节数据）
          每次单击K5：地址+1，数据+1，写入后读取，显示在LED上；
          当地址大于0x0F后，擦除全片

*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{
    uint8_t key;
    uint8_t com;
    uint8_t i;

    SystemClockConfig();                                   //配置时钟  
    DeviceClockAllEnable();                                //打开所有外设时钟

    SysTickInit();
    T16N3Init();
    LEDInit();
    KeyInit();
    IICMasterInit();

    com = 0;                                               //显示位的初始值com0

    g_addr_h = 0x00;                                       //初始化地址
    g_addr_l = 0x00;
    g_addr = (g_addr_h << 4) + g_addr_l;    
    g_data_h = 0x00;                                       //初始化数据
    g_data_l = 0x00;
    g_data = (g_data_h << 4) + g_data_l;

    g_wbuf[0] = 0x00;
    IICMasterWriteData(SLAVE_ADDR, g_addr, g_wbuf, 1);     //写入1个字节EEPROM数据
    Delay100us(100);
    IICMasterReadData(SLAVE_ADDR, g_addr, g_rbuf, 1);      //读出1个字节EEPROM数据

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
                IICMasterWriteData(SLAVE_ADDR, g_addr, g_wbuf, 1);                  //写入1个字节EEPROM数据
                Delay100us(100);
                IICMasterReadData(SLAVE_ADDR, g_addr, g_rbuf, 1);                   //读出1个字节EEPROM数据
            }

            if(g_wbuf[0] > 0x0F)
            {
                g_addr = 0x00;
                for (i=0; i<16; i++)                                //总共16页
                {
                    IICMasterErasePage(SLAVE_ADDR, g_addr);         //擦除128个字节EEPROM空间，写0xFF
                    Delay100us(100);
                    g_addr += 8;
                }
                g_addr_h = 0x00;                                    //地址回零
                g_addr_l = 0x00;
                g_addr = 0x00;
                IICMasterReadData(SLAVE_ADDR, g_addr, g_rbuf, 1);   //读出1个字节EEPROM数据，用于显示
                g_wbuf[0] = 0;
            }
            g_data_l = g_rbuf[0] & 0x0F;        //更新读出数据
            g_data_h = g_rbuf[0] >> 4;

            g_led_buf[0] = g_addr_h;           //更新显示缓存
            g_led_buf[1] = g_addr_l;
            g_led_buf[2] = g_data_h;
            g_led_buf[3] = g_data_l;
        }
    }
}
