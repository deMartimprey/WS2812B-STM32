#include "tools.h"

void my_memcpy(void *dest, void *src, uint16_t size)
{
  uint8_t *ptr_dest;
  uint8_t *ptr_src;
  uint16_t i;

  i = 0;
  ptr_dest = (uint8_t *)dest;
  ptr_src = (uint8_t *)src;
  while (i < size)
    {
      ptr_dest[i] = ptr_src[i];
      i += 1;
    }
}
