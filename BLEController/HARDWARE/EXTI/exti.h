#ifndef __EXTI_H
#define __EXIT_H	 
#include "sys.h"
#include "type.h"
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

#define EXTI_KEY1_EVT                               0x0001//启动设备
#define EXTI_KEY2_EVT                               0x0002//系统轮询定时器
#define EXTI_KEY3_EVT                               0x0004
#define EXTI_KEY4_EVT                               0x0008
#define EXTI_KEY5_EVT                               0x0010
#define EXTI_KEY6_EVT                               0x0020
#define EXTI_KEY7_EVT                               0x0040
#define EXTI_KEY8_EVT                               0x0080



void EXTIX_Init(uint8 task_id);//外部中断初始化	

uint16 EXTIX_ProcessEvent( uint8 task_id, uint16 events );

#endif

