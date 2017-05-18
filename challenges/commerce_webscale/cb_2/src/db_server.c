/* AUTOMATICALLY GENERATED - DO NOT EDIT! */
#include "cgc_librpc.h"
#include "cgc_db_server.h"

static unsigned char __buf[RPC_BUF_SIZE];
static rpc_common __rpc;
static void __DB_CURRENT_db_lookup(rpc_msg *msg, unsigned char *buf, cgc_size_t avail) {
int _result;
rpc_msg reply;
key a0;
result retval;
_result = cgc_unmarshal_key(&a0, &buf, &avail);
retval = cgc_DB_CURRENT_db_lookup(a0);
buf = __buf;
avail = sizeof(__buf);
reply.xid = msg->xid;
reply.body.mtype = REPLY;
reply.body.value.rbody.stat = MSG_ACCEPTED;
reply.body.value.rbody.value.areply.verf.flavor = AUTH_NONE;
reply.body.value.rbody.value.areply.verf.body.count = 0;
reply.body.value.rbody.value.areply.reply_data.stat = SUCCESS;
_result = cgc_marshal_rpc_msg(&reply, &buf, &avail);
_result = cgc_marshal_result(&retval, &buf, &avail);
_result = cgc__rpc_send(&__rpc, __buf, sizeof(__buf) - avail);
}
static void __DB_CURRENT_db_insert(rpc_msg *msg, unsigned char *buf, cgc_size_t avail) {
int _result;
rpc_msg reply;
record a0;
result retval;
_result = cgc_unmarshal_record(&a0, &buf, &avail);
retval = cgc_DB_CURRENT_db_insert(a0);
buf = __buf;
avail = sizeof(__buf);
reply.xid = msg->xid;
reply.body.mtype = REPLY;
reply.body.value.rbody.stat = MSG_ACCEPTED;
reply.body.value.rbody.value.areply.verf.flavor = AUTH_NONE;
reply.body.value.rbody.value.areply.verf.body.count = 0;
reply.body.value.rbody.value.areply.reply_data.stat = SUCCESS;
_result = cgc_marshal_rpc_msg(&reply, &buf, &avail);
_result = cgc_marshal_result(&retval, &buf, &avail);
_result = cgc__rpc_send(&__rpc, __buf, sizeof(__buf) - avail);
}
static void __DB_CURRENT_db_delete(rpc_msg *msg, unsigned char *buf, cgc_size_t avail) {
int _result;
rpc_msg reply;
key a0;
result retval;
_result = cgc_unmarshal_key(&a0, &buf, &avail);
retval = cgc_DB_CURRENT_db_delete(a0);
buf = __buf;
avail = sizeof(__buf);
reply.xid = msg->xid;
reply.body.mtype = REPLY;
reply.body.value.rbody.stat = MSG_ACCEPTED;
reply.body.value.rbody.value.areply.verf.flavor = AUTH_NONE;
reply.body.value.rbody.value.areply.verf.body.count = 0;
reply.body.value.rbody.value.areply.reply_data.stat = SUCCESS;
_result = cgc_marshal_rpc_msg(&reply, &buf, &avail);
_result = cgc_marshal_result(&retval, &buf, &avail);
_result = cgc__rpc_send(&__rpc, __buf, sizeof(__buf) - avail);
}
static void __DB_CURRENT_db_next(rpc_msg *msg, unsigned char *buf, cgc_size_t avail) {
int _result;
rpc_msg reply;
key a0;
result retval;
_result = cgc_unmarshal_key(&a0, &buf, &avail);
retval = cgc_DB_CURRENT_db_next(a0);
buf = __buf;
avail = sizeof(__buf);
reply.xid = msg->xid;
reply.body.mtype = REPLY;
reply.body.value.rbody.stat = MSG_ACCEPTED;
reply.body.value.rbody.value.areply.verf.flavor = AUTH_NONE;
reply.body.value.rbody.value.areply.verf.body.count = 0;
reply.body.value.rbody.value.areply.reply_data.stat = SUCCESS;
_result = cgc_marshal_rpc_msg(&reply, &buf, &avail);
_result = cgc_marshal_result(&retval, &buf, &avail);
_result = cgc__rpc_send(&__rpc, __buf, sizeof(__buf) - avail);
}
static void __DB_CURRENT_db_prev(rpc_msg *msg, unsigned char *buf, cgc_size_t avail) {
int _result;
rpc_msg reply;
key a0;
result retval;
_result = cgc_unmarshal_key(&a0, &buf, &avail);
retval = cgc_DB_CURRENT_db_prev(a0);
buf = __buf;
avail = sizeof(__buf);
reply.xid = msg->xid;
reply.body.mtype = REPLY;
reply.body.value.rbody.stat = MSG_ACCEPTED;
reply.body.value.rbody.value.areply.verf.flavor = AUTH_NONE;
reply.body.value.rbody.value.areply.verf.body.count = 0;
reply.body.value.rbody.value.areply.reply_data.stat = SUCCESS;
_result = cgc_marshal_rpc_msg(&reply, &buf, &avail);
_result = cgc_marshal_result(&retval, &buf, &avail);
_result = cgc__rpc_send(&__rpc, __buf, sizeof(__buf) - avail);
}
static void __handle_DB_CURRENT(rpc_msg *msg, unsigned char *buf, cgc_size_t avail) {
switch (msg->body.value.cbody.proc) {
case 1:
__DB_CURRENT_db_lookup(msg, buf, avail);
break;
case 2:
__DB_CURRENT_db_insert(msg, buf, avail);
break;
case 3:
__DB_CURRENT_db_delete(msg, buf, avail);
break;
case 4:
__DB_CURRENT_db_next(msg, buf, avail);
break;
case 5:
__DB_CURRENT_db_prev(msg, buf, avail);
break;
}
}
int cgc_database_run(int fdr, int fdw) {
    cgc_size_t avail;
    cgc_ssize_t _result;
    unsigned char *buf;
    __rpc.fdr = fdr;
    __rpc.fdw = fdw;
    while (1) {
        rpc_msg msg;
        if ((_result = cgc__rpc_recv(&__rpc, __buf, sizeof(__buf))) < 0) break;
        buf = __buf;
        avail = _result;
        _result = cgc_unmarshal_rpc_msg(&msg, &buf, &avail);
        if (_result < 0) continue;
        if (msg.body.mtype == CLOSE) break;
        if (msg.body.mtype != CALL) continue;
        if (msg.body.value.cbody.rpcvers != 2) continue;
        if (msg.body.value.cbody.prog != 232323) continue;
        switch (msg.body.value.cbody.vers) {
            case 1:
                __handle_DB_CURRENT(&msg, buf, avail);
                break;
        }
    }
    return 0;
}
