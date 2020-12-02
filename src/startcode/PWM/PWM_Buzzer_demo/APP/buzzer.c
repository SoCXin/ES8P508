/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*�ļ���:  buzzer.c
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/26
*��  ��:  ������ģ�����
*��  ע:  ������HRSDK-GDB-ES8P508x V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "buzzer.h"

/* ����Ƶ�ʱ����ڣ� */
const uint16_t BuzzerTab[]=
{    
    00,     //Null
    3816,//�������ף�
    3540,
    3039,
    2865,
    2551,
    2272,
    2024,
    00,     //Null
    00,     //Null
    00,     //Null
    1912,//�������ף�
    1730,
    1517,
    1432,
    1276,
    1136,
    1012,
    00,     //Null
    00,     //Null
    00,     //Null
    956, //�������ף�
    851,
    758,
    715,
    637,
    568,
    506,
    00,     //Null
    00,     //Null
    00,     //Null
    769, //����һ�����ף�
    684,
    615,
    577,
    513,
    461,
    410,
    384,
};

/*********************************************************
������: void Buzzer_Init(void)
��  ��: ��������ʼ��
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void Buzzer_Init(void)
{
    GPIO_InitStruType x;

    //BUZ2  PA23
    x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_0;
    x.GPIO_Direction = GPIO_Dir_Out;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
    x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOA,GPIO_Pin_23,&x);

    //PWM   PB9
    x.GPIO_Signal = GPIO_Pin_Signal_Digital;
    x.GPIO_Func = GPIO_Func_3;
    x.GPIO_Direction = GPIO_Dir_Out;
    x.GPIO_PUEN = GPIO_PUE_Input_Disable;
    x.GPIO_PDEN = GPIO_PDE_Input_Disable;
    x.GPIO_OD = GPIO_ODE_Output_Disable;
	x.GPIO_DS = GPIO_DS_Output_Normal;
    GPIO_Init(GPIOB,GPIO_Pin_9,&x);

    User_T16N2_PWMInit();           //PWM��ʼ��
    BUZ_OFF;                        //�رշ�������Դ
}

/*********************************************************
������: void PlayMusic(const uint8_t *sheet)
��  ��: ��������
����ֵ: ��������
���ֵ: ��
����ֵ: �� 
**********************************************************/
void PlayMusic(const uint8_t *sheet)
{
    uint16_t tone,length;
    while (1)
    {
        if (*sheet == 0xFF)                 //������
        {
            return;
        }
        else if (*sheet == 0)               //������β����
        {
            BUZ_OFF;                        //BUZ1�ر�
            sheet++;
            length = *sheet;                //��ȡʱ��
            Delay10ms(length);              //��ʱ����λ10ms
            sheet++;
        }
        else                                //��������
        {
            BUZ_ON;                         //BUZ1����
            tone = *sheet;
            PWMOutput(BuzzerTab[tone]);    //���PWMƵ�ʣ�ռ�ձ�50%
            sheet++;
            length = *sheet;                //��ȡʱ��
            Delay10ms(length);              //��ʱ����λ10ms
            sheet++;
        }
    }
}

/*********************************************************
������: void PlayTone(void)
��  ��: ����tone
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void PlayTone(void)
{
    uint8_t i;

    BUZ_ON;                                //BUZ1����
    for(i=1; i<=7; i++)
    {
        PWMOutput(BuzzerTab[i]);    
        Delay10ms(100);
    }
    BUZ_OFF;                               //BUZ1�ر�
    Delay10ms(50);

    BUZ_ON;                                //BUZ1����
    for(i=11;i<=17;i++)
    {
        PWMOutput(BuzzerTab[i]);    
        Delay10ms(100);
    }
    BUZ_OFF;                               //BUZ1�ر�
    Delay10ms(50);

    BUZ_ON;                                //BUZ1����
    for(i=21;i<=27;i++)
    {
        PWMOutput(BuzzerTab[i]);    
        Delay10ms(100);
    }
    BUZ_OFF;                               //BUZ1�ر�
    Delay10ms(50);

    BUZ_ON;                                //BUZ1����
    for(i=31;i<=38;i++)
    {
        PWMOutput(BuzzerTab[i]);    
        Delay10ms(100);
    }
    BUZ_OFF;                               //BUZ1�ر�
    Delay10ms(50);
}

/*********************************************************
������: void Delay10ms(uint16_t temp)
��  ��: 10ms��ʱ
����ֵ: Ҫ��ʱ10ms�ĸ���
���ֵ: ��
����ֵ: �� 
**********************************************************/
void Delay10ms(uint16_t temp)
{
    uint16_t i;
    for(i=0; i<temp; i++)
        Delay100us(100);
}
