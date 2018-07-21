#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
#include "type.h"
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
#define LED14 PBin(0)// PB5
#define LED15 PBin(1)
#define LED16 PBin(12)
#define LED17 PBin(13)
#define LED18 PBin(14)
#define LED19 PBin(15)
#define LED20 PCin(10)
#define LED21 PCin(11)

#define LED22 PCin(12)
#define LED23 PBin(5)
#define LED25 PBin(8)
#define LED26 PBin(9)


#define LED_SCAN_EVT                               0x0001



typedef struct LED_IN_s {
    char name[16];
    GPIO_TypeDef* GPIOx;
    uint16_t GPIO_Pin;
    u8 state;
} LED_IN_t;




#define ONOFF PBout(4)
#define K_START_STOP PAout(4)
#define K_AUTO PAout(5)
#define K_HA PAout(6)
#define K_LEVEL PAout(7)


void LED_Init(uint8 task_id);//初始化
u32 LED_Get_state(void);
u8 LED_Scan(u8 mode);

uint16 LED_ProcessEvent( uint8 task_id, uint16 events );
void LED_Notify(void);
u8 LED_GetMode(void);
		 				    
#endif
