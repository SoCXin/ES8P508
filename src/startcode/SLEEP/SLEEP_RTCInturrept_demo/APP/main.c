/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  main.c
*作  者:  
*版  本:  V1.00
*日  期:  2018/05/3
*描  述:  sleep示例程序，单独使用子板进行试验(需要断开子板上电源指示灯的限流电阻)，
          当供电电压低于3.5V进行休眠程序，
          当供电电压高于3.9V退出休眠程序，PA23连续翻转
          休眠程序唤醒源如下：
          1.提供WDT唤醒
          2.按键唤醒(PA20接0)后PA23连续翻转7次
          3.LVD唤醒系统软复位退出休眠函数
          4.RTC秒唤醒PA23翻转一次
*备  注:  适用于HRSDK-GDB-ES8P508x V1.1
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "main.h"

uint8_t g_sleep_flag = 0;
int main(void)
{
    uint32_t i;
    GPIO_InitStruType x;
    SystemClockConfig();                //配置时钟  
    DeviceClockAllEnable();             //打开所有外设时钟
    SysTickInit();                      //系统滴答初始化

    //以下开始检测LVD电压是否满足进入低功耗状态
    SCU_RegUnLock(); //scu写保护解锁
    SCU_LVDIFS_High(); //LVD低电压检测//高电平检测
    SCU_LVDVS_3V5();   //LVD休眠电压3.5V
    SCU_LVDFLT_Enable(); //LVD滤波使能
    SCU_LVDIT_Enable(); //LVD中断使能
    SCU_LVD_Enable();   //LVD使能
    SCU->PWRC.PORRSTF = 0;   //需要检测SOFT_RSTF标识需先将PORRSTF清零//上电复位标志
    SCU_RegLock();  //scu写保护上锁

    if(SCU_GetLVDFlagStatus(SCU_LVDFlag_Out) == SET)  //LVD检测到电压低于4V
    {
   
     Sleep(1); //进入休眠函数
 
    }
 
 
    //以下开始进行主循环初始化
    SCU_RegUnLock();
    SCU_LVDIFS_Rise(); //LVD电压降低检测//上升沿检测
    NVIC_Init(NVIC_LVD_IRQn,NVIC_Priority_0,ENABLE);  //LVD中断设置//中断优先级设为最高
    SCU_OpenXTAL();  //使能外部晶体
    SCU_RegLock();
 
   
   
    x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_Out;  
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS= GPIO_DS_Output_Normal;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    GPIO_Init(GPIOA,GPIO_Pin_23,&x); //PA23配置为输出
    GPIOA_SetBit(GPIO_Pin_6);
    GPIO_Init(GPIOA,GPIO_Pin_6,&x); //PA6配置为输出
    GPIOA_SetBit(GPIO_Pin_14);
    GPIO_Init(GPIOA,GPIO_Pin_14,&x);//PA14配置为输出

    if(SCU->PWRC.SOFT_RSTF == 0)  //程序没有经历过软复位
    {
      GPIOA_ToggleBit(GPIO_Pin_6);   //PA6翻转
      GPIOA_ResetBit(GPIO_Pin_14);   //PA14翻转，控制学习板灯暗灭
      for(i=0; i<165350; i++);
      GPIOA_ToggleBit(GPIO_Pin_6);    //PA6翻转
      GPIOA_SetBit(GPIO_Pin_14);
      for(i=0; i<165350; i++);
      GPIOA_ToggleBit(GPIO_Pin_6);    //PA6翻转
      GPIOA_ResetBit(GPIO_Pin_14);
      for(i=0; i<165350; i++);
      GPIOA_ToggleBit(GPIO_Pin_6);    //PA6翻转
      GPIOA_SetBit(GPIO_Pin_14);
      for(i=0; i<165350; i++);
      GPIOA_ToggleBit(GPIO_Pin_6);    //PA6翻转
      GPIOA_ResetBit(GPIO_Pin_14);
      for(i=0; i<165350; i++);
      GPIOA_ToggleBit(GPIO_Pin_6);    //PA6翻转
      GPIOA_SetBit(GPIO_Pin_14);
    }

	while (1)
    {
                          
      GPIOA_ToggleBit(GPIO_Pin_23);  //PA23翻转
      IWDT_Clear();   //清狗
      if(g_sleep_flag == 1)   //LVD中断检测到VDD电压低于3.6V，则复位进入休眠函数
      {
        NVIC_SystemReset();   
      }
    }
}
