/*
 * Copyright (c) 2015 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

# 1 "src/main.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 157 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "src/main.c" 2
# 24 "src/main.c"
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
# 25 "src/main.c" 2
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

# 1 "src/io.h" 1
# 35 "src/io.h"
int send_n_bytes(int fd, size_t n, char* buf);
int read_n_bytes(int fd, size_t n, char* buf);
int read_until(int fd, size_t n, char terminator, char* buf);
int transmit_string(int fd, char* buf);
# 30 "src/main.c" 2
typedef struct thunk_t thunk_t;
typedef struct list_t list_t;
struct list_t
{
  list_t *prev, *next;
  thunk_t* thunk;
};

void remove_head_list(list_t** list);







typedef struct note_t note_t;
struct note_t
{
  size_t size;
  size_t cap;
  char* buf;
  char* title;
};


note_t* note_store[(512)] = {0};

note_t* get_note(char* title)
{
  for(size_t i = 0; i < (512); i++)
    if (note_store[i] && strcmp(title, note_store[i]->title) == 0)
      return note_store[i];
  return ((void *)0);
}

note_t* new_note(char* title, char* data)
{
  if (!data || !title)
    return ((void *)0);

  if (get_note(title))
    return ((void *)0);

  note_t* note = calloc(sizeof(note_t), 1);
  ({ if (note == ((void *)0)) ({ fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 75); exit(1); }); });

  size_t data_size = strlen(data);

  if (data_size + 1 > (1024))
  {
    note->buf = calloc(sizeof(char), data_size + 1);
    ({ if (note->buf == ((void *)0)) ({ fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 82); exit(1); }); });
    note->size = note->cap = data_size;
    strcpy(note->buf, data);
  }
  else
  {
    note->buf = calloc(sizeof(char), (1024));
    ({ if (note->buf == ((void *)0)) ({ fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 89); exit(1); }); });
    note->size = data_size;
    note->cap = (1024);
    strcpy(note->buf, data);
  }

  note->title = calloc(sizeof(char), strlen(title) + 1);
  ({ if (note->title == ((void *)0)) ({ fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 96); exit(1); }); });
  strcpy(note->title, title);

  size_t i;
  for (i = 0; i < (512); i++)
  {
    if (note_store[i] == ((void *)0))
    {
      note_store[i] = note;
      break;
    }
  }

  if (i == (512))
    return ((void *)0);

  return note;
}

note_t* append_note(note_t* note, char* data)
{
  if (!note || !data)
    return ((void *)0);

  if (strlen(data) + note->size + 1 > note->cap)
  {
#ifdef PATCHED
    note->cap = (strlen(data) + note->size + 1) * 2;
#else
    note->cap *= 2;
#endif
    note->buf = realloc(note->buf, note->cap);
    ({ if (note->buf == ((void *)0)) ({ fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 124); exit(1); }); });
  }

  strcat(note->buf, data);
  note->size += strlen(data);
  return note;
}

int delete_note(note_t* note)
{
  if (!note)
    return -1;

  for (size_t i = 0; i < (512); i++)
    if (note_store[i] == note)
      note_store[i] = ((void *)0);

  if (note->buf)
    free(note->buf);
  if (note->title)
    free(note->title);
  free(note);
  return 0;
}






typedef int (*thunk_fp_t)(char **, list_t **);
struct thunk_t
{
  unsigned arity;
  char** argv;
  thunk_fp_t fp;
};

char* thunk_res = ((void *)0);

void free_thunk(thunk_t* thunk)
{
  for (unsigned i = 0; i < thunk->arity; i++)
    if (thunk->argv[i])
      free(thunk->argv[i]);

  free(thunk->argv);
  free(thunk);
}

thunk_t* new_thunk(thunk_fp_t fp, unsigned arity, char** argv)
{
  if (arity > 4 || !argv)
    return ((void *)0);

  thunk_t* thunk = calloc(sizeof(thunk_t), 1);
  ({ if (thunk == ((void *)0)) ({ fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 180); exit(1); }); });

  thunk->fp = fp;
  thunk->arity = arity;
  thunk->argv = calloc(sizeof(char *), thunk->arity);
  ({ if (thunk->argv == ((void *)0)) ({ fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 185); exit(1); }); });

  for (unsigned i = 0; i < thunk->arity; i++)
  {
    if (!argv[i])
      goto error;

    thunk->argv[i] = calloc(sizeof(char), strlen(argv[i]) + 1);
    ({ if (thunk->argv[i] == ((void *)0)) ({ fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 193); exit(1); }); });

    strcpy(thunk->argv[i], argv[i]);
  }

  return thunk;

error:
  free_thunk(thunk);
  return ((void *)0);
}

void run_thunk(list_t** list)
{
  if (!list || !*list)
    return;

  thunk_t* thunk = (*list)->thunk;
  thunk->fp(thunk->argv, list);
}


int append_thunk(char **argv, list_t** list)
{
  char tmp[(8192) + 1];

  if (!argv)
    return -1;

  char* note_title = argv[0];
  char* content = argv[1];

  if (!note_title || !content)
    return -1;

  strncpy(tmp, content, (8192));
  tmp[(8192)] = '\0';
  size_t rep_len = strlen("cloud");

  size_t idx = 0;
  while (idx < (8192) - rep_len)
  {
    if (strncmp(tmp + idx, "cloud", rep_len) == 0)
    {
      memcpy(tmp + idx, "butt ", rep_len);
      idx += rep_len;
    }
    idx++;
  }

  if (strcmp(content, tmp))
  {
    content = realloc(content, strlen(tmp) + 1);
    ({ if (content == ((void *)0)) ({ fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 246); exit(1); }); });
    strcpy(content, tmp);
  }

  note_t* note = get_note(note_title);
  if (note)
    append_note(note, content);

  remove_head_list(list);
  if (list)
    run_thunk(list);

  return 0;
}

int delete_thunk(char** argv, list_t** list)
{
  char* note_title = argv[0];
  if (!note_title)
    return -1;

  note_t* note = get_note(note_title);
  if (note)
    delete_note(note);

  remove_head_list(list);
  if (list)
    run_thunk(list);
  return 0;
}







list_t* thunks = ((void *)0);

list_t* new_list(list_t* prev, list_t* next, thunk_t* thunk)
{
  list_t* new = calloc(sizeof(list_t), 1);
  ({ if (new == ((void *)0)) ({ fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 288); exit(1); }); });
  new->prev = prev;
  new->next = next;
  new->thunk = thunk;
  return new;
}

int append_list(list_t** list, thunk_t* thunk)
{
  if (!*list)
  {
    *list = new_list(((void *)0), ((void *)0), thunk);
    return 0;
  }

  list_t* elem = *list;
  while (elem->next)
    elem = elem->next;

  list_t* new = new_list(elem, ((void *)0), thunk);
  elem->next = new;
  return 0;
}

void remove_head_list(list_t** list)
{
  if (!list || !*list)
    return;

  if ((*list)->next)
    (*list)->next->prev = ((void *)0);
  *list = (*list)->next;
}

size_t len_list(list_t* list)
{
  size_t len = 0;
  while (list && ++len)
    list = list->next;
  return len;
}






static const char* WELCOME_MSG =
  "      Welcome to the Note Keeper 9001!\n"
  "~~~~~ A PREMIERE NOTE TAKING SOLUTION ~~~~";

static const char* PROMPT_MSG = "nk9001> ";
static const char* ERROR_MSG = "I don't know what you want, but you can't find it here.\n";
static const char* NOTE_FULL = "Your note book is full.\n";
static const char* NOTE_UNK = "Unknown note.\n";
static const char* NOTE_CREATED = "Note successfully created.\n";
static const char* NOTE_DELETED = "Note successfully deleted.\n";
static const char* NOTE_APPENDED = "Note successfully appended.\n";

void prompt(int fd)
{
  transmit_string(fd, (char *)PROMPT_MSG);
}

void yell(int fd)
{
  transmit_string(fd, (char *)ERROR_MSG);
}

char* nth_word(unsigned n, char* input, int to_end)
{

  size_t len = strlen(input);
  char* word_start[128];
  char* p = input;
  memset(word_start, '\0', 128 * sizeof(char *));

  for (size_t i = 0; i < 128; i++)
  {
    if (*p && isspace(*p))
      p++;
    if (p >= input + len)
      break;

    word_start[i] = p;

    p = strchr(p, ' ');
    if (!p)
      break;
  }

  p = word_start[n];
  if (!p)
    return ((void *)0);

  char* end = ((void *)0);
  if (!to_end)
    end = strchr(p, ' ');
  if (!end)
    end = strchr(p, '\0');
  if (!end)
    ({ fdprintf(2, "ERROR %s:%d:\t" "malformed string" "\n", "src/main.c", 389); exit(1); });

  char* res = calloc(sizeof(char), end - p + 1);
  ({ if (res == ((void *)0)) ({ fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 392); exit(1); }); });
  return strncpy(res, p, end - p);
}

char** make_argv(char* input, size_t n)
{
  char** argv = calloc(sizeof(char *), n);

  size_t i;
  for(i = 0; i < n - 1; i++)
  {
    argv[i] = nth_word(i + 1, input, 0);
    if (!argv[i])
      goto error;
  }

  argv[i] = nth_word(i + 1, input, 1);
  if (!argv[i])
    goto error;
  return argv;

error:
  for(size_t i = 1; i < n - 1; i++)
    if (argv[i])
      free(argv[i]);
  free(argv);
  return ((void *)0);
}

void print_argv(char** argv, size_t n)
{
  for(size_t i = 0; i < n; i ++)
    if (argv[i])
                        ;
}

void free_argv(char** argv, size_t n)
{
  if (!argv || !n)
    return;

  for(size_t i = 0; i < n; i ++)
    if (argv[i])
      free(argv[i]);
  free(argv);
}
# 454 "src/main.c"
int main(void)
{

  char input_buf[(16 * 1024)];
  const char* resp;
  for (;;)
  {
    prompt(1);
    memset(input_buf, '\0', (16 * 1024));
    if (read_until(0, (16 * 1024), '\n', input_buf) < 0)
      break;

    if (strncmp(input_buf, "quit", 4) == 0)
        exit(0);

    char* command = nth_word(0, input_buf, 0);
    char** argv = ((void *)0);

    if (!command)
      continue;

#ifdef PATCHED
    if (len_list(thunks) > 32)
      run_thunk(&thunks);
#endif

    if (strncmp(command, "new-note", strlen("new-note")) == 0)
    {
      run_thunk(&thunks);
      argv = make_argv(input_buf, 2);
      if (argv)
      {
        if (new_note(argv[0], argv[1]) == ((void *)0))
          resp = NOTE_FULL;
        else
          resp = NOTE_CREATED;
        free_argv(argv, 2);
      }
    }
    else if (strncmp(command, "append-note", strlen("append-note")) == 0)
    {
      argv = make_argv(input_buf, 2);
      if (argv)
      {
        thunk_t* thunk = new_thunk(append_thunk, 2, argv);
        append_list(&thunks, thunk);
        resp = NOTE_APPENDED;
        free_argv(argv, 2);
      }
    }


    else if (strncmp(command, "delete-note", strlen("delete-note")) == 0)
    {
      argv = make_argv(input_buf, 1);
      if (argv)
      {
        thunk_t* thunk = new_thunk(delete_thunk, 1, argv);
        append_list(&thunks, thunk);
        resp = NOTE_DELETED;
        free_argv(argv, 1);
      }
    }
    else if (strncmp(command, "get-note", strlen("get-note")) == 0)
    {
      run_thunk(&thunks);
      argv = make_argv(input_buf, 1);
      if (argv)
      {
        note_t* note = get_note(argv[0]);
        if (note)
          fdprintf(1, "%s\n", note->buf);
        else
          resp = NOTE_UNK;
      }
    }

    else
    {
      yell(1);
    }

    if (resp)
      transmit_string(1, (char *)resp);
    resp = ((void *)0);
    free(command);
  }
}
