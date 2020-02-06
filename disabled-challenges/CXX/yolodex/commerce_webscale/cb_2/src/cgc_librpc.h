#include "cgc_stdlib.h"
#include "cgc_libxdr.h"
#include "cgc_rpc_xdr.h"

#define RPC_BUF_SIZE 32768

typedef struct rpc_common {
    int fdw;
    int fdr;
    unsigned long xid;
    unsigned long prog;
    unsigned long vers;
} rpc_common;

cgc_ssize_t cgc__rpc_recv(rpc_common *rpc, unsigned char *buf, cgc_size_t size);
int cgc__rpc_send(rpc_common *rpc, unsigned char *buf, cgc_size_t size);
