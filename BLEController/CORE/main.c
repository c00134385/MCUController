#include "sys.h"
#include "delay.h"
#include "usart.h"

#include "common.h"
#include "message.h"

#include "beep.h"
#include "led.h"
#include "key.h"
#include "exti.h"
#include "timer.h"
#include "adc.h"

#include "osal_simple.h"

#include <string.h>

/* version */
const char version_msg[200]={
"\r\n"
"**********************************************\r\n"
"[Ble Project]\r\n"
"V1.0c\r\n"
"2018/6/30\r\n"
"MODEM:cjl\r\n"
"**********************************************\r\n"
};


WORK_STATE_E work_state = STATE_POWER_ON;

int main(void)
{
    u8 t=0;
    u8 led_state = 1;
    u16 pwmval=0;
    u16 led0pwmval=0;
    u8 dir=1;	
    u16 adcx;

    char* str1 = "chengjl";
    char* str2 = "chengjl";
    char* str3 = "a";
    char* str4 = "b";

    delay_init();            //��ʱ������ʼ��	  
    NVIC_Configuration();    //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    uart_init(57600);    //���ڳ�ʼ��Ϊ9600

    printf(version_msg);

    LED_Init();         //��ʼ����LED���ӵ�Ӳ��

    
    //KEY_Init();             //��ʼ���밴�����ӵ�Ӳ���ӿ�
    //EXTIX_Init();

    //Message_init(Message_handler);

    #if 0
    TIM3_PWM_Init(999,72);    //����Ƶ��PWMƵ��=72000/72000=80Khz
    TIM_SetCompare1(TIM3,50);//��ʼֵΪ0	
    TIM_SetCompare2(TIM3,50);//��ʼֵΪ0	
    TIM_SetCompare3(TIM3,50);//��ʼֵΪ0	
    #else
    PWM_Init();
    #endif
    
    //Adc_Init();		  		//ADC��ʼ��
	
    printf("\r\nrequest ble...");

    printf("\r\n strcmp:%d", strcmp(str1, str2));
    printf("\r\n strcmp2:%d", strcmp(str3, str4));

    #if 0
    while(work_state == STATE_POWER_ON)
    {
        // send msg to ble
        unsigned char* msg = MSG_MCU_IS_READY;
        Message_send(msg, sizeof(msg));
        delay_ms(1000);
    }

    while(1)
    {
        delay_ms(2000);
        printf("\r\nwork_stat:%d", work_state);
    }
    

    while(1)
    {
        delay_ms(1000);	 
		if(dir)led0pwmval++;
		else led0pwmval--;

 		if(led0pwmval>899)dir=0;
		if(led0pwmval==0)dir=1;										 
		//TIM_SetCompare1(TIM3,led0pwmval);
        //TIM_SetCompare2(TIM3,led0pwmval);
        //TIM_SetCompare3(TIM3,led0pwmval);

        adcx=Get_Adc_Average(ADC_Channel_13,10);
        printf("\r\n adcx:0x%x", adcx);

        #if 0
        
        u8 key_val = KEY_Scan(0);
        if(key_val != 0)
        {
            printf("\r\nkey:%d is pressed.", key_val);

            if(key_val==6)
    		{		 
    			if(pwmval<250)pwmval+=10;
                TIM_SetCompare2(TIM3,pwmval);
    			TIM_SetCompare1(TIM4,pwmval); 		//���
    		}else if(key_val==7)	
    		{
    			if(pwmval>10)pwmval-=10;
    			else pwmval=0;
                TIM_SetCompare2(TIM3,pwmval);
    			TIM_SetCompare1(TIM4,pwmval); 		//���
    		}
        }
        #endif
    }

    #endif

    //osalInitTasks();
    osal_init_system();

    osal_start_system();
}

