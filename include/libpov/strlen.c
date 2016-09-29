
typedef unsigned int cgc_size_t;

cgc_size_t cgc_strlen(const char *str) {
   cgc_size_t res = 0;
   while (*str++) {res++;}
   return res;
}

