#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
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

void LED_Init(void);//��ʼ��

		 				    
#endif
