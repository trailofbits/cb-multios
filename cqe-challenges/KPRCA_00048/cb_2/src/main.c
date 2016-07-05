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
typedef long unsigned int size_t;
typedef long signed int ssize_t;





typedef long int _fd_mask;



typedef struct {
 _fd_mask _fd_bits[1024 / (8 * sizeof(_fd_mask))];
} fd_set;
# 38 "lib/libcgc.h"
struct timeval {
 int tv_sec;
 int tv_usec;
};
# 50 "lib/libcgc.h"
void _terminate(unsigned int status) __attribute__((__noreturn__));
int transmit(int fd, const void *buf, size_t count, size_t *tx_bytes);
int receive(int fd, void *buf, size_t count, size_t *rx_bytes);
int fdwait(int nfds, fd_set *readfds, fd_set *writefds,
    const struct timeval *timeout, int *readyfds);
int allocate(size_t length, int is_X, void **addr);
int deallocate(void *addr, size_t length);
int random(void *buf, size_t count, size_t *rnd_bytes);

typedef struct { long _b[8]; } jmp_buf[1];
int setjmp(jmp_buf) __attribute__((__returns_twice__));
void longjmp(jmp_buf, int) __attribute__((__noreturn__));

float sinf(float); double sin(double); long double sinl(long double);
float cosf(float); double cos(double); long double cosl(long double);
float tanf(float); double tan(double); long double tanl(long double);
float logf(float); double log(double); long double logl(long double);
float rintf(float); double rint(double); long double rintl(long double);
float sqrtf(float); double sqrt(double); long double sqrtl(long double);
float fabsf(float); double fabs(double); long double fabsl(long double);
float log2f(float); double log2(double); long double log2l(long double);
float exp2f(float); double exp2(double); long double exp2l(long double);
float expf(float); double exp(double); long double expl(long double);
float log10f(float); double log10(double); long double log10l(long double);
float powf(float, float);
double pow(double, double);
long double powl(long double, long double);
float atan2f(float, float);
double atan2(double, double);
long double atan2l(long double, long double);
float remainderf(float, float);
double remainder(double, double);
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
int isprint(int c);
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



typedef __builtin_va_list __gnuc_va_list;



typedef __gnuc_va_list va_list;
# 6 "lib/stdlib.h" 2
# 1 "lib/stddef.h" 1





typedef long int ptrdiff_t;
# 7 "lib/stdlib.h" 2




extern int fdprintf(int fd, const char *fmt, ...);
extern int sprintf(char *s, const char *fmt, ...);


long strtol(const char *str, char **endptr, int base);
unsigned long strtoul(const char *str, char **endptr, int base);

extern void *malloc(size_t size);
extern void *calloc(size_t nmemb, size_t size);
extern void *realloc(void *ptr, size_t size);
extern void free(void *ptr);
extern size_t malloc_size(void *ptr);

static void exit(int ret)
{
    _terminate(ret);
}
# 27 "src/main.c" 2
# 1 "lib/string.h" 1





extern void *memcpy(void *dest, const void *src, size_t n);
extern void *memmove(void *dest, const void *src, size_t n);
extern void *memset(void *dest, int c, size_t n);
extern int memcmp(void *s1, const void *s2, size_t n);
extern void *memchr(const void *s, int c, size_t n);

extern size_t strlen(const char *s);
extern char *strcpy(char *dest, const char *src);
extern char *strncpy(char *dest, const char *src, size_t n);
extern char *strchr(const char *s, int c);
extern char *strsep(char **stringp, const char *delim);
extern int strcmp(const char *s1, const char *s2);
extern int strncmp(const char *s1, const char *s2, size_t n);
extern int strcasecmp(const char *s1, const char *s2);
extern int strncasecmp(const char *s1, const char *s2, size_t n);
extern char *strcat(char *dest, const char *src);
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



void free_command(command_t* cmd)
{
  if (!cmd)
    return;

  if (cmd->argv)
  {
    for (size_t i = 0; i < cmd->arity; i++)
      if (cmd->argv[i])
        free(cmd->argv[i]);
    free(cmd->argv);
  }

  free(cmd);
}
# 30 "src/main.c" 2
# 1 "src/io.h" 1








int send_n_bytes(int fd, size_t n, char* buf);
int read_n_bytes(int fd, size_t n, char* buf);
int read_until(int fd, size_t n, char terminator, char* buf);
int transmit_string(int fd, char* buf);
# 31 "src/main.c" 2

typedef struct store_tree_t store_tree_t;
struct store_tree_t
{
  size_t klen;
  size_t vlen;
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

store_tree_t* make_tree(store_tree_t* l, store_tree_t* r, char* key, char* val)
{
  if (!key || !val)
    return ((void *)0);

  store_tree_t* new = calloc(sizeof(store_tree_t), 1);
  if (!new)
    ({ fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 57); exit(1); });
  if (l)
    new->l = l;
  if (r)
    new->r = r;

  new->klen = strlen(key);
  new->key = calloc(sizeof(char), new->klen + 1);
  if (!new->key)
    ({ fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 66); exit(1); });
  else
    strcpy(new->key, key);

  new->vlen = strlen(val);
  new->val = calloc(sizeof(char), new->vlen + 1);
  if (!new->val)
    ({ fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 73); exit(1); });
  else
    strcpy(new->val, val);

  return new;
}

store_tree_t* ins_tree(store_tree_t* root, char* key, char* val)
{
  if (!val)
    return ((void *)0);

  if (!root)
  {
                                       ;
    return make_tree(((void *)0), ((void *)0), key, val);
  }

  int sret = strcmp(root->key, key);

  if (sret < 0)
  {
    root->l = ins_tree(root->l, key, val);
  }
  else if (sret > 0)
  {
    root->r = ins_tree(root->r, key, val);
  }

  return root;
}

store_tree_t* find_tree(store_tree_t* root, char* key)
{
  if (!root || !key)
    return ((void *)0);

  int sret = strcmp(root->key, key);

  if (sret == 0)
    return root;
  else if (sret < 0)
    return find_tree(root->l, key);
  else
    return find_tree(root->r, key);
}

void replace_node(store_tree_t* old, store_tree_t* new)
{
  old->val = new->val;
  old->vlen = new->vlen;
  old->key = new->key;
  old->klen = new->klen;
}

store_tree_t* tree_min(store_tree_t* root)
{
  if (root->l)
    return tree_min(root->l);
  else
    return root;
}

store_tree_t* del_tree(store_tree_t* root, char* key)
{
  if (!key)
    return ((void *)0);

  if (!root)
    return root;

  int sret = strcmp(root->key, key);

  if (sret < 0)
  {
    root->l = del_tree(root->l, key);
    return root;
  }
  else if (sret > 0)
  {
    root->r = del_tree(root->r, key);
    return root;
  }

  if (root->l && root->r)
  {
    store_tree_t* min = tree_min(root->r);
    replace_node(root, min);
    root->r = del_tree(root->r, min->key);
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

int append_tree_val(store_tree_t* node, char* append_val)
{
  if (!append_val || !node)
    return -1;

  node->vlen += strlen(append_val);
  node->val = realloc(node->val, node->vlen + 1);
  if (!node->val)
      ({ fdprintf(2, "ERROR %s:%d:\t" "bad realloc" "\n", "src/main.c", 182); exit(1); });
  strcat(node->val, append_val);
  return 0;
}

int update_tree_val(store_tree_t* node, char* new_val)
{
  if (!new_val)
    return -1;

  free(node->val);
  node->val = calloc(sizeof(char), strlen(new_val) + 1);
  if (!node->val)
    ({ fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 195); exit(1); });
  strcpy(node->val, new_val);
  node->vlen = strlen(new_val);
  return 0;
}

unsigned char* read_command(int fd)
{
  int size;

  if (read_n_bytes(fd, sizeof(size), (char* )&size) < 0)
    return ((void *)0);

  if (strncmp("quit", (char *)&size, 4) == 0)
    exit(0);

  if (size > (16 * 1024) || size < 0)
    return ((void *)0);

  unsigned char* command = calloc(sizeof(unsigned char), size);
  if (!command)
    ({ fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 216); exit(1); });

  if (read_n_bytes(fd, size, (char* )command) != size)
  {
    free(command);
    return ((void *)0);
  }

  return command;
}

command_t* unserialize_command(unsigned char* serialized)
{
  command_t* command = calloc(sizeof(command_t), 1);
  if (!command)
    ({ fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 231); exit(1); });

  unsigned char* cur = serialized;

  memcpy(&command->type, cur, sizeof(command->type));
  cur += sizeof(command->type);

  memcpy(&command->arity, cur, sizeof(command->arity));
  cur += sizeof(command->arity);

  if (command->arity > 0)
  {
    command->argv = calloc(sizeof(char *), command->arity);
    if (!command->argv)
      ({ fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 245); exit(1); });
  }

  for (size_t i = 0; i < command->arity; i++)
  {
    command->argv[i] = calloc(sizeof(char), strlen((char *)cur) + 1);
    if (!command->argv[i])
      ({ fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 252); exit(1); });
    strcpy(command->argv[i], (char* )cur);
    cur += strlen(command->argv[i]) + 1;
  }

  return command;
}

static store_tree_t* groot;
static int authed = 0;
char* handle_append(command_t* command)
{
  char* key = command->argv[0];
  store_tree_t* node = find_tree(groot, key);
  if (!node)
  {
    ins_tree(groot, key, command->argv[1]),
    node = find_tree(groot, key);
  }
  else
  {
    append_tree_val(node, command->argv[1]);
  }

  char *res = calloc(sizeof(char), 32);
  if (!res)
    ({ fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 278); exit(1); });
  sprintf(res, "%d", (int)strlen(node->val));
  return res;
}

char* handle_auth(command_t* command)
{
  if (strncmp(command->argv[0], "password", strlen("password")) != 0)
    return (char *)AUTH_ERR;

  authed = 1;
  return (char *)AUTH_OK;
}

char* handle_bitcount(command_t* command)
{
  int bitcount = 0;
  char* key = command->argv[0];
  char *res = calloc(sizeof(char), 32);
  store_tree_t* node = find_tree(groot, key);
  if (!node)
    goto done;

  char *p = node->val;

  while (strlen(p) >= 4)
  {
    bitcount += __builtin_popcount(*(unsigned int *)p);
    p += 4;
  }

  if (strlen(p) > 0)
  {
    int i = strlen(p);
    unsigned mask = 0;
    for (int ii = 0; ii < i; ii++)
      mask |= (0xFF << (ii * 8));
    bitcount += __builtin_popcount((*(unsigned int *)p) & mask);
  }

done:
  if (!res)
    ({ fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 320); exit(1); });
  sprintf(res, "%d", bitcount);
  return res;
}

char safe_str_index(char* s, size_t i, char def)
{
  if (!s)
    return def;

  size_t max = strlen(s);

  if (i >= max)
    return def;
  else
    return s[i];
}

char* handle_bitop(command_t* command)
{
  enum bop_type {
    AND,
    OR,
    XOR,
    NOT
  } bop;

  if (strcasecmp(command->argv[0], "and") == 0)
      bop = AND;
  else if (strcasecmp(command->argv[0], "or") == 0)
      bop = OR;
  else if (strcasecmp(command->argv[0], "xor") == 0)
      bop = XOR;
  else if (strcasecmp(command->argv[0], "not") == 0)
      bop = NOT;
  else
    return (char* )synerr;

  char* s1, *s2;
  if (find_tree(groot, command->argv[1]))
    s1 = find_tree(groot, command->argv[1])->val;
  else
    s1 = ((void *)0);

  if (find_tree(groot, command->argv[2]))
    s2 = find_tree(groot, command->argv[2])->val;
  else
    s2 = ((void *)0);

#ifdef PATCHED
  if (!s1 || !s2)
#else
  if (!s1 && !s2)
#endif
    return (char *)_false;

  size_t llen = strlen(s1) > strlen(s2) ? strlen(s1) : strlen(s2);
  char *res = calloc(sizeof(char), llen + 1);
  if (!res)
      ({ fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 375); exit(1); });

  if (strlen(s1) > strlen(s2))
    strcpy(res, s1);
  else
    strcpy(res, s2);

  switch (bop)
  {
    case AND:
      for (size_t i = 0; i < llen; i++)
        res[i] = safe_str_index(s1, i, 0) & safe_str_index(s2, i, 0);
      break;
    case OR:
      for (size_t i = 0; i < llen; i++)
        res[i] = safe_str_index(s1, i, 0) | safe_str_index(s2, i, 0);
      break;
    case XOR:
      for (size_t i = 0; i < llen; i++)
        res[i] = safe_str_index(s1, i, 0) ^ safe_str_index(s2, i, 0);
      break;
    case NOT:
      for (size_t i = 0; i < llen; i++)
        res[i] = ~safe_str_index(s2, i, 0);
      break;
  }

  char* bytestring = calloc(sizeof(char), 16 * llen);
  size_t offset = 0;
  if (!bytestring)
    ({ fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 405); exit(1); });

  for (size_t i = 0; i < llen; i++)
  {
    if (!isprint(res[i]))
    {
      sprintf(bytestring + offset, "\\x%02x", res[i]);
      offset += 4;
    }
    else
    {
      *(bytestring + offset) = res[i];
      offset += 1;
    }
  }

  free(res);
  return bytestring;
}

char* handle_cr(command_t* command, int diff)
{
  int val;
  char* key = command->argv[0];
  store_tree_t* node = find_tree(groot, key);
  if (!node)
  {
    ins_tree(groot, key, "0");
    node = find_tree(groot, key);
  }

  val = strtol(node->val, ((void *)0), 10);
  val += diff;

  char NUM_BUF[32];
  memset(NUM_BUF, 0, 32);
  sprintf(NUM_BUF, "%d", val);
  update_tree_val(node, NUM_BUF);

  char* res = calloc(sizeof(char), strlen(NUM_BUF) + strlen("num is ") + 1);
  strcat(res, "num is ");
  strcat(res, NUM_BUF);

  return res;
}

char* handle_del(command_t* command)
{
  char* key = command->argv[0];
  store_tree_t* node = find_tree(groot, key);
  if (!node)
    return (char* )_false;

  del_tree(groot, key);
  return (char* ) _true;
}

char* handle_exists(command_t* command)
{
  char* key = command->argv[0];
  store_tree_t* node = find_tree(groot, key);
  if (!node)
    return (char* )_false;
  else
    return (char* ) _true;
}

char* handle_get(command_t* command)
{
  char* key = command->argv[0];
  store_tree_t* node = find_tree(groot, key);
  if (!node)
    return (char *)nil;

  char *res = calloc(sizeof(char), strlen(node->val) + 12);
  if (!res)
    ({ fdprintf(2, "ERROR %s:%d:\t" "bad calloc" "\n", "src/main.c", 481); exit(1); });

  sprintf(res, "val is \"%s\"", node->val);
  return res;
}

size_t size_tree(store_tree_t* root)
{
  if (!root)
    return 0;

  return 1 + size_tree(root->l) + size_tree(root->r);
}


void preorder_walk(store_tree_t* root, char** buffer, size_t max)
{
  if (!root)
    return;

  preorder_walk(root->l, buffer, max);
  if (root->key && strlen(root->key))
  {
    if (strlen(*buffer) + strlen(root->key) + 4 >= max)
    {


#ifdef PATCHED
      max = (strlen(*buffer) + strlen(root->key) + 4);
#else
      max = (strlen(*buffer) + strlen(root->key));
#endif

      *buffer = realloc(*buffer, max);
      if (!*buffer)
        ({ fdprintf(2, "ERROR %s:%d:\t" "bad realloc" "\n", "src/main.c", 513); exit(1); });
    }

      strcat(*buffer, "\"");
      strcat(*buffer, root->key);
      strcat(*buffer, "\"");
      strcat(*buffer, " ");
    }
  preorder_walk(root->r, buffer, max);
}

char* handle_keys(command_t* command)
{

  char* buffer = calloc(sizeof(char), 1024);
  preorder_walk(groot, &buffer, 1024);
  if (strlen(buffer) == 0)
    return "empty";
  return buffer;
}


char* handle_rename(command_t* command)
{
  store_tree_t* src = find_tree(groot, command->argv[0]);
  store_tree_t* dst = find_tree(groot, command->argv[1]);
  if (!src)
    return (char *)_false;

  char* v = src->val;
  if (src == dst)
    return (char *)_false;

  if (dst)
  {
    del_tree(groot, dst->key);
    free(dst->val);
    free(dst->key);
    free(dst);
    dst = ((void *)0);
  }

  ins_tree(groot, command->argv[1], v);

  if (src)
    del_tree(groot, src->key);
  return (char *)_true;
}

char* handle_set(command_t* command)
{
  store_tree_t* dst = find_tree(groot, command->argv[0]);
  if (dst)
    return (char *)_false;

  ins_tree(groot, command->argv[0], command->argv[1]);
                                          ;
  return (char *)_true;
}

char* call_command(command_t* command)
{
  switch (command->type)
  {
    case CMD_APPEND:
      return handle_append(command);
    case CMD_AUTH:
      return handle_auth(command);
    case CMD_BITCOUNT:
      return handle_bitcount(command);
    case CMD_BITOP:
      return handle_bitop(command);
    case CMD_DECR:
      return handle_cr(command, -1);
    case CMD_DEL:
      return handle_del(command);
    case CMD_EXISTS:
      return handle_exists(command);
    case CMD_GET:
      return handle_get(command);
    case CMD_INCR:
      return handle_cr(command, 1);
    case CMD_KEYS:
      return handle_keys(command);
    case CMD_RENAME:
      return handle_rename(command);
    case CMD_SET:
      return handle_set(command);
    default:
      return (char *)synerr;
  }
}


int main(void)
{
  int rx = 4;
  int tx = 5;

  struct timeval x;
  x.tv_sec = 1;
  x.tv_usec = 0;

  groot = make_tree(((void *)0), ((void *)0), "", "");

  for (;;)
  {
    unsigned char* serialized_command = read_command(rx);

    if (!serialized_command)
      continue;

    command_t* command = unserialize_command(serialized_command);
    if (!command)
    {
                                          ;
      free(serialized_command);
      continue;
    }
                                                  ;

    size_t i;
    for (i = 0; i < 12; i++)
      if (commands[i].type == command->type && commands[i].arity == command->arity)
        break;

    if (i == 12)
    {
      free(serialized_command);
      free(command);
      continue;
    }

    if (command->type != CMD_AUTH && !authed)
    {
      if (transmit_string(tx, "unauthed\n") != 0)
        ({ fdprintf(2, "ERROR %s:%d:\t" "send failed" "\n", "src/main.c", 649); exit(1); });
      continue;
    }

    char* result = call_command(command);
                                      ;
    if (transmit_string(tx, result) != 0)
      ({ fdprintf(2, "ERROR %s:%d:\t" "send failed" "\n", "src/main.c", 656); exit(1); });
    if (transmit_string(tx, "\n") != 0)
      ({ fdprintf(2, "ERROR %s:%d:\t" "send failed" "\n", "src/main.c", 658); exit(1); });

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
          free(result);
      default:
        break;
    }

    free(serialized_command);
    free_command(command);
  }
}
