
void *cgc_memset(void *dst, int c, unsigned int n) {
   char *d = (char*)dst;
   while (n--) {*d++ = (char)c;}
   return dst;
}

