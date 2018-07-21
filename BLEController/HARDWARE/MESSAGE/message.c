#include "message.h"
#include "led.h"
#include "action.h"
#include "simple_main.h"

uint8 Message_TaskID;


#define INPUT_BUFFER_SIZE            (32) /* size of the local packet buffer */

static int input_buf_index = 0;
static unsigned char input_buf[INPUT_BUFFER_SIZE];

static COMM_MSG_QUEUE_t msg_queue;

message_handler handler = NULL;

int queue_lock = 0;


void msg_queue_init(void)
{
    int i = 0;
    msg_queue.rp = 0;
    msg_queue.wp = 0;
    msg_queue.state = MSG_Q_STATE_EMPTY;
    msg_queue.size = MSG_QUEUE_SIZE;
    msg_queue.msg_list = (COMM_MSG_t*)malloc(sizeof(COMM_MSG_t) * MSG_QUEUE_SIZE);

    for(i = 0; i < MSG_QUEUE_SIZE; i ++)
    {
        COMM_MSG_t* msg = &msg_queue.msg_list[i];
        msg->state = 0;
        msg->wp = 0;
    }    
}

COMM_MSG_t* msg_queue_get_empty(void)
{
    COMM_MSG_t* msg = NULL;
    if(MSG_Q_STATE_FULL != msg_queue.state)
    {
        msg = &msg_queue.msg_list[msg_queue.rp];
    }
    else
    {
        printf("\r\n L:%d pelco msg queue is full.", __LINE__);
    }

    return msg;
}

void msg_queue_push(void)
{
    msg_queue.wp ++;
    msg_queue.wp %= msg_queue.size;
    if(msg_queue.rp == msg_queue.wp)
    {
        msg_queue.state = MSG_Q_STATE_FULL;
    }
    else
    {
        msg_queue.state = MSG_Q_STATE_NORMAL;
    }

    osal_set_event(Message_TaskID, MESSAGE_RECV_EVT);
}

COMM_MSG_t* msg_queue_pull(void)
{
    COMM_MSG_t* msg = NULL;
    
    if(MSG_Q_STATE_EMPTY == msg_queue.state)
    {
        return NULL;
    }

    msg = &msg_queue.msg_list[msg_queue.rp++];
    msg_queue.rp %= msg_queue.size;
    if(msg_queue.wp == msg_queue.rp)
    {
        msg_queue.state = MSG_Q_STATE_EMPTY;
    }
    else
    {
        msg_queue.state = MSG_Q_STATE_NORMAL;
    }
    return msg;
}


void uart_input_byte(unsigned char byte) {
    //input_buf[input_buf_index++] = byte;

    static COMM_MSG_t* msg = NULL;
    static unsigned char lastbyte = 0;

    //printf("\r\n%c",byte);
    
    if(NULL == msg && byte == MSG_STX)
    {
        msg = msg_queue_get_empty();
        if(NULL == msg)
        {
            return;
        }
        msg->wp = 0;
        return;
    }

    if((MSG_ETX == byte) && (msg != NULL))
    {
        msg->content[msg->wp++] = '\0';
        msg_queue_push();
        msg = NULL;
        return;
    }

    if(msg != NULL) 
    {
        #if 0
        if(MSG_STX == byte)
        {
            msg->wp = 0;
            msg->content[msg->wp++] = byte;
        }
        else
        {
            msg->content[msg->wp++] = byte;
            msg->wp %= MSG_MAX_SIZE;
        }
        #endif
        msg->content[msg->wp++] = byte;
        msg->wp %= MSG_MAX_SIZE;
    }
    
}

void Message_init(uint8 task_id)
{
    //handler = h;
    Message_TaskID = task_id;
    
    msg_queue_init();
    
    UART2_Configuration();
    uart2_set_input_byte_callback(uart_input_byte);    
}

void Message_send(unsigned char *msg, int length)
{
    uart2_comm_write(msg, length);
}

void print_message(COMM_MSG_t* msg)
{
    int i = 0;
    printf("\r\n msg_len:%d msg:", msg->wp);
    for(i = 0; i < msg->wp; i ++)
    {
        printf("%c", msg->content[i]);
    }
    printf("\r\n");
}

bool check_message(COMM_MSG_t* msg)
{
    if(msg->wp <= 0)
    {
        return false;
    }

    if((msg->content[msg->wp - 1] == '\0'))
    {
        int pos = strstr(msg->content, "AT+MCU+");
		//printf("pos:%d", pos);
		//printf("original is:%s", msg->content);
		if (pos > 0) {
			//printf("found the string '%s' in '%s' at position: %ld; result: %s\n", "AT+MCU+", msg->content, pos - (int)(msg->content), pos);
			
			return true;
		} else {
			//printf("the string '%s' was not found in '%s'\n", "AT+MCU+", msg->content);
			return false;
		}
        
    }
    else
    {
        return false;
    }

    #if 0
    if((msg->content[0] == MSG_STX) && (msg->content[msg->wp - 1] == '\0'))
    {
        return true;
    }
    else
    {
        return false;
    }
    #endif
}


COMM_MSG_t* pull_message(void)
{
    COMM_MSG_t* msg = NULL;
    if(queue_lock == 1)
    {
        return NULL;
    }
    
    if(MSG_Q_STATE_EMPTY == msg_queue.state)
    {
        return NULL;
    }

    
    msg = &msg_queue.msg_list[msg_queue.rp++];
    
    msg_queue.rp %= msg_queue.size;
    if(msg_queue.wp == msg_queue.rp)
    {
        msg_queue.state = MSG_Q_STATE_EMPTY;
    }
    else
    {
        msg_queue.state = MSG_Q_STATE_NORMAL;
    }
    return msg;
}

int Message_process(void)
{
    
    COMM_MSG_t* msg = NULL;

    //printf("\r\n wp:%d, rp:%d size:%d state:%d", msg_queue.wp, msg_queue.rp, msg_queue.size, msg_queue.state);
    
    msg = msg_queue_pull();
    if(NULL != msg)
    {
        printf("\r\n msgLen:%d", msg->wp);
        print_message(msg);
        
        if(handler && check_message(msg))
        {
            handler(msg);
        }

        msg->wp = 0;
    }
    return 0;
}

u8 str_cmp(u8 *p1,u8 *p2,u8 len)
{
  u8 i=0;
  while(i<len){
    if(p1[i]!=p2[i])
      return 0;
    i++;
  }
  return 1;
}


int Message_handler(COMM_MSG_t* msg)
{
    unsigned char bytes[20];
    if(!strcmp(msg->content, "AT+MCU+ONOFF"))
    {
        // do something
        //ACTION_OnOff();
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_POWER);
    }
    else if(!strcmp(msg->content, "AT+MCU+STARTSTOP"))
    {
        // do something
        ACTION_Key4();
    }
    else if(!strcmp(msg->content, "AT+MCU+FREQ+"))
    {
        // do something
        //PWM_level_up(0);
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_FREQ_INC);
    }
    else if(!strcmp(msg->content, "AT+MCU+FREQ-"))
    {
        // do something
        //PWM_level_down(0);
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_FREQ_DEC);
    }
    else if(!strcmp(msg->content, "AT+MCU+AUTO_T+"))
    {
        // do something
        //PWM_level_up(1);
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_MODE_INC);
    }
    else if(!strcmp(msg->content, "AT+MCU+AUTO_T-"))
    {
        // do something
        //PWM_level_down(1);
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_MODE_DEC);
    }
    else if(!strcmp(msg->content, "AT+MCU+TIME+"))
    {
        // do something
        //PWM_level_up(2);
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_TIME_INC);
    }
    else if(!strcmp(msg->content, "AT+MCU+TIME-"))
    {
        // do something
        //PWM_level_down(2);
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_TIME_DEC);
    }
    else if(!strcmp(msg->content, "AT+MCU+AUTO_L"))
    {
        // do something
        ACTION_Key1();
    }
    else if(!strcmp(msg->content, "AT+MCU+MANUAL"))
    {
        // do something
        ACTION_Key3();
    }
    else if(!strcmp(msg->content, "AT+MCU+LEVEL"))
    {
        // do something
        ACTION_Key2();
    }
    else if(!strcmp(msg->content, "AT+MCU+ALL"))
    {
        // do something
        printf("\r\n notify all message...");
        #if 0
        LED_Notify();
        delay_ms(100);
        PWM_Notify(1);
        delay_ms(100);
        PWM_Notify(2);
        delay_ms(100);
        PWM_Notify(3);
        #endif
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_NOTIFY_ALL);
    }
    else
    {
        printf("\r\n invalid message...");
    }    
    return 0;
}


uint16 Message_ProcessEvent( uint8 task_id, uint16 events )
{
    COMM_MSG_t* msg = NULL;
    if( events & MESSAGE_RECV_EVT)
    {
        msg = msg_queue_pull();
        if(NULL != msg)
        {
            printf("\r\n msgLen:%d", msg->wp);
            print_message(msg);
            
            if(check_message(msg))
            {
                Message_handler(msg);
            }

            msg->wp = 0;
        }
        return (events ^ MESSAGE_RECV_EVT);
    }
    
    return events;
}


