/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  led.h
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/25
*��  ��:  LEDģ�����ͷ�ļ�
*��  ע:  ������HRSDK-GDB-ES8P508x V1.1
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
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
