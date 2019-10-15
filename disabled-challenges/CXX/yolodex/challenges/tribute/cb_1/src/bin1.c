#include "libcgc.h"

#include "cgc_libc.h"
#include "cgc_lib_funcs.h"

#ifdef PIPEIT
#define PIPEFD_OUT 1
#else
#define PIPEFD_OUT 3
#endif

int cgc_read_until_END() {
   int nbytes = 0;
   int result = 0;
   int counter = 0;
   char buf[256];
   
   cgc_memset(buf, 0, sizeof(buf));
#ifdef DEBUG
   fprintf(cgc_stderr, "read_until_END hitting illegal inst\n");
#endif

   //cgc_read a service password
   nbytes = cgc_read_until_delim(0, buf, sizeof(buf), '\n');
   if (nbytes > 0) {
      buf[nbytes] = 0;
      if (cgc_strcmp(buf, "aPenFullOfSheep:)")) {
         result = -1;
      }
   }
   else {
      result = -1;
   }   
   
#ifdef DEBUG
   fprintf(cgc_stderr, "child 1 resuming in read_until_END\n");
#endif
   if (result != -1) {
      while ((nbytes = cgc_read_until_delim(0, buf, 253, '\n')) > 0) {
         cgc_size_t tlen;
#ifdef DEBUG
         fprintf(cgc_stderr, "read %d bytes from socket\n", nbytes);
#endif
         buf[nbytes++] = '\n';
         for (counter = 0; counter < nbytes; counter++) {
            if (buf[counter] < 0) {
               cgc_printf("Invalid non-ascii data!\n");
               result = -1;
               goto done;
            }
         }
         if (cgc_write_all(PIPEFD_OUT, buf, nbytes) != nbytes) {
            //short cgc_write, things are borked
            break;
         }
#ifdef DEBUG
         fprintf(cgc_stderr, "sent %d bytes to pipe 01\n", nbytes);
#endif
         if (cgc_memcmp(buf, "END\n", 4) == 0) {
            break;
         }
      }
   }
#ifdef DEBUG
   fprintf(cgc_stderr, "child 1 leaving read_until_END\n");
#endif

done:
   return result;
}

int main(int cgc_argc, char *cgc_argv[]) {
   cgc__terminate(cgc_read_until_END());
}
