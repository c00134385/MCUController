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

void PWM_Init(void);
void PWM_Set(uint8 id, uint8 level);
uint8 PWM_Get(uint8 id);
void PWM_level_up(uint8 id);
void PWM_level_down(uint8 id);


#endif
