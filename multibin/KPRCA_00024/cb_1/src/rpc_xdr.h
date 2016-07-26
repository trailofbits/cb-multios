/* AUTOMATICALLY GENERATED - DO NOT EDIT! */

#include <stdlib.h>
/* Standard definitions */
typedef unsigned char opaque;
typedef char string;
/* Begin constants */
#define AUTH_REJECTEDCRED 2
#define AUTH_REJECTEDVERF 4
#define SYSTEM_ERR 5
#define AUTH_SYS 1
#define AUTH_TOOWEAK 5
#define PROG_MISMATCH 2
#define AUTH_SHORT 2
#define MSG_ACCEPTED 0
#define CALL 0
#define AUTH_BADCRED 1
#define GARBAGE_ARGS 4
#define RPC_MISMATCH 0
#define SUCCESS 0
#define REPLY 1
#define CLOSE 2
#define PROC_UNAVAIL 3
#define MSG_DENIED 1
#define PROG_UNAVAIL 1
#define AUTH_OK 0
#define AUTH_BADVERF 3
#define AUTH_NONE 0
#define AUTH_FAILED 7
#define AUTH_ERROR 1
#define AUTH_INVALIDRESP 6
/* End constants */

typedef long msg_type;

typedef long reply_stat;

typedef long accept_stat;

typedef long reject_stat;

typedef long auth_stat;

typedef long auth_flavor;

typedef struct opaque_auth opaque_auth;

typedef struct call_body call_body;

typedef struct accepted_reply accepted_reply;

typedef struct rejected_reply rejected_reply;

typedef struct reply_body reply_body;

typedef struct rpc_msg rpc_msg;

;

;

;

;

;

;

struct opaque_auth {
auth_flavor flavor;
struct {
unsigned long count;
opaque *data;
} body;
};

struct call_body {
unsigned long rpcvers;
unsigned long prog;
unsigned long vers;
unsigned long proc;
opaque_auth cred;
opaque_auth verf;
};

struct accepted_reply {
opaque_auth verf;
struct  {
accept_stat stat;
union {
struct  {
unsigned long low;
unsigned long high;
} mismatch_info;
opaque results[0];
} value;
} reply_data;
};

struct rejected_reply {
reject_stat stat;
union {
auth_stat stat;
struct  {
unsigned long low;
unsigned long high;
} mismatch_info;
} value;
};

struct reply_body {
reply_stat stat;
union {
rejected_reply rreply;
accepted_reply areply;
} value;
};

struct rpc_msg {
unsigned long xid;
struct  {
msg_type mtype;
union {
reply_body rbody;
call_body cbody;
} value;
} body;
};

int marshal_msg_type(msg_type *data, unsigned char **_out, size_t *_size);
int unmarshal_msg_type(msg_type *data, unsigned char **_in, size_t *_size);
int marshal_reply_stat(reply_stat *data, unsigned char **_out, size_t *_size);
int unmarshal_reply_stat(reply_stat *data, unsigned char **_in, size_t *_size);
int marshal_accept_stat(accept_stat *data, unsigned char **_out, size_t *_size);
int unmarshal_accept_stat(accept_stat *data, unsigned char **_in, size_t *_size);
int marshal_reject_stat(reject_stat *data, unsigned char **_out, size_t *_size);
int unmarshal_reject_stat(reject_stat *data, unsigned char **_in, size_t *_size);
int marshal_auth_stat(auth_stat *data, unsigned char **_out, size_t *_size);
int unmarshal_auth_stat(auth_stat *data, unsigned char **_in, size_t *_size);
int marshal_auth_flavor(auth_flavor *data, unsigned char **_out, size_t *_size);
int unmarshal_auth_flavor(auth_flavor *data, unsigned char **_in, size_t *_size);
int marshal_opaque_auth(opaque_auth *data, unsigned char **_out, size_t *_size);
int unmarshal_opaque_auth(opaque_auth *data, unsigned char **_in, size_t *_size);
int marshal_call_body(call_body *data, unsigned char **_out, size_t *_size);
int unmarshal_call_body(call_body *data, unsigned char **_in, size_t *_size);
int marshal_accepted_reply(accepted_reply *data, unsigned char **_out, size_t *_size);
int unmarshal_accepted_reply(accepted_reply *data, unsigned char **_in, size_t *_size);
int marshal_rejected_reply(rejected_reply *data, unsigned char **_out, size_t *_size);
int unmarshal_rejected_reply(rejected_reply *data, unsigned char **_in, size_t *_size);
int marshal_reply_body(reply_body *data, unsigned char **_out, size_t *_size);
int unmarshal_reply_body(reply_body *data, unsigned char **_in, size_t *_size);
int marshal_rpc_msg(rpc_msg *data, unsigned char **_out, size_t *_size);
int unmarshal_rpc_msg(rpc_msg *data, unsigned char **_in, size_t *_size);
