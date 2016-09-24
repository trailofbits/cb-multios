
typedef unsigned int size_t;

size_t strlen(const char *str) {
   size_t res = 0;
   while (*str++) {res++;}
   return res;
}

