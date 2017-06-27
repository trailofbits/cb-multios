# 1 "src/main.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 157 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "src/main.c" 2
# 23 "src/main.c"
# 1 "lib/libcgc.h" 1
# 10 "lib/libcgc.h"
typedef long unsigned int cgc_size_t;
typedef long signed int cgc_ssize_t;





typedef long int _fd_mask;



typedef struct {
 _fd_mask _fd_bits[1024 / (8 * sizeof(_fd_mask))];
} cgc_fd_set;
# 38 "lib/libcgc.h"
struct cgc_timeval {
 int tv_sec;
 int tv_usec;
};
# 50 "lib/libcgc.h"
void cgc__terminate(unsigned int status) __attribute__((__noreturn__));
int cgc_transmit(int fd, const void *buf, cgc_size_t count, cgc_size_t *tx_bytes);
int cgc_receive(int fd, void *buf, cgc_size_t count, cgc_size_t *rx_bytes);
int cgc_fdwait(int nfds, cgc_fd_set *readfds, cgc_fd_set *writefds,
    const struct cgc_timeval *timeout, int *readyfds);
int cgc_allocate(cgc_size_t length, int is_X, void **addr);
int deallocate(void *addr, cgc_size_t length);
int cgc_random(void *buf, cgc_size_t count, cgc_size_t *rnd_bytes);

typedef struct { long _b[8]; } jmp_buf[1];
int setjmp(jmp_buf) __attribute__((__returns_twice__));
void longjmp(jmp_buf, int) __attribute__((__noreturn__));

float sinf(float); double cgc_sin(double); long double sinl(long double);
float cosf(float); double cgc_cos(double); long double cosl(long double);
float tanf(float); double cgc_tan(double); long double tanl(long double);
float cgc_logf(float); double cgc_log(double); long double logl(long double);
float rintf(float); double cgc_rint(double); long double rintl(long double);
float cgc_sqrtf(float); double cgc_sqrt(double); long double sqrtl(long double);
float fabsf(float); double cgc_fabs(double); long double fabsl(long double);
float cgc_log2f(float); double cgc_log2(double); long double log2l(long double);
float cgc_exp2f(float); double exp2(double); long double exp2l(long double);
float expf(float); double exp(double); long double expl(long double);
float log10f(float); double cgc_log10(double); long double log10l(long double);
float powf(float, float);
double cgc_pow(double, double);
long double powl(long double, long double);
float atan2f(float, float);
double cgc_atan2(double, double);
long double atan2l(long double, long double);
float remainderf(float, float);
double cgc_remainder(double, double);
long double remainderl(long double, long double);
float scalbnf(float, int);
double scalbn(double, int);
long double scalbnl(long double, int);
float scalblnf(float, long int);
double scalbln(double, long int);
long double scalblnl(long double, long int);
float significandf(float);
double significand(double);
long double significandl(long double);
# 24 "src/main.c" 2

# 1 "lib/ctype.h" 1



int isdigit(int c);
int isascii(int c);
int cgc_isprint(int c);
int isalnum(int c);
int isalpha(int c);
int islower(int c);
int isupper(int c);
int isspace(int c);
int ispunct(int c);
int tolower(int c);
int toupper(int c);
# 26 "src/main.c" 2
# 1 "lib/stdlib.h" 1




# 1 "lib/stdarg.h" 1


#ifdef WIN
#include <stdarg.h>
#else
typedef __builtin_va_list __gnuc_va_list;



typedef __gnuc_va_list va_list;
#endif
# 6 "lib/stdlib.h" 2
# 1 "lib/stddef.h" 1





typedef long int ptrdiff_t;
# 7 "lib/stdlib.h" 2




extern int cgc_fdprintf(int fd, const char *fmt, ...);
extern int cgc_sprintf(char *s, const char *fmt, ...);


long cgc_strtol(const char *str, char **endptr, int base);
unsigned long strtoul(const char *str, char **endptr, int base);

extern void *malloc(cgc_size_t size);
extern void *cgc_calloc(cgc_size_t nmemb, cgc_size_t size);
extern void *cgc_realloc(void *ptr, cgc_size_t size);
extern void cgc_free(void *ptr);
extern cgc_size_t malloc_size(void *ptr);

static void cgc_exit(int ret)
{
    cgc__terminate(ret);
}
# 27 "src/main.c" 2
# 1 "lib/string.h" 1





extern void *cgc_memcpy(void *dest, const void *src, cgc_size_t n);
extern void *cgc_memmove(void *dest, const void *src, cgc_size_t n);
extern void *cgc_memset(void *dest, int c, cgc_size_t n);
extern int memcmp(void *s1, const void *s2, cgc_size_t n);
extern void *memchr(const void *s, int c, cgc_size_t n);

extern cgc_size_t cgc_strlen(const char *s);
extern char *cgc_strcpy(char *dest, const char *src);
extern char *strncpy(char *dest, const char *src, cgc_size_t n);
extern char *strchr(const char *s, int c);
extern char *strsep(char **stringp, const char *delim);
extern int cgc_strcmp(const char *s1, const char *s2);
extern int cgc_strncmp(const char *s1, const char *s2, cgc_size_t n);
extern int cgc_strcasecmp(const char *s1, const char *s2);
extern int strncasecmp(const char *s1, const char *s2, cgc_size_t n);
extern char *cgc_strcat(char *dest, const char *src);
extern char *strdup(const char *src);
# 28 "src/main.c" 2

# 1 "src/commands.h" 1


typedef struct command_t command_t;
struct command_t
{
  unsigned arity;
  char **argv;
  char *symbol;
  enum {
    CMD_APPEND = 0xdead0001,
    CMD_AUTH = 0xdead0002,
    CMD_BITCOUNT = 0xdead0003,
    CMD_BITOP = 0xdead0004,
    CMD_DECR = 0xdead0005,
    CMD_DEL = 0xdead0006,
    CMD_EXISTS = 0xdead0007,
    CMD_GET = 0xdead0009,
    CMD_INCR = 0xdead000a,
    CMD_KEYS = 0xdead000b,
    CMD_RENAME = 0xdead000d,
    CMD_SET = 0xdead000e,
  } type;
};
# 34 "src/commands.h"
command_t commands[12] = {
    { .arity = 2, .symbol = "append", .type = CMD_APPEND, .argv = ((void *)0) },
    { .arity = 1, .symbol = "auth", .type = CMD_AUTH, .argv = ((void *)0) },
    { .arity = 1, .symbol = "bitcount", .type = CMD_BITCOUNT, .argv = ((void *)0) },
    { .arity = 3, .symbol = "bitop", .type = CMD_BITOP, .argv = ((void *)0) },
    { .arity = 1, .symbol = "decr", .type = CMD_DECR, .argv = ((void *)0) },
    { .arity = 1, .symbol = "del", .type = CMD_DEL, .argv = ((void *)0) },
    { .arity = 1, .symbol = "exists", .type = CMD_EXISTS, .argv = ((void *)0) },
    { .arity = 1, .symbol = "get", .type = CMD_GET, .argv = ((void *)0) },
    { .arity = 1, .symbol = "incr", .type = CMD_INCR, .argv = ((void *)0) },
    { .arity = 0, .symbol = "keys", .type = CMD_KEYS, .argv = ((void *)0) },
    { .arity = 2, .symbol = "rename", .type = CMD_RENAME, .argv = ((void *)0) },
    { .arity = 2, .symbol = "set", .type = CMD_SET, .argv = ((void *)0) },
};



void cgc_free_command(command_t* cmd)
{
  if (!cmd)
    return;

  if (cmd->argv)
  {
    for (cgc_size_t i = 0; i < cmd->arity; i++)
      if (cmd->argv[i])
        cgc_free(cmd->argv[i]);
    cgc_free(cmd->argv);
  }

  cgc_free(cmd);
}
# 30 "src/main.c" 2
# 1 "src/io.h" 1








int send_n_bytes(int fd, cgc_size_t n, char* buf);
int cgc_read_n_bytes(int fd, cgc_size_t n, char* buf);
int read_until(int fd, cgc_size_t n, char terminator, char* buf);
int cgc_transmit_string(int fd, char* buf);
# 31 "src/main.c" 2

typedef struct store_tree_t store_tree_t;
struct store_tree_t
{
  cgc_size_t klen;
  cgc_size_t vlen;
  char* key;
  char* val;
  store_tree_t* l;
  store_tree_t* r;
};

const static char* AUTH_OK = "auth ok";
const static char* nil = "nil";
const static char* AUTH_ERR = "auth error";
const static char* synerr = "syntax error";
const static char* _false = "0";
const static char* _true = "1";

store_tree_t* cgc_make_tree(store_tree_t* l, store_tree_t* r, char* key, char* val)
{
  if (!key || !val)
    return ((void *)0);

  store_tree_t* new = cgc_calloc(sizeof(store_tree_t), 1);
  if (!new)
    ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 57); cgc_exit(1); });
  if (l)
    new->l = l;
  if (r)
    new->r = r;

  new->klen = cgc_strlen(key);
  new->key = cgc_calloc(sizeof(char), new->klen + 1);
  if (!new->key)
    ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 66); cgc_exit(1); });
  else
    cgc_strcpy(new->key, key);

  new->vlen = cgc_strlen(val);
  new->val = cgc_calloc(sizeof(char), new->vlen + 1);
  if (!new->val)
    ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 73); cgc_exit(1); });
  else
    cgc_strcpy(new->val, val);

  return new;
}

store_tree_t* cgc_ins_tree(store_tree_t* root, char* key, char* val)
{
  if (!val)
    return ((void *)0);

  if (!root)
  {
                                       ;
    return cgc_make_tree(((void *)0), ((void *)0), key, val);
  }

  int sret = cgc_strcmp(root->key, key);

  if (sret < 0)
  {
    root->l = cgc_ins_tree(root->l, key, val);
  }
  else if (sret > 0)
  {
    root->r = cgc_ins_tree(root->r, key, val);
  }

  return root;
}

store_tree_t* cgc_find_tree(store_tree_t* root, char* key)
{
  if (!root || !key)
    return ((void *)0);

  int sret = cgc_strcmp(root->key, key);

  if (sret == 0)
    return root;
  else if (sret < 0)
    return cgc_find_tree(root->l, key);
  else
    return cgc_find_tree(root->r, key);
}

void cgc_replace_node(store_tree_t* old, store_tree_t* new)
{
  old->val = new->val;
  old->vlen = new->vlen;
  old->key = new->key;
  old->klen = new->klen;
}

store_tree_t* cgc_tree_min(store_tree_t* root)
{
  if (root->l)
    return cgc_tree_min(root->l);
  else
    return root;
}

store_tree_t* cgc_del_tree(store_tree_t* root, char* key)
{
  if (!key)
    return ((void *)0);

  if (!root)
    return root;

  int sret = cgc_strcmp(root->key, key);

  if (sret < 0)
  {
    root->l = cgc_del_tree(root->l, key);
    return root;
  }
  else if (sret > 0)
  {
    root->r = cgc_del_tree(root->r, key);
    return root;
  }

  if (root->l && root->r)
  {
    store_tree_t* min = cgc_tree_min(root->r);
    cgc_replace_node(root, min);
    root->r = cgc_del_tree(root->r, min->key);
  }
  else
  {
    if (!root->l)
      root = root->r;
    else if (!root->r)
      root = root->l;
  }

  return root;
}

int cgc_append_tree_val(store_tree_t* node, char* append_val)
{
  if (!append_val || !node)
    return -1;

  node->vlen += cgc_strlen(append_val);
  node->val = cgc_realloc(node->val, node->vlen + 1);
  if (!node->val)
      ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad realloc" "\n", "src/main.c", 182); cgc_exit(1); });
  cgc_strcat(node->val, append_val);
  return 0;
}

int cgc_update_tree_val(store_tree_t* node, char* new_val)
{
  if (!new_val)
    return -1;

  cgc_free(node->val);
  node->val = cgc_calloc(sizeof(char), cgc_strlen(new_val) + 1);
  if (!node->val)
    ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 195); cgc_exit(1); });
  cgc_strcpy(node->val, new_val);
  node->vlen = cgc_strlen(new_val);
  return 0;
}

unsigned char* cgc_read_command(int fd)
{
  int size;

  if (cgc_read_n_bytes(fd, sizeof(size), (char* )&size) < 0)
    return ((void *)0);

  if (cgc_strncmp("quit", (char *)&size, 4) == 0)
    cgc_exit(0);

  if (size > (16 * 1024) || size < 0)
    return ((void *)0);

  unsigned char* command = cgc_calloc(sizeof(unsigned char), size);
  if (!command)
    ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 216); cgc_exit(1); });

  if (cgc_read_n_bytes(fd, size, (char* )command) != size)
  {
    cgc_free(command);
    return ((void *)0);
  }

  return command;
}

command_t* cgc_unserialize_command(unsigned char* serialized)
{
  command_t* command = cgc_calloc(sizeof(command_t), 1);
  if (!command)
    ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 231); cgc_exit(1); });

  unsigned char* cur = serialized;

  cgc_memcpy(&command->type, cur, sizeof(command->type));
  cur += sizeof(command->type);

  cgc_memcpy(&command->arity, cur, sizeof(command->arity));
  cur += sizeof(command->arity);

  if (command->arity > 0)
  {
    command->argv = cgc_calloc(sizeof(char *), command->arity);
    if (!command->argv)
      ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 245); cgc_exit(1); });
  }

  for (cgc_size_t i = 0; i < command->arity; i++)
  {
    command->argv[i] = cgc_calloc(sizeof(char), cgc_strlen((char *)cur) + 1);
    if (!command->argv[i])
      ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 252); cgc_exit(1); });
    cgc_strcpy(command->argv[i], (char* )cur);
    cur += cgc_strlen(command->argv[i]) + 1;
  }

  return command;
}

static store_tree_t* groot;
static int authed = 0;
char* cgc_handle_append(command_t* command)
{
  char* key = command->argv[0];
  store_tree_t* node = cgc_find_tree(groot, key);
  if (!node)
  {
    cgc_ins_tree(groot, key, command->argv[1]),
    node = cgc_find_tree(groot, key);
  }
  else
  {
    cgc_append_tree_val(node, command->argv[1]);
  }

  char *res = cgc_calloc(sizeof(char), 32);
  if (!res)
    ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 278); cgc_exit(1); });
  cgc_sprintf(res, "%d", (int)cgc_strlen(node->val));
  return res;
}

char* cgc_handle_auth(command_t* command)
{
  if (cgc_strncmp(command->argv[0], "password", cgc_strlen("password")) != 0)
    return (char *)AUTH_ERR;

  authed = 1;
  return (char *)AUTH_OK;
}

char* cgc_handle_bitcount(command_t* command)
{
  int bitcount = 0;
  char* key = command->argv[0];
  char *res = cgc_calloc(sizeof(char), 32);
  store_tree_t* node = cgc_find_tree(groot, key);
  if (!node)
    goto done;

  char *p = node->val;

  while (cgc_strlen(p) >= 4)
  {
    bitcount += __builtin_popcount(*(unsigned int *)p);
    p += 4;
  }

  if (cgc_strlen(p) > 0)
  {
    int i = cgc_strlen(p);
    unsigned mask = 0;
    for (int ii = 0; ii < i; ii++)
      mask |= (0xFF << (ii * 8));
    bitcount += __builtin_popcount((*(unsigned int *)p) & mask);
  }

done:
  if (!res)
    ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 320); cgc_exit(1); });
  cgc_sprintf(res, "%d", bitcount);
  return res;
}

char cgc_safe_str_index(char* s, cgc_size_t i, char def)
{
  if (!s)
    return def;

  cgc_size_t max = cgc_strlen(s);

  if (i >= max)
    return def;
  else
    return s[i];
}

char* cgc_handle_bitop(command_t* command)
{
  enum bop_type {
    AND,
    OR,
    XOR,
    NOT
  } bop;

  if (cgc_strcasecmp(command->argv[0], "and") == 0)
      bop = AND;
  else if (cgc_strcasecmp(command->argv[0], "or") == 0)
      bop = OR;
  else if (cgc_strcasecmp(command->argv[0], "xor") == 0)
      bop = XOR;
  else if (cgc_strcasecmp(command->argv[0], "not") == 0)
      bop = NOT;
  else
    return (char* )synerr;

  char* s1, *s2;
  if (cgc_find_tree(groot, command->argv[1]))
    s1 = cgc_find_tree(groot, command->argv[1])->val;
  else
    s1 = ((void *)0);

  if (cgc_find_tree(groot, command->argv[2]))
    s2 = cgc_find_tree(groot, command->argv[2])->val;
  else
    s2 = ((void *)0);

#ifdef PATCHED
  if (!s1 || !s2)
#else
  if (!s1 && !s2)
#endif
    return (char *)_false;

  cgc_size_t llen = cgc_strlen(s1) > cgc_strlen(s2) ? cgc_strlen(s1) : cgc_strlen(s2);
  char *res = cgc_calloc(sizeof(char), llen + 1);
  if (!res)
      ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 375); cgc_exit(1); });

  if (cgc_strlen(s1) > cgc_strlen(s2))
    cgc_strcpy(res, s1);
  else
    cgc_strcpy(res, s2);

  switch (bop)
  {
    case AND:
      for (cgc_size_t i = 0; i < llen; i++)
        res[i] = cgc_safe_str_index(s1, i, 0) & cgc_safe_str_index(s2, i, 0);
      break;
    case OR:
      for (cgc_size_t i = 0; i < llen; i++)
        res[i] = cgc_safe_str_index(s1, i, 0) | cgc_safe_str_index(s2, i, 0);
      break;
    case XOR:
      for (cgc_size_t i = 0; i < llen; i++)
        res[i] = cgc_safe_str_index(s1, i, 0) ^ cgc_safe_str_index(s2, i, 0);
      break;
    case NOT:
      for (cgc_size_t i = 0; i < llen; i++)
        res[i] = ~cgc_safe_str_index(s2, i, 0);
      break;
  }

  char* bytestring = cgc_calloc(sizeof(char), 16 * llen);
  cgc_size_t offset = 0;
  if (!bytestring)
    ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 405); cgc_exit(1); });

  for (cgc_size_t i = 0; i < llen; i++)
  {
    if (!cgc_isprint(res[i]))
    {
      cgc_sprintf(bytestring + offset, "\\x%02x", res[i]);
      offset += 4;
    }
    else
    {
      *(bytestring + offset) = res[i];
      offset += 1;
    }
  }

  cgc_free(res);
  return bytestring;
}

char* cgc_handle_cr(command_t* command, int diff)
{
  int val;
  char* key = command->argv[0];
  store_tree_t* node = cgc_find_tree(groot, key);
  if (!node)
  {
    cgc_ins_tree(groot, key, "0");
    node = cgc_find_tree(groot, key);
  }

  val = cgc_strtol(node->val, ((void *)0), 10);
  val += diff;

  char NUM_BUF[32];
  cgc_memset(NUM_BUF, 0, 32);
  cgc_sprintf(NUM_BUF, "%d", val);
  cgc_update_tree_val(node, NUM_BUF);

  char* res = cgc_calloc(sizeof(char), cgc_strlen(NUM_BUF) + cgc_strlen("num is ") + 1);
  cgc_strcat(res, "num is ");
  cgc_strcat(res, NUM_BUF);

  return res;
}

char* cgc_handle_del(command_t* command)
{
  char* key = command->argv[0];
  store_tree_t* node = cgc_find_tree(groot, key);
  if (!node)
    return (char* )_false;

  cgc_del_tree(groot, key);
  return (char* ) _true;
}

char* cgc_handle_exists(command_t* command)
{
  char* key = command->argv[0];
  store_tree_t* node = cgc_find_tree(groot, key);
  if (!node)
    return (char* )_false;
  else
    return (char* ) _true;
}

char* cgc_handle_get(command_t* command)
{
  char* key = command->argv[0];
  store_tree_t* node = cgc_find_tree(groot, key);
  if (!node)
    return (char *)nil;

  char *res = cgc_calloc(sizeof(char), cgc_strlen(node->val) + 12);
  if (!res)
    ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 481); cgc_exit(1); });

  cgc_sprintf(res, "val is \"%s\"", node->val);
  return res;
}

cgc_size_t cgc_size_tree(store_tree_t* root)
{
  if (!root)
    return 0;

  return 1 + cgc_size_tree(root->l) + cgc_size_tree(root->r);
}


void cgc_preorder_walk(store_tree_t* root, char** buffer, cgc_size_t max)
{
  if (!root)
    return;

  cgc_preorder_walk(root->l, buffer, max);
  if (root->key && cgc_strlen(root->key))
  {
    if (cgc_strlen(*buffer) + cgc_strlen(root->key) + 4 >= max)
    {


#ifdef PATCHED
      max = (cgc_strlen(*buffer) + cgc_strlen(root->key) + 4);
#else
      max = (cgc_strlen(*buffer) + cgc_strlen(root->key));
#endif

      *buffer = cgc_realloc(*buffer, max);
      if (!*buffer)
        ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad realloc" "\n", "src/main.c", 513); cgc_exit(1); });
    }

      cgc_strcat(*buffer, "\"");
      cgc_strcat(*buffer, root->key);
      cgc_strcat(*buffer, "\"");
      cgc_strcat(*buffer, " ");
    }
  cgc_preorder_walk(root->r, buffer, max);
}

char* cgc_handle_keys(command_t* command)
{

  char* buffer = cgc_calloc(sizeof(char), 1024);
  cgc_preorder_walk(groot, &buffer, 1024);
  if (cgc_strlen(buffer) == 0)
    return "empty";
  return buffer;
}


char* cgc_handle_rename(command_t* command)
{
  store_tree_t* src = cgc_find_tree(groot, command->argv[0]);
  store_tree_t* dst = cgc_find_tree(groot, command->argv[1]);
  if (!src)
    return (char *)_false;

  char* v = src->val;
  if (src == dst)
    return (char *)_false;

  if (dst)
  {
    cgc_del_tree(groot, dst->key);
    cgc_free(dst->val);
    cgc_free(dst->key);
    cgc_free(dst);
    dst = ((void *)0);
  }

  cgc_ins_tree(groot, command->argv[1], v);

  if (src)
    cgc_del_tree(groot, src->key);
  return (char *)_true;
}

char* cgc_handle_set(command_t* command)
{
  store_tree_t* dst = cgc_find_tree(groot, command->argv[0]);
  if (dst)
    return (char *)_false;

  cgc_ins_tree(groot, command->argv[0], command->argv[1]);
                                          ;
  return (char *)_true;
}

char* cgc_call_command(command_t* command)
{
  switch (command->type)
  {
    case CMD_APPEND:
      return cgc_handle_append(command);
    case CMD_AUTH:
      return cgc_handle_auth(command);
    case CMD_BITCOUNT:
      return cgc_handle_bitcount(command);
    case CMD_BITOP:
      return cgc_handle_bitop(command);
    case CMD_DECR:
      return cgc_handle_cr(command, -1);
    case CMD_DEL:
      return cgc_handle_del(command);
    case CMD_EXISTS:
      return cgc_handle_exists(command);
    case CMD_GET:
      return cgc_handle_get(command);
    case CMD_INCR:
      return cgc_handle_cr(command, 1);
    case CMD_KEYS:
      return cgc_handle_keys(command);
    case CMD_RENAME:
      return cgc_handle_rename(command);
    case CMD_SET:
      return cgc_handle_set(command);
    default:
      return (char *)synerr;
  }
}


int main(int cgc_argc, char *cgc_argv[])
{
  int rx = 4;
  int tx = 5;

  struct cgc_timeval x;
  x.tv_sec = 1;
  x.tv_usec = 0;

  groot = cgc_make_tree(((void *)0), ((void *)0), "", "");

  for (;;)
  {
    unsigned char* serialized_command = cgc_read_command(rx);

    if (!serialized_command)
      continue;

    command_t* command = cgc_unserialize_command(serialized_command);
    if (!command)
    {
                                          ;
      cgc_free(serialized_command);
      continue;
    }
                                                  ;

    cgc_size_t i;
    for (i = 0; i < 12; i++)
      if (commands[i].type == command->type && commands[i].arity == command->arity)
        break;

    if (i == 12)
    {
      cgc_free(serialized_command);
      cgc_free(command);
      continue;
    }

    if (command->type != CMD_AUTH && !authed)
    {
      if (cgc_transmit_string(tx, "unauthed\n") != 0)
        ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "send failed" "\n", "src/main.c", 649); cgc_exit(1); });
      continue;
    }

    char* result = cgc_call_command(command);
                                      ;
    if (cgc_transmit_string(tx, result) != 0)
      ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "send failed" "\n", "src/main.c", 656); cgc_exit(1); });
    if (cgc_transmit_string(tx, "\n") != 0)
      ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "send failed" "\n", "src/main.c", 658); cgc_exit(1); });

    switch (command->type)
    {
      case CMD_APPEND:
      case CMD_BITCOUNT:
      case CMD_BITOP:
      case CMD_GET:
      case CMD_INCR:
      case CMD_KEYS:
        if (result == synerr ||
            result == _true ||
            result == _false ||
            result == nil)
          break;
        else
          cgc_free(result);
      default:
        break;
    }

    cgc_free(serialized_command);
    cgc_free_command(command);
  }
}
