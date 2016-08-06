#ifndef LIBC_H
#define LIBC_H

size_t strlen(const char *str);
char *strcpy(char *dst, const char *src);
int strcmp(const char *s1, const char *s2);
int memcmp(const char *s1, const char *s2, unsigned int len);
char *memcpy(char *s1, const char *s2, unsigned int len);
char *strchr(const char *s, int c);
int printf(const char *format, ...);

int toupper(int c);
int tolower(int c);

int transmit_all(int fd, const void *buf, const size_t size);
int receive_all(int fd, char *buf, const size_t size);

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

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

int  fgetc(FILE *);
int  getc(FILE *);
int  getchar(void);

char *fgets(char *, int, FILE *);
int fread(void *, size_t, size_t, FILE *);

int ferror(FILE *stream);
int feof(FILE *stream);

int printf(const char *format, ...);
int fprintf(FILE * stream, const char *format, ...);
void receive_until_delim(int fd, char delim);

#endif
