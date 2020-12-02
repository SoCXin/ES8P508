/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  buzzer.h
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  ������ģ�����ͷ�ļ�
*��  ע:  ������HRSDK-GDB-ES8P508 V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef __BUZZERX_H__
#define __BUZZERX_H__

#include "lib_config.h"
#include "systick.h"
#include "pwm.h"

#define  BUZ_OFF     GPIOA_ResetBit(GPIO_Pin_23)
#define  BUZ_ON      GPIOA_SetBit(GPIO_Pin_23)

void Buzzer_Init(void);
void Delay10ms(uint16_t temp);
void PlayMusic(const uint8_t *sheet);
void PlayTone(void);

#endif
