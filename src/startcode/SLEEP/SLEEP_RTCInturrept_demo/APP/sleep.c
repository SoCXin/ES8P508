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
    //SCU->WAKEUPTIME.Word = 0x00040000;        //深睡下关闭HRC、PLL、XTAL以及CLKFLT
    SCU_RegLock();
    
    __disable_irq(); //关闭IRQ总中断
    IWDT_Clear();  //清狗
    DeviceClockAllEnable();
    SCU_OpenXTAL();  //使能外部晶体
    GPIO->PAINEB.Word = 0XFFFFFFFF; //输入关闭
    GPIO->PBINEB.Word = 0XFFFFFFFF;
    GPIO->PADIR.Word = 0X00000000;  //输出打开
    GPIO->PBDIR.Word = 0X00000000;
    GPIO->PADATA.Word = 0XFFFFFFFF;  //PA全输出高
    GPIO->PBDATA.Word = 0XFFFFFFFF;  //PB全输出高

    KINTInit();                             //初始化KINT
    
    SCU_RegUnLock();
    SCU_LVDVS_3V9();    //LVD唤醒电压3.9V
    SCU_LVDIFS_Fall(); //LVD电压升高检测
    SCU_LVDFLT_Enable(); //LVD滤波使能
    SCU_LVD_Enable(); //LVD中断使能
    SCU->SCLKEN0.CLKFLT_BY = 0x55;//CLKFLT旁路，CLKFLT为系统时钟滤波器
    SCU->SCLKEN1.PLL_EN = 0;//PLL倍频工作禁止
    SCU->WAKEUPTIME.Word = 0x000173FF; 
    SCU->WAKEUPTIME.CLKFLT_EN =0x0;
    SCU_RegLock();  
      
    RTC_Init(RTC_LOSC,RTC_HOUR24);//实时时钟初始化
    RTC_WriteSecond(30);
    RTC_InterruptEnable(RTC_Interrupt_Source_Second);//使能实时时钟的秒中断

    IWDT_RegUnLock();//WDT关闭写保护
    IWDT_ITEnable(); //IE使能
    
    if(1 == mode)
    {
        SCB_SystemLPConfig(SCB_LP_SleepDeep, ENABLE);   //配置为深度睡眠模式
    }
    
    NVIC_EnableIRQ(RTC_IRQn);  //使能秒唤醒源
    NVIC_EnableIRQ(LVD_IRQn);  //使能LVD唤醒源
    NVIC_EnableIRQ(KINT_IRQn); //使能按键唤醒
    NVIC_EnableIRQ(IWDT_IRQn);  //使能WDT唤醒源
    RTC->WP.WP = 0x55AAAA55;   //RTC关闭写保护    
    
    while (1) //休眠主循环
    {
    SCU_RegUnLock();
    SCU->SCLKEN1.HRC_EN = 0; //HRC关闭系统时钟自动切换到LRC //系统时钟周期不可小于2us
      
    NVIC->ICPR[0] = 0XFFFFFFFF; //清NVIC挂起标识
    __NOP();
    __NOP();
    __WFI();
    __NOP(); 
    __NOP();
    
    SCU->SCLKEN1.HRC_EN = 1;
    while(SCU->SCLKEN1.HRC_RDY == 0);       //等待时钟开启
    SCU->SCLKEN0.CLK_SEL = SCU_SysClk_HRC;
    SCU_RegLock(); 
    
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

    if (RTC_GetFlagStatus(RTC_Interrupt_Source_Second) != RESET
        && RTC_GetITStatus(RTC_Interrupt_Source_Second) != RESET)  //秒唤醒
    {
      RTC->IF.Word = 1U<<0; //清秒中断标识
      GPIOA_ToggleBit(GPIO_Pin_23);  //PA23翻转
    }

    if(PINT_GetITStatus(PINT_IT_PINT4) != RESET)   //KINT唤醒
    {      
       GPIOA_ToggleBit(GPIO_Pin_23);  //PA23翻转
       for(i=0; i<565350; i++);
       GPIOA_ToggleBit(GPIO_Pin_23);  //PA23翻转
       for(i=0; i<565350; i++);
       GPIOA_ToggleBit(GPIO_Pin_23);  //PA23翻转
       for(i=0; i<565350; i++);
       GPIOA_ToggleBit(GPIO_Pin_23);  //PA23翻转
       for(i=0; i<565350; i++);
       GPIOA_ToggleBit(GPIO_Pin_23);  //PA23翻转
       for(i=0; i<565350; i++);
       GPIOA_ToggleBit(GPIO_Pin_23);  //PA23翻转
       for(i=0; i<565350; i++);
       GPIOA_ToggleBit(GPIO_Pin_23);  //PA23翻转
       for(i=0; i<565350; i++);
       GPIOA_ToggleBit(GPIO_Pin_23);  //PA23翻转
       PINT_ClearITPendingBit(PINT_IT_PINT4);
      }
    }
}
