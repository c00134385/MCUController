#include "simple_main.h"
#include "action.h"
#include "at24cxx.h"

BOOL g_power_on = FALSE;
BOOL g_run = FALSE;

#define VERSION_ADDR  (0)
#define VERSION_SIZE  (32)
#define SIMPLE_STATE_ADDR  (VERSION_ADDR + VERSION_SIZE)

const char* version = "JJ1807";

typedef struct Simple_state_s {
    u16 freq;
    u16 delay;
    u16 grade;
    u16 time;
} Simple_state_t;

Simple_state_t simple_state;

void Simple_read_state(void)
{
    int len = 0;
    len = AT24CXX_Read(SIMPLE_STATE_ADDR, (unsigned char*)&simple_state, sizeof(Simple_state_t));
    if(len != sizeof(Simple_state_t)) {
        printf("\r\n read version from eeprom failed.len:%d", len);
    }
    printf("\r\n freq:%d delay:%d grad:%d time:%d", 
        simple_state.freq, simple_state.delay, simple_state.grade, simple_state.time);
    printf("\r\n 24C02 Read state Finished!");
}

void Simple_write_state(void)
{
    int len = 0;

    len = AT24CXX_Write(SIMPLE_STATE_ADDR, (u8*)&simple_state, sizeof(Simple_state_t));
    if(len != (sizeof(Simple_state_t)))
    {
        printf("\r\n write state value to eeprom failed. len:%d", len);
    }

    printf("\r\n 24C02 Write state Finished!");
}

uint8 Simple_TaskID;
void Simple_Init(uint8 task_id)
{
    char current_version[VERSION_SIZE];
    u8 curr_level[4];
    int len;
    Simple_TaskID = task_id;

    simple_state.freq = 0;
    simple_state.delay = 0;
    simple_state.grade = 0;
    simple_state.time = 0;

    len = AT24CXX_Read(VERSION_ADDR, (unsigned char*)current_version, VERSION_SIZE);
    if(len != 32) {
        printf("\r\n read version from eeprom failed.len:%d", len);
    }
    current_version[VERSION_SIZE - 1] = '\0';

    if(strcmp(version, current_version))
    {
        printf("\r\n not match");
        len = AT24CXX_Write(VERSION_ADDR, (unsigned char*)version, strlen(version) + 1);
        if(len != (strlen(version) + 1))
        {
            printf("\r\n write version to eeprom failed. len:%d", len);
        }

        Simple_write_state();
    }
    else
    {
        printf("\r\n match");
        // read version 
        Simple_read_state();
    }

}



#define CURVE_MAX   (4)
static u8 curr_level[CURVE_MAX];
static u8 max_level[CURVE_MAX];
static u16* p_curve[CURVE_MAX];


static u16 freq_curve[] = {
    17, 34, 52, 71, 90, 110, 131, 152, 175, 199
};

static u16 delay_curve[] = {
    0, 17, 39, 60, 83, 107, 132, 160, 188, 215,
    245, 278, 311, 346, 380, 421, 461, 505, 552, 601,
    655, 705, 770, 833, 899, 999
};

static u16 time_curve[] = {
    0, 18, 35, 53, 75, 89, 112, 136, 158, 179,
    204, 232, 260, 287, 316, 346, 375, 410, 441, 481,
    516, 561, 601, 647, 696, 745, 795, 857, 916, 999
};

static u16 grade_curve[11] = {
    0, 65, 118, 175, 255, 335, 420, 520, 640, 775, 999
};


static u8 curr_mode = 0; // 0:auto   1: manual


void Simple_Reinit(void)
{
    curr_level[0] = 0;
    curr_level[1] = 0;
    curr_level[2] = 0;
    curr_level[3] = 0;
    
    max_level[0] = sizeof(freq_curve)/sizeof(u16);
    max_level[1] = sizeof(delay_curve)/sizeof(u16);
    max_level[2] = sizeof(time_curve)/sizeof(u16);
    max_level[3] = sizeof(grade_curve)/sizeof(u16);

    p_curve[0] = freq_curve;
    p_curve[1] = delay_curve;
    p_curve[2] = time_curve;
    p_curve[3] = grade_curve;

    printf("\r\n %d %d %d %d", max_level[0], max_level[1], max_level[2], max_level[3]);

    curr_level[0] = simple_state.freq;
    curr_level[1] = simple_state.delay;
    curr_level[2] = simple_state.time;
    curr_level[3] = simple_state.grade;
}

void Simple_save_state(void)
{
    simple_state.freq = curr_level[0];
    simple_state.delay = curr_level[1];;
    simple_state.time = curr_level[2];;
    simple_state.grade = curr_level[3];;
    Simple_write_state();
}

void Simple_Notify(uint8 id)
{
    unsigned char bytes[20];
    if(id >= 4)
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

void Simple_Notify_Mode(void)
{
    unsigned char bytes[20];
    
    sprintf(bytes, "AT+BLE+MODE%d\r\n", curr_mode);
    uart2_comm_write(bytes, strlen(bytes)); 
}

void Simple_Notify_Power(void)
{
    unsigned char bytes[20];
    
    sprintf(bytes, "AT+BLE+POWER%d\r\n", g_power_on);
    uart2_comm_write(bytes, strlen(bytes)); 
}

void Simple_level_up(uint8 id)
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
    
    PWM_SetValue(id, p_curve[id_][level]);
    curr_level[id_] = level;
    Simple_Notify(id_);
}


void Simple_level_down(uint8 id)
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
    
    PWM_SetValue(id, p_curve[id_][level]);
    curr_level[id_] = level;
    Simple_Notify(id_);
}


void Simple_recover(void)
{
    uint8 id = 0;
    uint8 id_ = 0;

    PWM_SetValue(id, p_curve[id][curr_level[id]]);
    PWM_Notify(id);
    
    id = 1;
    if(1 == curr_mode)
    {
        id_ = 3;
    }
    else
    {
        id_ = 1;
    }
    PWM_SetValue(id, p_curve[id_][curr_level[id_]]);
    PWM_Notify(id_);
    
    id = 2;
    PWM_SetValue(id, p_curve[id][curr_level[id]]);
    PWM_Notify(id);
}


void Simple_level_reset(uint8 id)
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
    
    PWM_SetValue(id, p_curve[id_][level]);
    curr_level[id_] = level;
    PWM_Notify(id_);
}


uint16 Simple_ProcessEvent(uint8 task_id, uint16 events)
{
    if( events & SIMPLE_EVENT_INIT)
    {
        printf("\r\n L:%d %s()", __LINE__, __FUNCTION__);
        Simple_Reinit();
        //Simple_recover();
        Simple_level_reset(0);
        Simple_level_reset(1);
        Simple_level_reset(2);
        return (events ^ SIMPLE_EVENT_INIT);
    }

    if( events & SIMPLE_EVENT_READ_STATE)
    {
        printf("\r\n L:%d %s()", __LINE__, __FUNCTION__);
        
        return (events ^ SIMPLE_EVENT_READ_STATE);
    }

    if( events & SIMPLE_EVENT_SAVE_STATE)
    {
        printf("\r\n L:%d %s()", __LINE__, __FUNCTION__);
        Simple_save_state();
        return (events ^ SIMPLE_EVENT_SAVE_STATE);
    }
    
    if( events & SIMPLE_EVENT_POWER)
    {
        printf("\r\n L:%d %s()", __LINE__, __FUNCTION__);
        if(g_power_on)
        {
            ACTION_Power_Off();
        }
        else
        {
            ACTION_Power_On();
        }
        g_power_on = (g_power_on)?FALSE:TRUE;
        return (events ^ SIMPLE_EVENT_POWER);
    }

    if( events & SIMPLE_EVENT_TRIGGER)
    {
        printf("\r\n L:%d %s()", __LINE__, __FUNCTION__);
        return (events ^ SIMPLE_EVENT_TRIGGER);
    }

    if( events & SIMPLE_EVENT_MODE_CHANGE)
    {
        u8 mode;
        mode = LED_GetMode();
        if(mode != curr_mode)
        {
            printf("\r\n L:%d %s()", __LINE__, __FUNCTION__);
            printf("mode:%d->%d", curr_mode, mode);
            curr_mode = mode;

            Simple_level_reset(1);
            Simple_Notify_Mode();
        }
        return (events ^ SIMPLE_EVENT_MODE_CHANGE);
    }

    
    if( events & SIMPLE_EVENT_FREQ_INC)
    {
        printf("\r\n L:%d %s()", __LINE__, __FUNCTION__);
        Simple_level_up(0);
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_SAVE_STATE);
        return (events ^ SIMPLE_EVENT_FREQ_INC);
    }


    if( events & SIMPLE_EVENT_FREQ_DEC)
    {
        printf("\r\n L:%d %s()", __LINE__, __FUNCTION__);
        Simple_level_down(0);
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_SAVE_STATE);
        return (events ^ SIMPLE_EVENT_FREQ_DEC);
    }

    if( events & SIMPLE_EVENT_MODE_INC)
    {
        printf("\r\n L:%d %s()", __LINE__, __FUNCTION__);
        Simple_level_up(1);
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_SAVE_STATE);
        return (events ^ SIMPLE_EVENT_MODE_INC);
    }


    if( events & SIMPLE_EVENT_MODE_DEC)
    {
        printf("\r\n L:%d %s()", __LINE__, __FUNCTION__);
        Simple_level_down(1);
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_SAVE_STATE);
        return (events ^ SIMPLE_EVENT_MODE_DEC);
    }

    if( events & SIMPLE_EVENT_TIME_INC)
    {
        printf("\r\n L:%d %s()", __LINE__, __FUNCTION__);
        Simple_level_up(2);
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_SAVE_STATE);
        return (events ^ SIMPLE_EVENT_TIME_INC);
    }


    if( events & SIMPLE_EVENT_TIME_DEC)
    {
        printf("\r\n L:%d %s()", __LINE__, __FUNCTION__);
        Simple_level_down(2);
        osal_set_event(Simple_TaskID, SIMPLE_EVENT_SAVE_STATE);
        return (events ^ SIMPLE_EVENT_TIME_DEC);
    }

    if( events & SIMPLE_EVENT_NOTIFY_ALL)
    {
        printf("\r\n L:%d %s()", __LINE__, __FUNCTION__);
        if(g_power_on)
        {
            LED_Notify();
            delay_ms(100);
            Simple_Notify(0);
            delay_ms(100);
            Simple_Notify(1);
            delay_ms(100);
            Simple_Notify(2);
            delay_ms(100);
            Simple_Notify(3);
        }
        else
        {
            Simple_Notify_Power();
        }
        return (events ^ SIMPLE_EVENT_NOTIFY_ALL);
    }
    
    return events;
}

