#ifndef __EXTI_H
#define __EXIT_H	 
#include "sys.h"
#include "type.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//�ⲿ�ж� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	

#define EXTI_KEY1_EVT                               0x0001//�����豸
#define EXTI_KEY2_EVT                               0x0002//ϵͳ��ѯ��ʱ��
#define EXTI_KEY3_EVT                               0x0004
#define EXTI_KEY4_EVT                               0x0008
#define EXTI_KEY5_EVT                               0x0010
#define EXTI_KEY6_EVT                               0x0020
#define EXTI_KEY7_EVT                               0x0040
#define EXTI_KEY8_EVT                               0x0080



void EXTIX_Init(uint8 task_id);//�ⲿ�жϳ�ʼ��	

uint16 EXTIX_ProcessEvent( uint8 task_id, uint16 events );

#endif

