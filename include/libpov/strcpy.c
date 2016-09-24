
char *strcpy(char *dst, const char *src) {
   char *d = dst;
   while ((*d++ = *src++) != 0) {}
   return dst;
}

