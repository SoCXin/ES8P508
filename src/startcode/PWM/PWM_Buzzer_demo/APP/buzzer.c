/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
*文件名:  buzzer.c
*作  者:  Liut
*版  本:  V1.00
*日  期:  2017/06/26
*描  述:  蜂鸣器模块程序
*备  注:  适用于HRSDK-GDB-ES8P508x V1.0
          本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
**********************************************************/
#include "buzzer.h"

/* 音符频率表（周期） */
const uint16_t BuzzerTab[]=
{    
    00,     //Null
    3816,//（低音阶）
    3540,
    3039,
    2865,
    2551,
    2272,
    2024,
    00,     //Null
    00,     //Null
    00,     //Null
    1912,//（中音阶）
    1730,
    1517,
    1432,
    1276,
    1136,
    1012,
    00,     //Null
    00,     //Null
    00,     //Null
    956, //（高音阶）
    851,
    758,
    715,
    637,
    568,
    506,
    00,     //Null
    00,     //Null
    00,     //Null
    769, //（另一套音阶）
    684,
    615,
    577,
    513,
    461,
    410,
    384,
};

/*********************************************************
函数名: void Buzzer_Init(void)
描  述: 蜂鸣器初始化
输入值: 无
输出值: 无
返回值: 无 
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

    User_T16N2_PWMInit();           //PWM初始化
    BUZ_OFF;                        //关闭蜂鸣器电源
}

/*********************************************************
函数名: void PlayMusic(const uint8_t *sheet)
描  述: 解码音乐
输入值: 乐曲曲谱
输出值: 无
返回值: 无 
**********************************************************/
void PlayMusic(const uint8_t *sheet)
{
    uint16_t tone,length;
    while (1)
    {
        if (*sheet == 0xFF)                 //结束符
        {
            return;
        }
        else if (*sheet == 0)               //拖音（尾音）
        {
            BUZ_OFF;                        //BUZ1关闭
            sheet++;
            length = *sheet;                //读取时长
            Delay10ms(length);              //延时，单位10ms
            sheet++;
        }
        else                                //音符数据
        {
            BUZ_ON;                         //BUZ1开启
            tone = *sheet;
            PWMOutput(BuzzerTab[tone]);    //输出PWM频率，占空比50%
            sheet++;
            length = *sheet;                //读取时长
            Delay10ms(length);              //延时，单位10ms
            sheet++;
        }
    }
}

/*********************************************************
函数名: void PlayTone(void)
描  述: 播放tone
输入值: 无
输出值: 无
返回值: 无 
**********************************************************/
void PlayTone(void)
{
    uint8_t i;

    BUZ_ON;                                //BUZ1开启
    for(i=1; i<=7; i++)
    {
        PWMOutput(BuzzerTab[i]);    
        Delay10ms(100);
    }
    BUZ_OFF;                               //BUZ1关闭
    Delay10ms(50);

    BUZ_ON;                                //BUZ1开启
    for(i=11;i<=17;i++)
    {
        PWMOutput(BuzzerTab[i]);    
        Delay10ms(100);
    }
    BUZ_OFF;                               //BUZ1关闭
    Delay10ms(50);

    BUZ_ON;                                //BUZ1开启
    for(i=21;i<=27;i++)
    {
        PWMOutput(BuzzerTab[i]);    
        Delay10ms(100);
    }
    BUZ_OFF;                               //BUZ1关闭
    Delay10ms(50);

    BUZ_ON;                                //BUZ1开启
    for(i=31;i<=38;i++)
    {
        PWMOutput(BuzzerTab[i]);    
        Delay10ms(100);
    }
    BUZ_OFF;                               //BUZ1关闭
    Delay10ms(50);
}

/*********************************************************
函数名: void Delay10ms(uint16_t temp)
描  述: 10ms延时
输入值: 要延时10ms的个数
输出值: 无
返回值: 无 
**********************************************************/
void Delay10ms(uint16_t temp)
{
    uint16_t i;
    for(i=0; i<temp; i++)
        Delay100us(100);
}
