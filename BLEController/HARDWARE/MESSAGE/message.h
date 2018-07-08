#ifndef __MESSAGE_H
#define __MESSAGE_H	

#include "uart2.h"
#include "type.h"

#define MSG_STX   'A'
#define MSG_ETX   '#'
#define MSG_MAX_SIZE   (32)

#define MSG_MCU_IS_READY "*AT+MCU_IS_READY#"
#define MSG_BLE_IS_READY "*AT+BLE_IS_READY#"
#define MSG_BLE_ACK "*BLE_ACK#"
#define MSG_AT_LED "AT+LED"


#define MESSAGE_RECV_EVT                               0x0001


typedef enum MSG_Q_STATE {
    MSG_Q_STATE_EMPTY = 0,
    MSG_Q_STATE_NORMAL,
    MSG_Q_STATE_FULL,
} MSG_Q_STATE_e;

typedef struct COMM_MSG {
    int wp;
    unsigned char content[MSG_MAX_SIZE];
    int state;
} COMM_MSG_t;



#define MSG_QUEUE_SIZE   (10)

typedef struct COMM_MSG_QUEUE {
    int rp;
    int wp;
    int size;
    MSG_Q_STATE_e state;
    COMM_MSG_t* msg_list;
} COMM_MSG_QUEUE_t;


typedef int (*message_handler)(COMM_MSG_t* msg);


void Message_init(uint8 task_id);

void Message_send(unsigned char *buff, int length);

int Message_process(void);

uint16 Message_ProcessEvent( uint8 task_id, uint16 events );


#endif




