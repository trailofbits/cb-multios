/* AUTOMATICALLY GENERATED - DO NOT EDIT! */
#include "librpc.h"
#include "db_client.h"

static unsigned char __buf[RPC_BUF_SIZE];
static rpc_common __rpc;

int database_init(int fd) {
__rpc.fd = fd;
__rpc.prog = 232323;
#ifdef DB_CURRENT
__rpc.vers = 1;
#endif
return 0;
}

void database_close() {
    size_t avail = sizeof(__buf);
    unsigned char *buf = __buf;
    rpc_msg msg;
    msg.xid = __rpc.xid++;
    msg.body.mtype = CLOSE;
    marshal_rpc_msg(&msg, &buf, &avail);
    _rpc_send(&__rpc, __buf, sizeof(__buf) - avail);
}

#ifdef DB_CURRENT
result db_lookup (key a0) {
int _result;
size_t avail = sizeof(__buf);
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
_result = marshal_rpc_msg(&msg, &buf, &avail);
ASSERT_RESULT();
_result = marshal_key(&a0, &buf, &avail);
ASSERT_RESULT();
_result = _rpc_send(&__rpc, __buf, sizeof(__buf) - avail);
ASSERT_RESULT();
_result = _rpc_recv(&__rpc, __buf, sizeof(__buf));
ASSERT_RESULT();
buf = __buf;
avail = _result;
_result = unmarshal_rpc_msg(&reply, &buf, &avail);
ASSERT_RESULT();
if (reply.xid != msg.xid) exit(1);
_result = unmarshal_result(&retval, &buf, &avail);
ASSERT_RESULT();
return retval;
}

result db_insert (record a0) {
int _result;
size_t avail = sizeof(__buf);
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
_result = marshal_rpc_msg(&msg, &buf, &avail);
ASSERT_RESULT();
_result = marshal_record(&a0, &buf, &avail);
ASSERT_RESULT();
_result = _rpc_send(&__rpc, __buf, sizeof(__buf) - avail);
ASSERT_RESULT();
_result = _rpc_recv(&__rpc, __buf, sizeof(__buf));
ASSERT_RESULT();
buf = __buf;
avail = _result;
_result = unmarshal_rpc_msg(&reply, &buf, &avail);
ASSERT_RESULT();
if (reply.xid != msg.xid) exit(1);
_result = unmarshal_result(&retval, &buf, &avail);
ASSERT_RESULT();
return retval;
}

result db_delete (key a0) {
int _result;
size_t avail = sizeof(__buf);
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
_result = marshal_rpc_msg(&msg, &buf, &avail);
ASSERT_RESULT();
_result = marshal_key(&a0, &buf, &avail);
ASSERT_RESULT();
_result = _rpc_send(&__rpc, __buf, sizeof(__buf) - avail);
ASSERT_RESULT();
_result = _rpc_recv(&__rpc, __buf, sizeof(__buf));
ASSERT_RESULT();
buf = __buf;
avail = _result;
_result = unmarshal_rpc_msg(&reply, &buf, &avail);
ASSERT_RESULT();
if (reply.xid != msg.xid) exit(1);
_result = unmarshal_result(&retval, &buf, &avail);
ASSERT_RESULT();
return retval;
}

result db_next (key a0) {
int _result;
size_t avail = sizeof(__buf);
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
_result = marshal_rpc_msg(&msg, &buf, &avail);
ASSERT_RESULT();
_result = marshal_key(&a0, &buf, &avail);
ASSERT_RESULT();
_result = _rpc_send(&__rpc, __buf, sizeof(__buf) - avail);
ASSERT_RESULT();
_result = _rpc_recv(&__rpc, __buf, sizeof(__buf));
ASSERT_RESULT();
buf = __buf;
avail = _result;
_result = unmarshal_rpc_msg(&reply, &buf, &avail);
ASSERT_RESULT();
if (reply.xid != msg.xid) exit(1);
_result = unmarshal_result(&retval, &buf, &avail);
ASSERT_RESULT();
return retval;
}

result db_prev (key a0) {
int _result;
size_t avail = sizeof(__buf);
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
_result = marshal_rpc_msg(&msg, &buf, &avail);
ASSERT_RESULT();
_result = marshal_key(&a0, &buf, &avail);
ASSERT_RESULT();
_result = _rpc_send(&__rpc, __buf, sizeof(__buf) - avail);
ASSERT_RESULT();
_result = _rpc_recv(&__rpc, __buf, sizeof(__buf));
ASSERT_RESULT();
buf = __buf;
avail = _result;
_result = unmarshal_rpc_msg(&reply, &buf, &avail);
ASSERT_RESULT();
if (reply.xid != msg.xid) exit(1);
_result = unmarshal_result(&retval, &buf, &avail);
ASSERT_RESULT();
return retval;
}

#endif /* defined(DB_CURRENT) */
