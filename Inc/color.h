#ifndef __COLOR_H
#define __COLOR_H

#include "stm32f1xx_hal.h"
#include "color.h"
#include "main.h"

void rainbow(uint8_t* r, uint8_t* g, uint8_t* b);

uint8_t get_G(uint8_t ledPos);
uint8_t get_R(uint8_t ledPos);
uint8_t get_B(uint8_t ledPos);

#endif /* __COLOR_H */
