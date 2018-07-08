#ifndef __OSAL_SIMPLE_H
#define __OSAL_SIMPLE_H	

#include "type.h"

/*********************************************************************
 * TYPEDEFS
 */

#define TASK_NO_TASK      0xFF


/*
 * Event handler function prototype
 */
typedef unsigned short (*pTaskEventHandlerFn)( unsigned char task_id, unsigned short event );

//void osalInitTasks( void );

uint8 osal_init_system(void);
void osal_start_system( void );
uint8 osal_set_event( uint8 task_id, uint16 event_flag );

/*
   * Clear a Task Event
   */
uint8 osal_clear_event( uint8 task_id, uint16 event_flag );

    

#endif

