#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
#include "type.h"
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

// 
//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define KEY2 PEin(2)	//PE2
//#define KEY3 PAin(0)	//PA0  WK_UP

#define KEY02  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)//读取按键0
#define KEY03  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)//读取按键1
#define KEY04  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)//读取按键1
#define KEY05  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)//读取按键1


#define KEY07  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)//读取按键0 
#define KEY09  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)//读取按键0
#define KEY11  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)//读取按键1
#define KEY06  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)//读取按键2 
#define KEY08  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)//读取按键3(WK_UP) 
#define KEY10  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)//读取按键3(WK_UP) 

#define KEY13  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)//ON/OFF


//#define KEY1_EVT                               0x0001//启动设备
#define KEY2_EVT                               0x0002//系统轮询定时器
#define KEY3_EVT                               0x0004
#define KEY4_EVT                               0x0008
#define KEY5_EVT                               0x0010
#define KEY6_EVT                               0x0020
#define KEY7_EVT                               0x0040
#define KEY8_EVT                               0x0080
#define KEY9_EVT                               0x0100
#define KEY10_EVT                               0x0200
#define KEY11_EVT                               0x0400
//#define KEY12_EVT                               0x0800
#define KEY13_EVT                               0x1000


void KEY_Init(uint8 task_id);//IO初始化
u8 KEY_Scan(void);  	//按键扫描函数	
void KEY_event(void);
uint16 KEY_ProcessEvent( uint8 task_id, uint16 events );

#endif
