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


static u8 Lock_Code[4]; // 
const u32 Lock_Code_Holder = 0x92AACDB9;
BOOL checkLockCode(void)
{
	u32 CpuID[3];
	u32 code;
	BOOL ret = false;
	//get cpu unique id
	CpuID[0]=*(vu32*)(0x1ffff7e8);
	CpuID[1]=*(vu32*)(0x1ffff7ec);
	CpuID[2]=*(vu32*)(0x1ffff7f0);
	//encrypt algy
	code=(CpuID[0]>>1)+(CpuID[1]>>2)+(CpuID[2]>>3);
	code = ~code;
	code *=3;
	//printf("\r\n 0x%08x 0x%08x 0x%08x 0x%08x", CpuID[0], CpuID[1], CpuID[2], code);
	Lock_Code[0] = code >> 24;
	Lock_Code[1] = code >> 16;
	Lock_Code[2] = code >> 8;
	Lock_Code[3] = code;

	//STMFLASH_Read((u32)&Lock_Code_Holder,(u16*)code,4);
	if(code == Lock_Code_Holder)
	{
		//printf("\r\n L:%d write flash...", __LINE__);
		//STMFLASH_Write((u32)&Lock_Code_Holder,(u16*)Lock_Code,4);
		//printf("\r\n L:%d write flash finished!", __LINE__);
		ret = true;
	}
	else
	{
		//printf("\r\n L:%d Lock_Code_bak:%02x %02x %02x %02x", __LINE__, code[0], code[1], code[2], code[3]);
		ret = false;
	}
	return ret;
}


int main(void)
{
    u8 t=0;
    u8 led_state = 1;
    u16 pwmval=0;
    u16 led0pwmval=0;
    u8 dir=1;	
    u16 adcx;
    BOOL check = true;

    #if 0
    char* str1 = "chengjl";
    char* str2 = "chengjl";
    char* str3 = "a";
    char* str4 = "b";
    #endif
    
    delay_init();            //延时函数初始化	  
    NVIC_Configuration();    //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    uart_init(57600);    //串口初始化为9600

    check = checkLockCode();
	if(!check)
	{
		printf("%c", 64);
		while(1)
		{
			printf(version_msg);
			delay_ms(250);
		}
	}

    printf(version_msg);


    #if 0
    KEY_Init(0);             //初始化与按键连接的硬件接口
    while(1)
    {
        u8 key_val = KEY_Scan(0);
        if(key_val != 0)
        {
            printf("\r\nkey:%d is pressed.", key_val);
        }
    }
    #endif

    
    //EXTIX_Init();

    //Message_init(Message_handler);

    #if 0
    TIM3_PWM_Init(999,72);    //不分频。PWM频率=72000/72000=80Khz
    TIM_SetCompare1(TIM3,50);//初始值为0	
    TIM_SetCompare2(TIM3,50);//初始值为0	
    TIM_SetCompare3(TIM3,50);//初始值为0	
    #else
    osal_init_system();

    #endif
    
    //Adc_Init();		  		//ADC初始化
	
    printf("\r\nrequest ble...");

    #if 0
    printf("\r\n strcmp:%d", strcmp(str1, str2));
    printf("\r\n strcmp2:%d", strcmp(str3, str4));
    #endif
    
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
    			TIM_SetCompare1(TIM4,pwmval); 		//输出
    		}else if(key_val==7)	
    		{
    			if(pwmval>10)pwmval-=10;
    			else pwmval=0;
                TIM_SetCompare2(TIM3,pwmval);
    			TIM_SetCompare1(TIM4,pwmval); 		//输出
    		}
        }
        #endif
    }

    #endif

    

    osal_start_system();
}

