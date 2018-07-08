#include "key.h"
#include "sys.h" 
#include "delay.h"
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
								    
//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
	//��ʼ��KEY0-->GPIOA.13,KEY1-->GPIOA.15  ��������
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTA,PORTEʱ��

    // S6(PC13)  S8(PC14)   S10(PC15)
    // S7(PC2)  S9(PC1)   S11(PC0)
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//PE2~4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4

	//��ʼ�� WK_UP-->GPIOA.0	  ��������
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PA0���ó����룬Ĭ������	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //PA0���ó����룬Ĭ������	  
	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOA.0

}
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��KEY3���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>KEY3!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY06==0||KEY07==0||KEY08==0||KEY09==0||KEY10==0||KEY11==0||KEY13==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY06==0)return 6;
		else if(KEY07==0)return 7;
		else if(KEY08==0)return 8;
		else if(KEY09==0)return 9;
        else if(KEY10==0)return 10;
        else if(KEY11==0)return 11;
        else if(KEY13==0)return 13;
	}else if(KEY06==1&&KEY07==1&&KEY08==1&&KEY09==1&&KEY10==1&&KEY11==1&&KEY13==1)key_up=1; 	
    
 	return 0;// �ް�������
}
