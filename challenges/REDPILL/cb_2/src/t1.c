#include "libcgc.h"
#include "cgc_libc.h"

cgc_size_t cgc_MY_TID = TID_T1;
cgc_size_t cgc_PIPE_RECV = tid2recvpipe(TID_T1);
char * STR_THREAD_NAME = "T1";
