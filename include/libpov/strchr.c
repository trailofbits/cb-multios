
#ifndef NULL
#define NULL ((void*)0)
#endif

typedef unsigned int size_t;

char *strchr(const char *s, int c) {
   while (*s && *s != c) {s++;}
   return (char*)(*s ? s : (c ? NULL : s));
}
