/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  buzzer.h
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  蜂鸣器模块程序头文件
*备  注:  适用于HRSDK-GDB-ES8P508 V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
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
