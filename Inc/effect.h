#ifndef __EFFECT_H
#define __EFFECT_H

#include "stm32f1xx_hal.h"
#include "main.h"

void k2000(uint8_t r, uint8_t g, uint8_t b, uint8_t lenght, uint8_t intensity);
void k2000_fix_color_effect(uint8_t R, uint8_t G, uint8_t B, uint8_t lenght, uint8_t intensity);
void color_rainbow_effect();
void k2000_rainbow_effect();

#endif /* __EFFECT_H */
