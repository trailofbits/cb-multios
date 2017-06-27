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
# 25 "src/main.c" 2
# 1 "lib/ctype.h" 1



int isdigit(int c);
int isascii(int c);
int isprint(int c);
int isalnum(int c);
int isalpha(int c);
int islower(int c);
int isupper(int c);
int cgc_isspace(int c);
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
extern int sprintf(char *s, const char *fmt, ...);


long strtol(const char *str, char **endptr, int base);
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
extern char *cgc_strncpy(char *dest, const char *src, cgc_size_t n);
extern char *cgc_strchr(const char *s, int c);
extern char *strsep(char **stringp, const char *delim);
extern int cgc_strcmp(const char *s1, const char *s2);
extern int cgc_strncmp(const char *s1, const char *s2, cgc_size_t n);
extern int strcasecmp(const char *s1, const char *s2);
extern int strncasecmp(const char *s1, const char *s2, cgc_size_t n);
extern char *cgc_strcat(char *dest, const char *src);
extern char *strdup(const char *src);
# 28 "src/main.c" 2

# 1 "src/io.h" 1
# 35 "src/io.h"
int send_n_bytes(int fd, cgc_size_t n, char* buf);
int read_n_bytes(int fd, cgc_size_t n, char* buf);
int cgc_read_until(int fd, cgc_size_t n, char terminator, char* buf);
int cgc_transmit_string(int fd, char* buf);
# 30 "src/main.c" 2
typedef struct thunk_t thunk_t;
typedef struct list_t list_t;
struct list_t
{
  list_t *prev, *next;
  thunk_t* thunk;
};

void cgc_remove_head_list(list_t** list);







typedef struct note_t note_t;
struct note_t
{
  cgc_size_t size;
  cgc_size_t cap;
  char* buf;
  char* title;
};


note_t* cgc_note_store[(512)] = {0};

note_t* cgc_get_note(char* title)
{
  for(cgc_size_t i = 0; i < (512); i++)
    if (cgc_note_store[i] && cgc_strcmp(title, cgc_note_store[i]->title) == 0)
      return cgc_note_store[i];
  return ((void *)0);
}

note_t* cgc_new_note(char* title, char* data)
{
  if (!data || !title)
    return ((void *)0);

  if (cgc_get_note(title))
    return ((void *)0);

  note_t* note = cgc_calloc(sizeof(note_t), 1);
  ({ if (note == ((void *)0)) ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 75); cgc_exit(1); }); });

  cgc_size_t data_size = cgc_strlen(data);

  if (data_size + 1 > (1024))
  {
    note->buf = cgc_calloc(sizeof(char), data_size + 1);
    ({ if (note->buf == ((void *)0)) ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 82); cgc_exit(1); }); });
    note->size = note->cap = data_size;
    cgc_strcpy(note->buf, data);
  }
  else
  {
    note->buf = cgc_calloc(sizeof(char), (1024));
    ({ if (note->buf == ((void *)0)) ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 89); cgc_exit(1); }); });
    note->size = data_size;
    note->cap = (1024);
    cgc_strcpy(note->buf, data);
  }

  note->title = cgc_calloc(sizeof(char), cgc_strlen(title) + 1);
  ({ if (note->title == ((void *)0)) ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 96); cgc_exit(1); }); });
  cgc_strcpy(note->title, title);

  cgc_size_t i;
  for (i = 0; i < (512); i++)
  {
    if (cgc_note_store[i] == ((void *)0))
    {
      cgc_note_store[i] = note;
      break;
    }
  }

  if (i == (512))
    return ((void *)0);

  return note;
}

note_t* cgc_append_note(note_t* note, char* data)
{
  if (!note || !data)
    return ((void *)0);

  if (cgc_strlen(data) + note->size + 1 > note->cap)
  {
#ifdef PATCHED
    note->cap = (cgc_strlen(data) + note->size + 1) * 2;
#else
    note->cap *= 2;
#endif
    note->buf = cgc_realloc(note->buf, note->cap);
    ({ if (note->buf == ((void *)0)) ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 124); cgc_exit(1); }); });
  }

  cgc_strcat(note->buf, data);
  note->size += cgc_strlen(data);
  return note;
}

int cgc_delete_note(note_t* note)
{
  if (!note)
    return -1;

  for (cgc_size_t i = 0; i < (512); i++)
    if (cgc_note_store[i] == note)
      cgc_note_store[i] = ((void *)0);

  if (note->buf)
    cgc_free(note->buf);
  if (note->title)
    cgc_free(note->title);
  cgc_free(note);
  return 0;
}






typedef int (*thunk_fp_t)(char **, list_t **);
struct thunk_t
{
  unsigned arity;
  char** argv;
  thunk_fp_t fp;
};

char* cgc_thunk_res = ((void *)0);

void cgc_free_thunk(thunk_t* thunk)
{
  for (unsigned i = 0; i < thunk->arity; i++)
    if (thunk->argv[i])
      cgc_free(thunk->argv[i]);

  cgc_free(thunk->argv);
  cgc_free(thunk);
}

thunk_t* cgc_new_thunk(thunk_fp_t fp, unsigned arity, char** argv)
{
  if (arity > 4 || !argv)
    return ((void *)0);

  thunk_t* thunk = cgc_calloc(sizeof(thunk_t), 1);
  ({ if (thunk == ((void *)0)) ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 180); cgc_exit(1); }); });

  thunk->fp = fp;
  thunk->arity = arity;
  thunk->argv = cgc_calloc(sizeof(char *), thunk->arity);
  ({ if (thunk->argv == ((void *)0)) ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 185); cgc_exit(1); }); });

  for (unsigned i = 0; i < thunk->arity; i++)
  {
    if (!argv[i])
      goto error;

    thunk->argv[i] = cgc_calloc(sizeof(char), cgc_strlen(argv[i]) + 1);
    ({ if (thunk->argv[i] == ((void *)0)) ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 193); cgc_exit(1); }); });

    cgc_strcpy(thunk->argv[i], argv[i]);
  }

  return thunk;

error:
  cgc_free_thunk(thunk);
  return ((void *)0);
}

void cgc_run_thunk(list_t** list)
{
  if (!list || !*list)
    return;

  thunk_t* thunk = (*list)->thunk;
  thunk->fp(thunk->argv, list);
}


int cgc_append_thunk(char **argv, list_t** list)
{
  char tmp[(8192) + 1];

  if (!argv)
    return -1;

  char* note_title = argv[0];
  char* content = argv[1];

  if (!note_title || !content)
    return -1;

  cgc_strncpy(tmp, content, (8192));
  tmp[(8192)] = '\0';
  cgc_size_t rep_len = cgc_strlen("cloud");

  cgc_size_t idx = 0;
  while (idx < (8192) - rep_len)
  {
    if (cgc_strncmp(tmp + idx, "cloud", rep_len) == 0)
    {
      cgc_memcpy(tmp + idx, "butt ", rep_len);
      idx += rep_len;
    }
    idx++;
  }

  if (cgc_strcmp(content, tmp))
  {
    content = cgc_realloc(content, cgc_strlen(tmp) + 1);
    ({ if (content == ((void *)0)) ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 246); cgc_exit(1); }); });
    cgc_strcpy(content, tmp);
  }

  note_t* note = cgc_get_note(note_title);
  if (note)
    cgc_append_note(note, content);

  cgc_remove_head_list(list);
  if (list)
    cgc_run_thunk(list);

  return 0;
}

int cgc_delete_thunk(char** argv, list_t** list)
{
  char* note_title = argv[0];
  if (!note_title)
    return -1;

  note_t* note = cgc_get_note(note_title);
  if (note)
    cgc_delete_note(note);

  cgc_remove_head_list(list);
  if (list)
    cgc_run_thunk(list);
  return 0;
}







list_t* cgc_thunks = ((void *)0);

list_t* cgc_new_list(list_t* prev, list_t* next, thunk_t* thunk)
{
  list_t* new = cgc_calloc(sizeof(list_t), 1);
  ({ if (new == ((void *)0)) ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 288); cgc_exit(1); }); });
  new->prev = prev;
  new->next = next;
  new->thunk = thunk;
  return new;
}

int cgc_append_list(list_t** list, thunk_t* thunk)
{
  if (!*list)
  {
    *list = cgc_new_list(((void *)0), ((void *)0), thunk);
    return 0;
  }

  list_t* elem = *list;
  while (elem->next)
    elem = elem->next;

  list_t* new = cgc_new_list(elem, ((void *)0), thunk);
  elem->next = new;
  return 0;
}

void cgc_remove_head_list(list_t** list)
{
  if (!list || !*list)
    return;

  if ((*list)->next)
    (*list)->next->prev = ((void *)0);
  *list = (*list)->next;
}

cgc_size_t cgc_len_list(list_t* list)
{
  cgc_size_t len = 0;
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

void cgc_prompt(int fd)
{
  cgc_transmit_string(fd, (char *)PROMPT_MSG);
}

void cgc_yell(int fd)
{
  cgc_transmit_string(fd, (char *)ERROR_MSG);
}

char* cgc_nth_word(unsigned n, char* input, int to_end)
{

  cgc_size_t len = cgc_strlen(input);
  char* word_start[128];
  char* p = input;
  cgc_memset(word_start, '\0', 128 * sizeof(char *));

  for (cgc_size_t i = 0; i < 128; i++)
  {
    if (*p && cgc_isspace(*p))
      p++;
    if (p >= input + len)
      break;

    word_start[i] = p;

    p = cgc_strchr(p, ' ');
    if (!p)
      break;
  }

  p = word_start[n];
  if (!p)
    return ((void *)0);

  char* end = ((void *)0);
  if (!to_end)
    end = cgc_strchr(p, ' ');
  if (!end)
    end = cgc_strchr(p, '\0');
  if (!end)
    ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "malformed string" "\n", "src/main.c", 389); cgc_exit(1); });

  char* res = cgc_calloc(sizeof(char), end - p + 1);
  ({ if (res == ((void *)0)) ({ cgc_fdprintf(2, "ERROR %s:%d:\t" "bad alloc" "\n", "src/main.c", 392); cgc_exit(1); }); });
  return cgc_strncpy(res, p, end - p);
}

char** cgc_make_argv(char* input, cgc_size_t n)
{
  char** argv = cgc_calloc(sizeof(char *), n);

  cgc_size_t i;
  for(i = 0; i < n - 1; i++)
  {
    argv[i] = cgc_nth_word(i + 1, input, 0);
    if (!argv[i])
      goto error;
  }

  argv[i] = cgc_nth_word(i + 1, input, 1);
  if (!argv[i])
    goto error;
  return argv;

error:
  for(cgc_size_t i = 1; i < n - 1; i++)
    if (argv[i])
      cgc_free(argv[i]);
  cgc_free(argv);
  return ((void *)0);
}

void cgc_print_argv(char** argv, cgc_size_t n)
{
  for(cgc_size_t i = 0; i < n; i ++)
    if (argv[i])
                        ;
}

void cgc_free_argv(char** argv, cgc_size_t n)
{
  if (!argv || !n)
    return;

  for(cgc_size_t i = 0; i < n; i ++)
    if (argv[i])
      cgc_free(argv[i]);
  cgc_free(argv);
}
# 454 "src/main.c"
int main(int cgc_argc, char *cgc_argv[])
{

  char input_buf[(16 * 1024)];
  const char* resp;
  for (;;)
  {
    cgc_prompt(1);
    cgc_memset(input_buf, '\0', (16 * 1024));
    if (cgc_read_until(0, (16 * 1024), '\n', input_buf) < 0)
      break;

    if (cgc_strncmp(input_buf, "quit", 4) == 0)
        cgc_exit(0);

    char* command = cgc_nth_word(0, input_buf, 0);
    char** argv = ((void *)0);

    if (!command)
      continue;

#ifdef PATCHED
    if (cgc_len_list(cgc_thunks) > 32)
      cgc_run_thunk(&cgc_thunks);
#endif

    if (cgc_strncmp(command, "new-note", cgc_strlen("new-note")) == 0)
    {
      cgc_run_thunk(&cgc_thunks);
      argv = cgc_make_argv(input_buf, 2);
      if (argv)
      {
        if (cgc_new_note(argv[0], argv[1]) == ((void *)0))
          resp = NOTE_FULL;
        else
          resp = NOTE_CREATED;
        cgc_free_argv(argv, 2);
      }
    }
    else if (cgc_strncmp(command, "append-note", cgc_strlen("append-note")) == 0)
    {
      argv = cgc_make_argv(input_buf, 2);
      if (argv)
      {
        thunk_t* thunk = cgc_new_thunk(cgc_append_thunk, 2, argv);
        cgc_append_list(&cgc_thunks, thunk);
        resp = NOTE_APPENDED;
        cgc_free_argv(argv, 2);
      }
    }


    else if (cgc_strncmp(command, "delete-note", cgc_strlen("delete-note")) == 0)
    {
      argv = cgc_make_argv(input_buf, 1);
      if (argv)
      {
        thunk_t* thunk = cgc_new_thunk(cgc_delete_thunk, 1, argv);
        cgc_append_list(&cgc_thunks, thunk);
        resp = NOTE_DELETED;
        cgc_free_argv(argv, 1);
      }
    }
    else if (cgc_strncmp(command, "get-note", cgc_strlen("get-note")) == 0)
    {
      cgc_run_thunk(&cgc_thunks);
      argv = cgc_make_argv(input_buf, 1);
      if (argv)
      {
        note_t* note = cgc_get_note(argv[0]);
        if (note)
          cgc_fdprintf(1, "%s\n", note->buf);
        else
          resp = NOTE_UNK;
      }
    }

    else
    {
      cgc_yell(1);
    }

    if (resp)
      cgc_transmit_string(1, (char *)resp);
    resp = ((void *)0);
    cgc_free(command);
  }
}
