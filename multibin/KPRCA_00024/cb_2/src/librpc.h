#include <stdlib.h>
#include "libxdr.h"
#include "rpc_xdr.h"

#define RPC_BUF_SIZE 32768

typedef struct rpc_common {
    int fd;
    unsigned long xid;
    unsigned long prog;
    unsigned long vers;
} rpc_common;

ssize_t _rpc_recv(rpc_common *rpc, unsigned char *buf, size_t size);
int _rpc_send(rpc_common *rpc, unsigned char *buf, size_t size);
