#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
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

#define KEY01  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//��ȡ����0 
#define KEY02  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)//��ȡ����0
#define KEY03  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//��ȡ����1
#define KEY04  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)//��ȡ����1


#define KEY07  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)//��ȡ����0 
#define KEY09  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)//��ȡ����0
#define KEY11  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)//��ȡ����1
#define KEY06  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)//��ȡ����2 
#define KEY08  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)//��ȡ����3(WK_UP) 
#define KEY10  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)//��ȡ����3(WK_UP) 

#define KEY13  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)//ON/OFF


#define KEY_UP 		4
#define KEY_LEFT	3
#define KEY_DOWN	2
#define KEY_RIGHT	1

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
