#include "string.h"

size_t strcpy(char* dst, const char* src)
{
  return (strncpy(dst, SIZE_MAX, src));
}

size_t strncpy(char* dst, size_t len, const char* src)
{
  size_t i = 0; 
  if ( (dst == NULL) || (src == NULL) || (len == 0) )
  {
    return (0);
  }

  dst[i] = '\0';
  while ( (src[i] != '\0') && (i < (len - 1)) )
  {
    dst[i] = src[i];
    i++;
    dst[i] = '\0';
  }

  return (i);

}

int strcmp(const char* s1, const char* s2)
{
  if (s1 == NULL)
  {
    if (s2 == NULL)
    {
      return (0);
    }
    else
    {
      return (-1);
    }
  }
  if (s2 == NULL)
  {
    return (1);
  }

  int i = 0;
  while (s1[i] != '\0')
  {
    if (s2[i] == '\0')
    {
      return (1);
    } 
    if (s1[i] < s2[i])
    {
      return (-1);
    }
    else if (s1[i] > s2[i])
    {
      return (1);
    }

    i++;
  }

  if (s2[i] == '\0')
  {
    return (0);
  }
  
  return (-1);
}

char* strstr(char* haystack, const char* needle)
{
  char* i = haystack;
  char* i2 = haystack;
  const char* j = needle;

  if ( (needle == NULL) || (haystack == NULL) )
  {
    return (NULL);
  }

  while (*i != '\0')
  {
    i2 = i;
    j = needle;
    while (*j != '\0')
    {
      //if i2 is NULL that means there aren't enough
      // characters in the haystack left to match the needle
      if (*i2 == '\0')
      {
        return (NULL);
      }
      if (*i2 != *j) 
      {
        break;
      }
      i2++;
      j++;  
    }

    //if we are here then the comparisons ended
    // if we ended because we have reached the end of needle
    // then just return i
    if (*j == '\0')
    {
      return (i); 
    }
    i++;
  }
  
  return (NULL);
}

//lazy implementation
char* strrstr(char* haystack, const char* needle)
{
  char* ret = NULL;
  char* last = NULL;
  size_t i = 0;

  do
  {
    ret = last;
    last = strstr(haystack + i, needle);
    i++;
  } while (last != NULL);

  return (ret);
}

char* strchr(char* haystack, char needle)
{
  char* ret = haystack;

  if (haystack == NULL)
  {
    return (NULL);
  }

  while ( *ret != '\0' )
  {
    if (*ret == needle)
    {
      return (ret);
    }
    ret++;
  }

  return (NULL);
}

char* strrchr(char* haystack, char needle)
{
  char* ret = haystack;
  char* temp = NULL;

  if (haystack == NULL)
  {
    return (NULL);
  }

  while( (*ret != '\0') )
  {
    if (*ret == needle)
    {
      temp = ret;
    }
    ret++;  
  }

  return (temp);
}

size_t strlen(const char* str)
{
  size_t ret = 0; 
  if (str == NULL)
  {
    return (0);
  }
  for (ret = 0; str[ret] != '\0'; ret++)
  {
  }
  return (ret);
}


/**
 * The maximum unsigned value is 4294967295 which is 0xFFFFFFFF
 * So the idea is to read in up to 9 digits and then convert that
 * into a uint64_t. We need a uint64_t because 9999999999 will overflow
 * uint32_t. 
 *
 * A 0 is returned - either because that is the actual number or because
 * the first 9 characters are not digits (NULL, '.' and ',' are all
 * terminal characters). Any subsequent characters are
 * simply ignored.
*/
uint32_t strToUint32(const char* str)
{
  int i = 0;
  uint64_t temp64 = 0;
  uint32_t temp = 0;

  if (str == NULL)
  {
    return (0);
  }

  while ( (str[i] >= '0') && (str[i] <= '9') )
  {
    temp = str[i] - '0';
    temp64 *= 10;
    temp64 += temp;
    i++;
  }

  return ((uint32_t)temp64);
}
