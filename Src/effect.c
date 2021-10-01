#include "effect.h"

void k2000(uint8_t r, uint8_t g, uint8_t b, uint8_t lenght, uint8_t intensity)
{
  static uint8_t posK2000 = 0;

  r = (uint8_t)((float)r * (float)intensity / (float)100);
  g = (uint8_t)((float)g * (float)intensity / (float)100);
  b = (uint8_t)((float)b * (float)intensity / (float)100);
  // Si la taille de la trainee est superieur au nombre total de led
  if (lenght > NB_OF_LEDS)
    lenght = NB_OF_LEDS;
  // reset all
  for(uint8_t i = 0; i < NB_OF_LEDS; i++)
    set_one_led(i, 0, 0, 0, 100);
  uint8_t tmp_intensity;
  for(uint8_t i = 0; i < lenght; i++)
    {
      // Calculate intensity first half
      if ((float)i > (float)lenght / (float)2)
	{
	  float halfLenght = (float)lenght / (float)2;
	  tmp_intensity = (uint8_t)(((float)(lenght - i) / (float)halfLenght) * (float)100);
	}
      // Calculate intensity second half
      else if ((float)i < (float)lenght / (float)2)
	{
	  tmp_intensity = (uint8_t)(((float)(i ? i * 2 : 0) / (float)lenght) * (float)100);
	}
      // Middle point to max intensity
      else
	tmp_intensity = 100;
      // Minimum brightness
      if (tmp_intensity == 0)
	tmp_intensity = 2;
      // if led pos and offset is more than number of led go to start
      if (i + posK2000 >= NB_OF_LEDS)
	set_one_led_color_intensity(i + posK2000 - NB_OF_LEDS, r, g, b, tmp_intensity);
      // led pos and offset is in the range of led number
      else
	set_one_led_color_intensity(posK2000 + i, r, g, b, tmp_intensity);
    }
  // Incremente offset
  posK2000++;
  // One cycle one done back to start again
  if (posK2000 == NB_OF_LEDS)
    {
      posK2000 = 0;
    }
}

void color_rainbow_effect()
{
  // Pre calculate rainbow color
  set_Color_rainbow(100);
  while (1)
    {
      // Juste decal color one led by one led last led comme back to the start
      shift_map(map, NB_OF_LEDS);
      ledUpdate();
      HAL_Delay(20);  
    }
}

void k2000_rainbow_effect()
{
  uint8_t R = 255;
  uint8_t G = 0;
  uint8_t B = 0;
  while (1)
  {
    // Speed of changing color
    rainbow(&R, &G, &B);
    rainbow(&R, &G, &B);
    rainbow(&R, &G, &B);
    rainbow(&R, &G, &B);
    rainbow(&R, &G, &B);
    rainbow(&R, &G, &B);
    rainbow(&R, &G, &B);
    rainbow(&R, &G, &B);
 
    // Aply light to only few led
    k2000(R, G, B, 4, 100);
 
    ledUpdate();
    HAL_Delay(20);
  }
}

void k2000_fix_color_effect(uint8_t R, uint8_t G, uint8_t B, uint8_t lenght, uint8_t intensity)
{
  while (1)
  {
    k2000(R, G, B, lenght, intensity);
    ledUpdate();
    HAL_Delay(20);
  }
}
