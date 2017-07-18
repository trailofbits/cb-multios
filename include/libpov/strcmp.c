
typedef unsigned int cgc_size_t;
typedef unsigned char uint8_t;

int cgc_strcmp(const char *s1, const char *s2) {
   while (*s1 != '\0' && *s2 != '\0'  && *s1 == *s2) {
      s1++;
      s2++;
   }
   return *s1 - *s2;
}

int cgc_strncmp(const char *s1, const char *s2, cgc_size_t n) {
   while (n != 0 && *s1 != '\0' && *s2 != '\0'  && *s1 == *s2) {
      s1++;
      s2++;
      n--;
   }
   return n == 0 ? 0 : (*s1 - *s2);
}

int cgc_memcmp(const void *b1, const void *b2, cgc_size_t n) {
   uint8_t *p1 = (uint8_t*)b1;
   uint8_t *p2 = (uint8_t*)b2;
   while (n > 0 && *p1 == *p2) {
      p1++;
      p2++;
      n--;
   }
   return n == 0 ? 0 : (*p1 - *p2);
}

