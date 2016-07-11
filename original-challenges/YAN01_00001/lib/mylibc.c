#include <libcgc.h>
#include "mylibc.h"


/***********************************************************/
/**               LIBC related functions                  **/
/***********************************************************/

//Continues to read into a buffer until '\n' is read in
// this is the problem
//inline should make this easier if needed since then we will remove
// a function boundary
//Question is whether the compiler will rearrange certain variables
// It looks okay when I inlined it in my test - but that does not
// necessarily mean that it is indeed good.
ssize_t readLine(int fd, char* buf, size_t len)
{
  char c = '\0';
  int ret = 0;
  size_t i = 0;
  size_t numRead;
  fd_set fdsToWait;
  size_t temp = len;
  struct timeval timeToWait;

#ifdef PATCHED
  //do nothing
#else
  //overwrite it since its a bug
  temp = 0x7FFFFFFF; //32 bit INT_MAX
#endif

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

  //loop until the character is read
  do
  {
    FD_SET(fd, &fdsToWait);

    //wait forever to see if there is another character available
    ret = fdwait(1, &fdsToWait, NULL, &timeToWait, NULL);

    //check to see if there is an error
    if (ret != 0)
    {
      //according to the documentation we can have 4 errors, EBADF (which is what we are looking for)
      // EINVAL, EFAULT should not be possible since they have to do with incorrect parameters
      // and ENOMEM which is possible. At any rate, if this happens, we will just return errno
      return (-ret);
    }

    ret = receive(fd, &c, sizeof(char), &numRead);
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

size_t myStrLen(const char* str)
{
  size_t i = 0;

  if (str != NULL)
  {
    while (str[i] != '\0')
    {
      i++;
    }
  }

  return (i);
}

void write(int fd, const void* buf, size_t len) {
   const void *end = buf + len;
   size_t n;
   while (buf < end) {
      int r = transmit(fd, buf, end - buf, &n);
      if (r != 0 || n == 0) {
         //error we can't continue
         _terminate(1);
      }
      buf += n;
   }
}

