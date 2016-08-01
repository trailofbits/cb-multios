#include <libcgc.h>

#include "libc.h"
#include "kernel.h"

struct list *pi_queue;
struct timeval timeToWait;
size_t thread_state[NUM_THREADS+1];

#ifdef DEBUG
size_t count_syscalls = 0;
#endif


#ifdef DEBUG_STACK
// NOTE: this isn't legal for CBs as it includes inline assembly.  
// This should never be done in released bins.
inline int get_esp() {

   unsigned int register esp;

   asm( "movl %%esp, %0;"
      : "=r"(esp));

   return esp;
}
#endif
// ^ DEBUG_STACK

inline int bytes_available(char **curr, char *end, size_t bytes) {
   if ((end-*curr) >= bytes) {
      return 1;
   } else {
      return 0;
   }
}

inline char * consume_bytes(char **curr, char *end, size_t bytes) {

   char *ret = NULL;

   if ((end-*curr) >= bytes) {
      ret = *curr;
      *curr += bytes;
   } else {
      // this is not an error condition when reading the final byte
      ret = NULL;
   }

   return ret;
}

// FUTEX consumes 2 bytes: 1B is MAJOR/MINOR action, 2B is arg to action.
// Requires ACK from thread to transition state.
int syscall_futex(unsigned char syscall, char **curr, char *end) {

#ifdef DEBUG
   DEBUG_INDENT_PRINT(str_syscall[syscall]);
   fprintf(stderr, " (0x%02x)", syscall);
#ifdef DEBUG_STACK
   fprintf(stderr, " ESP @ 0x%08x", get_esp());
#endif
   fprintf(stderr, "\n");
   indent_lvl++;
#endif

   int ret = SUCCESS;

   // Verify MINOR syscall
   unsigned char syscall_minor = syscall & MASK_MINOR;
   if (syscall_minor < MINOR_FUTEX_MIN || syscall_minor > MINOR_FUTEX_MAX ||
       syscall & MASK_ACK || syscall & MASK_PENDING) { 
#ifdef DEBUG
      fprintf(stderr, "%s: [D] futex(%s): invalid syscall_minor\n", 
         STR_THREAD_NAME, str_syscall[syscall]);
#endif
      ret = ERRNO_INVALID_SYSCALL; 
      goto _bail_futex;
   }

   // Get target thread
   char *orig = NULL;
   if (NULL == (orig = consume_bytes(curr, end, 1))) { 
#ifdef DEBUG
      fprintf(stderr, "%s: [E] futex(%s): insufficient bytes\n", 
         STR_THREAD_NAME, str_syscall[syscall]);
#endif
      ret = ERRNO_INSUFFICIENT_BYTES; 
      goto _bail_futex;
   }
   unsigned char tid = orig[0];

   // If we're doing FUTEX_CMP_REQUEUE_PI, then we need to consume another byte.
   unsigned char op = 0;
   if (MINOR_FUTEX_CMP_REQUEUE_PI == syscall_minor) {
         char *orig = NULL;
         if (NULL == (orig = consume_bytes(curr, end, 1))) { 
#ifdef DEBUG
         fprintf(stderr, "%s: [E] futex(%s): insufficient bytes\n", 
            STR_THREAD_NAME, str_syscall[syscall]);
#endif
         ret = ERRNO_INSUFFICIENT_BYTES; 
         goto _bail_futex;
      }
      op = orig[0];
   }

   // Check if it's a valid TID and whether its already killed.
   if (tid < 1 || tid > NUM_THREADS) { 
#ifdef DEBUG
      fprintf(stderr, "%s: [E] %s: invalid tid: 0x%02x\n", 
         STR_THREAD_NAME, str_syscall[syscall], syscall_minor);
#endif
      ret = ERRNO_INVALID_ARG; 
      goto _bail_futex;
   }
   if (thread_state[tid] == MAJOR_TGKILL) {
#ifdef DEBUG
      fprintf(stderr, "%s: [D] %s: refusing action; thread is killed: 0x%02x\n", 
         STR_THREAD_NAME, str_syscall[syscall], tid);
#endif
      ret = ERRNO_BEATING_A_DEAD_HORSE;
      goto _bail_futex;
   }

   // FUTEX_FD was removed from the Linux kernel as of 2.6.25 due to its 
   // inherent raciness.  This doesn't prevent users from attempting to utilize 
   // FUTEX_FD; they just aren't to get any value out of it.  Similarly, 
   // REDPILL treats this call as a no-op and does not send anything to the 
   // requested thread, nor does it change kernel state.
   if (MINOR_FUTEX_FD == syscall_minor) { 
      goto _bail_futex;
   }

   // Send to thread
   thread_state[tid] = syscall | MASK_PENDING;
   ret = pkt_send(tid, MY_TID, syscall);

   // We expect the requested state ACKed back. There *shouldn't* be a 
   // reason why the thread wouldn't correctly ACK this back synchronously. 
   // Unless, of course, the CRS patched the threads incorrectly.
   fd_set fdsToWait;
   FD_ZERO(&fdsToWait);
   int fdsReady = 0;
   int got_resp = 0;
   struct packet pkt;

   for (int i=0; i<ACK_TRIES; i++) {

      FD_SET(PIPE_RECV, &fdsToWait);
      if (SUCCESS != (ret = fdwait(PIPE_RECV+1, &fdsToWait, NULL, &timeToWait, &fdsReady))) {
#ifdef DEBUG
         fprintf(stderr, "%s: [E] error during fdwait()\n", STR_THREAD_NAME);
#endif
      }
      if (1 == fdsReady) {
         got_resp = 1;
         break;
      } else {
#ifdef DEBUG
         fprintf(stderr, "%s: [!] expected ACK, didn't get one (%d/3)\n", STR_THREAD_NAME, i+1);
#endif
      }
   }

   if (got_resp && (SUCCESS == receive_all(PIPE_RECV, &pkt, sizeof(pkt), NULL))) {

      unsigned char syscall = pkt_get_msg(&pkt);
      unsigned char src = pkt_get_src(&pkt);

      if (src < 1 || src > NUM_THREADS) { 
#ifdef DEBUG
         fprintf(stderr, "%s: [E] received ACK from invalid TID: 0x%02x", STR_THREAD_NAME, src);
#endif
         ret = ERRNO_INVALID_ACK;
         goto _bail_futex;
      }

      if ((syscall & MASK_ACK)) {

         switch (syscall_minor) {

            case MINOR_FUTEX_WAIT:
               if ((MAJOR_FUTEX | MINOR_FUTEX_WAIT | MASK_PENDING) == thread_state[src]) {

                  struct node *new = NULL;
                  if (NULL == (new = node_create(src))) {
#ifdef DEBUG
                     fprintf(stderr, "%s: [E] futex(%s): node_create(): failed allocation\n", STR_THREAD_NAME, str_syscall[syscall]);
#endif    
                     thread_state[src] = MAJOR_UNKNOWN;
                     ret = ERRNO_ALLOC;
                     goto _bail_futex;
                  }

                  // Attempt to push the node onto the list.  This might fail
                  // due to the thread already being asleep.  In this case, 
                  // list_push returns ERRNO_LIST_PUSH.  This isn't actuallly 
                  // an error condition, so we suppress it.
                  ret = list_push(pi_queue, new);
                  if (SUCCESS != ret && ERRNO_LIST_PUSH != ret) { 
#ifdef DEBUG
                     fprintf(stderr, "%s: [E] futex(%s): list_push: UNKNOWN ERROR\n", STR_THREAD_NAME, str_syscall[syscall]);
#endif   
                     thread_state[src] = MAJOR_UNKNOWN;

                  } else {
                     ret = SUCCESS;
                     thread_state[src] = (MAJOR_FUTEX | MINOR_FUTEX_WAIT);
                  }

               } else {
                  thread_state[src] = MAJOR_UNKNOWN;
#ifdef DEBUG
                  fprintf(stderr, "%s: [E] futex(%s): unexpected response: 0x%02x", STR_THREAD_NAME, str_syscall[syscall], syscall);
#endif
               }
               break;

            case MINOR_FUTEX_WAKE:
               if ((MAJOR_FUTEX | MINOR_FUTEX_WAKE | MASK_PENDING) == thread_state[src]) {

                  thread_state[src] = (MAJOR_FUTEX | MINOR_FUTEX_WAKE);

                  // Attempt to remove the node from the list.  This might fail 
                  // due to the thread already being awake (and therefore not
                  // in the queue).  In this case, list_remove() returns NULL.
                  // This isn't actually an error condition, but we don't want 
                  // to call node_destroy(NULL).
                  struct node *needle = NULL;
                  if (NULL == (needle = list_remove(pi_queue, src))) {
#ifdef DEBUG
                     fprintf(stderr, "%s: [D] futex(%s): list_remove: attempted to remove a non-element\n", STR_THREAD_NAME, str_syscall[syscall]);
#endif                   
                  } else {

                     // This, however, is an error condition.
                     if (SUCCESS != (ret = node_destroy(needle))) {
#ifdef DEBUG
                        fprintf(stderr, "%s: [E] futex(%s): error during node_destroy()\n", STR_THREAD_NAME, str_syscall[syscall]);
#endif                           
                        thread_state[src] = MAJOR_UNKNOWN;
                     }
                  }

               } else {
                  thread_state[src] = MAJOR_UNKNOWN;
#ifdef DEBUG
                  fprintf(stderr, "%s: [E] futex(%s): unexpected response: 0x%02x", STR_THREAD_NAME, str_syscall[syscall], syscall);
#endif
               }
               break;

            // The same functionality as FUTEX_CMP_REQUEUE_PI minus the op.
            case MINOR_FUTEX_REQUEUE_PI:
               if ((MAJOR_FUTEX | MINOR_FUTEX_REQUEUE_PI | MASK_PENDING) == thread_state[src]) {
 
                  unsigned char pushdown[PAGE_SZ] = { 0 };

                  struct node new;
                  new.value = src;

                  // Try to push.  list_push() returns ERRNO_LIST_PUSH when 
                  // thread is already in the queue.  This would happen when 
                  // the thread is already WAITing or REQUEUED.  We don't 
                  // particularly care which it is and this is not an error 
                  // condition, so we ignore the return value.
                  list_push(pi_queue, &new);

                  // Irrespective of the thread's previous state, we change its
                  // state to the REQUEUE state.  This is somewhat of a hack 
                  // so that pollers can verify the REQUEUE functionality works.
                  // In the real world, REQUEUE would... requeue - and move the 
                  // thread to another queue.  We don't do this here because it 
                  // _uninterestingly_ complicates analysis.  Verification in 
                  // the real world would be done by verifying all queues.  
                  // See more discussion in README.md.
                  thread_state[src] = (MAJOR_FUTEX | MINOR_FUTEX_REQUEUE_PI);

                  if (NULL == list_remove(pi_queue, src)) { 
#ifdef DEBUG
                     fprintf(stderr, "%s: [E] %s attempted list_remove(), but failed", 
                        STR_THREAD_NAME, str_syscall[syscall]);
#endif
                     thread_state[src] = MAJOR_UNKNOWN; 
                  }

               } else {
                  thread_state[src] = MAJOR_UNKNOWN;
#ifdef DEBUG
                  fprintf(stderr, "%s: [E] %s unexpected resp msg: 0x%02x", 
                     STR_THREAD_NAME, str_syscall[syscall], syscall);
#endif
               }
               break;

            case MINOR_FUTEX_CMP_REQUEUE_PI:
               if ((MAJOR_FUTEX | MINOR_FUTEX_CMP_REQUEUE_PI | MASK_PENDING) == thread_state[src]) {

                  thread_state[src] = (MAJOR_FUTEX | MINOR_FUTEX_CMP_REQUEUE_PI);

                  unsigned char pushdown[PAGE_SZ] = { 0 };

                  struct node new;
                  new.value = src;

                  // Try to push.  list_push() returns ERRNO_LIST_PUSH when 
                  // thread is already in the queue.  This would happen when 
                  // the thread is already WAITing or REQUEUED.  We don't 
                  // particularly care which it is and this is not an error 
                  // condition, so we ignore the return value.
                  // This has the side effect that the vulnerability can only 
                  // triggered by specifying a thread that isn't already in the 
                  // queue - tricky.
                  list_push(pi_queue, &new);

                  // Force reasoning about op's relation to the thread.
                  // See README.md for comments on the simplification done here.
                  if (op == (~src & 0xFF)) {
#ifdef DEBUG
                     fprintf(stderr, "[D] passed op check\n");
#endif
                     // Having fun with automated analysis; this isn't actually 
                     // used.
                     op = ~op;

#ifdef PATCHED
                     // VULN here: fails to call list_remove() under certain 
                     // conditions (when op is the bitwise NOT of src).

                     // Unlike the other list_remove() calls, if this one fails 
                     // it is an error.  If the thread wasn't already on the 
                     // queue, the list_push() above should have added it.
                     if (NULL == list_remove(pi_queue, src)) {
#ifdef DEBUG
                        fprintf(stderr, "%s: [E] futex(%s): failed list_remove() (actual error)\n",
                           STR_THREAD_NAME, str_syscall[syscall]);
#endif                      
                        thread_state[src] = MAJOR_UNKNOWN;
                     }
#endif
                  } else {
#ifdef DEBUG
                     fprintf(stderr, "[D] failed op check\n");
#endif
                     op++;
                     if (NULL == list_remove(pi_queue, src)) { 
#ifdef DEBUG
                        fprintf(stderr, "%s: [E] futex(%s): failed list_remove() (actual error)\n",
                           STR_THREAD_NAME, str_syscall[syscall]);
#endif                      
                        thread_state[src] = MAJOR_UNKNOWN;
                     }
                  }

               } else {
                  thread_state[src] = MAJOR_UNKNOWN;
#ifdef DEBUG
                  fprintf(stderr, "%s: [E] unexpected response: 0x%02x", 
                     STR_THREAD_NAME, str_syscall[syscall], syscall);
#endif
               }
               break;

            default:
#ifdef DEBUG
               fprintf(stderr, "%s: [E] invalid response: 0x%02x", STR_THREAD_NAME, syscall);
#endif
               ret = ERRNO_RECV;
               break;
         }

#ifdef DEBUG
         fprintf(stderr, "%s: [D] %s is now: %s\n", 
            STR_THREAD_NAME, str_tids[src], str_syscall[thread_state[src]]);
#endif

      } else {
#ifdef DEBUG
         fprintf(stderr, "%s: [E] got a response that wasnt an ACK: 0x%02x (%s)", STR_THREAD_NAME, syscall, str_syscall[syscall]);
#endif  
         ret = ERRNO_INVALID_ACK; 
      }
   } else {
#ifdef DEBUG
         fprintf(stderr, "%s: [D] bad response; thread might be killed...\n", STR_THREAD_NAME);
         ret = ERRNO_RECV;
#endif
   }

_bail_futex:
#ifdef DEBUG
   indent_lvl--;
   DEBUG_INDENT_PRINT(str_syscall[syscall]);
   fprintf(stderr, " (0x%02x)", syscall);
#ifdef DEBUG_STACK
   fprintf(stderr, " ESP @ 0x%08x", get_esp());
#endif
   fprintf(stderr, "\n");
#endif

   return ret;
}

// PAUSE takes 2 bytes: 1 to determine action, 1 to provide argument to that action.
// Functionality wholly contained within KERNEL; requires no ACK from threads.
// Requires no validation of arg because sleeps between 0 and 255s are legit.
int syscall_pause(unsigned char syscall, char **curr, char *end) {

#ifdef DEBUG
   DEBUG_INDENT_PRINT(str_syscall[syscall]);
   fprintf(stderr, " (0x%02x)", syscall);
#ifdef DEBUG_STACK
   fprintf(stderr, " ESP @ 0x%08x", get_esp());
#endif
   fprintf(stderr, "\n");
   indent_lvl++;
#endif

   int ret = SUCCESS;

   char *orig = NULL;
   if (NULL == (orig = consume_bytes(curr, end, 1))) { 
#ifdef DEBUG
      fprintf(stderr, "%s: [E] pause(%s / 0x%02x): insufficient bytes\n", 
         STR_THREAD_NAME, str_syscall[syscall], syscall);
#endif
      ret = ERRNO_INSUFFICIENT_BYTES; 
      goto _bail_pause;
   }

   unsigned char arg = orig[0];
   pause(arg);

_bail_pause:
#ifdef DEBUG
   indent_lvl--;
   DEBUG_INDENT_PRINT(str_syscall[syscall]);
   fprintf(stderr, " (0x%02x)", syscall);
#ifdef DEBUG_STACK
   fprintf(stderr, " ESP @ 0x%08x", get_esp());
#endif
   fprintf(stderr, "\n");
#endif

   return ret;
}

// sendmsg(), sendmsg(), recvmmsg() & recvmsg() were used by Towelroot to 
// consume a chosen amount of stack in order to control the content underneath 
// the dangling pointer on the PI queue.
// We emulate this functionality here by providing a (single) recursive 
// interface. 
// Our sendmsg() takes two arguments, each 1B in length:
//  arg0: the number of times to recurse
//  arg1: the "message" we wish to send (same message is sent on each recursion to make it simpler)
int syscall_sendmsg(unsigned char syscall, char **curr, char *end) {

#ifdef DEBUG
   DEBUG_INDENT_PRINT(str_syscall[syscall]);
   fprintf(stderr, " (0x%02x)", syscall);
#ifdef DEBUG_STACK
   fprintf(stderr, " ESP @ 0x%08x", get_esp());
#endif
   fprintf(stderr, "\n");
   indent_lvl++;
#endif

   int ret = SUCCESS;

   unsigned char syscall_minor = syscall & MASK_MINOR;
   if (0 != syscall_minor) {
#ifdef DEBUG
      fprintf(stderr, "%s: [D] sendmsg(%s): invalid MINOR syscall; ignoring...\n", 
         STR_THREAD_NAME, str_syscall[syscall]);
      ret = ERRNO_INVALID_SYSCALL;
      goto _bail_sendmsg;
#endif
   }

   char *orig = NULL;
   if (NULL == (orig = consume_bytes(curr, end, 2))) { 
#ifdef DEBUG
      fprintf(stderr, "%s: [E] sendmsg(%s): insufficient bytes\n", 
         STR_THREAD_NAME, str_syscall[syscall]);
#endif
      ret = ERRNO_INSUFFICIENT_BYTES;
      goto _bail_sendmsg;
   }
   unsigned char recursions = orig[0];
   unsigned char msg = orig[1];

   _syscall_sendmsg(recursions, msg);

_bail_sendmsg:
#ifdef DEBUG
   indent_lvl--;
   DEBUG_INDENT_PRINT(str_syscall[syscall]);
   fprintf(stderr, " (0x%02x)", syscall);
#ifdef DEBUG_STACK
   fprintf(stderr, " ESP @ 0x%08x", get_esp());
#endif
   fprintf(stderr, "\n");
#endif

   return ret;
}

// This function consumes a minimum of 0x70B (when CLOBBER_LEN = 0x10).
void _syscall_sendmsg(unsigned char recursions, unsigned char msg) {

#ifdef DEBUG_SENDMSG
   DEBUG_INDENT_PRINT("_syscall_sendmsg");
#ifdef DEBUG_STACK
   fprintf(stderr, " ESP @ 0x%08x", get_esp());
#endif
   fprintf(stderr, "\n");
   indent_lvl++;
#endif

   if (0 == recursions) { 

#ifdef DEBUG_SENDMSG
      indent_lvl--;
      DEBUG_INDENT_PRINT("_syscall_sendmsg");
#ifdef DEBUG_STACK
      fprintf(stderr, " ESP @ 0x%08x", get_esp());
#endif
      fprintf(stderr, "\n");
#endif
   
      return; 
   }

#define CLOBBER_LEN 0x80

   unsigned char clobber[CLOBBER_LEN];
   memset(clobber, msg, CLOBBER_LEN);

#ifdef DEBUG_SENDMSG
   fprintf(stderr, "%s: [D] _syscall_sendmsg(): i've clobbered %p - %p\n", 
      STR_THREAD_NAME, &clobber, &(clobber[CLOBBER_LEN-1]));
#endif

   _syscall_sendmsg(recursions-1, msg);

#ifdef DEBUG_SENDMSG
   indent_lvl--;
   DEBUG_INDENT_PRINT("_syscall_sendmsg");
#ifdef DEBUG_STACK
   fprintf(stderr, " ESP @ 0x%08x", get_esp());
#endif
   fprintf(stderr, "\n");
#endif
}

// PROC takes only a MAJOR/MINOR syscall pair and dumps internal memory state.
// This call is meant to emulate the information userspace might get from 
// reading the procfs.  This interface is crucial to verifying correct behavior
// via pollers.
int syscall_proc(unsigned char syscall, char **curr, char *end) {

#ifdef DEBUG
   DEBUG_INDENT_PRINT(str_syscall[syscall]);
   fprintf(stderr, " (0x%02x)", syscall);
#ifdef DEBUG_STACK
   fprintf(stderr, " ESP @ 0x%08x", get_esp());
#endif
   fprintf(stderr, "\n");
   indent_lvl++;
#endif

   int ret = SUCCESS;

   unsigned char syscall_minor = syscall & MASK_MINOR;
   if (syscall_minor < MINOR_PROC_MIN || syscall_minor > MINOR_PROC_MAX ||
       syscall & MASK_ACK || syscall & MASK_PENDING) { 
#ifdef DEBUG
      fprintf(stderr, "%s: [D] proc(%s): invalid syscall_minor\n", 
         STR_THREAD_NAME, str_syscall[syscall]);
#endif
      ret = ERRNO_INVALID_SYSCALL; 
      goto _bail_proc;
   }

   unsigned char state = '\0';
   size_t tx_bytes = 0;
   size_t len = 0;

   switch (syscall_minor) {

      case MINOR_PROC_THREAD_STATE:
#ifdef DEBUG 
         fprintf(stderr, "%s: [D] syscall_proc(): dumping thread state...\n", STR_THREAD_NAME);

         for (int i = 1; i<=NUM_THREADS; i++) {
            state = thread_state[i];
            fprintf(stderr, "%s: [D] syscall_proc(): thread_state[%d] = 0x%02x (%s)\n", 
               STR_THREAD_NAME, i, state, str_syscall[state]);
         }
#endif

         tx_bytes = 0;
         len = sizeof(thread_state)-sizeof(size_t);
         size_t *start = thread_state + 1;
         // TODO: Why is transmit() returning EINVAL? (according to /usr/include/libcgc.h)
         if (SUCCESS != (ret = transmit_all(STDOUT, thread_state + 1, len, &tx_bytes)) || 
             tx_bytes != len) { 
#ifdef DEBUG
            fprintf(stderr, 
               "%s: [E] proc(): error during thread_state transmit(); ret = 0x%02x; len = 0x%02x\n", 
               STR_THREAD_NAME, ret, len);
            fprintf(stderr, 
               "%s: [E] proc(): thread_state + 1: %d; thread_state[1]: %d; &(thread_state[1]): %d; start = %d\n", 
               STR_THREAD_NAME, thread_state + 1, thread_state[1], &(thread_state[1]), start);
#endif
         }
         break;

      case MINOR_PROC_LIST_DUMP:
#ifdef DEBUG 
         fprintf(stderr, "%s: [D] syscall_proc(): dumping queue state...\n", STR_THREAD_NAME);
         list_dump(pi_queue);
#endif     
         
         // Send the list struct
         tx_bytes = 0;
         len = sizeof(struct list);
         if (SUCCESS != (ret = transmit_all(STDOUT, pi_queue, len, &tx_bytes)) || 
             tx_bytes != len) { 
#ifdef DEBUG
            fprintf(stderr, 
               "%s: [E] proc(): error during pi_queue transmit()\n", 
               STR_THREAD_NAME);
#endif
         } else {

            // Send each node struct
            struct node *curr = pi_queue->head;
            tx_bytes = 0;
            len = sizeof(struct node);
            while (NULL != curr) {
               if (SUCCESS != (ret = transmit_all(STDOUT, curr, len, &tx_bytes)) || 
                   tx_bytes != len) { 
#ifdef DEBUG
               fprintf(stderr, 
                  "%s: [E] proc(): error during node transmit()\n", 
                  STR_THREAD_NAME);
#endif
                  break;
               }
               curr = curr->next;
            }
         }
         break;

      default:
#ifdef DEBUG
         fprintf(stderr, "%s: [E] syscall_proc(): bad MINOR\n", STR_THREAD_NAME);
         ret = ERRNO_RECV;
#endif
         break;
   }

_bail_proc:
#ifdef DEBUG
   indent_lvl--;
   DEBUG_INDENT_PRINT(str_syscall[syscall]);
   fprintf(stderr, " (0x%02x)", syscall);
#ifdef DEBUG_STACK
   fprintf(stderr, " ESP @ 0x%08x", get_esp());
#endif
   fprintf(stderr, "\n");
#endif

   return ret;
}

// Send a signal to a thread, causing thread to _terminate(signal).
// Destination thread is encoded in a 2nd byte.
// Signal number is encoded as the syscall_minor.
int syscall_tgkill(unsigned char syscall, char **curr, char *end) {

#ifdef DEBUG
   DEBUG_INDENT_PRINT(str_syscall[syscall]);
   fprintf(stderr, " (0x%02x)", syscall);
#ifdef DEBUG_STACK
   fprintf(stderr, " ESP @ 0x%08x", get_esp());
#endif
   fprintf(stderr, "\n");
   indent_lvl++;
#endif

   int ret = SUCCESS;

   unsigned char syscall_minor = syscall & MASK_MINOR;
   if (0 != syscall_minor ||
       syscall & MASK_ACK || syscall & MASK_PENDING) { 
#ifdef DEBUG
      fprintf(stderr, "%s: [D] tgkill(%s): invalid syscall_minor\n", 
         STR_THREAD_NAME, str_syscall[syscall]);
#endif
      ret = ERRNO_INVALID_SYSCALL; 
      goto _bail_tgkill;
   }

   // Get TID.
   char *orig = NULL;
   if (NULL == (orig = consume_bytes(curr, end, 1))) { 
#ifdef DEBUG
      fprintf(stderr, "%s: [E] tgkill(%s): insufficient bytes\n", 
         STR_THREAD_NAME, str_syscall[syscall]);
#endif
      ret = ERRNO_INSUFFICIENT_BYTES; 
      goto _bail_tgkill;
   }
   unsigned char tid = orig[0];

   // Check if it's a valid TID and whether its already killed.
   if (tid < 1 || tid > NUM_THREADS) { 
#ifdef DEBUG
      fprintf(stderr, "%s: [E] %s: invalid tid: 0x%02x\n", 
         STR_THREAD_NAME, str_syscall[syscall], syscall_minor);
#endif
      ret = ERRNO_INVALID_ARG; 
      goto _bail_tgkill;
   }
   if (thread_state[tid] == MAJOR_TGKILL) {
#ifdef DEBUG
      fprintf(stderr, "%s: [D] %s: refusing action; thread is killed: 0x%02x\n", 
         STR_THREAD_NAME, str_syscall[syscall], tid);
#endif
      ret = ERRNO_BEATING_A_DEAD_HORSE;
      goto _bail_tgkill;
   }

   // Send to thread
   thread_state[tid] = syscall | MASK_PENDING;
   ret = pkt_send(tid, MY_TID, syscall);

   fd_set fdsToWait;
   FD_ZERO(&fdsToWait);
   int fdsReady = 0;
   int got_resp = 0;
   struct packet pkt;

   for (int i=0; i<ACK_TRIES; i++) {

      FD_SET(PIPE_RECV, &fdsToWait);
      if (SUCCESS != (ret = fdwait(PIPE_RECV+1, &fdsToWait, NULL, &timeToWait, &fdsReady))) {
#ifdef DEBUG
         fprintf(stderr, "%s: [E] error during fdwait()\n", STR_THREAD_NAME);
#endif
      }

      if (1 == fdsReady) {
         got_resp = 1;
         break;

      } else {
#ifdef DEBUG
         fprintf(stderr, "%s: [!] failed to recv ACK (%d/3)\n", STR_THREAD_NAME, i+1);
#endif
      }
   }

   if (got_resp && (SUCCESS == receive_all(PIPE_RECV, &pkt, sizeof(pkt), NULL))) {

      unsigned char syscall = pkt_get_msg(&pkt);
      unsigned char src = pkt_get_src(&pkt);

      if (src < 1 || src > NUM_THREADS) { 
#ifdef DEBUG
         fprintf(stderr, "%s: [E] received ACK from invalid TID: 0x%02x", STR_THREAD_NAME, src);
#endif
         thread_state[src] = MAJOR_UNKNOWN;
         ret = ERRNO_INVALID_ACK;
      } else {

         if ((MAJOR_TGKILL | MASK_ACK) == (syscall & (MASK_MAJOR | MASK_ACK)) && 
             (MAJOR_TGKILL | MASK_PENDING) == (thread_state[src] & (MASK_MAJOR | MASK_PENDING))) {

            thread_state[src] = MAJOR_TGKILL;

            // Attempt to remove the node from the list.  This might fail 
            // due to the thread already being awake (and therefore not
            // in the queue).  In this case, list_remove() returns NULL.
            // This isn't actually an error condition, but we don't want 
            // to call node_destroy(NULL).
            struct node *needle = NULL;
            if (NULL == (needle = list_remove(pi_queue, src))) {
#ifdef DEBUG
               fprintf(stderr, "%s: [D] futex(%s): list_remove: attempted to remove a non-element\n", STR_THREAD_NAME, str_syscall[syscall]);
#endif                   
            } else {

               // This, however, is an error condition.
               if (SUCCESS != (ret = node_destroy(needle))) {
#ifdef DEBUG
                  fprintf(stderr, "%s: [E] tgkill(%s): error during node_destroy()\n", STR_THREAD_NAME, str_syscall[syscall]);
#endif                           
                  thread_state[src] = MAJOR_UNKNOWN;
               }
            }  
         } else {
            thread_state[src] = MAJOR_UNKNOWN;
   #ifdef DEBUG
            fprintf(stderr, "%s: [E] unexpected response: 0x%02x", STR_THREAD_NAME, str_syscall[syscall], syscall);
   #endif
         }
      }

#ifdef DEBUG
      fprintf(stderr, "%s: [D] %s is now: %s\n", STR_THREAD_NAME, str_tids[src], str_syscall[thread_state[src]]);
#endif 
   }

_bail_tgkill:
#ifdef DEBUG
   indent_lvl--;
   DEBUG_INDENT_PRINT(str_syscall[syscall]);
   fprintf(stderr, " (0x%02x)", syscall);
#ifdef DEBUG_STACK
   fprintf(stderr, " ESP @ 0x%08x", get_esp());
#endif
   fprintf(stderr, "\n");
#endif

   return ret;
}

int syscall_dispatch(char **curr, char *end) {

#ifdef DEBUG
   fprintf(stderr, "\n");
   DEBUG_INDENT_PRINT("syscall_dispatch()");
#ifdef DEBUG_STACK
   fprintf(stderr, " ESP @ 0x%08x", get_esp());
#endif
   fprintf(stderr, "\n");
   indent_lvl++;
#endif

   int ret = SUCCESS;
   char *orig = NULL;
   unsigned char syscall;

   while(NULL != (orig = consume_bytes(curr, end, 1))) {

      // If we've killed all the threads, do a shutdown.  
      // This should make testing quicker.
      int all_dead = 1;
      for (int i=1; i<=NUM_THREADS; i++) {
         if (MAJOR_TGKILL != thread_state[i]) { 
            all_dead = 0;
            break; 
         }
      }

      if (all_dead) {
#ifdef DEBUG
         fprintf(stderr, "%s: we've killed all threads; shutting down...\n", STR_THREAD_NAME);
#endif  
         ret = ERRNO_SHUTDOWN;
         goto _bail_dispatch;      
      }

      syscall = orig[0];

      switch (syscall & MASK_MAJOR) {

         case MAJOR_FUTEX:
            ret = syscall_futex(syscall, curr, end);
            if (SUCCESS != ret && ERRNO_BEATING_A_DEAD_HORSE != ret) { 
#ifdef DEBUG
               fprintf(stderr, "%s: [D] error during futex()\n", STR_THREAD_NAME);
#endif
            }
            break;

         case MAJOR_PAUSE:
            if (SUCCESS != (ret = syscall_pause(syscall, curr, end))) {
#ifdef DEBUG
               fprintf(stderr, "%s: [D] error during pause()\n", STR_THREAD_NAME);
#endif
            }
            break;

         case MAJOR_SENDMSG:
            if (SUCCESS != (ret = syscall_sendmsg(syscall, curr, end))) {
#ifdef DEBUG
               fprintf(stderr, "%s: [D] error during sendmsg()\n", STR_THREAD_NAME);
#endif
            }
            break;

         case MAJOR_PROC:
            if (SUCCESS != (ret = syscall_proc(syscall, curr, end))) {
#ifdef DEBUG
               fprintf(stderr, "%s: [D] error during proc()\n", STR_THREAD_NAME);
#endif
            }
            break;

         case MAJOR_TGKILL:
            if (SUCCESS != (ret = syscall_tgkill(syscall, curr, end))) {
#ifdef DEBUG
               fprintf(stderr, "%s: [D] error during tgkill()\n", STR_THREAD_NAME);
#endif
            }
            break;

         default:
#ifdef DEBUG
            fprintf(stderr, "%s: [D] invalid MAJOR syscall: 0x%02x\n", STR_THREAD_NAME, syscall);
#endif
            ret = ERRNO_INVALID_SYSCALL;
            break;
      }
   }

_bail_dispatch:
#ifdef DEBUG
   indent_lvl--;
   DEBUG_INDENT_PRINT("syscall_dispatch()");
#ifdef DEBUG_STACK
   fprintf(stderr, " ESP @ 0x%08x", get_esp());
#endif
   fprintf(stderr, "\n");
#endif

   return ret;
}

int main() {

#ifdef DEBUG
   fprintf(stderr, "\n\n\n");
   DEBUG_INDENT_PRINT("main()");
#ifdef DEBUG_STACK
   fprintf(stderr, " ESP @ 0x%08x", get_esp());
#endif
   fprintf(stderr, "\n");
   indent_lvl = 1;
#endif

   int ret = SUCCESS;
   char buf[256];

   for (int i=1; i<=NUM_THREADS; i++) { thread_state[i] = MAJOR_UNKNOWN; }

   timeToWait.tv_sec = LISTEN_TIMEOUT;
   timeToWait.tv_usec = 0;

   // Intialize the PI queue
   if (NULL == (pi_queue = list_create())) { 
#ifdef DEBUG
      fprintf(stderr, "%s: [E] error during list_create()\n", STR_THREAD_NAME);
#endif
      ret = ERRNO_ALLOC;
      goto _bail_main;
   }

   while (1) {

#ifdef DEBUG
      fprintf(stderr, "%s: [D] syscall #%d\n", STR_THREAD_NAME, ++count_syscalls);
#endif 

      memset(buf, 0, sizeof(buf));
      char *curr = buf;

      // Read in the length of the syscall buffer
      size_t rx_bytes = 0;
      if (SUCCESS != (ret = receive_all(STDIN, buf, 1, &rx_bytes)) || rx_bytes != 1) {
   #ifdef DEBUG
         fprintf(stderr, "%s: [D] failed to read length byte; bailing...\n", STR_THREAD_NAME);
   #endif
         goto _bail_main;
      }

      unsigned char len = buf[0];

      // If a zero length is specified, shutdown everything.
      if ('\0' == len) { 
#ifdef DEBUG
         fprintf(stderr, "%s: [D] got shutdown signal; bailing...\n", STR_THREAD_NAME);
#endif
         goto _bail_main; 
      }
      
      // TODO: Why is transmit() returning EINVAL? (according to /usr/include/libcgc.h)
      if (SUCCESS != (ret = receive_all(STDIN, buf, len, &rx_bytes)) || rx_bytes != len) {
   #ifdef DEBUG
         fprintf(stderr, "%s: [E] wrong number of syscall bytes read; bailing...\n", STR_THREAD_NAME);
   #endif
         goto _bail_main; 
      }

      // forcibly NULL-terminate the buffer
      buf[len] = '\0';

      // start the parsing
      if (ERRNO_SHUTDOWN == syscall_dispatch(&curr, buf+len)) { goto _bail_main; }
   }

   // This should happen on shutdowns.
_bail_main:
#ifdef DEBUG
   indent_lvl--;
   fprintf(stderr, "WE'RE EXITING; ret = %d\n", ret);
   DEBUG_INDENT_PRINT("main()");
#ifdef DEBUG_STACK
   fprintf(stderr, " ESP @ 0x%08x", get_esp());
#endif
#endif

   return ret;
}

