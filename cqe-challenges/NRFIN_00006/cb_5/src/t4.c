#include <libcgc.h>
#include "libc.h"

size_t MY_TID = TID_T4;
size_t PIPE_RECV = tid2recvpipe(TID_T4);
char * STR_THREAD_NAME = "T4";
