#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "type.h"


#if 0
void TIM3_Int_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM5_Cap_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr,u16 psc);
#endif

typedef void (*pTimerHandler)(void);


void TIM2_Int_Init(u16 arr,u16 psc);
void TIM2_Start(pTimerHandler handler);
void TIM2_Stop(void);

void TIM4_Int_Init(u16 arr,u16 psc);

void PWM_Init(void);
void PWM_Set(uint8 id, uint8 level);
void PWM_level_up(uint8 id);
void PWM_level_down(uint8 id);
void PWM_level_reset(uint8 id);
void PWM_Notify(uint8 id);

void PWM_SetMode(u8 mode);
void PWM_SetValue(uint8 id, uint32 value);
void PWM_ValueUp(uint8 id);
void PWM_ValueDown(uint8 id);
void PWM_SetCurrLevel(u8* pCurr);


#endif
