/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  spi.h
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  SPI����ģ��ͷ�ļ�
*��  ע:  ������HRSDK-GDB-ES8P508x V1.1
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef __SPI_H__
#define __SPI_H__

#include "ES8P508x.h"
#include "lib_config.h"
#include "lib_spi.h"

#define Slave_Addr  0x5A

#define CS_SET GPIOA_SetBit(GPIO_Pin_27)
#define CS_RESET GPIOA_ResetBit(GPIO_Pin_27)
#define SCK_PIN GPIO_Pin_26
#define CS_PIN  GPIO_Pin_27
#define SDI_PIN GPIO_Pin_25
#define SDO_PIN GPIO_Pin_24

/* �������� */
void SPI_GPIO_Init(void);

#endif
