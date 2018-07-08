#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
#include "type.h"
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//ADC 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/7
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 


#define ADC_READ_EVT                               0x0040

#define ADC_BEEP_THRESHOLD                         (1)

void Adc_Init(uint8 task_id);
u16  Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times); 
uint16 Adc_ProcessEvent( uint8 task_id, uint16 events );



#endif 
