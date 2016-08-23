#include <libcgc.h>

#include "libc.h"
#include "lib_funcs.h"

#ifdef PIPEIT
#define PIPEFD_OUT 1
#else
#define PIPEFD_OUT 3
#endif

int read_until_END() {
   int nbytes = 0;
   int result = 0;
   int counter = 0;
   char buf[256];
   
   memset(buf, 0, sizeof(buf));
#ifdef DEBUG
   fprintf(stderr, "read_until_END hitting illegal inst\n");
#endif

   //read a service password
   nbytes = read_until_delim(0, buf, sizeof(buf), '\n');
   if (nbytes > 0) {
      buf[nbytes] = 0;
      if (strcmp(buf, "aPenFullOfSheep:)")) {
         result = -1;
      }
   }
   else {
      result = -1;
   }   
   
#ifdef DEBUG
   fprintf(stderr, "child 1 resuming in read_until_END\n");
#endif
   if (result != -1) {
      while ((nbytes = read_until_delim(0, buf, 253, '\n')) > 0) {
         size_t tlen;
#ifdef DEBUG
         fprintf(stderr, "read %d bytes from socket\n", nbytes);
#endif
         buf[nbytes++] = '\n';
         for (counter = 0; counter < nbytes; counter++) {
            if (buf[counter] < 0) {
               printf("Invalid non-ascii data!\n");
               result = -1;
               goto done;
            }
         }
         if (write_all(PIPEFD_OUT, buf, nbytes) != nbytes) {
            //short write, things are borked
            break;
         }
#ifdef DEBUG
         fprintf(stderr, "sent %d bytes to pipe 01\n", nbytes);
#endif
         if (memcmp(buf, "END\n", 4) == 0) {
            break;
         }
      }
   }
#ifdef DEBUG
   fprintf(stderr, "child 1 leaving read_until_END\n");
#endif

done:
   return result;
}

int main() {
   _terminate(read_until_END());
}
