#include "libcgc.h"
#include "cgc_string.h"
#include "cgc_stdlib.h"
#include "cgc_strdup.h"

char* cgc_strdup(char *s)
{
  int sz = 0;
  if (s)
  {
    sz = cgc_strlen(s) + 1;
    char *d = cgc_malloc(sz);
    if (d)
    {
      cgc_memset(d, 0, sz);
      cgc_memcpy(d, s, sz);
      return d;
    }
  }
  return NULL;
}
