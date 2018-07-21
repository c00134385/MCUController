#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "beep.h"

uint8 Exti_TaskID;


//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//外部中断 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   
//外部中断0服务程序
void EXTIX_Init(uint8 task_id)
{
    
    
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
	
	Exti_TaskID = task_id;

    //KEY_Init();	 //	按键端口初始化

    //return;
    
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

  //GPIOE.2 中断线以及中断初始化配置   下降沿触发
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource0);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource1);
    EXTI_InitStructure.EXTI_Line=EXTI_Line1;	//KEY2
    EXTI_Init(&EXTI_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource2);
    EXTI_InitStructure.EXTI_Line=EXTI_Line2;	//KEY2
    EXTI_Init(&EXTI_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource2);
    EXTI_InitStructure.EXTI_Line=EXTI_Line2;	//KEY2
    EXTI_Init(&EXTI_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource3);
    EXTI_InitStructure.EXTI_Line=EXTI_Line3;	//KEY2
    EXTI_Init(&EXTI_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource4);
    EXTI_InitStructure.EXTI_Line=EXTI_Line4;	//KEY2
    EXTI_Init(&EXTI_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource9);
    EXTI_InitStructure.EXTI_Line=EXTI_Line9;   //KEY2
    EXTI_Init(&EXTI_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource10);
    EXTI_InitStructure.EXTI_Line=EXTI_Line10;   //KEY2
    EXTI_Init(&EXTI_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource11);
    EXTI_InitStructure.EXTI_Line=EXTI_Line11;   //KEY2
    EXTI_Init(&EXTI_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource12);
    EXTI_InitStructure.EXTI_Line=EXTI_Line12;   //KEY2
    EXTI_Init(&EXTI_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);
    EXTI_InitStructure.EXTI_Line=EXTI_Line13;	//KEY2
    EXTI_Init(&EXTI_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource14);
    EXTI_InitStructure.EXTI_Line=EXTI_Line14;	//KEY2
    EXTI_Init(&EXTI_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource15);
    EXTI_InitStructure.EXTI_Line=EXTI_Line15;	//KEY2
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键WK_UP所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;           //使能按键KEY2所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;    //抢占优先级2， 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;                   //子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                             //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键KEY1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;            //使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
    
    #if 0
 //GPIOE.3	  中断线以及中断初始化配置 下降沿触发 //KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

 //GPIOE.4	  中断线以及中断初始化配置  下降沿触发	//KEY0
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource0); 
      
    EXTI_InitStructure.EXTI_Line=EXTI_Line0;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);     //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器



  //GPIOA.0	  中断线以及中断初始化配置 上升沿触发 PA0  WK_UP
 	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 

 	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键WK_UP所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键KEY1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 #endif
}

//外部中断0服务程序 
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//消抖
	printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
    if(KEY07 == 0)
    {
        osal_set_event(Exti_TaskID, EXTI_KEY7_EVT);		 
    }
    
	EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
}

void EXTI1_IRQHandler(void)
{
	delay_ms(10);//消抖
	printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
    if(KEY09 == 0)
    {
        osal_set_event(Exti_TaskID, EXTI_KEY9_EVT);		 
    }
	EXTI_ClearITPendingBit(EXTI_Line1);  //清除LINE2上的中断标志位  
}


//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
	delay_ms(10);//消抖
	printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
    if(KEY11 == 0)
    {
        osal_set_event(Exti_TaskID, EXTI_KEY11_EVT);	 
    }

    
	EXTI_ClearITPendingBit(EXTI_Line2);  //清除LINE2上的中断标志位  
}
//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	delay_ms(10);//消抖
	printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
	if(KEY06==0)	 //按键KEY1
	{				 
		//LED1=!LED1;
	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位  
}

void EXTI4_IRQHandler(void)
{
	delay_ms(10);//消抖
	printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
    if(KEY13 == 0)
    {
        osal_set_event(Exti_TaskID, EXTI_KEY13_EVT);		 
    }

	EXTI_ClearITPendingBit(EXTI_Line4);  //清除LINE4上的中断标志位  
}

void EXTI9_5_IRQHandler (void)
{
    delay_ms(10);//消抖
    //printf("\r\n L:%d %s", __LINE__, __FUNCTION__);

    if(EXTI_GetITStatus(EXTI_Line5) != RESET)
    {
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        EXTI_ClearITPendingBit(EXTI_Line5);
    }

    if(EXTI_GetITStatus(EXTI_Line6) != RESET)
    {
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        EXTI_ClearITPendingBit(EXTI_Line6);
    }

    if(EXTI_GetITStatus(EXTI_Line7) != RESET)
    {
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        EXTI_ClearITPendingBit(EXTI_Line7);
    }

    if(EXTI_GetITStatus(EXTI_Line8) != RESET)
    {
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        EXTI_ClearITPendingBit(EXTI_Line8);
    }
   
    if(EXTI_GetITStatus(EXTI_Line9) != RESET)          
    {
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        if(KEY04 == 0)
        {
            osal_set_event(Exti_TaskID, EXTI_KEY4_EVT);	 
        }
        
        EXTI_ClearITPendingBit(EXTI_Line9);
    }
}

void EXTI15_10_IRQHandler(void)
{
    delay_ms(10);//消抖
    
    if(EXTI_GetITStatus(EXTI_Line10) != RESET)
    {
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        EXTI_ClearITPendingBit(EXTI_Line10);
    }

    if(EXTI_GetITStatus(EXTI_Line11) != RESET)
    {
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        EXTI_ClearITPendingBit(EXTI_Line11);
    }
    if(EXTI_GetITStatus(EXTI_Line12) != RESET)
    {
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        EXTI_ClearITPendingBit(EXTI_Line12);
    }
    if(EXTI_GetITStatus(EXTI_Line13) != RESET)
    {
        if(KEY06 == 0)
        {
            osal_set_event(Exti_TaskID, EXTI_KEY6_EVT);	 
        }
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        EXTI_ClearITPendingBit(EXTI_Line13);
    }
    if(EXTI_GetITStatus(EXTI_Line14) != RESET)
    {
        if(KEY08 == 0)
        {
            osal_set_event(Exti_TaskID, EXTI_KEY8_EVT);	 
        }
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        EXTI_ClearITPendingBit(EXTI_Line14);
    }
    if(EXTI_GetITStatus(EXTI_Line15) != RESET)
    {
        if(KEY10 == 0)
        {
            osal_set_event(Exti_TaskID, EXTI_KEY10_EVT);	 
        }
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        EXTI_ClearITPendingBit(EXTI_Line15);
    }
}

uint16 EXTIX_ProcessEvent( uint8 task_id, uint16 events )
{
    unsigned char bytes[32];
    u8 ledId = 0;
    
    if ( events & EXTI_KEY1_EVT )
    {
        //printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        
        ledId = 1;
        sprintf(bytes, "AT+LED%d\r\n", ledId);
        uart2_comm_write(bytes, strlen(bytes));
        return (events ^ EXTI_KEY1_EVT);
    }

    if( events & EXTI_KEY2_EVT )
    {
        //printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        ledId = 2;
        sprintf(bytes, "AT+LED%d\r\n", ledId);
        uart2_comm_write(bytes, strlen(bytes));
        return (events ^ EXTI_KEY2_EVT);
    }


    if( events & EXTI_KEY3_EVT )
    {
        //printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        ledId = 3;
        sprintf(bytes, "AT+LED%d\r\n", ledId);
        uart2_comm_write(bytes, strlen(bytes));
        return (events ^ EXTI_KEY3_EVT);
    }

    if( events & EXTI_KEY4_EVT ) 
    {
        printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        //ledId = 4;
        //sprintf(bytes, "AT+LED%d\r\n", ledId);
        //uart2_comm_write(bytes, strlen(bytes));
        return (events ^ EXTI_KEY4_EVT);
    }

    if( events & EXTI_KEY5_EVT )
    {
        //printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        ledId = 5;
        sprintf(bytes, "AT+LED%d\r\n", ledId);
        uart2_comm_write(bytes, strlen(bytes));
        return (events ^ EXTI_KEY5_EVT);
    }

    if( events & EXTI_KEY6_EVT )
    {
        //printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        //ledId = 6;
        //sprintf(bytes, "AT+LED%d\r\n", ledId);
        //uart2_comm_write(bytes, strlen(bytes));
        // freq +
        PWM_level_up(1);
        return (events ^ EXTI_KEY6_EVT);
    }

    if( events & EXTI_KEY7_EVT )
    {
        //printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        //ledId = 7;
        //sprintf(bytes, "AT+LED%d\r\n", ledId);
        //uart2_comm_write(bytes, strlen(bytes));
        // freq -
        PWM_level_down(1);
        return (events ^ EXTI_KEY7_EVT);
    }

    if( events & EXTI_KEY8_EVT )
    {
        //printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        //ledId = 8;
        //sprintf(bytes, "AT+LED%d\r\n", ledId);
        //uart2_comm_write(bytes, strlen(bytes));
        PWM_level_up(2);
        return (events ^ EXTI_KEY8_EVT);
    }

    if( events & EXTI_KEY9_EVT )
    {
        //printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        //ledId = 8;
        //sprintf(bytes, "AT+LED%d\r\n", ledId);
        //uart2_comm_write(bytes, strlen(bytes));
        //GPIO_onoff();
        PWM_level_down(2);
        return (events ^ EXTI_KEY9_EVT);
    }

    if( events & EXTI_KEY10_EVT )
    {
        //printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        //ledId = 8;
        //sprintf(bytes, "AT+LED%d\r\n", ledId);
        //uart2_comm_write(bytes, strlen(bytes));
        PWM_level_up(3);
        return (events ^ EXTI_KEY10_EVT);
    }

    if( events & EXTI_KEY11_EVT )
    {
        //printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        //ledId = 8;
        //sprintf(bytes, "AT+LED%d\r\n", ledId);
        //uart2_comm_write(bytes, strlen(bytes));
        //GPIO_onoff();
        PWM_level_down(3);
        return (events ^ EXTI_KEY11_EVT);
    }

    if( events & EXTI_KEY13_EVT )
    {
        //printf("\r\n L:%d %s", __LINE__, __FUNCTION__);
        //ledId = 8;
        //sprintf(bytes, "AT+LED%d\r\n", ledId);
        //uart2_comm_write(bytes, strlen(bytes));
        //GPIO_onoff();
        return (events ^ EXTI_KEY13_EVT);
    }
}

 
