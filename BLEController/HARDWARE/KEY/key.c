#include "key.h"
#include "sys.h" 
#include "delay.h"
#include "action.h"
#include "simple_main.h"
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


uint8 KEY_TaskID;
BOOL b_timer_start = FALSE;
uint8 g_key_value = 0;

void KEY_timer_handler(void) 
{
    switch(g_key_value)
    {
        case 6:
            osal_set_event(KEY_TaskID, KEY6_EVT);
            break;
        case 7:
            osal_set_event(KEY_TaskID, KEY7_EVT);
            break;
        case 8:
            osal_set_event(KEY_TaskID, KEY8_EVT);
            break;
        case 9:
            osal_set_event(KEY_TaskID, KEY9_EVT);
            break;
        case 10:
            osal_set_event(KEY_TaskID, KEY10_EVT);
            break;
        case 11:
            osal_set_event(KEY_TaskID, KEY11_EVT);
            break;
    }
}

//按键初始化函数
void KEY_Init(uint8 task_id) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;

    KEY_TaskID = task_id;
	//3?ê??ˉKEY0-->GPIOA.13,KEY1-->GPIOA.15  é?à-ê?è?
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);//??PORTA,PORTE??
    //GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_9|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//PE2~4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //???????
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//???GPIOE2,3,4
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10|GPIO_Pin_11;	 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //????
    GPIO_Init(GPIOB, &GPIO_InitStructure);	

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PA0?????,????	  
	GPIO_Init(GPIOD, &GPIO_InitStructure);//???GPIOA.0

    #if 0
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);//??PORTA,PORTE??

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;	  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //????
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);//???GPIOA.0
    GPIO_ResetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //????
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);//???GPIOA.0
    GPIO_ResetBits(GPIOC,GPIO_Pin_5);


        //GPIO_ResetBits(GPIOC,GPIO_Pin_5);

        GPIO_SetBits(GPIOC,GPIO_Pin_5);
  
	
		
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //????
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO????50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);					 //?????????GPIOB.5

    GPIO_ResetBits(GPIOB,GPIO_Pin_4);
    #endif

}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，KEY3按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>KEY3!!

u8 KEY_Scan1(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	u8 key_val = 0;
	if(mode)key_up=1;  //支持连按		

	if(key_up&&(KEY02==0||KEY03==0||KEY04==0||KEY05==0||KEY13==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
        if(KEY02==0)
            key_val = 2;
		else if(KEY03==0)
            key_val = 3;
		else if(KEY04==0)
            key_val = 4;
		else if(KEY05==0)
            key_val = 5;
        else if(KEY13==0)
            key_val = 13;
	}else if(KEY02==1&&KEY03==1&&KEY04==1&&KEY05==1
	    &&KEY13==1)key_up=1; 	
    
    #if 1
    switch(key_val)
    {
        case 2:
            osal_set_event(KEY_TaskID, KEY2_EVT);		
            break;
        case 3:
            osal_set_event(KEY_TaskID, KEY3_EVT);
            break;
        case 4:
            osal_set_event(KEY_TaskID, KEY4_EVT);
            break;
        case 5:
            osal_set_event(KEY_TaskID, KEY5_EVT);
            break;
        case 6:
            osal_set_event(KEY_TaskID, KEY6_EVT);
            break;
        case 7:
            osal_set_event(KEY_TaskID, KEY7_EVT);
            break;
        case 8:
            osal_set_event(KEY_TaskID, KEY8_EVT);
            break;
        case 9:
            osal_set_event(KEY_TaskID, KEY9_EVT);
            break;
        case 10:
            osal_set_event(KEY_TaskID, KEY10_EVT);
            break;
        case 11:
            osal_set_event(KEY_TaskID, KEY11_EVT);
            break;
        case 13:
            //onoff
            osal_set_event(KEY_TaskID, KEY13_EVT);
            break;
    }
    #endif
    
 	return key_val;// 无按键按下
}

u8 KEY_Scan2(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	u8 key_val = 0;
	if(mode)key_up=1;  //支持连按		

	if(key_up&&(KEY06==0||KEY07==0||KEY08==0||KEY09==0||KEY10==0||KEY11==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
        if(KEY06==0)
            key_val = 6;
		else if(KEY07==0)
            key_val = 7;
		else if(KEY08==0)
            key_val = 8;
		else if(KEY09==0)
            key_val = 9;
        else if(KEY10==0)
            key_val = 10;
        else if(KEY11==0)
            key_val = 11;
	}else if(KEY02==1&&KEY03==1&&KEY04==1&&KEY05==1
	    &&KEY13==1)key_up=1; 	


    g_key_value = key_val;
    if((0 != key_val) && (!b_timer_start))
    {
        TIM2_Start(KEY_timer_handler);
        b_timer_start = TRUE;
    }
    else if((0 == key_val) && (b_timer_start))
    {
        TIM2_Stop();
        b_timer_start = FALSE;
    }
        
 	return key_val;// 无按键按下
}

u8 KEY_Scan(void)
{
    u8 key_val = 0;
    key_val = KEY_Scan1(0);
    if(0 != key_val)
    {
        return key_val;
    }
    key_val = KEY_Scan2(1);
    return key_val;
}

uint16 KEY_ProcessEvent( uint8 task_id, uint16 events)
{
    if ( events & KEY2_EVT )
    {
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        ACTION_Key4();
        return (events ^ KEY2_EVT);
    }

    if ( events & KEY3_EVT )
    {
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        ACTION_Key1();
        return (events ^ KEY3_EVT);
    }
    if ( events & KEY4_EVT )
    {
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        ACTION_Key3();
        return (events ^ KEY4_EVT);
    }

    if ( events & KEY5_EVT )
    {
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        ACTION_Key2();
        return (events ^ KEY5_EVT);
    }
    if ( events & KEY6_EVT )
    {
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        //PWM_level_up(0);
        //PWM_ValueUp(1);
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_FREQ_INC);
        return (events ^ KEY6_EVT);
    }
    if ( events & KEY7_EVT )
    {
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        //PWM_level_down(0);
        //PWM_ValueDown(1);
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_FREQ_DEC);
        return (events ^ KEY7_EVT);
    }

    if ( events & KEY8_EVT )
    {
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        //PWM_level_up(1);
        //PWM_ValueUp(2);
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_MODE_INC);
        return (events ^ KEY8_EVT);
    }

    if ( events & KEY9_EVT )
    {
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        //PWM_level_down(1);
        //PWM_ValueDown(2);
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_MODE_DEC);
        return (events ^ KEY9_EVT);
    }
    if ( events & KEY10_EVT )
    {
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        //PWM_level_up(2);
        //PWM_ValueUp(3);
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_TIME_INC);
        return (events ^ KEY10_EVT);
    }

    if ( events & KEY11_EVT )
    {
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        //PWM_level_down(2);
        //PWM_ValueDown(3);
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_TIME_DEC);
        return (events ^ KEY11_EVT);
    }
    
    if ( events & KEY13_EVT )
    {
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        //ACTION_OnOff();
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_POWER);
        return (events ^ KEY13_EVT);
    }

    return events;
}

