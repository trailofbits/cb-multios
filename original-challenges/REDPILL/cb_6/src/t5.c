#include <libcgc.h>
#include "libc.h"

size_t MY_TID = TID_T5;
size_t PIPE_RECV = tid2recvpipe(TID_T5);
char * STR_THREAD_NAME = "T5";
