#include "timer.h"
#include "led.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//PWM  ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/12/03
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  

//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!

#if 0
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //�Զ���װ������ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //Ԥ��Ƶֵ  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx
 
	TIM_ITConfig(  TIM3,TIM_IT_Update  |  TIM_IT_Trigger,  ENABLE  );//ʹ�ܸ��´���TIM�ж�

	//�жϷ�������
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����
							 
}

void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		LED1=!LED1;
		}
}

#endif

//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��

pTimerHandler tim2_handler = NULL;
void TIM2_Int_Init(u16 arr,u16 psc)
{  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //����?����1?��
	
	//?������?��TIM33?��??��
	TIM_TimeBaseStructure.TIM_Period = arr; //����???��??��????��D?��??t���㨨????����?��??��??����????��??��?��?����??��	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����??��?�������?aTIMx����?��?��?��3y��y��??�衤??��?��
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����??����?����???:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM?����???��y?�꨺?
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //?��?Y???����?2?��y3?��??��TIMx��?����???����y�̣�??
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //��1?��???����?TIM3?D??,?��D��?��D??D??

	//?D??��??��??NVIC����??
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3?D??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //?��??��??��??0??
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�䨮��??��??3??
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ�����̨���?��1?��
	NVIC_Init(&NVIC_InitStructure);  //3?��??��NVIC??��??��

	TIM_Cmd(TIM2, ENABLE);  //��1?��TIMx	
}

void TIM2_IRQHandler(void)   //TIM3?D??
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //?��2��TIM3?��D??D??���騦����?��?
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //??3yTIMx?��D??D??����?? 
		//LED1=!LED1;
		if(NULL != tim2_handler)
		{
            tim2_handler();
            printf("\r\n TIM2 IRQ");
		}
        else
        {
		    printf("\r\n TIM2 IRQ");
        }
    }
}

void TIM2_Start(pTimerHandler handler)
{
    printf("\r\n %s()", __FUNCTION__);
    tim2_handler = handler;
    TIM2_Int_Init(4999,7199);
}

void TIM2_Stop(void)
{
    printf("\r\n %s()", __FUNCTION__);
    tim2_handler = NULL;
    TIM_Cmd(TIM2, DISABLE);
}


//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��

void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��ʹ��
	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE); //Timer3������ӳ��  TIM3_CH2->PB5                                                                       	 //����TIM3��CH2�����PWMͨ����LED��ʾ
 
   //���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//GPIO_WriteBit(GPIOA, GPIO_Pin_7,Bit_SET); // PA7����	

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���

    TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���

    TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
	
	TIM_ARRPreloadConfig(TIM3, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
 
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����
 

}


//������??������?��3?D??3?��??��
//?a��?����?��?????aAPB1��?2��?��???APB1?a36M
//arr��o��??��??����?��?��
//psc��o����?��?�衤??�̨�y
//?a��?��1��?��?��??������?��3!
void TIM4_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //����?����1?��
	
	//?������?��TIM33?��??��
	TIM_TimeBaseStructure.TIM_Period = arr; //����???��??��????��D?��??t���㨨????����?��??��??����????��??��?��?����??��	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����??��?�������?aTIMx����?��?��?��3y��y��??�衤??��?��
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����??����?����???:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM?����???��y?�꨺?
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //?��?Y???����?2?��y3?��??��TIMx��?����???����y�̣�??
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //��1?��???����?TIM3?D??,?��D��?��D??D??

	//?D??��??��??NVIC����??
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3?D??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //?��??��??��??0??
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�䨮��??��??3??
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ�����̨���?��1?��
	NVIC_Init(&NVIC_InitStructure);  //3?��??��NVIC??��??��


	TIM_Cmd(TIM4, ENABLE);  //��1?��TIMx					 
}
//?������?��3?D??��t??3��D��


#if 0
//��ʱ��5ͨ��1���벶������

TIM_ICInitTypeDef  TIM5_ICInitStructure;

void TIM5_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
   	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��ʹ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;  //PA0 ���֮ǰ����  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 ����  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);						 //PA0 ����
		 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ ���10ms���  
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//Ԥ��Ƶ��,1M�ļ���Ƶ��,1us��1.	   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ

	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
  	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�

  	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
		
   	TIM_Cmd(TIM5,ENABLE ); 	//ʹ�ܶ�ʱ��5
   	TIM_ITConfig( TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�	


	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 
}

u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u16	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ
 
//��ʱ��5�жϷ������	 
void TIM5_IRQHandler(void)
{ 

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
				{
					TIM5CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM5CH1_CAPTURE_VAL=0XFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//����1���������¼�
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ��������
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM5CH1_CAPTURE_STA=0;			//���
				TIM5CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM5,0);
				TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 ����Ϊ�½��ز���
			}		    
		}			     	    					   
 	}
 
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); 
 
}

#endif



#define AUTO_MODE  (0)
#define MANUAL_MODE  (1)
u8 curr_mode = 0; // 0:auto   1: manual

void PWM_SetMode(u8 mode)
{
    if(mode != curr_mode)
    {
        printf("mode:%d->%d", curr_mode, mode);
        curr_mode = mode;
        PWM_level_reset(1);
    }
}

#if 0
static u16 curve1[11] = {
    0, 17, 34, 52, 71, 90, 110, 131, 152, 175, 199
};
static u16 curve2[11] = {
    0, 65, 118, 175, 255, 335, 420, 520, 640, 775, 999
};
static u16 curve3[30] = {
    0, 18, 35, 53, 75, 89, 112, 136, 158, 179,
    204, 232, 260, 287, 316, 346, 375, 410, 441, 481,
    516, 561, 601, 647, 696, 745, 795, 857, 916, 999
};
static u16 curve4[26] = {
    0, 17, 39, 60, 83, 107, 132, 160, 188, 215,
    245, 278, 311, 346, 380, 421, 461, 505, 552, 601,
    655, 705, 770, 833, 899, 999
};
#endif
#define PWM_MAX   (4)
u8 curr_level[PWM_MAX];
u8 max_level[PWM_MAX];
u16* pwm_curve[PWM_MAX];


#if 1
static u16 pwm1_curve[11] = {
    17, 34, 52, 71, 90, 110, 131, 152, 175, 199
};

static u16 pwm2_curve[26] = {
    0, 17, 39, 60, 83, 107, 132, 160, 188, 215,
    245, 278, 311, 346, 380, 421, 461, 505, 552, 601,
    655, 705, 770, 833, 899, 999
};

static u16 pwm3_curve[30] = {
    0, 18, 35, 53, 75, 89, 112, 136, 158, 179,
    204, 232, 260, 287, 316, 346, 375, 410, 441, 481,
    516, 561, 601, 647, 696, 745, 795, 857, 916, 999
};

static u16 pwm4_curve[11] = {
    0, 65, 118, 175, 255, 335, 420, 520, 640, 775, 999
};
#endif



#define PWM_FREQ_ARR  (1000)
void PWM_Init(void)
{
    //Pwm_taskID = task_id;
    int i = 0;

    TIM3_PWM_Init((PWM_FREQ_ARR - 1),4);    //����Ƶ��PWMƵ��=72000000/72/1000=1Khz
    
    curr_level[0] = 0;
    curr_level[1] = 0;
    curr_level[2] = 0;
    curr_level[3] = 0;
    
    max_level[0] = sizeof(pwm1_curve)/sizeof(u16);
    max_level[1] = sizeof(pwm2_curve)/sizeof(u16);
    max_level[2] = sizeof(pwm3_curve)/sizeof(u16);
    max_level[3] = sizeof(pwm4_curve)/sizeof(u16);

    pwm_curve[0] = pwm1_curve;
    pwm_curve[1] = pwm2_curve;
    pwm_curve[2] = pwm3_curve;
    pwm_curve[3] = pwm4_curve;

    printf("\r\n %d %d %d %d", max_level[0], max_level[1], max_level[2], max_level[3]);

    TIM_SetCompare1(TIM3,0);//��ʼֵΪ0	
    TIM_SetCompare2(TIM3,0);//��ʼֵΪ0	
    TIM_SetCompare3(TIM3,0);//��ʼֵΪ0
}

void PWM_Set(uint8 id, uint8 level)
{
    unsigned char bytes[32];
    if(id >= PWM_MAX)
    {
        return;
    }

    if((level < max_level[id]) && (level != curr_level[id]))
    {
        printf("\r\nL:%d %s() id(%d) level:%d value:%d", __LINE__, __FUNCTION__, id, level, curr_level[id]);
        switch(id)
        {
            case 0:
                TIM_SetCompare1(TIM3,pwm_curve[id][level]);
                curr_level[id] = level;
                sprintf(bytes, "AT+BLE+FREQ%d\r\n", level);
                uart2_comm_write(bytes, strlen(bytes));
                break;
            case 1:
                TIM_SetCompare2(TIM3,pwm_curve[id][level]);
                curr_level[id] = level;
                sprintf(bytes, "AT+BLE+AUTO%d\r\n", level);
                uart2_comm_write(bytes, strlen(bytes));
                break;
            case 2:
                TIM_SetCompare3(TIM3,pwm_curve[id][level]);
                curr_level[id] = level;
                sprintf(bytes, "AT+BLE+TIME%d\r\n", level);
                uart2_comm_write(bytes, strlen(bytes));
                break;
            case 3:
                TIM_SetCompare2(TIM3,pwm_curve[id][level]);
                curr_level[id] = level;
                sprintf(bytes, "AT+BLE+MANUAL%d\r\n", level);
                uart2_comm_write(bytes, strlen(bytes));
                break;
            default:
                break;
        }
    }
}

void PWM_Notify(uint8 id)
{
    unsigned char bytes[20];
    if(id >= PWM_MAX)
    {
        return;
    }
    if(0 == id)
    {
        sprintf(bytes, "AT+BLE+FREQ%d\r\n", curr_level[id]);
        uart2_comm_write(bytes, strlen(bytes));  
    }
    else if(1 == id)
    {
        sprintf(bytes, "AT+BLE+AUTO%d\r\n", curr_level[id]);
        uart2_comm_write(bytes, strlen(bytes));  
    }
    else if(2 == id)
    {
        sprintf(bytes, "AT+BLE+TIME%d\r\n", curr_level[id]);
        uart2_comm_write(bytes, strlen(bytes));
    }
    else if(3 == id)
    {
        sprintf(bytes, "AT+BLE+MANUAL%d\r\n", curr_level[id]);
        uart2_comm_write(bytes, strlen(bytes)); 
    }
}

void PWM_level_up(uint8 id)
{
    uint8 id_ = id;
    uint8 level;

    if(id >= 3)
    {
        return;
    }

    if((1 == curr_mode) && (1 == id))
    {
        id_ = 3;
    }

    if(curr_level[id_] < (max_level[id_] - 1))
    {
        level = curr_level[id_] + 1;
    }
    else
    {
        level = (max_level[id_] - 1);
    }
    
    PWM_SetValue(id, pwm_curve[id_][level]);
    curr_level[id_] = level;
    PWM_Notify(id_);
}

void PWM_level_reset(uint8 id)
{
    uint8 id_ = id;
    uint8 level;

    if(id >= 3)
    {
        return;
    }

    if((1 == curr_mode) && (1 == id))
    {
        id_ = 3;
    }

    level = curr_level[id_];
    
    PWM_SetValue(id, pwm_curve[id_][level]);
    curr_level[id_] = level;
    PWM_Notify(id_);
}


void PWM_level_down(uint8 id)
{
    uint8 id_ = id;
    uint8 level = 0;

    if(id >= 3)
    {
        return;
    }

    if((1 == curr_mode) && (1 == id))
    {
        id_ = 3;
    }

    if(curr_level[id_] > 0)
    {
        level = curr_level[id_] - 1;
    }
    
    PWM_SetValue(id, pwm_curve[id_][level]);
    curr_level[id_] = level;
    PWM_Notify(id_);
}

void PWM_SetValue(uint8 id, uint32 value)
{
    if((0 == id) && (value <= PWM_FREQ_ARR))
    {
        printf("\r\nL:%d %s() id(%d) value:%d", __LINE__, __FUNCTION__, id, value);
        TIM_SetCompare1(TIM3,value);
    }
    else if((1 == id) && (value <= PWM_FREQ_ARR))
    {
        printf("\r\nL:%d %s() id(%d) value:%d", __LINE__, __FUNCTION__, id, value);
        TIM_SetCompare2(TIM3,value);
    }
    else if((2 == id) && (value <= PWM_FREQ_ARR))
    {
        printf("\r\nL:%d %s() id(%d) value:%d", __LINE__, __FUNCTION__, id, value);
        TIM_SetCompare3(TIM3,value);
    }
}

void PWM_ValueUp(uint8 id)
{
    u32 value = 0;
    switch(id)
    {
        case 1:
            value = 0;
            value++;
            value %= PWM_FREQ_ARR;
            break;
        case 2:
            value = 0;
            value++;
            value %= PWM_FREQ_ARR;
            break;
        case 3:
            value = 0;
            value++;
            value %= PWM_FREQ_ARR;
            break;
        default:
            return;
    }

    PWM_SetValue(id, value);
}

void PWM_ValueDown(uint8 id)
{
    u32 value = 0;
    switch(id)
    {
        case 1:
            value = 0;
            if(value > 0)
            {
                value--;
            }
            break;
        case 2:
            value = 0;
            if(value > 0)
            {
                value--;
            }
            break;
        case 3:
            value = 0;
            if(value > 0)
            {
                value--;
            }
            break;
        default:
            return;
    }

    PWM_SetValue(id, value);
}


void PWM_SetCurrLevel(u8* pCurr)
{
    curr_level[0] = pCurr[0];
    curr_level[1] = pCurr[1];
    curr_level[2] = pCurr[2];
    curr_level[3] = pCurr[3];
}

