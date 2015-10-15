#include <ctype.h>

int strcasecmp(const char *s1, const char *s2)
{
  unsigned char *_s1 = (unsigned char *)s1;
  unsigned char *_s2 = (unsigned char *)s2;
  while (*_s1 && *_s2)
    if (!(*_s1 == *_s2 || tolower(*_s1) == tolower(*_s2)))
      break;
    else
      _s1++, _s2++;

  return tolower(*_s1) - tolower(*_s2);
}
