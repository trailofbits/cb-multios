#include <libcgc.h>
#include "libc.h"

#define ACK_TRIES 3

size_t MY_TID = TID_K;
size_t PIPE_RECV = tid2recvpipe(TID_K);
char * STR_THREAD_NAME = "K";

char * consume_bytes(char **curr, char *end, size_t len);

int syscall_dispatch(char **curr, char *end);
int syscall_futex(unsigned char syscall, char **curr, char *end);
int syscall_pause(unsigned char syscall, char **curr, char *end);
int syscall_sendmsg(unsigned char syscall, char **curr, char *end);
void _syscall_sendmsg(unsigned char recursions, unsigned char msg);

#ifdef DEBUG_STACK
int get_esp(void);
#endif
