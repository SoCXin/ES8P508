/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  iic.h
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  IIC����ģ��ͷ�ļ�
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef __IICUSER_H__
#define __IICUSER_H__

#include "lib_config.h"
#include "systick.h"

extern uint8_t g_txbuf[0xFF];          //�������ݻ���
extern uint8_t g_tx_length;            //�������ݳ���
extern uint8_t g_tx_count;             //�����ֽڼ���

extern uint8_t g_rxbuf[0xFF];          //�������ݻ���
extern uint8_t g_rx_length;            //�������ݳ���
extern uint8_t g_rx_count;             //�����ֽڼ���

void IICMasterInit(void);
uint8_t IICReadByte(uint8_t slave_addr, uint8_t memory_addr);
ErrorStatus IICWriteByte(uint8_t slave_addr, uint8_t memory_addr, uint8_t buf);
void IICMasterWriteData(uint8_t slave_addr, uint8_t memory_addr, uint8_t *buf, uint8_t n);
void IICMasterReadData(uint8_t slave_addr, uint8_t memory_addr, uint8_t *buf, uint8_t n);
ErrorStatus IICMasterErasePage(uint8_t slave_addr, uint8_t memory_addr);

#endif
