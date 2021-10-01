#ifndef __WS2812B_H
#define __WS2812B_H

#include "stm32f1xx_hal.h"
#include "main.h"

void shift_map(uint8_t *map, uint16_t nb_of_led);
void set_one_led_color_intensity(uint16_t ledPos, uint8_t r, uint8_t g, uint8_t b, uint8_t intensity);
void all_led_intensity_increase(uint8_t intensity);
void set_one_led_intensity_increase(uint16_t ledPos, uint8_t intensity);
void set_one_led(uint16_t ledPos, uint8_t r, uint8_t g, uint8_t b, uint8_t intensity);
void set_Color(uint8_t r, uint8_t g, uint8_t b, uint8_t intensity);
void set_Color_rainbow(uint8_t intensity);
void ledUpdate();

#endif /* __WS2812B_H */
