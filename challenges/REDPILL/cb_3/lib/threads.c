#include "libcgc.h"

#include "cgc_libc.h"

extern cgc_size_t cgc_MY_TID;
extern cgc_size_t cgc_PIPE_RECV;
extern char * STR_THREAD_NAME;

int cgc_ack_state(char msg) {
   return cgc_pkt_send(TID_K, cgc_MY_TID, (msg | MASK_ACK));
}

int cgc_loop() {

   int ret = SUCCESS;
   struct packet pkt;
   int fdsReady;
   unsigned char state = MAJOR_UNKNOWN;

   struct cgc_timeval timeToWait;
   timeToWait.tv_sec = LISTEN_TIMEOUT;
   timeToWait.tv_usec = 0;

   cgc_fd_set fdsToWait;
   FD_ZERO(&fdsToWait);

   while (1) {

      fdsReady = 0;
      while(!fdsReady) {

         // try listening for a few seconds
         FD_SET(cgc_PIPE_RECV, &fdsToWait);
         if (SUCCESS != (ret = cgc_fdwait(cgc_PIPE_RECV+1, &fdsToWait, NULL, &timeToWait, &fdsReady))) {
#ifdef DEBUG
            fprintf(cgc_stderr, "%s: [E] error during cgc_fdwait()\n", STR_THREAD_NAME);
#endif
         }

#ifdef DEBUG
         // periodically print state
         if ((MAJOR_FUTEX | MINOR_FUTEX_WAIT) == state) {
            fprintf(cgc_stderr, "%s: im waiting.\n", STR_THREAD_NAME);
         } else if ((MAJOR_FUTEX | MINOR_FUTEX_WAKE) == state) {
            fprintf(cgc_stderr, "%s: im awake.\n", STR_THREAD_NAME);
         } else {
            fprintf(cgc_stderr, "%s: UNK state.\n", STR_THREAD_NAME);
         }
#endif
      }

      // the fd is ready; cgc_read it, advance state, ACK to kernel
      cgc_receive_all(cgc_PIPE_RECV, &pkt, sizeof(pkt), NULL);
      state = cgc_pkt_get_msg(&pkt);
      cgc_ack_state(state);

      if (MAJOR_TGKILL == (state & MASK_MAJOR)) { 
         cgc_size_t sig = (state & MASK_MINOR) >> IDX_MINOR;
#ifdef DEBUG
         fprintf(cgc_stderr, "%s: got signal; _terminate(%d)ing...\n", STR_THREAD_NAME, sig);
#endif

         cgc__terminate(sig); 

#ifdef DEBUG
         fprintf(cgc_stderr, "%s: I'M A ZOMBIE AHHHH\n", STR_THREAD_NAME);
#endif
      }
   }

   return ret;
}

int main(int cgc_argc, char *cgc_argv[]) { cgc__terminate(cgc_loop()); }
