#include "libcgc.h"
#include "cgc_libc.h"

#define ACK_TRIES 3

cgc_size_t cgc_MY_TID = TID_K;
cgc_size_t cgc_PIPE_RECV = tid2recvpipe(TID_K);
char * STR_THREAD_NAME = "K";

char * cgc_consume_bytes(char **curr, char *end, cgc_size_t len);

int cgc_syscall_dispatch(char **curr, char *end);
int cgc_syscall_futex(unsigned char syscall, char **curr, char *end);
int cgc_syscall_pause(unsigned char syscall, char **curr, char *end);
int cgc_syscall_sendmsg(unsigned char syscall, char **curr, char *end);
void cgc__syscall_sendmsg(unsigned char recursions, unsigned char msg);

#ifdef DEBUG_STACK
int get_esp(void);
#endif
