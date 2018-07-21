#ifndef __ACTION_H
#define __ACTION_H	 
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



void ACTION_Init(void);//IO初始化
void ACTION_Power_On(void);
void ACTION_Power_Off(void);
void ACTION_Key1(void);
void ACTION_Key2(void);
void ACTION_Key3(void);
void ACTION_Key4(void);




#endif
