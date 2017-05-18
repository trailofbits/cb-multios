/* AUTOMATICALLY GENERATED - DO NOT EDIT! */
#include "cgc_libxdr.h"
#include "cgc_rpc_xdr.h"
int cgc_marshal_msg_type(msg_type *data, unsigned char **_out, cgc_size_t *_size) {
int _result;
_result = marshal_int(&(*data), _out, _size);
CHECK_RESULT();
return 0;
}

int cgc_unmarshal_msg_type(msg_type *data, unsigned char **_in, cgc_size_t *_size) {
int _result;
_result = unmarshal_int(&(*data), _in, _size);
CHECK_RESULT();
return 0;
}

int cgc_marshal_reply_stat(reply_stat *data, unsigned char **_out, cgc_size_t *_size) {
int _result;
_result = marshal_int(&(*data), _out, _size);
CHECK_RESULT();
return 0;
}

int cgc_unmarshal_reply_stat(reply_stat *data, unsigned char **_in, cgc_size_t *_size) {
int _result;
_result = unmarshal_int(&(*data), _in, _size);
CHECK_RESULT();
return 0;
}

int cgc_marshal_accept_stat(accept_stat *data, unsigned char **_out, cgc_size_t *_size) {
int _result;
_result = marshal_int(&(*data), _out, _size);
CHECK_RESULT();
return 0;
}

int cgc_unmarshal_accept_stat(accept_stat *data, unsigned char **_in, cgc_size_t *_size) {
int _result;
_result = unmarshal_int(&(*data), _in, _size);
CHECK_RESULT();
return 0;
}

int cgc_marshal_reject_stat(reject_stat *data, unsigned char **_out, cgc_size_t *_size) {
int _result;
_result = marshal_int(&(*data), _out, _size);
CHECK_RESULT();
return 0;
}

int cgc_unmarshal_reject_stat(reject_stat *data, unsigned char **_in, cgc_size_t *_size) {
int _result;
_result = unmarshal_int(&(*data), _in, _size);
CHECK_RESULT();
return 0;
}

int cgc_marshal_auth_stat(auth_stat *data, unsigned char **_out, cgc_size_t *_size) {
int _result;
_result = marshal_int(&(*data), _out, _size);
CHECK_RESULT();
return 0;
}

int cgc_unmarshal_auth_stat(auth_stat *data, unsigned char **_in, cgc_size_t *_size) {
int _result;
_result = unmarshal_int(&(*data), _in, _size);
CHECK_RESULT();
return 0;
}

int cgc_marshal_auth_flavor(auth_flavor *data, unsigned char **_out, cgc_size_t *_size) {
int _result;
_result = marshal_int(&(*data), _out, _size);
CHECK_RESULT();
return 0;
}

int cgc_unmarshal_auth_flavor(auth_flavor *data, unsigned char **_in, cgc_size_t *_size) {
int _result;
_result = unmarshal_int(&(*data), _in, _size);
CHECK_RESULT();
return 0;
}

int cgc_marshal_opaque_auth(opaque_auth *data, unsigned char **_out, cgc_size_t *_size) {
int _result;
_result = cgc_marshal_auth_flavor(&(*data).flavor, _out, _size);
CHECK_RESULT();
_result = marshal_unsigned_int(&(*data).body.count, _out, _size);
CHECK_RESULT();
if ((*data).body.count > 400) return -1;
{
cgc_size_t i;
for (i = 0; i < (*data).body.count; i++) {
_result = marshal_opaque(&(*data).body.data[i], _out, _size);
CHECK_RESULT();
}
}
return 0;
}

int cgc_unmarshal_opaque_auth(opaque_auth *data, unsigned char **_in, cgc_size_t *_size) {
int _result;
_result = cgc_unmarshal_auth_flavor(&(*data).flavor, _in, _size);
CHECK_RESULT();
_result = unmarshal_unsigned_int(&(*data).body.count, _in, _size);
CHECK_RESULT();
if ((*data).body.count > 400) return -1;
_result = _checked_calloc((void **)&(*data).body.data, (*data).body.count, sizeof((*data).body.data[0]));
{
cgc_size_t i;
for (i = 0; i < (*data).body.count; i++) {
_result = unmarshal_opaque(&(*data).body.data[i], _in, _size);
CHECK_RESULT();
}
}
return 0;
}

int cgc_marshal_call_body(call_body *data, unsigned char **_out, cgc_size_t *_size) {
int _result;
_result = marshal_unsigned_int(&(*data).rpcvers, _out, _size);
CHECK_RESULT();
_result = marshal_unsigned_int(&(*data).prog, _out, _size);
CHECK_RESULT();
_result = marshal_unsigned_int(&(*data).vers, _out, _size);
CHECK_RESULT();
_result = marshal_unsigned_int(&(*data).proc, _out, _size);
CHECK_RESULT();
_result = cgc_marshal_opaque_auth(&(*data).cred, _out, _size);
CHECK_RESULT();
_result = cgc_marshal_opaque_auth(&(*data).verf, _out, _size);
CHECK_RESULT();
return 0;
}

int cgc_unmarshal_call_body(call_body *data, unsigned char **_in, cgc_size_t *_size) {
int _result;
_result = unmarshal_unsigned_int(&(*data).rpcvers, _in, _size);
CHECK_RESULT();
_result = unmarshal_unsigned_int(&(*data).prog, _in, _size);
CHECK_RESULT();
_result = unmarshal_unsigned_int(&(*data).vers, _in, _size);
CHECK_RESULT();
_result = unmarshal_unsigned_int(&(*data).proc, _in, _size);
CHECK_RESULT();
_result = cgc_unmarshal_opaque_auth(&(*data).cred, _in, _size);
CHECK_RESULT();
_result = cgc_unmarshal_opaque_auth(&(*data).verf, _in, _size);
CHECK_RESULT();
return 0;
}

int cgc_marshal_accepted_reply(accepted_reply *data, unsigned char **_out, cgc_size_t *_size) {
int _result;
_result = cgc_marshal_opaque_auth(&(*data).verf, _out, _size);
CHECK_RESULT();
_result = cgc_marshal_accept_stat(&(*data).reply_data.stat, _out, _size);
CHECK_RESULT();
switch ((*data).reply_data.stat) {
case PROG_MISMATCH:
_result = marshal_unsigned_int(&(*data).reply_data.value.mismatch_info.low, _out, _size);
CHECK_RESULT();
_result = marshal_unsigned_int(&(*data).reply_data.value.mismatch_info.high, _out, _size);
CHECK_RESULT();
break;
default:
break;
case SUCCESS:
{
cgc_size_t i;
for (i = 0; i < 0; i++) {
_result = marshal_opaque(&(*data).reply_data.value.results[i], _out, _size);
CHECK_RESULT();
}
}
break;
}
return 0;
}

int cgc_unmarshal_accepted_reply(accepted_reply *data, unsigned char **_in, cgc_size_t *_size) {
int _result;
_result = cgc_unmarshal_opaque_auth(&(*data).verf, _in, _size);
CHECK_RESULT();
_result = cgc_unmarshal_accept_stat(&(*data).reply_data.stat, _in, _size);
CHECK_RESULT();
switch ((*data).reply_data.stat) {
case PROG_MISMATCH:
_result = unmarshal_unsigned_int(&(*data).reply_data.value.mismatch_info.low, _in, _size);
CHECK_RESULT();
_result = unmarshal_unsigned_int(&(*data).reply_data.value.mismatch_info.high, _in, _size);
CHECK_RESULT();
break;
default:
break;
case SUCCESS:
{
cgc_size_t i;
for (i = 0; i < 0; i++) {
_result = unmarshal_opaque(&(*data).reply_data.value.results[i], _in, _size);
CHECK_RESULT();
}
}
break;
}
return 0;
}

int cgc_marshal_rejected_reply(rejected_reply *data, unsigned char **_out, cgc_size_t *_size) {
int _result;
_result = cgc_marshal_reject_stat(&(*data).stat, _out, _size);
CHECK_RESULT();
switch ((*data).stat) {
case AUTH_ERROR:
_result = cgc_marshal_auth_stat(&(*data).value.stat, _out, _size);
CHECK_RESULT();
break;
case RPC_MISMATCH:
_result = marshal_unsigned_int(&(*data).value.mismatch_info.low, _out, _size);
CHECK_RESULT();
_result = marshal_unsigned_int(&(*data).value.mismatch_info.high, _out, _size);
CHECK_RESULT();
break;
default:
return -1;
}
return 0;
}

int cgc_unmarshal_rejected_reply(rejected_reply *data, unsigned char **_in, cgc_size_t *_size) {
int _result;
_result = cgc_unmarshal_reject_stat(&(*data).stat, _in, _size);
CHECK_RESULT();
switch ((*data).stat) {
case AUTH_ERROR:
_result = cgc_unmarshal_auth_stat(&(*data).value.stat, _in, _size);
CHECK_RESULT();
break;
case RPC_MISMATCH:
_result = unmarshal_unsigned_int(&(*data).value.mismatch_info.low, _in, _size);
CHECK_RESULT();
_result = unmarshal_unsigned_int(&(*data).value.mismatch_info.high, _in, _size);
CHECK_RESULT();
break;
default:
return -1;
}
return 0;
}

int cgc_marshal_reply_body(reply_body *data, unsigned char **_out, cgc_size_t *_size) {
int _result;
_result = cgc_marshal_reply_stat(&(*data).stat, _out, _size);
CHECK_RESULT();
switch ((*data).stat) {
case MSG_DENIED:
_result = cgc_marshal_rejected_reply(&(*data).value.rreply, _out, _size);
CHECK_RESULT();
break;
case MSG_ACCEPTED:
_result = cgc_marshal_accepted_reply(&(*data).value.areply, _out, _size);
CHECK_RESULT();
break;
default:
return -1;
}
return 0;
}

int cgc_unmarshal_reply_body(reply_body *data, unsigned char **_in, cgc_size_t *_size) {
int _result;
_result = cgc_unmarshal_reply_stat(&(*data).stat, _in, _size);
CHECK_RESULT();
switch ((*data).stat) {
case MSG_DENIED:
_result = cgc_unmarshal_rejected_reply(&(*data).value.rreply, _in, _size);
CHECK_RESULT();
break;
case MSG_ACCEPTED:
_result = cgc_unmarshal_accepted_reply(&(*data).value.areply, _in, _size);
CHECK_RESULT();
break;
default:
return -1;
}
return 0;
}

int cgc_marshal_rpc_msg(rpc_msg *data, unsigned char **_out, cgc_size_t *_size) {
int _result;
_result = marshal_unsigned_int(&(*data).xid, _out, _size);
CHECK_RESULT();
_result = cgc_marshal_msg_type(&(*data).body.mtype, _out, _size);
CHECK_RESULT();
switch ((*data).body.mtype) {
case REPLY:
_result = cgc_marshal_reply_body(&(*data).body.value.rbody, _out, _size);
CHECK_RESULT();
break;
case CALL:
_result = cgc_marshal_call_body(&(*data).body.value.cbody, _out, _size);
CHECK_RESULT();
break;
default:
return -1;
}
return 0;
}

int cgc_unmarshal_rpc_msg(rpc_msg *data, unsigned char **_in, cgc_size_t *_size) {
int _result;
_result = unmarshal_unsigned_int(&(*data).xid, _in, _size);
CHECK_RESULT();
_result = cgc_unmarshal_msg_type(&(*data).body.mtype, _in, _size);
CHECK_RESULT();
switch ((*data).body.mtype) {
case REPLY:
_result = cgc_unmarshal_reply_body(&(*data).body.value.rbody, _in, _size);
CHECK_RESULT();
break;
case CALL:
_result = cgc_unmarshal_call_body(&(*data).body.value.cbody, _in, _size);
CHECK_RESULT();
break;
default:
break;
}
return 0;
}

