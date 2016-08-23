#include <libcgc.h>
#include "libc.h"

size_t MY_TID = TID_T1;
size_t PIPE_RECV = tid2recvpipe(TID_T1);
char * STR_THREAD_NAME = "T1";
