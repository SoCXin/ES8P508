/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  led.h
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/25
*描  述:  LED模块程序头文件
*备  注:  适用于HRSDK-GDB-ES8P508x V1.1
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#ifndef __LED_H__
#define __LED_H__

#include <ES8P508x.h>
#include "lib_config.h"

void LEDInit(void);
void LEDDisplayData(uint8_t com, uint8_t dat);
void LEDDisplaySeg(uint8_t seg);
void DispHextoBcd(uint32_t hex_data, uint8_t *bcd_data);

#endif
