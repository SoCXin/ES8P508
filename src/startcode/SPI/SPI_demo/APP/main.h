/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  main.h
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  SPI������ʾ������ͷ�ļ�
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef   __MAIN_H__
#define   __MAIN_H__

#include "lib_config.h"
#include "sysTick.h"
#include "timer.h"
#include "key.h"
#include "spi.h"
#include "led.h"

uint8_t g_wbuf[2];      //д�����ݻ���
uint8_t g_rbuf[2];      //�������ݻ���    

uint8_t g_addr;         //Ƭ�ڵ�ַ��EEPROM��                
uint8_t g_addr_h;       //Ƭ�ڵ�ַ�߰��ֽڣ���ʾλ��g_led_buf[0]��
uint8_t g_addr_l;       //Ƭ�ڵ�ַ�Ͱ��ֽڣ���ʾλ��g_led_buf[1]��

uint8_t g_data;         //��д���ݣ�EEPROM��
uint8_t g_data_h;       //��д���ݸ߰��ֽڣ���ʾλ��g_led_buf[2]��
uint8_t g_data_l;       //��д���ݵͰ��ֽڣ���ʾλ��g_led_buf[3]��

uint8_t g_led_buf[4];   //��ʾ����

uint8_t g_2ms_flag;     //2ms��־
uint8_t g_10ms_flag;    //10ms��־
uint16_t g_10ms_cnt;    //10ms����
uint32_t g_1s_cnt;    //1s����
uint32_t g_1s_flag;    //1s��־


#endif
