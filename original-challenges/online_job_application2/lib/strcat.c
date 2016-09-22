#include <string.h>

char *strcat(char *dest, const char *src)
{
  strcpy(dest + cgc_strlen(dest), src);
  return dest;
}
