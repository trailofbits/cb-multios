#include <libcgc.h>
#include <stdlib.h>
#include "strncmp.h"

int strncmp(char *s1, char *s2, int n)
{
  while (*s1 && *s2 && n--)
  {
    if (*s1 != *s2)
      break;
    else
      s1++, s2++;
  }
  if (n == 0)
    return 0;
  return *s2 - *s1;
}

