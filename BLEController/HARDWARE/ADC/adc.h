#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
#include "type.h"
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//ADC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 


#define ADC_READ_EVT                               0x0040

#define ADC_BEEP_THRESHOLD                         (1)

void Adc_Init(uint8 task_id);
u16  Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times); 
uint16 Adc_ProcessEvent( uint8 task_id, uint16 events );



#endif 
