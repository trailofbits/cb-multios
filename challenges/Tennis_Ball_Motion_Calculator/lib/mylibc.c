#include "libcgc.h"
#include "cgc_mylibc.h"


/***********************************************************/
/**               LIBC related functions                  **/
/***********************************************************/

//Continues to cgc_read into a buffer until '\n' is cgc_read in
// this is the problem
//inline should make this easier if needed since then we will remove
// a function boundary
//Question is whether the compiler will rearrange certain variables
// It looks okay when I inlined it in my test - but that does not
// necessarily mean that it is indeed good.
cgc_ssize_t cgc_readLine(int fd, char* buf, cgc_size_t len)
{
  char c = '\0';
  int ret = 0;
  cgc_size_t i = 0;
  cgc_size_t numRead;
  cgc_fd_set fdsToWait;
  cgc_size_t temp = len;
  struct cgc_timeval timeToWait;

  if (buf == NULL)
  {
    return (-EINVAL);
  }

  //wait in 1 second intervals
  timeToWait.tv_sec = 1;
  timeToWait.tv_usec = 0;

  //FD_ZERO is in libcgc.h, but just to make sure its not optimized, we will implement our own loop 
  for (i = 0; i < FD_SETSIZE / _NFDBITS; i++)
  {
    fdsToWait._fd_bits[i] = 0;  
  }

  //reset i to 0
  i = 0;

  //loop until the character is cgc_read
  do
  {
    FD_SET(fd, &fdsToWait);

    //wait forever to see if there is another character available
    ret = cgc_fdwait(1, &fdsToWait, NULL, &timeToWait, NULL);

    //check to see if there is an error
    if (ret != 0)
    {
      //according to the documentation we can have 4 errors, EBADF (which is what we are looking for)
      // EINVAL, EFAULT should not be possible since they have to do with incorrect parameters
      // and ENOMEM which is possible. At any rate, if this happens, we will just return errno
      return (-ret);
    }

    ret = cgc_receive(fd, &c, sizeof(char), &numRead);
    if ( (ret != 0) )
    {
      //since receive also returns errno, we can just pass it back
      return (-ret); 
    }
    if ( numRead == 0 ) //if EOF
    {
      return (-EPIPE);
    }

    if (numRead != sizeof(char)) 
    {
      //try again
      continue;
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

cgc_size_t cgc_myStrLen(const char* str)
{
  cgc_size_t i = 0;

  if (str != NULL)
  {
    while (str[i] != '\0')
    {
      i++;
    }
  }

  return (i);
}

void cgc_write(int fd, const void* buf, cgc_size_t len) {
   const void *end = buf + len;
   cgc_size_t n;
   while (buf < end) {
      int r = cgc_transmit(fd, buf, end - buf, &n);
      if (r != 0 || n == 0) {
         //error we can't continue
         cgc__terminate(1);
      }
      buf += n;
   }
}
