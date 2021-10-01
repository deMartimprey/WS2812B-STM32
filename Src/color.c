#include "color.h"

/**
  * @brief  Take color as pointeurs and set the next color in the rainbow
  * @note   Depend of the static variable, not the color you give it. Start by defaut with pur RED
  * @param  None
  * @retval None
  */
void rainbow(uint8_t* r, uint8_t* g, uint8_t* b)
{
  static uint8_t R = 255;
  static uint8_t G = 0;
  static uint8_t B = 0;
  static uint8_t part = 0;

  if (part == 0)
    {
      G++;
      if (G == 255)
	part = 1;
    }
  else if (part == 1)
    {
      R--;
      if (R == 0)
	part = 2;
    }
  else if (part == 2)
    {
      B++;
      if (B == 255)
	part = 3;
    }
  else if (part == 3)
    {
      G--;
      if (G == 0)
	part = 4;
    }
  else if (part == 4)
    {
      R++;
      if (R == 255)
	part = 5;
    }
  else if (part == 5)
    {
      B--;
      if (B == 0)
	part = 0;
    }
  *r = R;
  *g = G;
  *b = B;
}

/**
  * @brief  Get green color of one led in the map
  * @note   Note use
  * @param  None
  * @retval None
  */
uint8_t get_G(uint8_t ledPos)
{
  uint8_t G = 0;

  G |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 0] == CC_1 ? 1 : 0) << 7;
  G |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 1] == CC_1 ? 1 : 0) << 6;
  G |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 2] == CC_1 ? 1 : 0) << 5;
  G |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 3] == CC_1 ? 1 : 0) << 4;
  G |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 4] == CC_1 ? 1 : 0) << 3;
  G |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 5] == CC_1 ? 1 : 0) << 2;
  G |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 6] == CC_1 ? 1 : 0) << 1;
  G |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 7] == CC_1 ? 1 : 0) << 0;
  return G;
}

/**
  * @brief  Get red color of one led in the map
  * @note   Note use
  * @param  None
  * @retval None
  */
uint8_t get_R(uint8_t ledPos)
{
  uint8_t R = 0;

  R |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 8] == CC_1 ? 1 : 0) << 7;
  R |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 9] == CC_1 ? 1 : 0) << 6;
  R |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 10] == CC_1 ? 1 : 0) << 5;
  R |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 11] == CC_1 ? 1 : 0) << 4;
  R |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 12] == CC_1 ? 1 : 0) << 3;
  R |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 13] == CC_1 ? 1 : 0) << 2;
  R |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 14] == CC_1 ? 1 : 0) << 1;
  R |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 15] == CC_1 ? 1 : 0) << 0;
  return R;
}

/**
  * @brief  Get blue color of one led in the map
  * @note   Note use
  * @param  None
  * @retval None
  */
uint8_t get_B(uint8_t ledPos)
{
  uint8_t B = 0;

  B |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 16] == CC_1 ? 1 : 0) << 7;
  B |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 17] == CC_1 ? 1 : 0) << 6;
  B |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 18] == CC_1 ? 1 : 0) << 5;
  B |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 19] == CC_1 ? 1 : 0) << 4;
  B |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 20] == CC_1 ? 1 : 0) << 3;
  B |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 21] == CC_1 ? 1 : 0) << 2;
  B |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 22] == CC_1 ? 1 : 0) << 1;
  B |= (map[RESET_PULSE + ledPos * RAW_BYTES_PER_LED * CONF_BYTE_PER_LED + 23] == CC_1 ? 1 : 0) << 0;
  return B;
}
