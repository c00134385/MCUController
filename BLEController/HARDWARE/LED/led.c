#include "led.h"
#include "type.h"
#include "timer.h"
#include "simple_main.h"

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

//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��

uint8 LED_TaskID;

void LED_Init(uint8 task_id)
{
 
    GPIO_InitTypeDef  GPIO_InitStructure;  

    LED_TaskID = task_id;
 	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PB,PE�˿�ʱ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;                //LED0-->PB.5 �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;        //�������
    //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);                   //�����趨������ʼ��GPIOB.5

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;	    		 //LED1-->PE.5 �˿�����, �������
    GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
    //GPIO_SetBits(GPIOC,GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12); 

    #if 0
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //LED0-->PB.5 �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //�������
    //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
    //GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);						 //PB.5 �����

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;	    		 //LED1-->PE.5 �˿�����, �������
    GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
    //GPIO_SetBits(GPIOC,GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12); 						 //PE.5 ����� 

 
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	    		 //ON/OFF
    GPIO_Init(GPIOB, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
    GPIO_ResetBits(GPIOB,GPIO_Pin_4); 	

 //��ʼ�� WK_UP-->GPIOA.0	  ��������
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;	  
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0
    GPIO_ResetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
    #endif


    TIM4_Int_Init(4999,7199);
}

void TIM4_IRQHandler(void)   //TIM3?D??
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //?��2��TIM3?��D??D??���騦����?��?
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //??3yTIMx?��D??D??����?? 
		//LED1=!LED1;
		//printf("\r\n TIM4 IRQ");
		osal_set_event(LED_TaskID, LED_SCAN_EVT);	
    }
}



LED_IN_t led_list[16] = {
    {"LED14", GPIOB, GPIO_Pin_0, 3},
    {"LED15", GPIOB, GPIO_Pin_1, 3},
    {"LED16", GPIOB, GPIO_Pin_12, 3},

    
    {"LED17", GPIOB, GPIO_Pin_13, 2},
    {"LED18", GPIOB, GPIO_Pin_14, 3},
    {"LED19", GPIOB, GPIO_Pin_15, 3},
    {"LED20", GPIOC, GPIO_Pin_10, 4},
    {"LED21", GPIOC, GPIO_Pin_11, 3},
        
    {"LED22", GPIOC, GPIO_Pin_12, 3},
    {"LED23", GPIOB, GPIO_Pin_5, 3},

    {"LED25", GPIOB, GPIO_Pin_8, 3},
    {"LED26", GPIOB, GPIO_Pin_9, 3},
};


#define LED22 PCin(12)
#define LED23 PBin(5)


u32 LED_Get_state(void)
{
    u32 led_state = 0;
    u8 count = 0;
    u8 i;

    count = sizeof(led_list)/sizeof(LED_IN_t);
    for(i = 0; i < count; i++)
    {
        led_state |= (led_list[i].state << i);
    }

    return led_state;
}

u8 LED_Scan(u8 mode)
{
	static u8 key_up=1;//�������ɿ���־
	u8 count = 0;
    u8 i;
    u8 state = 0;
	if(mode)key_up=1;  //֧������

    count = sizeof(led_list)/sizeof(LED_IN_t);
    for(i = 0; i < count; i++)
    {
        if(led_list[i].state != GPIO_ReadInputDataBit(led_list[i].GPIOx, led_list[i].GPIO_Pin))
        {
            delay_ms(10);//ȥ���� 
            if(led_list[i].state != GPIO_ReadInputDataBit(led_list[i].GPIOx, led_list[i].GPIO_Pin))
            {
                state |= 1;
                led_list[i].state = GPIO_ReadInputDataBit(led_list[i].GPIOx, led_list[i].GPIO_Pin);
                //printf("\r\n LED update");
            }
        }
    }

    if((LED22 == 0) && (LED23 == 1))
    {
        PWM_SetMode(0);
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_MODE_CHANGE);
    }
    else if((LED22 == 1) && (LED23 == 0))
    {
        PWM_SetMode(1);
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_MODE_CHANGE);
    }

    return state;
}

u8 LED_GetMode(void)
{
    if((LED22 == 0) && (LED23 == 1))
    {
        return 0;
    }
    else if((LED22 == 1) && (LED23 == 0))
    {
        return 1;
    }
    else
    {
        return 2;
    }
}


uint16 LED_ProcessEvent( uint8 task_id, uint16 events )
{
    unsigned char bytes[32];
    if ( events & LED_SCAN_EVT )
    {
        if(LED_Scan(0))
        {
            u32 led_state = LED_Get_state();
            printf("\r\n LED:0x%08x", led_state);
            // update to cellphone throught ble

            sprintf(bytes, "AT+BLE+LED%04x\r\n", led_state);
            uart2_comm_write(bytes, strlen(bytes));
        }
        
        return (events ^ LED_SCAN_EVT);
    }
    return events;
}

void LED_Notify(void)
{
    unsigned char bytes[20];
    u32 led_state = LED_Get_state();
    printf("\r\n LED:0x%08x", led_state);
    // update to cellphone throught ble

    sprintf(bytes, "AT+BLE+LED%04x\r\n", led_state);
    uart2_comm_write(bytes, strlen(bytes));
}

