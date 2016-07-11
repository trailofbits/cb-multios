#include <libcgc.h>
#include "stdarg.h"
#include "printf.h"
#include "inttypes.h"

#define PRINTF_BUF_SIZE 200

#define _PRINTF_BUF_OVERFLOW_SIZE 56
#define _PRINTF_BUF_SIZE (PRINTF_BUF_SIZE + _PRINTF_BUF_OVERFLOW_SIZE)

typedef struct _PrintfInfo
{
  int fd;
  size_t bufSize; 
  size_t end; 
  size_t count;
  struct _PrintfInfo*  next; 
  char* buf;  
  char _buf[];
} PrintfInfo;

#define INIT_PRINTF_INFO(_pInfo, _fd, _str)	\
do						\
{						\
  (_pInfo)->fd = _fd;				\
  (_pInfo)->buf = _str;                         \
  (_pInfo)->bufSize = PRINTF_BUF_SIZE;		\
  (_pInfo)->end = 0;				\
  (_pInfo)->count = 0;				\
  (_pInfo)->next = NULL;			\
} while(0)					


PrintfInfo* gPrintfHead = NULL;
int gbFlushOnNewline = 0;

void printf_setFlushOnNewline(int bEnabled)
{
  gbFlushOnNewline = bEnabled;
}

/** Returns a pointer to the PrintfInfo struct that contains the buffer
 *    for the current fd. A new struct is created if it doesn't exist.
 *    Note that this function always creates a new one. A different
 *    version that only searches might be a good idea as well.
**/
static PrintfInfo* getPrintfInfo(int fd)
{
  PrintfInfo** pTemp = &gPrintfHead;
  int ret = 0;

  while (*pTemp != NULL)
  {
    if ( (*pTemp)->fd == fd )
    {
      return (*pTemp);
    }
    pTemp = &((*pTemp)->next);
  }

  ret = allocate(sizeof(PrintfInfo) + _PRINTF_BUF_SIZE, 0, (void**)pTemp);

  if (ret != 0)
  {
    _terminate(2);
  }

  INIT_PRINTF_INFO(*pTemp, fd, (*pTemp)->_buf);

  return (*pTemp);
}

/** Flushes the corresponding buffer by calling transmit. 
 *    Note that this function does not handle transmit not
 *    transmitting the whole buffer. This can be done by
 *    adding another start field in the data structure and
 *    then moving the start out to the return value of rx_bytes
 *    but that seemed unnecessary right now.
**/

static size_t pflush(PrintfInfo* pInfo)
{
  size_t rx_bytes = 0;
  size_t total = 0;
  int ret = 0;

  if (pInfo == NULL)
  {
    return (-1);
  }

  //if empty or invalid fd
  if ( (pInfo->end == 0) || (pInfo->fd == -1) )
  {
    return (0);
  }

  do
  {
    ret = transmit(pInfo->fd, pInfo->buf + total, pInfo->end - total, &rx_bytes);
    if ( (ret != 0) || (rx_bytes == 0) )
    {
      return (-1);
    }
    total += rx_bytes;
  } while (total < pInfo->end);

  pInfo->count += pInfo->end;
  pInfo->end = 0;
 
  return (total);
}

/** Exported function to flush a file descriptor's buffer
 *    uses pflush() internally
**/
size_t fflush(int fd)
{
  size_t rx_bytes = 0;
  size_t sret = 0;
  int ret = 0;

  PrintfInfo* pInfo = getPrintfInfo(fd);
  if (pInfo == NULL)
  {
    return (-1);
  }

  sret = pflush(pInfo);
  if (sret == -1)
  {
    _terminate(1);
  }

  return (sret);
}

#define _PUT_CHAR(_pInfo, _c) (_pInfo)->buf[(_pInfo)->end++] = (_c)

size_t printfProcessString(PrintfInfo* pInfo, const char* str)
{
  size_t ret = 0;
  size_t ret2 = 0;
  size_t i = 0;

  if (pInfo == NULL)
  {
    return (-1);
  }
  if (str == NULL)
  {
    return (0);
  }

  for (i = 0; str[i] != '\0'; i++)
  {
    _PUT_CHAR(pInfo, str[i]);
    if (pInfo->end >= pInfo->bufSize)
    {
      if (pInfo->fd == -1) //i.e. its snprintf
      {
        return (pInfo->bufSize);
      }

      ret2 = pflush(pInfo);
      if (ret2 == -1)
      {
        _terminate(1);
      }
      ret += ret2;
    }
  }   
 
  if (pInfo->fd == -1)
  {
    return (i);
  }

  return (ret);
}

static inline char _nibbleToHexChar(uint8_t nib, int bUpcase)
{
  nib &= 0xF;
  if ( nib <= 9)
  {
    return (nib + '0');
  }
  else
  {
    return ( (nib - 0xA) + (bUpcase ? 'A' : 'a'));
  }
  return (0); //should not be here
}

static size_t uint32ToHexStr(char* str, uint32_t ui, int bLeadingZeroes, int bUpcase)
{
  if (str == NULL) 
  {
    return (-1);
  }


  int i = 0;
  int j = 0;
  size_t firstNonZero = 0;
  char buf[9];

  for (i = 24, j = 0; i > 0; i -= 8, j++)
  {
    buf[j] = _nibbleToHexChar( (uint8_t)(ui >> (i + 4)), bUpcase);
    if (!firstNonZero && buf[j] != '0')
    {
      firstNonZero = j;
    }

    j++;
    buf[j] = _nibbleToHexChar( (uint8_t)(ui >> (i)), bUpcase);
    if (!firstNonZero && buf[j] != '0')
    {
      firstNonZero = j;
    }
  }

  if (bLeadingZeroes)
  {
    firstNonZero = 0;
  }

  for (i = firstNonZero, j = 0; i < 8; i++, j++)
  {
    str[j] = buf[i];
  }

  return (j);
}

static size_t _pprintf(PrintfInfo* pInfo, const char* fstr, va_list args)
{
  size_t ret = 0;
  size_t ret2 = 0;
  size_t tempRet = 0;
  
  if (fstr == NULL)
  {
    return (0);
  }

  if (pInfo == NULL)
  {
    return (0);
  }

  size_t i = 0;
  size_t nonFormatCount = 0;
  int bLeadingZeroes = 0;
  while (fstr[i] != '\0')
  {
    switch(fstr[i])
    {
      case('#'):
      {
        i++;
        if (fstr[i] == '0')
        {
          bLeadingZeroes = 1;
          i++;
        }

        switch(fstr[i])
        {
          case('#'):
          {
            _PUT_CHAR(pInfo, '#');
            nonFormatCount++;
            i++;
            break;
          }
          case('x'):
          {
            tempRet = uint32ToHexStr(pInfo->buf + pInfo->end, va_arg(args, uint32_t), bLeadingZeroes, 0); 
            pInfo->end += tempRet;
            ret += tempRet;
            i++;
            break;  
          }
          case('X'):
          {
            tempRet = uint32ToHexStr(pInfo->buf + pInfo->end, va_arg(args, uint64_t), bLeadingZeroes, 1);
            pInfo->end += tempRet;
            ret += tempRet; 
            i++;
            break;  
          }
          case('s'):
          {
            //pInfo->end is already updated by printfProcessString
            tempRet = printfProcessString(pInfo, va_arg(args, const char*));
            ret += tempRet; 
            i++;
            break;
          }
          default:
          {
            _PUT_CHAR(pInfo, '#');
            nonFormatCount++;
            //we don't increment i since we didn't consume the char after %
          }
        }
        break;
      }
      case('\\'):
      {
        i++;
        switch(fstr[i])
        {
          case ('n'):
          {
            _PUT_CHAR(pInfo, '\n');
            nonFormatCount++;
            i++;
            break;
          }
          case ('\\'):
          {
            _PUT_CHAR(pInfo, '\\');
            nonFormatCount++;
            i++;
            break;
          }
          case ('t'):
          {
            _PUT_CHAR(pInfo, '\t');
            nonFormatCount++;
            i++;
            break;
          }
          case ('\"'):
          {
            _PUT_CHAR(pInfo, '\"');
            nonFormatCount++;
            i++;
            break;
          }
          case ('\''):
          {
            _PUT_CHAR(pInfo, '\'');
            nonFormatCount++;
            i++;
            break;
          }
          default:
          {
            _PUT_CHAR(pInfo, '\\');
            nonFormatCount++;
            break;
          }
        }
        break;
      }
      default:
      {
        _PUT_CHAR(pInfo, fstr[i]);
        nonFormatCount++;
        i++;
        if (gbFlushOnNewline && (fstr[i-1] == '\n'))
        {
          ret2 = pflush(pInfo);
          if (ret2 == -1)
          {
            _terminate(1);
          }
           
          ret += ret2;
        }
        break;
      }
    }
    if (pInfo->end >= pInfo->bufSize)
    {
      ret2 = pflush(pInfo);
      if (ret2 == -1)
      {
        _terminate(1);
      }
           
      ret += ret2;
    }
  }
  
  if (pInfo->fd == -1) //if snprintf
  {
    return (ret + nonFormatCount);
  }

  return (ret);
}

static size_t _fprintf(int fd, const char* fstr, va_list args)
{
  PrintfInfo* pInfo = NULL;
  pInfo = getPrintfInfo(fd);
  return (_pprintf(pInfo, fstr, args));
}

size_t snprintf(char* str, size_t len, const char* fstr, ...)
{
  size_t ret = 0;
  PrintfInfo printfInfo;

  va_list args;
  va_start(args, fstr);

  INIT_PRINTF_INFO(&printfInfo, -1, str);
  printfInfo.bufSize = len;

  ret = _pprintf(&printfInfo, fstr, args);

  va_end(args);
 
  return (ret);
}

size_t fprintf(int fd, const char* fstr, ...)
{
  size_t ret = 0;
  va_list args;
  va_start(args, fstr);

  ret = _fprintf(fd, fstr, args);

  va_end(args);

  return (ret);
}

size_t printf(const char* fstr, ...)
{
  size_t ret = 0;
  va_list args;
  va_start(args, fstr);

  ret = _fprintf(STDOUT, fstr, args);

  va_end(args);

  return (ret);
}

#undef _PRINTF_BUF_OVERFLOW_SIZE
#undef _PRINTF_BUF_SIZE
