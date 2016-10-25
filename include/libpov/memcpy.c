
typedef unsigned int cgc_size_t;

void *cgc_memcpy(void *dst, const void *src, cgc_size_t n) {
   char *d = (char*)dst;
   const char *s = (const char *)src;
   while (n--) {*d++ = *s++;}
   return dst;
}

