#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED14 PBout(0)// PB5
#define LED15 PBout(1)
#define LED16 PBout(12)
#define LED17 PBout(13)
#define LED18 PBout(14)
#define LED19 PBout(15)
#define LED20 PCout(10)
#define LED21 PCout(11)
#define LED22 PCout(12)
#define LED23 PBout(5)
#define LED25 PBout(8)
#define LED26 PBout(9)

void LED_Init(void);//初始化

		 				    
#endif
