#include "ws2812b.h"


/**
  * @brief  Start DMA and PWN, update led color, wait until DMA transfert end
  * @note   None
  * @param  None
  * @retval None
  */
void ledUpdate()
{
  HAL_TIM_PWM_Start_DMA_UPDATE(&htim1, TIM_CHANNEL_3, (uint8_t *)&map[0], RAW_BYTES_PER_LED * CONF_BYTE_PER_LED * NB_OF_LEDS + RESET_PULSE);
  dataSend = 0;
  while (!dataSend);
}


/**
  * @brief  Update map on one led with color and intensity
  * @note   None
  * @param  None
  * @retval None
  */
void set_one_led_color_intensity(uint16_t ledPos, uint8_t r, uint8_t g, uint8_t b, uint8_t intensity)
{
  r = (uint8_t)((float)r * (float)intensity / (float)100);
  g = (uint8_t)((float)g * (float)intensity / (float)100);
  b = (uint8_t)((float)b * (float)intensity / (float)100);
  set_one_led(ledPos, r, g, b, intensity);
}

/**
  * @brief  Take color code and put it into map for 1 led so it can be transfert by DMA to CC register to generate 1 and 0
  * @note   None
  * @param  None
  * @retval None
  */
void set_one_led(uint16_t ledPos, uint8_t r, uint8_t g, uint8_t b, uint8_t intensity)
{
  map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED] = (g >> 7 & 1 ? CC_1 : CC_0) ; // green
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 1] = (g >> 6 & 1 ? CC_1 : CC_0) ;
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 2] = (g >> 5 & 1 ? CC_1 : CC_0) ;
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 3] = (g >> 4 & 1 ? CC_1 : CC_0) ;
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 4] = (g >> 3 & 1 ? CC_1 : CC_0) ;
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 5] = (g >> 2 & 1 ? CC_1 : CC_0) ;
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 6] = (g >> 1 & 1 ? CC_1 : CC_0) ;
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 7] = (g >> 0 & 1 ? CC_1 : CC_0) ;
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 8] = (r >> 7 & 1 ? CC_1 : CC_0) ; // red
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 9] = (r >> 6 & 1 ? CC_1 : CC_0) ;
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 10] = (r >> 5 & 1 ? CC_1 : CC_0) ;
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 11] = (r >> 4 & 1 ? CC_1 : CC_0) ;
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 12] = (r >> 3 & 1 ? CC_1 : CC_0) ;
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 13] = (r >> 2 & 1 ? CC_1 : CC_0) ;
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 14] = (r >> 1 & 1 ? CC_1 : CC_0) ;
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 15] = (r >> 0 & 1 ? CC_1 : CC_0) ;
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 16] = (b >> 7 & 1 ? CC_1 : CC_0) ; // blue
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 17] = (b >> 6 & 1 ? CC_1 : CC_0) ;
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 18] = (b >> 5 & 1 ? CC_1 : CC_0) ;
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 19] = (b >> 4 & 1 ? CC_1 : CC_0) ;
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 20] = (b >> 3 & 1 ? CC_1 : CC_0) ;
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 21] = (b >> 5 & 1 ? CC_1 : CC_0) ;
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 22] = (b >> 1 & 1 ? CC_1 : CC_0) ;
      map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 23] = (b >> 0 & 1 ? CC_1 : CC_0) ;  
}


/**
  * @brief  Take color code and put it into map for all led so it can be transfert by DMA to CC register to generate 1 and 0
  * @note   None
  * @param  None
  * @retval None
  */
void set_Color(uint8_t r, uint8_t g, uint8_t b, uint8_t intensity)
{
  r = (uint8_t)((float)r * (float)intensity / (float)100);
  g = (uint8_t)((float)g * (float)intensity / (float)100);
  b = (uint8_t)((float)b * (float)intensity / (float)100);
  for(uint8_t i = 0; i < NB_OF_LEDS; i++)
    {
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED] = (g >> 7 & 1 ? 15 : 8) ; // green
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 1] = (g >> 6 & 1 ? 15 : 8) ;
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 2] = (g >> 5 & 1 ? 15 : 8) ;
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 3] = (g >> 4 & 1 ? 15 : 8) ;
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 4] = (g >> 3 & 1 ? 15 : 8) ;
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 5] = (g >> 2 & 1 ? 15 : 8) ;
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 6] = (g >> 1 & 1 ? 15 : 8) ;
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 7] = (g >> 0 & 1 ? 15 : 8) ;
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 8] = (r >> 7 & 1 ? 15 : 8) ; // red
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 9] = (r >> 6 & 1 ? 15 : 8) ;
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 10] = (r >> 5 & 1 ? 15 : 8) ;
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 11] = (r >> 4 & 1 ? 15 : 8) ;
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 12] = (r >> 3 & 1 ? 15 : 8) ;
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 13] = (r >> 2 & 1 ? 15 : 8) ;
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 14] = (r >> 1 & 1 ? 15 : 8) ;
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 15] = (r >> 0 & 1 ? 15 : 8) ;
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 16] = (b >> 7 & 1 ? 15 : 8) ; // blue
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 17] = (b >> 6 & 1 ? 15 : 8) ;
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 18] = (b >> 5 & 1 ? 15 : 8) ;
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 19] = (b >> 4 & 1 ? 15 : 8) ;
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 20] = (b >> 3 & 1 ? 15 : 8) ;
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 21] = (b >> 5 & 1 ? 15 : 8) ;
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 22] = (b >> 1 & 1 ? 15 : 8) ;
      map[RESET_PULSE + i * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 23] = (b >> 0 & 1 ? 15 : 8) ;
    }
  map[RAW_BYTES_PER_LED * CONF_BYTE_PER_LED * NB_OF_LEDS + RESET_PULSE - 1] = 0 ;
}


/**
  * @brief  Full the map with color of rainbow
  * @note   Change the number in the segond for th change the resolution of the rainbow
  * @param  None
  * @retval None
  */
void set_Color_rainbow(uint8_t intensity)
{
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;

  for(uint8_t i = 0; i < NB_OF_LEDS; i++)
    {
      for (uint8_t i = 0; i < 26; i++)
	rainbow(&r, &g, &b);
      set_one_led_color_intensity(i, r, g, b, intensity);
    }
  map[RAW_BYTES_PER_LED * CONF_BYTE_PER_LED * NB_OF_LEDS + RESET_PULSE - 1] = 0;
}

/**
  * @brief  Decal all led by one
  * @note   None
  * @param  None
  * @retval None
  */void shift_map(uint8_t *map, uint16_t nb_of_led)
{
  uint8_t first_led[24] = {0, };
  my_memcpy(first_led, &map[RESET_PULSE], RAW_BYTES_PER_LED * CONF_BYTE_PER_LED * sizeof(uint8_t));
  my_memcpy(&map[RESET_PULSE], &map[RESET_PULSE + RAW_BYTES_PER_LED * CONF_BYTE_PER_LED], RAW_BYTES_PER_LED * CONF_BYTE_PER_LED * (NB_OF_LEDS - 1) * sizeof(uint8_t));
  my_memcpy(&map[RAW_BYTES_PER_LED * CONF_BYTE_PER_LED * (NB_OF_LEDS - 1) + RESET_PULSE], first_led, RAW_BYTES_PER_LED * CONF_BYTE_PER_LED * sizeof(uint8_t));
}


/**
  * @brief  Experimentale
  * @note   Note use
  * @param  None
  * @retval None
  */
void all_led_intensity_increase(uint8_t intensity)
{
  for(uint8_t i = 0; i < NB_OF_LEDS; i++)
    set_one_led_intensity_increase(i, intensity);
}

/**
  * @brief  Experimentale
  * @note   Note use
  * @param  None
  * @retval None
  */
void set_one_led_intensity_increase(uint16_t ledPos, uint8_t intensity)
{
  float r = get_R(ledPos);
  float g = get_G(ledPos);
  float b = get_B(ledPos);

  r *= (float)(intensity + 100) / (float)100;
  g *= (float)(intensity + 100) / (float)100;
  b *= (float)(intensity + 100) / (float)100;

  if (r > 255)
    r = 255;
  if (g > 255)
    g = 255;
  if (b > 255)
    b = 255;
  if (r < 0)
    r = 0;
  if (g < 0)
    g = 0;
  if (b < 0)
    b = 0;
    
  set_one_led(ledPos, (uint8_t)r, (uint8_t)g, (uint8_t)b, 100);
}
