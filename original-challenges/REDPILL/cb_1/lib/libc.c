#include <libcgc.h>
#include "libc.h"

#ifdef DEBUG
char *str_tids[] = { "K", "T1", "T2", "T3", "T4", "T5" };
char *str_syscall[] = { 

  ////
  // FUTEX: 0000 0000b (0 / 0x0) - 0001 1111b (15 / 0x1F)
  ////

  // FUTEX_WAIT: 0 - 3
  "FUTEX_WAIT",         // 0000 0000b
  "FUTEX_WAIT_ACK",     // 0000 0001b
  "FUTEX_WAIT_PENDING", // 0000 0010b
  "FUTEX_WAIT_INVALID", // 0000 0011b

  // FUTEX_WAKE: 4 - 7
  "FUTEX_WAKE",         // 0000 0100b
  "FUTEX_WAKE_ACK",     // 0000 0101b
  "FUTEX_WAKE_PENDING", // 0000 0110b
  "FUTEX_WAKE_INVALID", // 0000 0111b

  // FUTEX_FD: 8 - 11
  "FUTEX_FD",           // 0000 1000b
  "FUTEX_FD_ACK",       // 0000 1001b
  "FUTEX_FD_PENDING",   // 0000 1010b
  "FUTEX_FD_INVALID",   // 0000 1011b

  // FUTEX_REQUEUE_PI: (12 / 0x0C) - (15 / 0x0F)
  "FUTEX_REQUEUE_PI",         // 0000 1100b
  "FUTEX_REQUEUE_PI_ACK",     // 0000 1101b
  "FUTEX_REQUEUE_PI_PENDING", // 0000 1110b
  "FUTEX_REQUEUE_PI_INVALID", // 0000 1111b

  // FUTEX_CMP_REQUEUE_PI: (16 / 0x10) - (19 / 0x13)
  "FUTEX_CMP_REQUEUE_PI",         // 0001 0000b
  "FUTEX_CMP_REQUEUE_PI_ACK",     // 0001 0001b
  "FUTEX_CMP_REQUEUE_PI_PENDING", // 0001 0010b
  "FUTEX_CMP_REQUEUE_PI_INVALID", // 0001 0011b

  // UNUSED in FUTEX space: 0001 1000b (24 / 0x18) - 0001 1111b (31 / 0x1F)
  "FUTEX_UNUSED", "FUTEX_UNUSED", "FUTEX_UNUSED", "FUTEX_UNUSED", 
  "FUTEX_UNUSED", "FUTEX_UNUSED", "FUTEX_UNUSED", "FUTEX_UNUSED", 
  "FUTEX_UNUSED", "FUTEX_UNUSED", "FUTEX_UNUSED", "FUTEX_UNUSED",

  ////
  // PAUSE: 0010 0000b (32 / 0x20) - 0011 1111b (63 / 0x3F)
  ////

  // PAUSE_DURATION
  "PAUSE_DURATION", // 0010 0000b
  "PAUSE_INVALID",  // 0010 0001b
  "PAUSE_INVALID",  // 0010 0010b
  "PAUSE_INVALID",  // 0010 0011b

  // UNUSED in PAUSE space: 0010 0100b (36 / 0x24) - 0011 1111b (63 / 0x3F)
  "PAUSE_UNUSED", "PAUSE_UNUSED", "PAUSE_UNUSED", "PAUSE_UNUSED", 
  "PAUSE_UNUSED", "PAUSE_UNUSED", "PAUSE_UNUSED", "PAUSE_UNUSED", 
  "PAUSE_UNUSED", "PAUSE_UNUSED", "PAUSE_UNUSED", "PAUSE_UNUSED", 
  "PAUSE_UNUSED", "PAUSE_UNUSED", "PAUSE_UNUSED", "PAUSE_UNUSED", 
  "PAUSE_UNUSED", "PAUSE_UNUSED", "PAUSE_UNUSED", "PAUSE_UNUSED", 
  "PAUSE_UNUSED", "PAUSE_UNUSED", "PAUSE_UNUSED", "PAUSE_UNUSED", 
  "PAUSE_UNUSED", "PAUSE_UNUSED", "PAUSE_UNUSED", "PAUSE_UNUSED", 

  ////
  // SENDMSG: 0100 0000b (64 / 0x40) - 0101 1111b (95 / 0x5F)
  ////

  // SENDMSG_RECURSE
  "SENDMSG_RECURSE",         // 0100 0000b
  "SENDMSG_RECURSE_ACK",     // 0100 0001b
  "SENDMSG_RECURSE_PENDING", // 0100 0010b
  "SENDMSG_RECURSE_INVALID", // 0100 0011b 

  // UNUSED in SENDMSG space: 0100 0100b (68 / 0x44) - 0101 1111b (95 / 0x5F)
  "SENDMSG_UNUSED", "SENDMSG_UNUSED", "SENDMSG_UNUSED", "SENDMSG_UNUSED",
  "SENDMSG_UNUSED", "SENDMSG_UNUSED", "SENDMSG_UNUSED", "SENDMSG_UNUSED",
  "SENDMSG_UNUSED", "SENDMSG_UNUSED", "SENDMSG_UNUSED", "SENDMSG_UNUSED",
  "SENDMSG_UNUSED", "SENDMSG_UNUSED", "SENDMSG_UNUSED", "SENDMSG_UNUSED",
  "SENDMSG_UNUSED", "SENDMSG_UNUSED", "SENDMSG_UNUSED", "SENDMSG_UNUSED",
  "SENDMSG_UNUSED", "SENDMSG_UNUSED", "SENDMSG_UNUSED", "SENDMSG_UNUSED",
  "SENDMSG_UNUSED", "SENDMSG_UNUSED", "SENDMSG_UNUSED", "SENDMSG_UNUSED",

  ////
  // PROC: 0110 0000b (96 / 0x60) - 0111 1111b (127 / 0x7C)
  ////

  // PROC_THREAD_STATE
  "PROC_THREAD_STATE", // (96 / 0x60)
  "PROC_THREAD_STATE_INVALID",
  "PROC_THREAD_STATE_INVALID",
  "PROC_THREAD_STATE_INVALID",

  // PROC_LIST_DUMP
  "PROC_LIST_DUMP",   // (100 / 0x64)
  "PROC_LIST_DUMP_INVALID",
  "PROC_LIST_DUMP_INVALID",
  "PROC_LIST_DUMP_INVALID",

  // UNUSED in PROC space: 104 - 127 / 0x7C
  "PROC_UNUSED", "PROC_UNUSED", "PROC_UNUSED", "PROC_UNUSED", 
  "PROC_UNUSED", "PROC_UNUSED", "PROC_UNUSED", "PROC_UNUSED",
  "PROC_UNUSED", "PROC_UNUSED", "PROC_UNUSED", "PROC_UNUSED",
  "PROC_UNUSED", "PROC_UNUSED", "PROC_UNUSED", "PROC_UNUSED",
  "PROC_UNUSED", "PROC_UNUSED", "PROC_UNUSED", "PROC_UNUSED",
  "PROC_UNUSED", "PROC_UNUSED", "PROC_UNUSED", "PROC_UNUSED",

  ////
  // TGKILL: 1000 0000b (128 / 0x80) - 1001 1111b (159 / 0x9F)
  ////
  "TGKILL",         
  "TGKILL_ACK",     
  "TGKILL_PENDING", 
  "TGKILL_INVALID",

  // UNUSED in TGKILL space: 132 / 0x84 - 159 / 0x9F
  "TGKILL_UNUSED", "TGKILL_UNUSED", "TGKILL_UNUSED", "TGKILL_UNUSED",
  "TGKILL_UNUSED", "TGKILL_UNUSED", "TGKILL_UNUSED", "TGKILL_UNUSED",
  "TGKILL_UNUSED", "TGKILL_UNUSED", "TGKILL_UNUSED", "TGKILL_UNUSED",
  "TGKILL_UNUSED", "TGKILL_UNUSED", "TGKILL_UNUSED", "TGKILL_UNUSED",
  "TGKILL_UNUSED", "TGKILL_UNUSED", "TGKILL_UNUSED", "TGKILL_UNUSED",
  "TGKILL_UNUSED", "TGKILL_UNUSED", "TGKILL_UNUSED", "TGKILL_UNUSED",
  "TGKILL_UNUSED", "TGKILL_UNUSED", "TGKILL_UNUSED", "TGKILL_UNUSED",

  ////
  // Some of the MAJOR space is unused.
  ////

  // (160 / 0xA0) - (223 / 0xDF)
  "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED",
  "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED",
  "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED",
  "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED",

  "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED",
  "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED",
  "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED",
  "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED", "UNUSED",

  ////
  // The final MAJOR block is reserved for the "unknown" / initial state.
  ////

  // (224 / 0xE0 - 255 / 0xFF)
  "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN",
  "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN",
  "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN",
  "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN", "UNKNOWN",
};
#endif
// ^ DEBUG

// Address fragmentation issue.
// Keep looping until we've receive'd count bytes.
// Fixed fd ignoring bug from JUSTINTIME
int receive_all(int fd, void *buf, size_t count, size_t *rx_bytes) {

   int ret = SUCCESS;
   size_t bytes_left = count;
   size_t rx_bytes_local = 0;

   while (bytes_left) {

      rx_bytes_local = 0;

      if (SUCCESS != (ret = receive(fd, buf+(count-bytes_left), bytes_left, &rx_bytes_local))) {
#ifdef DEBUG
         fprintf(stderr, "[E] receive () call within receive_all() failed\n");
#endif
         goto bail;
      }

      bytes_left -= rx_bytes_local;

      // Assume EOF if 0-lengthed buffer.
      if (0 == rx_bytes_local) {
         if (NULL != rx_bytes) { *rx_bytes = count-bytes_left; }
         goto bail;
      }
   }

   // If we got here, then we got all the bytes.
   if (NULL != rx_bytes) { *rx_bytes = count; }

bail:
   return ret;
}

// Address fragmentation issue.
// Keep looping until we've transmit'ed count bytes.
// Fixed fd ignoring bug from JUSTINTIME
int transmit_all(int fd, const void *buf, size_t count, size_t *tx_bytes) {

   int ret = SUCCESS;
   size_t bytes_left = count;
   size_t tx_bytes_local = 0;

   while (bytes_left) {

      tx_bytes_local = 0;

      if (SUCCESS != (ret = transmit(fd, buf, bytes_left, &tx_bytes_local))) {
#ifdef DEBUG
         fprintf(stderr, "[E] transmit () call within transmit_all() failed\n");
#endif
         goto bail;
      }

      bytes_left -= tx_bytes_local;

      // Assume EOF if 0-lengthed buffer.
      if (0 == tx_bytes_local) {
         if (NULL != tx_bytes) { *tx_bytes = count-bytes_left; }
         goto bail;
      }
   }

   // If we got here, then we got all the bytes.
   if (NULL != tx_bytes) { *tx_bytes = count; }

bail:
   return ret;
}

// Send a packet to a chosen thread ID.
// Expects the caller to validate tid.
int pkt_send(size_t tid, char src, char msg) {

  int ret = SUCCESS;
  struct packet pkt;

  int fd = tid2sendpipe(tid);

  if (SUCCESS != (ret = pkt_serialize(&pkt, src, msg))) { return ret; }

#ifdef DEBUG
  fprintf(stderr, "\t\t%s -> fd #%d (%s):\n", str_tids[src], fd, str_tids[tid]);
  pkt_dump(&pkt);
#endif

  if (SUCCESS != (ret = transmit_all(fd, &pkt, sizeof(pkt), NULL))) { return ret; }

  return ret;
}

int pkt_serialize(struct packet *pkt, char src, char msg) {
  int ret = SUCCESS;

  pkt->src = src;
  pkt->msg = msg;

  return ret;
}

unsigned char pkt_get_src(struct packet *pkt) { return pkt->src; }
unsigned char pkt_get_msg(struct packet *pkt) { return pkt->msg; }

#ifdef DEBUG
void pkt_dump(struct packet *pkt) {

  // sanity
  if (pkt->src < 0 || pkt->src > NUM_THREADS) { 
    fprintf(stderr, "[E] invalid pkt (src OOB): 0x%02x\n", pkt->src);
    return;
  }

  // msg doesn't need to be validated because the str_syscall[] array has 256 entries.
  fprintf(stderr, "\t\tVVV packet VVV\n");
  fprintf(stderr, "\t\tpkt->src: 0x%02x - %s\n", pkt->src, str_tids[pkt->src]);
  fprintf(stderr, "\t\tpkt->msg: 0x%02x - %s\n", pkt->msg, str_syscall[pkt->msg]);
  fprintf(stderr, "\t\t^^^ packet ^^^\n");
}
#endif

// Allocates and initializes a list.
// RETURNS
//  success: &(the new list)
//  failure: NULL
struct list * list_create() {
  struct list *new = NULL;
  if (SUCCESS != (allocate(PAGE_SZ, 0, (void *)&new))) { return NULL; }
  new->head = NULL;
  new->tail = NULL;
  return new;
}

// Append the provided node to the provided list.
// RETURNS
//  success: SUCCESS
//  failure: ERRNO_LIST_PUSH
int list_push(struct list *lst, struct node *nd) {

  int ret = SUCCESS;

  // Cowardly refuse to add the same value twice
  if (NULL != list_find(lst, nd->value)) {
  #ifdef DEBUG
      fprintf(stderr, "K: [D] list_push(): refusing dupe value push\n");
  #endif  
      return ERRNO_LIST_PUSH;             
    }

  nd->next = NULL;
  nd->prev = lst->tail;

  // 0 elements (base case)
  if (NULL == lst->head) {
    lst->head = nd;
    lst->tail = nd;

  // >= 1 element
  } else {
    lst->tail->next = nd; 
    lst->tail = nd;
  }

#ifdef DEBUG_LISTS
  fprintf(stderr, "\t\tpushed node; dump after:\n");
  list_dump(lst);
#endif

  return ret;
}

// Walk the list forward, identify first matching node for provided value.
// RETURNS:
//  found: VA of the matching node
//  not found: NULL
struct node * list_find(struct list *lst, char value) {

  struct node *curr = lst->head;
#ifdef DEBUG
  fprintf(stderr, "K: [D] list_find(); curr = %p\n", curr);
#endif

  while (NULL != curr && value != curr->value) { 
#ifdef DEBUG
  fprintf(stderr, "K: [D] list_find(); curr = %p\n", curr);
#endif
    curr = curr->next; 
  }
  return curr;
}

// Remove the first element in the list whose value matches the provided value.
// RETURNS:
//  success: VA of the unlinked node
//  failure: NULL
struct node * list_remove(struct list *lst, char value) {

#ifdef DEBUG_LISTS
  fprintf(stderr, "K: [D] enter: list_remove\n");
#endif

  struct node *needle = NULL;

  if (NULL == (needle = list_find(lst, value))) { return NULL; }

  // if we're removing the first element...
  if (lst->head == needle) { lst->head = needle->next; }

  // if we're removing the last element...
  if (lst->tail == needle) { lst->tail = needle->prev; }

  // unlink any adjacent nodes
  if (needle->prev) { needle->prev->next = needle->next; }
  if (needle->next) { needle->next->prev = needle->prev; }

#ifdef DEBUG_LISTS
  fprintf(stderr, "K: [D] exit: list_remove, needle: %p\n", needle);
  fprintf(stderr, "\t\tremoved node; dump after:\n");
  list_dump(lst);
#endif

  return needle;
}

// Allocate space for and initialize a new node struct.
// RETURNS:
//  success: VA of new node
//  failure: NULL
struct node * node_create(char value) {
  struct node *new = NULL;
  if (SUCCESS != (allocate(PAGE_SZ, 0, (void *)&new))) { return NULL; }
  new->value = value;
  new->next = NULL; // these will be set during list insertion
  new->prev = NULL;
  return new;
}

// Reset node contents and deallocate node.
// RETURNS
//  success: 0 (SUCCESS)
//  failue: various ERRNO
int node_destroy(struct node *nd) {

  int ret = SUCCESS;

#ifdef DEBUG_LISTS
  fprintf(stderr, "K: [D] enter: node_destroy\n");
#endif

  nd->value = 0;
  nd->next = NULL;
  nd->prev = NULL;

  ret = deallocate((void *)nd, PAGE_SZ);

#ifdef DEBUG_LISTS
  fprintf(stderr, "K: [D] exit: node_destroy; ret = %d\n", ret);
#endif

  return ret;
}

// MODIFIED FROM: FASTLANE
// NOTE: not POSIX
// MOD: it works in reverse
// RETURN: the first argument
unsigned char * memset(void *b, char c, size_t len) {

  char *ptr = (char *)b; 
  while (len) {
      ptr[len-1] = c;
      len--;
  }
  return b;
}

// REUSE: FASTLANE
// Emulate sleep() via a timeout given to fdwait().
void pause(size_t seconds) {

    struct timeval tv;

    tv.tv_sec = seconds;
    tv.tv_usec = 0;

    fdwait(0, NULL, NULL, &tv, NULL);
}
// END REUSE

#ifdef DEBUG

void list_dump(struct list *lst) {

  struct node *curr = lst->head;

  fprintf(stderr, "\t\tVVV list VVV\n");
  while (curr) {
    fprintf(stderr, "\t\t0x%08x: node\n", curr);
    fprintf(stderr, "\t\t\t0x%08x: node->valu: 0x%02x\n", &(curr->value), curr->value);
    fprintf(stderr, "\t\t\t0x%08x: node->next: %p\n", &(curr->next), curr->next);
    fprintf(stderr, "\t\t\t0x%08x: node->prev: %p\n", &(curr->prev), curr->prev);
    curr = curr->next;
  }
  fprintf(stderr, "\t\t^^^ list ^^^\n");
}

inline void DEBUG_INDENT_PRINT(char *msg) {
   for (size_t i = indent_lvl; 0<i; i--) { fprintf(stderr, "-"); }
   fprintf(stderr, msg);
}

////
// The following is verbatim from EAGLE_00004, but isn't included in the 
// released binary (DEBUG is not defined), so this reuse shouldn't be a concern.
////

typedef __builtin_va_list va_list;
#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap) __builtin_va_end(ap)
#define va_arg(ap, type) __builtin_va_arg(ap, type)

static FILE std_files[3] = { {0, _FILE_STATE_OPEN}, {1, _FILE_STATE_OPEN}, {2, _FILE_STATE_OPEN} };

FILE *stdin = &std_files[0];
FILE *stdout = &std_files[1];
FILE *stderr = &std_files[2];

int vfprintf(FILE *stream, const char *format, va_list ap);
int vdprintf(int fd, const char *format, va_list ap);

#define IS_DIGIT     1
#define IS_UPPER     2
#define IS_LOWER     4
#define IS_SPACE     8
#define IS_XDIGIT    16
#define IS_CTRL      32
#define IS_BLANK     64

#define IS_ALPHA     (IS_LOWER | IS_UPPER)
#define IS_ALNUM     (IS_ALPHA | IS_DIGIT)

static unsigned char type_flags[256] = {
     0, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL,
     IS_CTRL, IS_SPACE | IS_BLANK, IS_SPACE, IS_SPACE, IS_SPACE, IS_SPACE, IS_CTRL, IS_CTRL,

     IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL,
     IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL,

     IS_SPACE | IS_BLANK, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

     IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT,
     IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT, 0, 0, 0, 0, 0, 0,

     0, IS_UPPER | IS_XDIGIT, IS_UPPER | IS_XDIGIT, IS_UPPER | IS_XDIGIT, IS_UPPER | IS_XDIGIT, IS_UPPER | IS_XDIGIT, IS_UPPER | IS_XDIGIT, IS_UPPER,
     IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER,

     IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER,
     IS_UPPER, IS_UPPER, IS_UPPER, 0, 0, 0, 0, 0,

     0, IS_LOWER | IS_XDIGIT, IS_LOWER | IS_XDIGIT, IS_LOWER | IS_XDIGIT, IS_LOWER | IS_XDIGIT, IS_LOWER | IS_XDIGIT, IS_LOWER | IS_XDIGIT, IS_LOWER,
     IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER,

     IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER,
     IS_LOWER, IS_LOWER, IS_LOWER, 0, 0, 0, 0, 0,
};

int isalpha(int c) {
   return (type_flags[c & 0xff] & IS_ALPHA) != 0;
}

int isdigit(int c) {
   return (type_flags[c & 0xff] & IS_DIGIT) != 0;
}

int isxdigit(int c) {
   return (type_flags[c & 0xff] & IS_XDIGIT) != 0;
}

int toupper(int c) {
   if (isalpha(c)) {
      return c & ~0x20;
   }
   return c;
}

size_t strlen(const char *str) {
   size_t res = 0;
   while (*str++) {res++;}
   return res;
}

int vfprintf(FILE * stream, const char *format, va_list ap) {
   return vdprintf(stream->fd, format, ap);
}

int fprintf(FILE * stream, const char *format, ...) {
   va_list va;
   va_start(va, format);
   return vfprintf(stream, format, va);
}

struct _fd_printer {
   int fd;
   int err;
   unsigned int count;
};

//if flag != 0 return number of chars output so far
static unsigned int fd_printer(char ch, void *_fp, int flag) {
   struct _fd_printer *fp = (struct _fd_printer *)_fp;
   if (flag) {
      return fp->count;
   }
   else {
      fp->count++;
      transmit(fp->fd, &ch, 1, NULL);
   }
   return 0;
}

#define STATE_NORMAL 0
#define STATE_ESCAPE 1
#define STATE_PERCENT 2
#define STATE_OCTAL 3
#define STATE_HEX 4
#define STATE_FLAGS 5
#define STATE_WIDTH 6
#define STATE_PRECISION 7
#define STATE_LENGTH 8
#define STATE_CONVERSION 9
#define STATE_WIDTH_ARG 10
#define STATE_WIDTH_VAL 11
#define STATE_PRECISION_ARG 12
#define STATE_PRECISION_VAL 13
#define STATE_NARG 15

#define FLAGS_TICK 1
#define FLAGS_LEFT 2
#define FLAGS_SIGN 4
#define FLAGS_SPACE 8
#define FLAGS_HASH 16
#define FLAGS_ZERO 32

#define LENGTH_H 1
#define LENGTH_HH 2
#define LENGTH_L 3
#define LENGTH_J 5
#define LENGTH_Z 6
#define LENGTH_T 7
#define LENGTH_CAPL 8

static char *r_utoa(unsigned int val, char *outbuf) {
   char *p = outbuf;
   *p = '0';
   while (val) {
      *p++ = (val % 10) + '0';
      val /= 10;
   }
   return p != outbuf ? (p - 1) : p;
}

//outbuf needs to be at least 22 chars
static char *r_llotoa(unsigned long long val, char *outbuf) {
   char *p = outbuf;
   *p = '0';
   while (val) {
      *p++ = (val & 7) + '0';
      val >>= 3;
   }
   return p != outbuf ? (p - 1) : p;
}

static char *r_otoa(unsigned int val, char *outbuf) {
   return r_llotoa(val, outbuf);
}

//outbuf needs to be at least 22 chars
static char *r_llxtoa(unsigned long long val, char *outbuf, int caps) {
   char *p = outbuf;
   *p = '0';
   while (val) {
      char digit = (char)(val & 0xf);
      if (digit < 10) {
         digit += '0';
      }
      else {
         digit = caps ? (digit + 'A' - 10) : (digit + 'a' - 10);
      }
      *p++ = digit;
      val >>= 4;
   }
   return p != outbuf ? (p - 1) : p;
}

static char *r_xtoa(unsigned int val, char *outbuf, int caps) {
   return r_llxtoa(val, outbuf, caps);
}

static int hex_value_of(char ch) {
   if (isdigit(ch)) {
      return ch - '0';
   }
   else if (isalpha(ch)) {
      return toupper(ch) - 'A' + 10;
   }
   return -1;
}

//func is responsible for outputing the given character
//user is a pointer to data required by func
static void printf_core(unsigned int (*func)(char, void *, int), void *user, const char *format, va_list ap) {
   int state = STATE_NORMAL;
   int flags;
   int digit_count = 0;
   int value = 0;
   char ch;
   int arg_count = 0;
   int width_value;
   int prec_value;
   int field_arg;
   int length;
   char **args = (char**)ap;
   for (ch = *format++; ch; ch = *format++) {
      switch (state) {
         case STATE_NORMAL:
            if (ch == '%') {
               state = STATE_PERCENT;
            }
            else if (ch == '\\') {
               state = STATE_ESCAPE;
            }
            else {
               func(ch, user, 0);
            }
            break;
         case STATE_ESCAPE:
            switch (ch) {
               case 'n':
                  func('\n', user, 0);
                  break;
               case 't':
                  func('\t', user, 0);
                  break;
               case 'r':
                  func('\r', user, 0);
                  break;
               case 'b':
                  func('\b', user, 0);
                  break;
               case 'f':
                  func('\f', user, 0);
                  break;
               case 'v':
                  func('\v', user, 0);
                  break;
               case '\\': case '\'': case '"':
                  func(ch, user, 0);
                  break;
               case 'x':
                  state = STATE_HEX;
                  digit_count = 0;
                  value = 0;
                  break;
               default:
                  if (ch > '0' && ch < '8') {
                     state = STATE_OCTAL;
                     digit_count = 1;
                     value = ch - '0';
                  }
                  else {
                     func(*format, user, 0);
                  }
                  break;
            }
            if (state == STATE_ESCAPE) {
               state = STATE_NORMAL;
            }
            break;
         case STATE_PERCENT:
            if (ch == '%') {
               func(ch, user, 0);
               state = STATE_NORMAL;
            }
            else {
               state = STATE_NARG;
               flags = 0;
               format--;
            }
            break;
         case STATE_OCTAL:
            if (ch > '0' && ch < '8' && digit_count < 3) {
               digit_count++;
               value = value * 8 + (ch - '0');
               if (digit_count == 3) {
                  func(value, user, 0);
                  state = STATE_NORMAL;
               }
            }
            else {
               func(value, user, 0);
               state = STATE_NORMAL;
               format--;
            }
            break;
         case STATE_HEX:
            if (isxdigit(ch) && digit_count < 2) {
               digit_count++;
               value = value * 16 + hex_value_of(ch);
               if (digit_count == 2) {
                  func(value, user, 0);
                  state = STATE_NORMAL;
               }
            }
            else {
               func(value, user, 0);
               state = STATE_NORMAL;
               format--;
            }
            break;
         case STATE_NARG:
            width_value = -1;
            prec_value = -1;
            flags = 0;
            length = 0;
            field_arg = -1;
            if (ch == '0') {
               format--;
               state = STATE_FLAGS;
               break;
            }
            if (isdigit(ch)) {
               //could be width or could be arg specifier or a 0 flag
               //width and arg values don't start with 0
               width_value = 0;
               while (isdigit(ch)) {
                  width_value = width_value * 10 + (ch - '0');
                  ch = *format++;
               }
               if (ch == '$') {
                  field_arg = width_value - 1;
                  width_value = 0;
                  state = STATE_FLAGS;
               }
               else {
                  //this was a width
                  format--;
                  state = STATE_PRECISION;
               }
            }
            else {
               format--;
               state = STATE_FLAGS;
            }
            break;
         case STATE_FLAGS:
            switch (ch) {
               case '\'':
                  flags |= FLAGS_TICK;
                  break;
               case '-':
                  flags |= FLAGS_LEFT;
                  break;
               case '+':
                  flags |= FLAGS_SIGN;
                  break;
               case ' ':
                  flags |= FLAGS_SPACE;
                  break;
               case '#':
                  flags |= FLAGS_HASH;
                  break;
               case '0':
                  flags |= FLAGS_ZERO;
                  break;
               default:
                  format--;
                  if ((flags & (FLAGS_ZERO | FLAGS_LEFT)) == (FLAGS_ZERO | FLAGS_LEFT)) {
                     //if both '-' and '0' appear, '0' is ignored
                     flags &= ~FLAGS_ZERO;
                  }
                  state = STATE_WIDTH;
                  break;
            }
            break;
         case STATE_WIDTH:
            if (ch == '*') {
               ch = *format++;
               int width_arg = 0;
               if (isdigit(ch)) {
                  while (isdigit(ch)) {
                     width_arg = width_arg * 10 + (ch - '0');
                     ch = *format++;
                  }
                  width_arg--;
                  if (ch != '$') {
                     //error
                  }
               }
               else {
                  width_arg = arg_count++;
                  format--;
               }
               width_value = (int)args[width_arg];
            }
            else if (isdigit(ch)) {
               width_value = 0;
               while (isdigit(ch)) {
                  width_value = width_value * 10 + (ch - '0');
                  ch = *format++;
               }
               format--;
            }
            else {
               //no width specified
               format--;
            }
            state = STATE_PRECISION;
            break;
         case STATE_PRECISION:
            if (ch == '.') {
               //have a precision
               ch = *format++;
               if (ch == '*') {
                  ch = *format++;
                  int prec_arg = 0;
                  if (isdigit(ch)) {
                     while (isdigit(ch)) {
                        prec_arg = prec_arg * 10 + (ch - '0');
                        ch = *format++;
                     }
                     prec_arg--;
                     if (ch != '$') {
                        //error
                     }
                  }
                  else {
                     prec_arg = arg_count++;
                     format--;
                  }
                  prec_value = (int)args[prec_arg];
               }
               else if (isdigit(ch)) {
                  prec_value = 0;
                  while (isdigit(ch)) {
                     prec_value = prec_value * 10 + (ch - '0');
                     ch = *format++;
                  }
                  format--;
               }
               else {
                  //no precision specified
                  format--;
               }
            }
            else {
               //no precision specified
               format--;
            }
            state = STATE_LENGTH;
            break;
         case STATE_LENGTH:
            switch (ch) {
               case 'h':
                  length = LENGTH_H;
                  if (*format == 'h') {
                     length++;
                     format++;
                  }
                  break;
               case 'l':
                  length = LENGTH_L;
                  if (*format == 'l') {
//                     length++;
                     format++;
                  }
                  break;
               case 'j':
                  length = LENGTH_J;
                  break;
               case 'z':
                  length = LENGTH_Z;
                  break;
               case 't':
                  length = LENGTH_T;
                  break;
               case 'L':
                  length = LENGTH_CAPL;
                  break;
               default:
                  format--;
                  break;
            }
            state = STATE_CONVERSION;
            break;
         case STATE_CONVERSION: {
            char num_buf[32];
            char *num_ptr;
            int use_caps = 1;
            int sign;
            int val;
            long long llval;
            if (field_arg == -1) {
               field_arg = arg_count++;
            }
            switch (ch) {
               case 'd': case 'i': {
                  int len;
                  switch (length) {
                     case LENGTH_H:
                        val = (short)(int)args[field_arg];
                        sign = val < 0;
                        if (sign) {
                           val = -val;
                        }
                        num_ptr = r_utoa(val, num_buf);
                        break;
                     case LENGTH_HH:
                        val = (char)(int)args[field_arg];
                        sign = val < 0;
                        if (sign) {
                           val = -val;
                        }
                        num_ptr = r_utoa(val, num_buf);
                        break;
                     case LENGTH_L:
                     default:
                        val = (long)args[field_arg];
                        sign = val < 0;
                        if (sign) {
                           val = -val;
                        }
                        num_ptr = r_utoa(val, num_buf);
                        break;
                  }
                  len = num_ptr - num_buf + 1;
                  if (width_value == -1) {
                     //by default min length is the entire value
                     width_value = len;
                     if (sign || (flags & FLAGS_SIGN)) {
                        width_value++;
                     }
                  }
                  if (prec_value == -1) {
                     //by default max is entire value
                     prec_value = len;
                     if ((flags & FLAGS_ZERO) != 0 && prec_value < width_value) {
                        //widen precision if necessary to pad to width with '0'
                        if (sign || (flags & FLAGS_SIGN)) {
                           prec_value = width_value - 1;
                        }
                        else {
                           prec_value = width_value;
                        }
                     }
                  }
                  else {
                     if (prec_value < len) {
                        prec_value = len;
                     }
                     //number won't need leading zeros
                     flags &= ~FLAGS_ZERO;
                  }
                  if (flags & FLAGS_LEFT) {
                     if (sign) {
                        func('-', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     else if ((flags & FLAGS_SIGN) != 0) {
                        func('+', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (width_value != 0) {
                        func(' ', user, 0);
                        width_value--;
                     }
                  }
                  else {
                     while (width_value > (prec_value + 1)) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     if (sign) {
                        func('-', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     else if ((flags & FLAGS_SIGN) != 0) {
                        func('+', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     if (width_value > prec_value) {
                        func(' ', user, 0);
                        width_value--;
                     }                        
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                     }
                  }
                  break;
               }
               case 'o': {
                  int len;
                  switch (length) {
                     case LENGTH_H:
                        num_ptr = r_otoa((unsigned short)(unsigned int)args[field_arg], num_buf);
                        break;
                     case LENGTH_HH:
                        num_ptr = r_otoa((unsigned char)(unsigned int)args[field_arg], num_buf);
                        break;
                     case LENGTH_L:
                     default:
                        num_ptr = r_otoa((unsigned long)args[field_arg], num_buf);
                        break;
                  }
                  if (flags & FLAGS_HASH) {
                     if (*num_ptr != '0') {
                        num_ptr++;
                        *num_ptr = '0';
                     }
                  }
                  len = num_ptr - num_buf + 1;
                  if (width_value == -1) {
                     //by default min length is the entire value
                     width_value = len;
                  }
                  if (prec_value == -1) {
                     //by default max is entire value
                     prec_value = len;
                     if ((flags & FLAGS_ZERO) != 0 && prec_value < width_value) {
                        //widen precision if necessary to pad to width with '0'
                        prec_value = width_value;
                     }
                  }
                  else {
                     if (prec_value < len) {
                        prec_value = len;
                     }
                     flags &= ~FLAGS_ZERO;
                  }
                  if (flags & FLAGS_LEFT) {
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (width_value != 0) {
                        func(' ', user, 0);
                        width_value--;
                     }
                  }
                  else {
                     while (width_value > prec_value) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                     }
                  }
                  break;
               }
               case 'u': {
                  int len;
                  switch (length) {
                     case LENGTH_H:
                        num_ptr = r_utoa((unsigned short)(unsigned int)args[field_arg], num_buf);
                        break;
                     case LENGTH_HH:
                        num_ptr = r_utoa((unsigned char)(unsigned int)args[field_arg], num_buf);
                        break;
                     case LENGTH_L:
                     default:
                        num_ptr = r_utoa((unsigned long)args[field_arg], num_buf);
                        break;
                  }
                  len = num_ptr - num_buf + 1;
                  if (width_value == -1) {
                     //by default min length is the entire value
                     width_value = len;
                  }
                  if (prec_value == -1) {
                     //by default max is entire value
                     prec_value = len;
                     if ((flags & FLAGS_ZERO) != 0 && prec_value < width_value) {
                        //widen precision if necessary to pad to width with '0'
                        prec_value = width_value;
                     }
                  }
                  else {
                     if (prec_value < len) {
                        prec_value = len;
                     }
                     flags &= ~FLAGS_ZERO;
                  }
                  if (flags & FLAGS_LEFT) {
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (width_value != 0) {
                        func(' ', user, 0);
                        width_value--;
                     }
                  }
                  else {
                     while (width_value > prec_value) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                     }
                  }
                  break;
               }
               case 'x':
                  use_caps = 0;  //now fall into X case
               case 'X': {
                  int len;
                  switch (length) {
                     case LENGTH_H:
                        num_ptr = r_xtoa((unsigned short)(unsigned int)args[field_arg], num_buf, use_caps);
                        break;
                     case LENGTH_HH:
                        num_ptr = r_xtoa((unsigned char)(unsigned int)args[field_arg], num_buf, use_caps);
                        break;
                     case LENGTH_L:
                     default:
                        num_ptr = r_xtoa((unsigned long)args[field_arg], num_buf, use_caps);
                        break;
                  }
                  len = num_ptr - num_buf + 1;
                  if (width_value == -1) {
                     //by default min length is the entire value
                     width_value = len;
                  }
                  if (prec_value == -1) {
                     //by default max is entire value
                     prec_value = len;
                     if ((flags & FLAGS_ZERO) != 0 && prec_value < width_value) {
                        //widen precision if necessary to pad to width with '0'
                        prec_value = width_value;
                     }
                  }
                  else {
                     if (prec_value < len) {
                        prec_value = len;
                     }
                     flags &= ~FLAGS_ZERO;
                  }
                  if (flags & FLAGS_LEFT) {
                     if (flags & FLAGS_HASH && (len != 1 || *num_ptr != '0')) {
                        func('0', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                        func(use_caps ? 'X' : 'x', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (width_value != 0) {
                        func(' ', user, 0);
                        width_value--;
                     }
                  }
                  else {
                     while (width_value > (prec_value + 2)) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     if (flags & FLAGS_HASH && (len != 1 || *num_ptr != '0')) {
                        func('0', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                        func(use_caps ? 'X' : 'x', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     else {
                        while (width_value > prec_value) {
                           func(' ', user, 0);
                           width_value--;
                        }
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                     }
                  }
                  break;
               }
               case 'f': case 'F':
                  break;
               case 'e': case 'E':
                  break;
               case 'g': case 'G':
                  break;
               case 'a': case 'A':
                  break;
               case 'c': {
                  unsigned char ch = (unsigned char)(unsigned int)args[field_arg];
                  if (width_value == -1) {
                     width_value = 1;
                  }
                  if (flags & FLAGS_LEFT) {
                     func((char)ch, user, 0);
                     if (width_value > 0) {
                        width_value--;
                     }
                     while (width_value != 0) {
                        func(' ', user, 0);
                        width_value--;
                     }
                  }
                  else {
                     while (width_value > 1) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     func(ch, user, 0);
                  }
                  break;
               }
               case 's': {
                  const char *s_arg = (const char *)args[field_arg];
                  int len = strlen(s_arg);
                  if (width_value == -1) {
                     //by default min length is the entire string
                     width_value = len;
                  }
                  if (prec_value == -1 || prec_value > len) {
                     //by default max is entire string but no less than width
                     prec_value = len;
                  }
                  if (flags & FLAGS_LEFT) {
                     while (prec_value != 0) {
                        func(*s_arg++, user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (width_value != 0) {
                        func(' ', user, 0);
                        width_value--;
                     }
                  }
                  else {
                     while (width_value > prec_value) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     while (prec_value != 0) {
                        func(*s_arg++, user, 0);
                        prec_value--;
                     }
                  }
                  break;
               }
               case 'p': {
                  int len;
                  flags |= FLAGS_HASH;
                  num_ptr = r_xtoa((unsigned int)args[field_arg], num_buf, 0);
                  len = num_ptr - num_buf + 1;
                  if (prec_value == -1) {
                     //by default max is entire value
                     prec_value = len;
                  }
                  else {
                     if (prec_value < len) {
                        prec_value = len;
                     }
                     flags &= ~FLAGS_ZERO;
                  }
                  if (width_value == -1) {
                     //by default min length is the entire value
                     width_value = prec_value + 2;
                  }
                  if (flags & FLAGS_LEFT) {
                     func('0', user, 0);
                     if (width_value > 0) {
                        width_value--;
                     }
                     func('x', user, 0);
                     if (width_value > 0) {
                        width_value--;
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (width_value != 0) {
                        func(' ', user, 0);
                        width_value--;
                     }
                  }
                  else {
                     while (width_value > (prec_value + 2)) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     func('0', user, 0);
                     if (width_value > 0) {
                        width_value--;
                     }
                     func('x', user, 0);
                     if (width_value > 0) {
                        width_value--;
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                     }
                  }
                  break;
               }
               case 'n': {
                  void *np = (void*)args[field_arg];
                  unsigned int len = func(0, user, 1);
                  switch (length) {
                     case LENGTH_HH:
                        *(unsigned char*)np = (unsigned char)len;
                        break;
                     case LENGTH_H:
                        *(unsigned short*)np = (unsigned short)len;
                        break;
                     case LENGTH_L:
                     default:
                        *(unsigned int*)np = len;
                        break;
                  }
                  break;
               }
               case 'C':
                  break;
               case 'S':
                  break;
               default:
                  break;
            }
            state = STATE_NORMAL;
            break;
         }
      }
   }
}

int vdprintf(int fd, const char *format, va_list ap) {
   struct _fd_printer fp;
   fp.fd = fd;
   fp.err = 0;
   fp.count = 0;
   printf_core(fd_printer, &fp, format, ap);
   return fp.count;
}

#endif

