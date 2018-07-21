/******************************************************************************

 @file  OSAL_SimpleBLEPeripheral.c

 @brief This file contains function that allows user setup tasks

 Group: WCS, BTS
 Target Device: CC2540, CC2541

 *****************************************************************************/

#include "osal_simple.h"
#include "simple_main.h"

#include "key.h"
#include "exti.h"
#include "message.h"
#include "timer.h"
#include "adc.h"
#include "led.h"
#include "myiic.h"
#include "at24cxx.h"

// The order in this table must be identical to the task initialization calls below in osalInitTask.
const pTaskEventHandlerFn tasksArr_peripheral[] =
{
    #if 0
  LL_ProcessEvent,                                                  // task 0
  Hal_ProcessEvent,                                                 // task 1
  HCI_ProcessEvent,                                                 // task 2
#if defined ( OSAL_CBTIMER_NUM_TASKS )
  OSAL_CBTIMER_PROCESS_EVENT( osal_CbTimerProcessEvent ),           // task 3
#endif
  L2CAP_ProcessEvent,                                               // task 4
  GAP_ProcessEvent,                                                 // task 5
  GATT_ProcessEvent,                                                // task 6
  SM_ProcessEvent,                                                  // task 7
  GAPRole_ProcessEvent,                                             // task 8
  GAPBondMgr_ProcessEvent,                                          // task 9
  GATTServApp_ProcessEvent,                                         // task 10
  SimpleBLEPeripheral_ProcessEvent                                  // task 11
  #endif

    KEY_ProcessEvent,
    Message_ProcessEvent,
    Adc_ProcessEvent,
    LED_ProcessEvent,
    Simple_ProcessEvent,
};

static uint8 activeTaskID = TASK_NO_TASK;


uint8 tasksCnt;
uint16 *tasksEvents;
pTaskEventHandlerFn tasksArr[12];

uint8 osal_init_system(void)
{
    uint8 taskID = 0;

    tasksCnt = sizeof( tasksArr_peripheral ) / sizeof( tasksArr_peripheral[0] );  
    memcpy(tasksArr, tasksArr_peripheral, sizeof( tasksArr_peripheral));    

    tasksEvents = (uint16 *)malloc( sizeof( uint16 ) * tasksCnt);
    memset( tasksEvents, 0, (sizeof( uint16 ) * tasksCnt));

    PWM_Init();

    IWDG_Init(4,625);    //¨®?¡¤??¦Ì¨ºy?a64,?????¦Ì?a625,¨°?3?¨º¡À???a1s	
    ACTION_Init();
    IIC_Init();
    AT24CXX_Init();

    KEY_Init(taskID++);
    Message_init(taskID++);
    Adc_Init(taskID++);
    LED_Init(taskID++);
    Simple_Init(taskID++);

    osal_set_event(Simple_TaskID, SIMPLE_EVENT_INIT);
    
    #if 0
    while(1)
    {
        u8 key_val = KEY_Scan(0);
        if(key_val != 0)
        {
            printf("\r\n key:%d is pressed~~", key_val);
        }

        IWDG_Feed();
    }
    #endif
    return 0;
}
void osal_start_system( void )
{
    uint32 count = 0;
    u8 key_val;
    u8 led_val;
    for(;;)
    {
        uint8 idx = 0;
        key_val = KEY_Scan();
        if(key_val != 0)
        {
            //intf("\r\n key:%d is pressed", key_val);
        }

        count ++;
        if(count % 100000 == 0)
        {
            printf(".");
            count = 0;
        }
        
        
        do {
            if (tasksEvents[idx])  // Task is highest priority that is ready.
            {
                break;
            }
        } while (++idx < tasksCnt);

        if (idx < tasksCnt)
        {
            uint16 events;
            events = tasksEvents[idx];
            tasksEvents[idx] = 0;// Clear the Events for this task.

            activeTaskID = idx;
            events = (tasksArr[idx])( idx, events );
            activeTaskID = TASK_NO_TASK;

            tasksEvents[idx] |= events;
        }

        IWDG_Feed();//¨¨?1?WK_UP¡ã¡ä??,?¨°?11¡¤
    }
}


uint8 osal_set_event( uint8 task_id, uint16 event_flag )
{
    tasksEvents[task_id] |= event_flag;
}

uint8 osal_clear_event( uint8 task_id, uint16 event_flag )
{
    tasksEvents[task_id] &= (~event_flag);
}


