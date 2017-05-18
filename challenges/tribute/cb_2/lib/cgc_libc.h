#ifndef LIBC_H
#define LIBC_H

#define LONG_MAX 0x7FFFFFFF
#define LONG_MIN 0x80000000
#define ERANGE 20

unsigned int cgc_htonl(unsigned int hostlong);

cgc_size_t cgc_strlen(const char *str);
char *cgc_strcpy(char *dst, const char *src);
int cgc_strcmp(const char *s1, const char *s2);
char *cgc_strchr(const char *s, int c);
long cgc_strtol(const char *str, char **endptr, int base);
char *cgc_strsep(char **stringp, const char *delim);

void *cgc_memset(void *dst, int c, unsigned int n);
int cgc_memcmp(const void *b1, const void *b2, cgc_size_t n);

int cgc_toupper(int c);
int cgc_tolower(int c);

int cgc_transmit_all(int fd, const char *buf, const cgc_size_t size);

extern int errno;

#define EOF                  -1

#ifndef NULL
#define NULL ((void*)0)
#endif

#define _FILE_STATE_OPEN  1
#define _FILE_STATE_ERROR 2
#define _FILE_STATE_EOF   4
#define _FILE_HAVE_LAST   8

typedef struct _FILE {
   int fd;
   int state;
   int last;
} FILE;

extern FILE *cgc_stdin;
extern FILE *cgc_stdout;
extern FILE *cgc_stderr;

int  cgc_fgetc(FILE *);
int  cgc_getc(FILE *);
int  cgc_getchar(void);

char *cgc_fgets(char *, int, FILE *);

int ferror(FILE *stream);
int feof(FILE *stream);

int cgc_printf(const char *format, ...);
int cgc_fprintf(FILE * stream, const char *format, ...);
int cgc_snprintf(char *str, cgc_size_t size, const char *format, ...);

#endif
