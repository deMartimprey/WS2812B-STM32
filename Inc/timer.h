#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f1xx_hal.h"
#include "main.h"

extern TIM_HandleTypeDef htim1;

// Timer Init
void MX_TIM1_Init(void);

// Callback PWM
void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim);

#endif /* __TIMER_H */
