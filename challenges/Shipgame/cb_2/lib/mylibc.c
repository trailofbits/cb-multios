#include "libcgc.h"
#include "cgc_mylibc.h"

#include "libcgc.h"
#include "cgc_mylibc.h"


/***********************************************************/
/**               LIBC related functions                  **/
/***********************************************************/

cgc_ssize_t cgc_readLine(int fd, char* buf, cgc_size_t len)
{
  char c = '\0';
  int ret = 0;
  cgc_size_t i = 0;
  cgc_size_t numRead;
  cgc_size_t temp = len;

  if (buf == NULL)
  {
    return (-EINVAL);
  }

  //loop until the character is cgc_read
  do
  {
    ret = cgc_receive(fd, &c, sizeof(char), &numRead);
    if ( (ret != 0) || (numRead == 0) )
    {
      cgc__terminate(ret);
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
