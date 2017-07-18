
#ifndef NULL
#define NULL ((void*)0)
#endif

typedef unsigned int cgc_size_t;

char *cgc_strchr(const char *s, int c) {
   while (*s && *s != c) {s++;}
   return (char*)(*s ? s : (c ? NULL : s));
}
