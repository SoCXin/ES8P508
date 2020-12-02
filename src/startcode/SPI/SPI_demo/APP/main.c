/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/25
*描  述:  SPI主机演示主程序
          EEPROM型号：93AA46，访问地址范围0x00~0x7F
          地址或读写操作，LED显示结果（1字节地址+1字节数据）
          地址+1（0x00-0x0F），数据+1（0x00-0x0F），写入EEPROM，然后读出数据显示到LED上，最大0x0F后擦除全片
          注：引脚连接：PA26-SCK(SPI_CLK),PA27-NSS(SPI_CS),PA25-SDI(SPI_MISO),PA24-SDO(SPI_MOSI) !!!!!!!!!!!!
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

int main(void)
{
    uint8_t com;

    SystemClockConfig();               //配置时钟  
    DeviceClockAllEnable();            //打开所有外设时钟

    SysTickInit();                     //系统滴答初始化
    T16N3Init();
    LEDInit();
    KeyInit();
    SPI_GPIO_Init();

    com = 0;                           //显示位的初始值com0

    g_addr_h = 0x00;                         //初始化地址
    g_addr_l = 0x00;
    g_addr = (g_addr_h << 4) + g_addr_l;
    g_data_h = 0x00;                         //初始化数据
    g_data_l = 0x00;
    g_data = (g_data_h << 4) + g_data_l;

    g_wbuf[0] = 0x00;
    SPIWriteData(g_addr, g_wbuf, 1);        //写入1个字节EEPROM数据
    Delay1ms(100);
    SPIReadData(g_addr, g_rbuf, 1);         //读出1个字节EEPROM数据

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

            SPIWriteData(g_addr, g_wbuf, 1);        //写入1个字节EEPROM数据
            Delay1ms(100);
            SPIReadData(g_addr, g_rbuf, 1);         //读出1个字节EEPROM数据

            if(g_wbuf[0] > 0x0F)
            {
                SPIEraseAll();                          //擦除全片
                g_addr_h = 0x00;                        //地址回零
                g_addr_l = 0x00;
                g_addr = 0x00;
                SPIReadData(g_addr, g_rbuf, 1);         //读出1个字节EEPROM数据
                g_wbuf[0] = 0;
            }
        }

        if (g_10ms_flag == 1)
        {
            g_10ms_flag = 0;

            g_data_l = g_rbuf[0] & 0x0F;                    //更新读出数据
            g_data_h = g_rbuf[0] >> 4;

            g_led_buf[0] = g_addr_h;                        //更新显示缓存
            g_led_buf[1] = g_addr_l;
            g_led_buf[2] = g_data_h;
            g_led_buf[3] = g_data_l;
        }
    }
}
