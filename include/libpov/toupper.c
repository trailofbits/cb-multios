
int cgc_isalpha(int c);

int cgc_toupper(int c) {
   if (cgc_isalpha(c)) {
      return c & ~0x20;
   }
   return c;
}

int cgc_tolower(int c) {
   if (cgc_isalpha(c)) {
      return c | 0x20;
   }
   return c;
}

