#ifndef __MAIN_H
#define __MAIN_H

#define RAW_BYTES_PER_LED	8	// 8 bit color
#define CONF_BYTE_PER_LED	3	// RGB
#define NB_OF_LEDS		60	// Number of WS2812B
#define RESET_PULSE		100	// First part force 0, reset signal
#define CC_0			8	// CCR bit 0
#define CC_1			15	// CCR bit 1

#include "stm32f1xx_hal.h"
#include "ws2812b.h"
#include "color.h"
#include "effect.h"
#include "timer.h"
#include "dma.h"
#include "tools.h"

extern TIM_HandleTypeDef htim1;
extern uint8_t dataSend;
extern uint8_t map[RAW_BYTES_PER_LED * CONF_BYTE_PER_LED * NB_OF_LEDS + RESET_PULSE];

//Handler
void Error_Handler(void);

// Clock
void SystemClock_Config(void);
void MX_TIM1_Init(void);

// IO
void MX_GPIO_Init(void);

#endif /* __MAIN_H */
