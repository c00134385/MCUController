#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
#include "type.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 

// 
//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define KEY2 PEin(2)	//PE2
//#define KEY3 PAin(0)	//PA0  WK_UP

#define KEY02  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)//��ȡ����0
#define KEY03  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)//��ȡ����1
#define KEY04  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)//��ȡ����1
#define KEY05  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)//��ȡ����1


#define KEY07  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)//��ȡ����0 
#define KEY09  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)//��ȡ����0
#define KEY11  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)//��ȡ����1
#define KEY06  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)//��ȡ����2 
#define KEY08  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)//��ȡ����3(WK_UP) 
#define KEY10  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)//��ȡ����3(WK_UP) 

#define KEY13  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)//ON/OFF


//#define KEY1_EVT                               0x0001//�����豸
#define KEY2_EVT                               0x0002//ϵͳ��ѯ��ʱ��
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


void KEY_Init(uint8 task_id);//IO��ʼ��
u8 KEY_Scan(void);  	//����ɨ�躯��	
void KEY_event(void);
uint16 KEY_ProcessEvent( uint8 task_id, uint16 events );

#endif
