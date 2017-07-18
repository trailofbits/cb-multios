/* AUTOMATICALLY GENERATED - DO NOT EDIT! */
#include "cgc_librpc.h"
#include "cgc_db_client.h"

static unsigned char __buf[RPC_BUF_SIZE];
static rpc_common __rpc;

int cgc_database_init(int fdr, int fdw) {
__rpc.fdr = fdr;
__rpc.fdw = fdw;
__rpc.prog = 232323;
#ifdef DB_CURRENT
__rpc.vers = 1;
#endif
return 0;
}

void cgc_database_close() {
    cgc_size_t avail = sizeof(__buf);
    unsigned char *buf = __buf;
    rpc_msg msg;
    msg.xid = __rpc.xid++;
    msg.body.mtype = CLOSE;
    cgc_marshal_rpc_msg(&msg, &buf, &avail);
    cgc__rpc_send(&__rpc, __buf, sizeof(__buf) - avail);
}

#ifdef DB_CURRENT
result cgc_db_lookup (key a0) {
int _result;
cgc_size_t avail = sizeof(__buf);
unsigned char *buf = __buf;
rpc_msg msg, reply;
result retval;
msg.xid = __rpc.xid++;
msg.body.mtype = CALL;
msg.body.value.cbody.rpcvers = 2;
msg.body.value.cbody.prog = __rpc.prog;
msg.body.value.cbody.vers = __rpc.vers;
msg.body.value.cbody.proc = 1;
msg.body.value.cbody.cred.flavor = AUTH_NONE;
msg.body.value.cbody.cred.body.count = 0;
msg.body.value.cbody.verf.flavor = AUTH_NONE;
msg.body.value.cbody.verf.body.count = 0;
_result = cgc_marshal_rpc_msg(&msg, &buf, &avail);
ASSERT_RESULT();
_result = cgc_marshal_key(&a0, &buf, &avail);
ASSERT_RESULT();
_result = cgc__rpc_send(&__rpc, __buf, sizeof(__buf) - avail);
ASSERT_RESULT();
_result = cgc__rpc_recv(&__rpc, __buf, sizeof(__buf));
ASSERT_RESULT();
buf = __buf;
avail = _result;
_result = cgc_unmarshal_rpc_msg(&reply, &buf, &avail);
ASSERT_RESULT();
if (reply.xid != msg.xid) cgc_exit(1);
_result = cgc_unmarshal_result(&retval, &buf, &avail);
ASSERT_RESULT();
return retval;
}

result cgc_db_insert (record a0) {
int _result;
cgc_size_t avail = sizeof(__buf);
unsigned char *buf = __buf;
rpc_msg msg, reply;
result retval;
msg.xid = __rpc.xid++;
msg.body.mtype = CALL;
msg.body.value.cbody.rpcvers = 2;
msg.body.value.cbody.prog = __rpc.prog;
msg.body.value.cbody.vers = __rpc.vers;
msg.body.value.cbody.proc = 2;
msg.body.value.cbody.cred.flavor = AUTH_NONE;
msg.body.value.cbody.cred.body.count = 0;
msg.body.value.cbody.verf.flavor = AUTH_NONE;
msg.body.value.cbody.verf.body.count = 0;
_result = cgc_marshal_rpc_msg(&msg, &buf, &avail);
ASSERT_RESULT();
_result = cgc_marshal_record(&a0, &buf, &avail);
ASSERT_RESULT();
_result = cgc__rpc_send(&__rpc, __buf, sizeof(__buf) - avail);
ASSERT_RESULT();
_result = cgc__rpc_recv(&__rpc, __buf, sizeof(__buf));
ASSERT_RESULT();
buf = __buf;
avail = _result;
_result = cgc_unmarshal_rpc_msg(&reply, &buf, &avail);
ASSERT_RESULT();
if (reply.xid != msg.xid) cgc_exit(1);
_result = cgc_unmarshal_result(&retval, &buf, &avail);
ASSERT_RESULT();
return retval;
}

result cgc_db_delete (key a0) {
int _result;
cgc_size_t avail = sizeof(__buf);
unsigned char *buf = __buf;
rpc_msg msg, reply;
result retval;
msg.xid = __rpc.xid++;
msg.body.mtype = CALL;
msg.body.value.cbody.rpcvers = 2;
msg.body.value.cbody.prog = __rpc.prog;
msg.body.value.cbody.vers = __rpc.vers;
msg.body.value.cbody.proc = 3;
msg.body.value.cbody.cred.flavor = AUTH_NONE;
msg.body.value.cbody.cred.body.count = 0;
msg.body.value.cbody.verf.flavor = AUTH_NONE;
msg.body.value.cbody.verf.body.count = 0;
_result = cgc_marshal_rpc_msg(&msg, &buf, &avail);
ASSERT_RESULT();
_result = cgc_marshal_key(&a0, &buf, &avail);
ASSERT_RESULT();
_result = cgc__rpc_send(&__rpc, __buf, sizeof(__buf) - avail);
ASSERT_RESULT();
_result = cgc__rpc_recv(&__rpc, __buf, sizeof(__buf));
ASSERT_RESULT();
buf = __buf;
avail = _result;
_result = cgc_unmarshal_rpc_msg(&reply, &buf, &avail);
ASSERT_RESULT();
if (reply.xid != msg.xid) cgc_exit(1);
_result = cgc_unmarshal_result(&retval, &buf, &avail);
ASSERT_RESULT();
return retval;
}

result cgc_db_next (key a0) {
int _result;
cgc_size_t avail = sizeof(__buf);
unsigned char *buf = __buf;
rpc_msg msg, reply;
result retval;
msg.xid = __rpc.xid++;
msg.body.mtype = CALL;
msg.body.value.cbody.rpcvers = 2;
msg.body.value.cbody.prog = __rpc.prog;
msg.body.value.cbody.vers = __rpc.vers;
msg.body.value.cbody.proc = 4;
msg.body.value.cbody.cred.flavor = AUTH_NONE;
msg.body.value.cbody.cred.body.count = 0;
msg.body.value.cbody.verf.flavor = AUTH_NONE;
msg.body.value.cbody.verf.body.count = 0;
_result = cgc_marshal_rpc_msg(&msg, &buf, &avail);
ASSERT_RESULT();
_result = cgc_marshal_key(&a0, &buf, &avail);
ASSERT_RESULT();
_result = cgc__rpc_send(&__rpc, __buf, sizeof(__buf) - avail);
ASSERT_RESULT();
_result = cgc__rpc_recv(&__rpc, __buf, sizeof(__buf));
ASSERT_RESULT();
buf = __buf;
avail = _result;
_result = cgc_unmarshal_rpc_msg(&reply, &buf, &avail);
ASSERT_RESULT();
if (reply.xid != msg.xid) cgc_exit(1);
_result = cgc_unmarshal_result(&retval, &buf, &avail);
ASSERT_RESULT();
return retval;
}

result cgc_db_prev (key a0) {
int _result;
cgc_size_t avail = sizeof(__buf);
unsigned char *buf = __buf;
rpc_msg msg, reply;
result retval;
msg.xid = __rpc.xid++;
msg.body.mtype = CALL;
msg.body.value.cbody.rpcvers = 2;
msg.body.value.cbody.prog = __rpc.prog;
msg.body.value.cbody.vers = __rpc.vers;
msg.body.value.cbody.proc = 5;
msg.body.value.cbody.cred.flavor = AUTH_NONE;
msg.body.value.cbody.cred.body.count = 0;
msg.body.value.cbody.verf.flavor = AUTH_NONE;
msg.body.value.cbody.verf.body.count = 0;
_result = cgc_marshal_rpc_msg(&msg, &buf, &avail);
ASSERT_RESULT();
_result = cgc_marshal_key(&a0, &buf, &avail);
ASSERT_RESULT();
_result = cgc__rpc_send(&__rpc, __buf, sizeof(__buf) - avail);
ASSERT_RESULT();
_result = cgc__rpc_recv(&__rpc, __buf, sizeof(__buf));
ASSERT_RESULT();
buf = __buf;
avail = _result;
_result = cgc_unmarshal_rpc_msg(&reply, &buf, &avail);
ASSERT_RESULT();
if (reply.xid != msg.xid) cgc_exit(1);
_result = cgc_unmarshal_result(&retval, &buf, &avail);
ASSERT_RESULT();
return retval;
}

#endif /* defined(DB_CURRENT) */
