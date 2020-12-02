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
    SCU->WAKEUPTIME.Word = 0x00040000;        //��˯�¹ر�HRC��PLL��XTAL�Լ�CLKFLT
    SCU_RegLock();

    __disable_irq(); //�ر�IRQ���ж�
    DeviceClockAllEnable();

    GPIO->PAINEB.Word = 0XFFFFFFFF; //����ر�
    GPIO->PBINEB.Word = 0XFFFFFFFF;
    GPIO->PADIR.Word = 0X00000000;  //�����
    GPIO->PBDIR.Word = 0X00000000;
    GPIO->PADATA.Word = 0X00004000;  //PA6����߹ر�LED1
    GPIO->PBDATA.Word = 0X00000080;  //PB7����������
 

    KINTInit();                             //��ʼ��KINT

    SCU->PCLKEN0.Word = 0x00000003;         //�ر���������ʱ�ӣ�scu�޷��رգ�ͬʱ����GPIOʱ�ӹ��ⲿ�жϻ���
    SCU->PCLKEN1.Word = 0x00000000;

    SCU_RegUnLock();
    SCU_LVDVS_3V9();    //LVD���ѵ�ѹ3.9V
    SCU_LVDIFS_Fall(); //LVD��ѹ���߼��
    SCU_LVDFLT_Enable(); //LVD�˲�ʹ��
    SCU_LVD_Enable(); //LVD�ж�ʹ��
    SCU->WAKEUPTIME.MOSC_EN = 0; //��˯����ʱ���Զ��ر�
    SCU->WAKEUPTIME.WAKEUPTIME = 20; //����ʱ�䲻��С��40us 
    SCU_RegLock();  

    if(1 == mode)
    {
      SCB_SystemLPConfig(SCB_LP_SleepDeep, ENABLE);   //����Ϊ���˯��ģʽ
    }
    NVIC_EnableIRQ(LVD_IRQn);  //ʹ��LVD����Դ
    NVIC_EnableIRQ(KINT_IRQn); //ʹ�ܰ�������
    NVIC_EnableIRQ(IWDT_IRQn);  //ʹ��WDT����Դ
 
    while (1) //������ѭ��
    {
      
    NVIC->ICPR[0] = 0XFFFFFFFF; //��NVIC�����ʶ
    __NOP();
    __NOP();
    __WFI();
    __NOP(); 
    __NOP();

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
    if(PINT_GetITStatus(PINT_IT_PINT4) != RESET)   //KINT����
      {

        GPIOA_ToggleBit(GPIO_Pin_23);  //PA23��ת
        for(i=0; i<165350; i++);
        GPIOA_ToggleBit(GPIO_Pin_23);  //PA23��ת
        for(i=0; i<165350; i++);
        GPIOA_ToggleBit(GPIO_Pin_23);  //PA23��ת
        for(i=0; i<165350; i++);
        GPIOA_ToggleBit(GPIO_Pin_23);  //PA23��ת
        for(i=0; i<165350; i++);
        GPIOA_ToggleBit(GPIO_Pin_23);  //PA23��ת
        for(i=0; i<165350; i++);
        GPIOA_ToggleBit(GPIO_Pin_23);  //PA23��ת
        for(i=0; i<165350; i++);
        GPIOA_ToggleBit(GPIO_Pin_23);  //PA23��ת
        for(i=0; i<165350; i++);
        GPIOA_ToggleBit(GPIO_Pin_23);  //PA23��ת
        PINT_ClearITPendingBit(PINT_IT_PINT4);
      }

    }
}
