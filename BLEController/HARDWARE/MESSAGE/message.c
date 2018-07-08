#include "message.h"
#include "led.h"

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
    
    if(NULL == msg)
    {
        msg = msg_queue_get_empty();
        if(NULL == msg)
        {
            return;
        }
        msg->wp = 0;
    }

    if((MSG_ETX == byte) && (msg != NULL))
    {
        msg->content[msg->wp++] = byte;
        msg_queue_push();
        msg = NULL;
        return;
    }

    if(msg != NULL) 
    {
        if(MSG_STX == byte)
        {
            msg->wp = 0;
            msg->content[msg->wp++] = byte;
            //msg->wp %= MSG_MAX_SIZE;
        }
        else
        {
            msg->content[msg->wp++] = byte;
            msg->wp %= MSG_MAX_SIZE;
        }
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
    
    if((msg->content[0] == MSG_STX) && (msg->content[msg->wp - 1] == MSG_ETX))
    {
        return true;
    }
    else
    {
        return false;
    }
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

void handle_message(COMM_MSG_t* msg)
{
    printf("\r\n handle...");
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
    if(str_cmp(msg->content, "AT+BTN1", 7))
    {
        LED14 = 0;
    }
    else if(str_cmp(msg->content, "AT+BTN2", 7))
    {
        LED14 = 1;
    }
    else if(str_cmp(msg->content, "AT+BTN3", 7))
    {
        LED15 = 0;
    }
    else if(str_cmp(msg->content, "AT+BTN4", 7))
    {
        LED15 = 1;
    }
    else if(str_cmp(msg->content, "AT+BTN5", 7))
    {
        LED16 = 0;
    }
    else if(str_cmp(msg->content, "AT+BTN6", 7))
    {
        LED16 = 1;
    }
    else if(str_cmp(msg->content, "AT+BTN7", 7))
    {
        LED17 = 0;
    }
    else if(str_cmp(msg->content, "AT+BTN8", 7))
    {
        LED17 = 1;
    }
    else
    {
        printf("\r\nincorrect msg.");
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


