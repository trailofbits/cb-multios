#include <libcgc.h>
#include "mylibc.h"

#include <libcgc.h>
#include "mylibc.h"


/***********************************************************/
/**               LIBC related functions                  **/
/***********************************************************/

ssize_t readLine(int fd, char* buf, size_t len)
{
  char c = '\0';
  int ret = 0;
  size_t i = 0;
  size_t numRead;
  size_t temp = len;

  if (buf == NULL)
  {
    return (-EINVAL);
  }

  //loop until the character is read
  do
  {
    ret = receive(fd, &c, sizeof(char), &numRead);
    if ( (ret != 0) || (numRead == 0) )
    {
      _terminate(ret);
    }

    buf[i] = c; 
    i++;
    if (i >= temp)
    {
      i = temp - 1;
    }
  } while ( c != '\n');
 
  buf[i] = '\0';

  return (i);
}
