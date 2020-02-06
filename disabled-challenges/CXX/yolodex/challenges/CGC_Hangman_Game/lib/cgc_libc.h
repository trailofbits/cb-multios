#ifndef LIBC_H
#define LIBC_H

cgc_size_t cgc_strlen(const char *str);
char *cgc_strcpy(char *dst, const char *src);
int cgc_strcmp(const char *s1, const char *s2);
char *cgc_strchr(const char *s, int c);
int cgc_printf(const char *format, ...);

int cgc_toupper(int c);
int cgc_tolower(int c);

int cgc_transmit_all(int fd, const void *buf, const cgc_size_t size);

#define EOF                  -1

#ifndef NULL
#define NULL ((void*)0)
#endif

#define _FILE_STATE_OPEN  1
#define _FILE_STATE_ERROR 2
#define _FILE_STATE_EOF   4
#define _FILE_HAVE_LAST   8

struct _FILE;
typedef struct _FILE FILE;

extern FILE *cgc_stdin;
extern FILE *cgc_stdout;
extern FILE *cgc_stderr;

int  cgc_fgetc(FILE *);
int  cgc_getc(FILE *);
int  cgc_getchar(void);

char *cgc_fgets(char *, int, FILE *);
int cgc_fread(void *, cgc_size_t, cgc_size_t, FILE *);

int ferror(FILE *stream);
int feof(FILE *stream);

int cgc_printf(const char *format, ...);
int fprintf(FILE * stream, const char *format, ...);

#endif
