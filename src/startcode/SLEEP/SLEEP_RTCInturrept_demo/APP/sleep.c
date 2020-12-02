/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  sleep.c
*��  ��:  
*��  ��:  V1.00
*��  ��:  2018/05/3
*��  ��:  
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "sleep.h"
#include "key.h"

/*********************************************************
������: void Sleep(uchar mode)
��  ��: �������ģʽ�ӳ���
����ֵ: mode - IDLEģʽ 
���ֵ: ��
����ֵ: �� 
**********************************************************/
void Sleep(uint8_t mode)
{
    uint32_t i;
    SCU_RegUnLock();
    //SCU->WAKEUPTIME.Word = 0x00040000;        //��˯�¹ر�HRC��PLL��XTAL�Լ�CLKFLT
    SCU_RegLock();
    
    __disable_irq(); //�ر�IRQ���ж�
    IWDT_Clear();  //�幷
    DeviceClockAllEnable();
    SCU_OpenXTAL();  //ʹ���ⲿ����
    GPIO->PAINEB.Word = 0XFFFFFFFF; //����ر�
    GPIO->PBINEB.Word = 0XFFFFFFFF;
    GPIO->PADIR.Word = 0X00000000;  //�����
    GPIO->PBDIR.Word = 0X00000000;
    GPIO->PADATA.Word = 0XFFFFFFFF;  //PAȫ�����
    GPIO->PBDATA.Word = 0XFFFFFFFF;  //PBȫ�����

    KINTInit();                             //��ʼ��KINT
    
    SCU_RegUnLock();
    SCU_LVDVS_3V9();    //LVD���ѵ�ѹ3.9V
    SCU_LVDIFS_Fall(); //LVD��ѹ���߼��
    SCU_LVDFLT_Enable(); //LVD�˲�ʹ��
    SCU_LVD_Enable(); //LVD�ж�ʹ��
    SCU->SCLKEN0.CLKFLT_BY = 0x55;//CLKFLT��·��CLKFLTΪϵͳʱ���˲���
    SCU->SCLKEN1.PLL_EN = 0;//PLL��Ƶ������ֹ
    SCU->WAKEUPTIME.Word = 0x000173FF; 
    SCU->WAKEUPTIME.CLKFLT_EN =0x0;
    SCU_RegLock();  
      
    RTC_Init(RTC_LOSC,RTC_HOUR24);//ʵʱʱ�ӳ�ʼ��
    RTC_WriteSecond(30);
    RTC_InterruptEnable(RTC_Interrupt_Source_Second);//ʹ��ʵʱʱ�ӵ����ж�

    IWDT_RegUnLock();//WDT�ر�д����
    IWDT_ITEnable(); //IEʹ��
    
    if(1 == mode)
    {
        SCB_SystemLPConfig(SCB_LP_SleepDeep, ENABLE);   //����Ϊ���˯��ģʽ
    }
    
    NVIC_EnableIRQ(RTC_IRQn);  //ʹ���뻽��Դ
    NVIC_EnableIRQ(LVD_IRQn);  //ʹ��LVD����Դ
    NVIC_EnableIRQ(KINT_IRQn); //ʹ�ܰ�������
    NVIC_EnableIRQ(IWDT_IRQn);  //ʹ��WDT����Դ
    RTC->WP.WP = 0x55AAAA55;   //RTC�ر�д����    
    
    while (1) //������ѭ��
    {
    SCU_RegUnLock();
    SCU->SCLKEN1.HRC_EN = 0; //HRC�ر�ϵͳʱ���Զ��л���LRC //ϵͳʱ�����ڲ���С��2us
      
    NVIC->ICPR[0] = 0XFFFFFFFF; //��NVIC�����ʶ
    __NOP();
    __NOP();
    __WFI();
    __NOP(); 
    __NOP();
    
    SCU->SCLKEN1.HRC_EN = 1;
    while(SCU->SCLKEN1.HRC_RDY == 0);       //�ȴ�ʱ�ӿ���
    SCU->SCLKEN0.CLK_SEL = SCU_SysClk_HRC;
    SCU_RegLock(); 
    
    if(SCU_GetLVDFlagStatus(SCU_LVDFlag_IF) != RESET)  //LVD����
    {
      SCU_RegUnLock();
      SCU_LVDClearIFBit();
      SCU_RegLock();
      NVIC_SystemReset();   //��λ����
    }
      
    if(IWDT_GetFlagStatus() != RESET)
    {
      IWDT_Clear();   //�幷
    }

    if (RTC_GetFlagStatus(RTC_Interrupt_Source_Second) != RESET
        && RTC_GetITStatus(RTC_Interrupt_Source_Second) != RESET)  //�뻽��
    {
      RTC->IF.Word = 1U<<0; //�����жϱ�ʶ
      GPIOA_ToggleBit(GPIO_Pin_23);  //PA23��ת
    }

    if(PINT_GetITStatus(PINT_IT_PINT4) != RESET)   //KINT����
    {      
       GPIOA_ToggleBit(GPIO_Pin_23);  //PA23��ת
       for(i=0; i<565350; i++);
       GPIOA_ToggleBit(GPIO_Pin_23);  //PA23��ת
       for(i=0; i<565350; i++);
       GPIOA_ToggleBit(GPIO_Pin_23);  //PA23��ת
       for(i=0; i<565350; i++);
       GPIOA_ToggleBit(GPIO_Pin_23);  //PA23��ת
       for(i=0; i<565350; i++);
       GPIOA_ToggleBit(GPIO_Pin_23);  //PA23��ת
       for(i=0; i<565350; i++);
       GPIOA_ToggleBit(GPIO_Pin_23);  //PA23��ת
       for(i=0; i<565350; i++);
       GPIOA_ToggleBit(GPIO_Pin_23);  //PA23��ת
       for(i=0; i<565350; i++);
       GPIOA_ToggleBit(GPIO_Pin_23);  //PA23��ת
       PINT_ClearITPendingBit(PINT_IT_PINT4);
      }
    }
}
