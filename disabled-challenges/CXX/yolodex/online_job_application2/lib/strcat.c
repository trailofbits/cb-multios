#include "cgc_string.h"

char *cgc_strcat(char *dest, const char *src)
{
  cgc_strcpy(dest + cgc_strlen(dest), src);
  return dest;
}
