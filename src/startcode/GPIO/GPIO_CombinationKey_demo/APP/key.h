/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  key.h
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/25
*��  ��:  Keyģ��ͷ�ļ�
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef __KEY_H__
#define __KEY_H__

#include "lib_config.h"

void KeyInit(void);                     //Key��ʼ��
uint8_t KeyGetValue(void);              //Key��ȡ��ֵ
void KINTInit(void);

#endif
