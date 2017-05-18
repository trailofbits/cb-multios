#include "cgc_ctype.h"

int cgc_strcasecmp(const char *s1, const char *s2)
{
  unsigned char *_s1 = (unsigned char *)s1;
  unsigned char *_s2 = (unsigned char *)s2;
  while (*_s1 && *_s2)
    if (!(*_s1 == *_s2 || cgc_tolower(*_s1) == cgc_tolower(*_s2)))
      break;
    else
      _s1++, _s2++;

  return cgc_tolower(*_s1) - cgc_tolower(*_s2);
}
