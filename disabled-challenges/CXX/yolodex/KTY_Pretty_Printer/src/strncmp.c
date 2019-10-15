#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_strncmp.h"

int cgc_strncmp(char *s1, char *s2, int n)
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

