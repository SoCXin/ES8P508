/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  main.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/24
*描  述:  CRC演示程序
          给定数据，计算CRC值，与目标值进行对比
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"
#include "lib_crc.h"


int test_0(void)
{	
	uint8_t in_data[6] = {0x11,0x22,0x33,0x44,0x55,0x66};
	uint32_t out_data =0;
	CRC_CONValueStruType x;
	uint32_t type;
	x.xorout = CRC_XOROUT_NORMAL;                //数据输出不取反
	x.refout = CRC_REFOUT_REVERSE;               //数据输出倒序
	x.refin = CRC_REFIN_REVERSE;                 //数据输入倒序
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





