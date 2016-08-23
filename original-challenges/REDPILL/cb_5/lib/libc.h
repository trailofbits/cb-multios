#ifndef LIBC_H
#define LIBC_H

// DEBUG
// #define DEBUG 1
// #define DEBUG_LISTS 1
// #define DEBUG_STACK 1
// #define DEBUG_SENDMSG 1

#define SERVICE_ID 00006
#define LISTEN_TIMEOUT 3
#define NUM_THREADS 5

#define PAGE_SZ 0x1000

// Errors / statuses
#define SUCCESS 0
#define ERRNO_SEND (SERVICE_ID+1)
#define ERR_RECV "[E] could not read or insufficient bytes\n"
#define ERRNO_RECV (SERVICE_ID+2)
#define ERRNO_ALLOC (SERVICE_ID+3)
#define ERRNO_INSUFFICIENT_BYTES (SERVICE_ID+4)
#define ERR_INVALID_SYSCALL "[E] invalid syscall\n"
#define ERRNO_INVALID_SYSCALL (SERVICE_ID+5)
#define ERR_INVALID_ARG "[E] invalid argument\n"
#define ERRNO_INVALID_ARG (SERVICE_ID+5)
#define ERRNO_LIST_PUSH (SERVICE_ID+7)
#define ERR_INVALID_STATE "[E] invalid state\n"
#define ERRNO_INVALID_ACK (SERVICE_ID+9)
#define ERRNO_BEATING_A_DEAD_HORSE (SERVICE_ID+10)
#define ERRNO_SHUTDOWN (SERVICE_ID+11)

// Thread IDs
#define TID_K 0
#define TID_T1 1
#define TID_T2 2
#define TID_T3 3
#define TID_T4 4
#define TID_T5 5

// syscall format 3.0:
// -------------------
// XXXX XXXX
// |||| |||+- ACK bit
// |||| ||+-- PENDING bit
// |||+-++--- MINOR action
// +++------- MAJOR action
#define IDX_MAJOR 	5
#define IDX_MINOR 	2
#define IDX_PENDING 1
#define IDX_ACK 	0

#define MASK_MAJOR 		(7<<IDX_MAJOR) 	 // XXX0 0000b
#define MASK_MINOR 		(7<<IDX_MINOR) 	 // 000X XX00b
#define MASK_PENDING 	(1<<IDX_PENDING) // 0000 00X0b
#define MASK_ACK 		(1<<IDX_ACK)	 // 0000 000Xb

#define MAJOR_FUTEX 	(0<<IDX_MAJOR)
#define MAJOR_PAUSE 	(1<<IDX_MAJOR)
#define MAJOR_SENDMSG	(2<<IDX_MAJOR)
#define MAJOR_PROC		(3<<IDX_MAJOR)
#define MAJOR_TGKILL	(4<<IDX_MAJOR)
#define MAJOR_MIN MAJOR_FUTEX
#define MAJOR_MAX MAJOR_TGKILL
#define MAJOR_UNKNOWN 	(7<<IDX_MAJOR)

#define MINOR_FUTEX_WAIT 			(0<<IDX_MINOR)
#define MINOR_FUTEX_WAKE 			(1<<IDX_MINOR)
#define MINOR_FUTEX_FD 				(2<<IDX_MINOR)
#define MINOR_FUTEX_REQUEUE_PI 		(3<<IDX_MINOR)
#define MINOR_FUTEX_CMP_REQUEUE_PI 	(4<<IDX_MINOR)
#define MINOR_FUTEX_MIN MINOR_FUTEX_WAIT
#define MINOR_FUTEX_MAX MINOR_FUTEX_CMP_REQUEUE_PI

#define MINOR_PROC_THREAD_STATE (0<<IDX_MINOR)
#define MINOR_PROC_LIST_DUMP (1<<IDX_MINOR)
#define MINOR_PROC_MIN MINOR_PROC_THREAD_STATE
#define MINOR_PROC_MAX MINOR_PROC_LIST_DUMP

#define tid2sendpipe(tid) ((tid * 2) + 3)
#define tid2recvpipe(tid) ((tid * 2) + 3 + 1)

// Fragmentation related
int receive_all(int fd, void *buf, size_t count, size_t *rx_bytes);
int transmit_all(int fd, const void *buf, size_t count, size_t *tx_bytes);

// Packet related
struct packet {
	unsigned char src;
	unsigned char msg;
};
int pkt_serialize(struct packet *pkt, char src, char msg);
unsigned char pkt_get_src(struct packet *pkt);
unsigned char pkt_get_msg(struct packet *pkt);
int pkt_send(size_t tid, char src, char msg);

unsigned char * memset(void *b, char c, size_t len);

// List related
struct list {
	struct node *head;
	struct node *tail;
};
struct list * list_create();
int list_push(struct list *lst, struct node *nd);
struct node * list_find(struct list *lst, char value);
struct node * list_remove(struct list *lst, char value);
void list_dump(struct list *lst);

// Node related
struct node {
	unsigned char value;
	struct node *next;
	struct node *prev;
};
struct node * node_create(char value);
int node_destroy(struct node *nd);

// REUSE: FASTLANE
void pause(size_t seconds);
// END USED BY: FASTLANE

#ifdef DEBUG
void DEBUG_INDENT_PRINT(char *msg);
void pkt_dump(struct packet *pkt);
size_t indent_lvl;
char *str_tids[NUM_THREADS+1];
char *str_syscall[256];

////
// The following is verbatim from EAGLE_00004, but isn't included in the 
// released binary (DEBUG is not defined), so this reuse shouldn't be a concern.
////

#define _FILE_STATE_OPEN  1
#define _FILE_STATE_ERROR 2
#define _FILE_STATE_EOF   4
#define _FILE_HAVE_LAST   8

typedef struct _FILE {
   int fd;
   int state;
   int last;
} FILE;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

int fprintf(FILE * stream, const char *format, ...);

#endif
// ^ DEBUG

#endif
// ^ LIBC_H
