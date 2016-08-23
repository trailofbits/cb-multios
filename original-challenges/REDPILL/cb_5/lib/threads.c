#include <libcgc.h>

#include "libc.h"

extern size_t MY_TID;
extern size_t PIPE_RECV;
extern char * STR_THREAD_NAME;

int ack_state(char msg) {
   return pkt_send(TID_K, MY_TID, (msg | MASK_ACK));
}

int loop() {

   int ret = SUCCESS;
   struct packet pkt;
   int fdsReady;
   unsigned char state = MAJOR_UNKNOWN;

   struct timeval timeToWait;
   timeToWait.tv_sec = LISTEN_TIMEOUT;
   timeToWait.tv_usec = 0;

   fd_set fdsToWait;
   FD_ZERO(&fdsToWait);

   while (1) {

      fdsReady = 0;
      while(!fdsReady) {

         // try listening for a few seconds
         FD_SET(PIPE_RECV, &fdsToWait);
         if (SUCCESS != (ret = fdwait(PIPE_RECV+1, &fdsToWait, NULL, &timeToWait, &fdsReady))) {
#ifdef DEBUG
            fprintf(stderr, "%s: [E] error during fdwait()\n", STR_THREAD_NAME);
#endif
         }

#ifdef DEBUG
         // periodically print state
         if ((MAJOR_FUTEX | MINOR_FUTEX_WAIT) == state) {
            fprintf(stderr, "%s: im waiting.\n", STR_THREAD_NAME);
         } else if ((MAJOR_FUTEX | MINOR_FUTEX_WAKE) == state) {
            fprintf(stderr, "%s: im awake.\n", STR_THREAD_NAME);
         } else {
            fprintf(stderr, "%s: UNK state.\n", STR_THREAD_NAME);
         }
#endif
      }

      // the fd is ready; read it, advance state, ACK to kernel
      receive_all(PIPE_RECV, &pkt, sizeof(pkt), NULL);
      state = pkt_get_msg(&pkt);
      ack_state(state);

      if (MAJOR_TGKILL == (state & MASK_MAJOR)) { 
         size_t sig = (state & MASK_MINOR) >> IDX_MINOR;
#ifdef DEBUG
         fprintf(stderr, "%s: got signal; _terminate(%d)ing...\n", STR_THREAD_NAME, sig);
#endif

         _terminate(sig); 

#ifdef DEBUG
         fprintf(stderr, "%s: I'M A ZOMBIE AHHHH\n", STR_THREAD_NAME);
#endif
      }
   }

   return ret;
}

int main() { _terminate(loop()); }
