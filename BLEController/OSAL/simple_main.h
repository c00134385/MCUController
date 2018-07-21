#ifndef _SIMPLE_MAIN__
#define _SIMPLE_MAIN__

#include "type.h"

#define SIMPLE_EVENT_INIT      (0x0001)   // power on off
#define SIMPLE_EVENT_POWER     (0x0002)   // power on off
#define SIMPLE_EVENT_TRIGGER   (0x0004)   // run /stop
#define SIMPLE_EVENT_READ_STATE      (0x0008)   // run /stop
#define SIMPLE_EVENT_SAVE_STATE     (0x0010)   // run /stop
#define SIMPLE_EVENT_MODE_CHANGE     (0x0020)   // run /stop

#define SIMPLE_EVENT_FREQ_INC        (0x0040)   // freq+
#define SIMPLE_EVENT_FREQ_DEC        (0x0080)   // freq-
#define SIMPLE_EVENT_MODE_INC        (0x0100)   // freq+
#define SIMPLE_EVENT_MODE_DEC        (0x0200)   // freq-
#define SIMPLE_EVENT_TIME_INC        (0x0400)   // freq+
#define SIMPLE_EVENT_TIME_DEC        (0x0800)   // freq-
#define SIMPLE_EVENT_NOTIFY_ALL      (0x1000)   // freq-





extern uint8 Simple_TaskID;               // 主机任务
void Simple_Init(uint8 task_id);
uint16 Simple_ProcessEvent(uint8 task_id, uint16 events);


#endif
