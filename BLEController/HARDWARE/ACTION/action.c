#include "action.h"
#include "sys.h" 
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  

uint8 Action_TaskID;


#define ACTION_ONOFF PBout(4)
#define ACTION_JP27 PAout(4)
#define ACTION_JP28 PAout(5)
#define ACTION_JP29 PAout(6)
#define ACTION_JP30 PAout(7)




u8 curr_onoff = 0;



//按键初始化函数
void ACTION_Init(void) //IO初始化
{
    #if 0
 	GPIO_InitTypeDef GPIO_InitStructure;

    //Action_TaskID = task_id;
	//初始化KEY0-->GPIOA.13,KEY1-->GPIOA.15  上拉输入
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);//使能PORTA,PORTE时钟

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;	  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0
    GPIO_ResetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOA.0
    GPIO_ResetBits(GPIOC,GPIO_Pin_5);

    if(curr_onoff == 0)
    {
        GPIO_ResetBits(GPIOC,GPIO_Pin_5);
    }
    else
    {
        GPIO_SetBits(GPIOC,GPIO_Pin_5);
    }

    #if 0
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    //GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5

    if(curr_onoff == 0)
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_4);
    }
    else
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_4);
    }
    #endif

    #else
		
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);//??PORTA,PORTE??

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;   
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //????
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);//???GPIOA.0
    GPIO_ResetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);

    #if 0
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //????
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);//???GPIOA.0
    GPIO_ResetBits(GPIOC,GPIO_Pin_5);
    #endif

    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //????
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;        //IO????50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);                   //?????????GPIOB.5

    if(curr_onoff == 0)
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_4);
    }
    else
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_4);
    }
    
    #endif
    
}

void ACTION_Power_On(void)
{
    printf("\r\n L:%d %s on", __LINE__, __FUNCTION__);
    ACTION_ONOFF = 1;
}

void ACTION_Power_Off(void)
{
    #if 0
    if(curr_onoff == 0)
    {
        printf("\r\n L:%d %s on", __LINE__, __FUNCTION__);
        ACTION_ONOFF = 1;
        curr_onoff = 1;
    }
    else
    {
        printf("\r\n L:%d %s off", __LINE__, __FUNCTION__);
        ACTION_ONOFF = 0;
        curr_onoff = 0;
    }
    #endif
    printf("\r\n L:%d %s off", __LINE__, __FUNCTION__);
    ACTION_ONOFF = 0;
}

void ACTION_Key1(void)
{
    ACTION_JP27 = 1;
    delay_ms(50);
    ACTION_JP27 = 0;
}
void ACTION_Key2(void)
{
    ACTION_JP28 = 1;
    delay_ms(50);
    ACTION_JP28 = 0;
}
void ACTION_Key3(void)
{
    ACTION_JP29 = 1;
    delay_ms(50);
    ACTION_JP29 = 0;
}
void ACTION_Key4(void)
{
    ACTION_JP30 = 1;
    delay_ms(50);
    ACTION_JP30 = 0;
}


