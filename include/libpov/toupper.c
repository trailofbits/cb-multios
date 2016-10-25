
int isalpha(int c);

int toupper(int c) {
   if (isalpha(c)) {
      return c & ~0x20;
   }
   return c;
}

int tolower(int c) {
   if (isalpha(c)) {
      return c | 0x20;
   }
   return c;
}

