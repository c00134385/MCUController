#include "timer.h"
#include "led.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//PWM  驱动代码			   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/12/03
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  

//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!

#if 0
void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //自动重装载周期值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //预分频值  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx
 
	TIM_ITConfig(  TIM3,TIM_IT_Update  |  TIM_IT_Trigger,  ENABLE  );//使能更新触发TIM中断

	//中断分组设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设
							 
}

void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		LED1=!LED1;
		}
}

#endif

//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数

pTimerHandler tim2_handler = NULL;
void TIM2_Int_Init(u16 arr,u16 psc)
{  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ê±?óê1?ü
	
	//?¨ê±?÷TIM33?ê??ˉ
	TIM_TimeBaseStructure.TIM_Period = arr; //éè???ú??ò????üD?ê??t×°è????ˉμ?×??ˉ??×°????′??÷?ü?úμ??μ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //éè??ó?à′×÷?aTIMxê±?ó?μ?ê3yêyμ??¤·??μ?μ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //éè??ê±?ó·???:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM?òé???êy?￡ê?
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //?ù?Y???¨μ?2?êy3?ê??ˉTIMxμ?ê±???ùêyμ￥??
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ê1?ü???¨μ?TIM3?D??,?êDí?üD??D??

	//?D??ó??è??NVICéè??
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3?D??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //?è??ó??è??0??
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //′óó??è??3??
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQí¨μà±?ê1?ü
	NVIC_Init(&NVIC_InitStructure);  //3?ê??ˉNVIC??′??÷

	TIM_Cmd(TIM2, ENABLE);  //ê1?üTIMx	
}

void TIM2_IRQHandler(void)   //TIM3?D??
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //?ì2éTIM3?üD??D??·￠éúó?·?
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //??3yTIMx?üD??D??±ê?? 
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


//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数

void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟使能
	
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5                                                                       	 //用于TIM3的CH2输出的PWM通过该LED显示
 
   //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//GPIO_WriteBit(GPIOA, GPIO_Pin_7,Bit_SET); // PA7上拉	

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器

    TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器

    TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIMx在CCR2上的预装载寄存器
	
	TIM_ARRPreloadConfig(TIM3, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
 
	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设
 

}


//í¨ó??¨ê±?÷3?D??3?ê??ˉ
//?aà?ê±?ó?????aAPB1μ?2±?￡???APB1?a36M
//arr￡o×??ˉ??×°?μ?￡
//psc￡oê±?ó?¤·??μêy
//?aà?ê1ó?μ?ê??¨ê±?÷3!
void TIM4_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ê±?óê1?ü
	
	//?¨ê±?÷TIM33?ê??ˉ
	TIM_TimeBaseStructure.TIM_Period = arr; //éè???ú??ò????üD?ê??t×°è????ˉμ?×??ˉ??×°????′??÷?ü?úμ??μ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //éè??ó?à′×÷?aTIMxê±?ó?μ?ê3yêyμ??¤·??μ?μ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //éè??ê±?ó·???:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM?òé???êy?￡ê?
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //?ù?Y???¨μ?2?êy3?ê??ˉTIMxμ?ê±???ùêyμ￥??
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //ê1?ü???¨μ?TIM3?D??,?êDí?üD??D??

	//?D??ó??è??NVICéè??
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3?D??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //?è??ó??è??0??
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //′óó??è??3??
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQí¨μà±?ê1?ü
	NVIC_Init(&NVIC_InitStructure);  //3?ê??ˉNVIC??′??÷


	TIM_Cmd(TIM4, ENABLE);  //ê1?üTIMx					 
}
//?¨ê±?÷3?D??·t??3ìDò


#if 0
//定时器5通道1输入捕获配置

TIM_ICInitTypeDef  TIM5_ICInitStructure;

void TIM5_Cap_Init(u16 arr,u16 psc)
{	 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
   	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟使能
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;  //PA0 清除之前设置  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0 输入  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);						 //PA0 下拉
		 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 最大10ms溢出  
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 	//预分频器,1M的计数频率,1us加1.	   
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式

	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波

  	TIM_ICInit(TIM5, &TIM5_ICInitStructure);
		
   	TIM_Cmd(TIM5,ENABLE ); 	//使能定时器5
   	TIM_ITConfig( TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	


	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
}

u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u16	TIM5CH1_CAPTURE_VAL;	//输入捕获值
 
//定时器5中断服务程序	 
void TIM5_IRQHandler(void)
{ 

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		 
		{	    
			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM5CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM5CH1_CAPTURE_VAL=0XFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
	if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次上升沿
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH1_CAPTURE_STA=0;			//清空
				TIM5CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM5,0);
				TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
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

    TIM3_PWM_Init((PWM_FREQ_ARR - 1),4);    //不分频。PWM频率=72000000/72/1000=1Khz
    
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

    TIM_SetCompare1(TIM3,0);//初始值为0	
    TIM_SetCompare2(TIM3,0);//初始值为0	
    TIM_SetCompare3(TIM3,0);//初始值为0
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

