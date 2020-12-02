/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  main.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/24
*��  ��:  CRC��ʾ����
          �������ݣ�����CRCֵ����Ŀ��ֵ���жԱ�
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "main.h"
#include "lib_crc.h"


int test_0(void)
{	
	uint8_t in_data[6] = {0x11,0x22,0x33,0x44,0x55,0x66};
	uint32_t out_data =0;
	CRC_CONValueStruType x;
	uint32_t type;
	x.xorout = CRC_XOROUT_NORMAL;                //���������ȡ��
	x.refout = CRC_REFOUT_REVERSE;               //�����������
	x.refin = CRC_REFIN_REVERSE;                 //�������뵹��
	x.mode = CRC_MOD_CRC16;
	x.init_data_type = CRC_INIT_DATA_ALL_0;
	x.hs_type = CRC_HS_TYPE_DISABLE;
	type = CRC_getTypeValue(x);
	out_data = CRC_UserCal(in_data,6,type);
	if(out_data == 0x6d0b)
		return 1;
	else
		return 0;
}

int main()
{
	
	SystemClockConfig();
	DeviceClockAllEnable();
	
	while(test_0() == 0);
	
	while(1)
	{
		
	}
}





