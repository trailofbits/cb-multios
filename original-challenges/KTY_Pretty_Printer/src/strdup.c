#include <libcgc.h>
#include <string.h>
#include <stdlib.h>
#include "strdup.h"

char* strdup(char *s)
{
  int sz = 0;
  if (s)
  {
    sz = cgc_strlen(s) + 1;
    char *d = malloc(sz);
    if (d)
    {
      cgc_memset(d, 0, sz);
      cgc_memcpy(d, s, sz);
      return d;
    }
  }
  return NULL;
}
