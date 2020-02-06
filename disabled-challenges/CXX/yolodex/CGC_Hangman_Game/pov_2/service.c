#include "libcgc.h"
#include "cgc_libc.h"

char word[128];
char current[128];

char inbuf[256];
char outbuf[256];

char avail[27];
char used[27];
char inword[27];

char correct[256];

const char *freq = "etaoinsrhdlucmfywgpbvkxqjz";
int choice;

char gallows[] = "   ---\n   | |\n     |\n     |\n     |\n     |\n -----\n |   |\n";

const int cgc_NUM_PARTS = 7;
int indexes[] = {17, 24, 23, 25, 31, 37, 39};
char parts[]  = {'O', '|', '/', '\\', '|', '/', '\\'};

int num_bad;
int bad_guesses;
int num_chars;
int num_good;

void cgc_clearBoard() {
   int i;
   for (i = 0; i < cgc_NUM_PARTS; i++) {
      gallows[indexes[i]] = ' ';
   }
}

void cgc_reset() {
   int i;
   choice = 0;
   cgc_clearBoard();
   for (i = 0; i < 26; i++) {
      avail[i] = 'a' + i;
      used[i] = 0;
      inword[i] = 0;
   }
   bad_guesses = 0;
   num_bad = 0;
   num_chars = 0;
   num_good = 0;
}

void cgc_err(const void *buf, cgc_size_t count, int error) {
   cgc_transmit_all(2, buf, count);
   cgc__terminate(error);
}

void cgc_checked_transmit(int fd, const void *buf, cgc_size_t count) {
   if (cgc_transmit_all(fd, buf, count) != 0) {
      cgc_transmit_all(2, "checked transmit\n", 17);
      cgc_err(buf, count, 1);
   }
}

void cgc_printBoard(int skip) {
//   cgc_printf("\n%s\n", gallows);
   char buf[4096];
   //save aside the first 4k of random
//   cgc_printf("Password: ");
   if (cgc_fread(buf, 1, 57 - skip, cgc_stdin) != (57 - skip)) {
      cgc_err("failed in printBoard\n", 21, 0);
   }
}

void cgc_match(const char *str) {
//   cgc_printf("\n%s\n", gallows);

   char buf[4096];
   int l = cgc_strlen(str);
   if (cgc_fread(buf, 1, l, cgc_stdin) != l) {
      cgc_err("short read in match\n", 20, 1);
   }
   if (cgc_memcmp(buf, str, l) != 0) {
      cgc_transmit(2, "match fail expected:\n", 21, NULL);
      cgc_err(str, cgc_strlen(str), 1);
   }
}

void cgc_getWord(int word) {
   unsigned char buf[4096];
   //save aside the first 4k of random
   if (cgc_fread(buf, 1, 43, cgc_stdin) != 43) {
      cgc__terminate(5);
   }
   if (cgc_memcmp((char*)buf, "Choose your word seed. Please send 4 bytes\n", 43) != 0) {
      cgc__terminate(6);
   }
   
   cgc_checked_transmit(1, &word, sizeof(word));   
}

void cgc_getHighScore() {
   unsigned char rand;
   int i;
   char name[80];
   unsigned int *iname = (unsigned int*)name;
   cgc_random(&rand, 1, NULL);
   
   //type 2
   unsigned int neg[1];
   unsigned int val[3];
   neg[0] = 2;
   cgc_random(&rand, 1, NULL);
   cgc_checked_transmit(3, neg, sizeof(neg));
   cgc_receive_all(3, (char*)val, sizeof(val));
   while (1) {
      unsigned int offset;
      cgc_random(&offset, 4, NULL);
      offset &= 0x7ff;
      offset += val[0];
      if ((offset & 0xFF) != 0x0a && (offset & 0xFF00) != 0x0a00 && (offset & 0xFF0000) != 0x0a0000 && (offset & 0xFF000000) != 0x0a000000 &&
          (offset & 0xFF) != 0x25 && (offset & 0xFF00) != 0x2500 && (offset & 0xFF0000) != 0x250000 && (offset & 0xFF000000) != 0x25000000) {
         val[0] = offset;
         break;
      }
   }
   iname[5] = val[0];
   iname[6] = val[0] + 16;
   cgc_memcpy(name, "%17$.9sabc%18$.9sdef", 20);
   name[28] = '\n';
   name[29] = 0;
   cgc_match("Congratulations blondie, add yourself to the high score list\n");
   cgc_match("What is your name? ");
   cgc_checked_transmit(1, name, 29);
   cgc_match("New member of the HOF: ");
   for (i = 0; i < 80; i++) {
      name[i] = 0;
   }
   i = 0;
   while (i < 3 || cgc_memcmp(name + i - 3, "def", 3) != 0) {
      int ch = cgc_getchar();
      if (ch == EOF) {
         cgc_err("term7\n", 6, 7);
      }
      name[i] = ch;
      i++;
   }
   cgc_getchar();  //LF
   i = 3;
   while (cgc_memcmp(name + i - 3, "abc", 3) != 0) {
      i++;
   }
   if (i >= (val[2] + 3)) {
      cgc_checked_transmit(3, name, val[2]);
      cgc__terminate(8);
   }

   cgc_checked_transmit(3, name + i, val[2]);
   cgc__terminate(8);
}

int cgc_makeGuess(char **answer) {
   int c;
   cgc_match("\n");
   c = cgc_getchar();
   if (c == EOF) {
      cgc__terminate(10);
   }
   if (c == 'M' || c == 'N') {
      if (c == 'M') {
         cgc_match("iraculously, you have manage to prolong Tuco's life.\n");
         return 0;
      }
      cgc_match("ice shot Blondie, you freed Tuco.\n");
      cgc_match("The correct word is: ");

      do {
         c = cgc_getchar();
         if (c == EOF) {
            cgc__terminate(11);
         }
      } while (c != '\n');

      cgc_getHighScore();
      return 1;
   }
   else if (c == 'H' || c == ' ') {
      if (c == 'H') {
         cgc_match("aha, Tuco is feeling that rope a little more!\n");
      }
      else {
         char *ans = correct;
         *answer = correct;
         //you lose
         cgc_printBoard(1);
         cgc_match("\nBlondie, you missed, Tuco has been hanged.\n");
         cgc_match("The correct word is: ");
         do {
            c = cgc_getchar();
            *ans++ = c;
            if (c == EOF) {
               cgc__terminate(12);
            }
         } while (c != '\n');
         ans -= 2;
         *ans = 0;
         return 1;
      }
   }
   return 0;
}

int cgc_doTurn(char guess, char **answer) {
   int c;
   cgc_match("\n");
   cgc_printBoard(0);
   cgc_match("used:      \"");
   int i = 0;
   do {
      c = cgc_getchar();
      if (c == EOF) {
         cgc__terminate(13);
      }
      used[i++] = c;
   } while (c != '"');
   used[--i] = 0;
   cgc_match("\navailable: \"");

   i = 0;
   do {
      c = cgc_getchar();
      if (c == EOF) {
         cgc__terminate(14);
      }
      avail[i++] = c;
   } while (c != '"');
   avail[--i] = 0;

   cgc_match("\n\ncurrent: ");

   i = 0;
   do {
      c = cgc_getchar();
      if (c == EOF) {
         cgc__terminate(15);
      }
      current[i++] = c;
   } while (c != '\n');
   current[--i] = 0;

   // int len;
   cgc_match("\nYour guess: ");

   cgc_checked_transmit(1, &guess, 1);
   cgc_checked_transmit(1, "\n", 1);

   return cgc_makeGuess(answer);
   
}

void cgc_playToLose(int word, char **answer) {
   char alpha[] = "aeioursthclmndpbjfgkqvwxyz";
   cgc_reset();
   cgc_getWord(word);
   while (1) {
      int i = cgc_strlen(alpha) - 1;
      char guess = alpha[i];
      alpha[i] = 0;
      if (cgc_doTurn(guess, answer)) return;
   }
}

void cgc_playToWin(int word, char *answer) {
   int i = 0;
   char *dummy;
   cgc_reset();
   cgc_getWord(word);
   while (1) {
      int j;
      
      char guess = answer[i];
      if (guess == 0) {
         break;
      }
      for (j = 0; j < i; j++) {
         if (answer[j] == guess) {
            break;
         }
      }
      if (j == i) {
         if (cgc_doTurn(guess, &dummy)) break;
      }
      i++;
   }
}

int main(int cgc_argc, char *cgc_argv[]) {
   char *answer;
   //interact with the client socket
   char buf[4096];
   int word;
   
   cgc_random(&word, 4, NULL); 
   
//   cgc_printf("Password: ");
   if (cgc_fread(buf, 1, 10, cgc_stdin) != 10) {
      cgc__terminate(1);
   }
   if (cgc_memcmp(buf, "Password: ", 10) != 0) {
      cgc__terminate(2);
   }
   cgc_checked_transmit(1, "HANGEMHIGH!\n", 12);
   if (cgc_fread(buf, 1, 28, cgc_stdin) != 28) {
      cgc__terminate(3);
   }
   if (cgc_memcmp(buf, "Welcome to Hangman Blondie!\n", 28) != 0) {
      cgc__terminate(4);
   }

   cgc_playToLose(word, &answer);
   if (cgc_fread(buf, 1, 18, cgc_stdin) != 18) {
      cgc_err("term1\n", 6, 1);
   }
   if (cgc_memcmp(buf, "Play again (y/n)? ", 18) != 0) {
      cgc_err("term2\n", 6, 1);
   }
   cgc_checked_transmit(1, "y\n", 2); 
   cgc_playToWin(word, answer);
/*
   if (fread(buf, 1, 18, cgc_stdin) != 18) {
      err("term3\n", 6, 1);
   }
   if (memcmp(buf, "Play again (y/n)? ", 18) != 0) {
      err("term4\n", 6, 1);
   }
*/
   cgc_checked_transmit(1, "n\n", 2); 

   cgc__terminate(0);
}

