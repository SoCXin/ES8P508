/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  led.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/25
*描  述:  LED模块程序
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "led.h"

const uint8_t LED7Code[] =
{
    0x7E,     // 0
    0x0C,     // 1
    0xB6,     // 2
    0x9E,     // 3
    0xCC,     // 4
    0xDA,     // 5
    0xFA,     // 6
    0x0E,     // 7
    0xFE,     // 8
    0xDE,     // 9
    0xEE,     // A
    0xF8,     // B
    0x72,     // C
    0xBC,     // D
    0xF2,     // E
    0xE2,     // F
    0x00     // 16=blank
};

/*********************************************************
函数名: void LEDInit(void)
描  述: LED数码管初始化
输入值: 无
输出值: 无
返回值: 无
**********************************************************/
void LEDInit(void)
{
    GPIO_InitStruType x;

    x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_Out;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;

    GPIO_Init(GPIOA, GPIO_Pin_4, &x);   //LED SEG0~SEG7 PA4 PA3 PA2 PA1 PA0 PB13 PB12 PB11 ,DIG0~DIG3 PA 10 9 6 5
    GPIO_Init(GPIOA, GPIO_Pin_3, &x);
    GPIO_Init(GPIOA, GPIO_Pin_2, &x);
    GPIO_Init(GPIOA, GPIO_Pin_1, &x);
    GPIO_Init(GPIOA, GPIO_Pin_0, &x);
    GPIO_Init(GPIOB, GPIO_Pin_13, &x);
    GPIO_Init(GPIOB, GPIO_Pin_12, &x);
    GPIO_Init(GPIOB, GPIO_Pin_11, &x);

    GPIO_Init(GPIOA, GPIO_Pin_10, &x);
    GPIO_Init(GPIOA, GPIO_Pin_9, &x);
    GPIO_Init(GPIOA, GPIO_Pin_6, &x);
    GPIO_Init(GPIOA, GPIO_Pin_5, &x);
}

/*********************************************************
函数名: void LEDDisplayData(uint8_t com, uint8_t dat)
描  述: LED显示数据
输入值: 选择位数，要显示的数据
输出值: 无
返回值: 无
**********************************************************/
void LEDDisplayData(uint8_t com, uint8_t dat)
{
    uint8_t seg;

    GPIOA_SetBit(GPIO_Pin_10);
    GPIOA_SetBit(GPIO_Pin_9);
    GPIOA_SetBit(GPIO_Pin_6);
    GPIOA_SetBit(GPIO_Pin_5);

    seg = LED7Code[dat];
    LEDDisplaySeg(seg);

    switch (com)
    {
        case 0:
            GPIOA_ResetBit(GPIO_Pin_10);
            break;

        case 1:
            GPIOA_ResetBit(GPIO_Pin_9);
            break;

        case 2:
            GPIOA_ResetBit(GPIO_Pin_6);
            break;

        case 3:
            GPIOA_ResetBit(GPIO_Pin_5);
            break;
    }
}

/*********************************************************
函数名: void LEDDisplaySeg(uint8_t seg)
描  述: LED显示SEG
输入值: seg
输出值: 无
返回值: 无
**********************************************************/
void LEDDisplaySeg(uint8_t seg)
{
    if (seg & 0x01)                     //SEGH
        GPIOB_SetBit(GPIO_Pin_13);
    else
        GPIOB_ResetBit(GPIO_Pin_13);

    if (seg & 0x02)                     //SEGA
        GPIOA_SetBit(GPIO_Pin_4);
    else
        GPIOA_ResetBit(GPIO_Pin_4);

    if (seg & 0x04)                     //SEGB
        GPIOA_SetBit(GPIO_Pin_2);
    else
        GPIOA_ResetBit(GPIO_Pin_2);

    if (seg & 0x08)                     //SEGC
        GPIOA_SetBit(GPIO_Pin_0);
    else
        GPIOA_ResetBit(GPIO_Pin_0);

    if (seg & 0x10)                     //SEGD
        GPIOB_SetBit(GPIO_Pin_12);
    else
        GPIOB_ResetBit(GPIO_Pin_12);

    if (seg & 0x20)                     //SEGE
        GPIOB_SetBit(GPIO_Pin_11);
    else
        GPIOB_ResetBit(GPIO_Pin_11);

    if (seg & 0x40)                     //SEGF
        GPIOA_SetBit(GPIO_Pin_3);
    else
        GPIOA_ResetBit(GPIO_Pin_3);

    if (seg & 0x80)                     //SEGG
        GPIOA_SetBit(GPIO_Pin_1);
    else
        GPIOA_ResetBit(GPIO_Pin_1);
}

/*********************************************************
函数名: void DispHextoBcd(uint32_t hex_data, uint8_t *bcd_data)
描  述: 十六进制转BCD
输入值: 十六进制数据
输出值: bcd码
返回值: 无
**********************************************************/
void DispHextoBcd(uint32_t hex_data, uint8_t *bcd_data)
{
    uint32_t hex_temp;

    hex_temp = hex_data;
    *(bcd_data + 0) = 0;
    *(bcd_data + 1) = 0;
    *(bcd_data + 2) = 0;
    *(bcd_data + 3) = 0;

    while (hex_temp >= 1000)
    {
        hex_temp -= 1000;
        *(bcd_data + 0) += 1;
    }

    while (hex_temp >= 100)
    {
        hex_temp -= 100;
        *(bcd_data + 1) += 1;
    }

    while (hex_temp >= 10)
    {
        hex_temp -= 10;
        *(bcd_data + 2) += 1;
    }

    *(bcd_data + 3) = hex_temp;
}
