/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名:  sleep.c
*作  者:  
*版  本:  V1.00
*日  期:  2018/05/3
*描  述:  
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "sleep.h"
#include "key.h"

/*********************************************************
函数名: void Sleep(uchar mode)
描  述: 进入待机模式子程序
输入值: mode - IDLE模式 
输出值: 无
返回值: 无 
**********************************************************/
void Sleep(uint8_t mode)
{
    uint32_t i;
    SCU_RegUnLock();
    SCU->WAKEUPTIME.Word = 0x00040000;        //深睡下关闭HRC、PLL、XTAL以及CLKFLT
    SCU_RegLock();

    __disable_irq(); //关闭IRQ总中断
    DeviceClockAllEnable();

    GPIO->PAINEB.Word = 0XFFFFFFFF; //输入关闭
    GPIO->PBINEB.Word = 0XFFFFFFFF;
    GPIO->PADIR.Word = 0X00000000;  //输出打开
    GPIO->PBDIR.Word = 0X00000000;
    GPIO->PADATA.Word = 0X00004000;  //PA6输出高关闭LED1
    GPIO->PBDATA.Word = 0X00000080;  //PB7有上拉电阻
 

    KINTInit();                             //初始化KINT

    SCU->PCLKEN0.Word = 0x00000003;         //关闭所有外设时钟，scu无法关闭，同时保留GPIO时钟供外部中断唤醒
    SCU->PCLKEN1.Word = 0x00000000;

    SCU_RegUnLock();
    SCU_LVDVS_3V9();    //LVD唤醒电压3.9V
    SCU_LVDIFS_Fall(); //LVD电压升高检测
    SCU_LVDFLT_Enable(); //LVD滤波使能
    SCU_LVD_Enable(); //LVD中断使能
    SCU->WAKEUPTIME.MOSC_EN = 0; //深睡眠下时钟自动关闭
    SCU->WAKEUPTIME.WAKEUPTIME = 20; //唤醒时间不可小于40us 
    SCU_RegLock();  

    if(1 == mode)
    {
      SCB_SystemLPConfig(SCB_LP_SleepDeep, ENABLE);   //配置为深度睡眠模式
    }
    NVIC_EnableIRQ(LVD_IRQn);  //使能LVD唤醒源
    NVIC_EnableIRQ(KINT_IRQn); //使能按键唤醒
    NVIC_EnableIRQ(IWDT_IRQn);  //使能WDT唤醒源
 
    while (1) //休眠主循环
    {
      
    NVIC->ICPR[0] = 0XFFFFFFFF; //清NVIC挂起标识
    __NOP();
    __NOP();
    __WFI();
    __NOP(); 
    __NOP();

    if(SCU_GetLVDFlagStatus(SCU_LVDFlag_IF) != RESET)  //LVD唤醒
    {
      SCU_RegUnLock();
      SCU_LVDClearIFBit();
      SCU_RegLock();
      NVIC_SystemReset();   //复位唤醒
    }

    if(IWDT_GetFlagStatus() != RESET)
      {
        IWDT_Clear();   //清狗
      }
    if(PINT_GetITStatus(PINT_IT_PINT4) != RESET)   //KINT唤醒
      {

        GPIOA_ToggleBit(GPIO_Pin_23);  //PA23翻转
        for(i=0; i<165350; i++);
        GPIOA_ToggleBit(GPIO_Pin_23);  //PA23翻转
        for(i=0; i<165350; i++);
        GPIOA_ToggleBit(GPIO_Pin_23);  //PA23翻转
        for(i=0; i<165350; i++);
        GPIOA_ToggleBit(GPIO_Pin_23);  //PA23翻转
        for(i=0; i<165350; i++);
        GPIOA_ToggleBit(GPIO_Pin_23);  //PA23翻转
        for(i=0; i<165350; i++);
        GPIOA_ToggleBit(GPIO_Pin_23);  //PA23翻转
        for(i=0; i<165350; i++);
        GPIOA_ToggleBit(GPIO_Pin_23);  //PA23翻转
        for(i=0; i<165350; i++);
        GPIOA_ToggleBit(GPIO_Pin_23);  //PA23翻转
        PINT_ClearITPendingBit(PINT_IT_PINT4);
      }

    }
}
