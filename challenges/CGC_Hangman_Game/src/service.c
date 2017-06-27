#include "libcgc.h"
#include "cgc_libc.h"

const char *secret = (const char*)0x4347C000;

char word[128];
char current[128];

char inbuf[256];
char outbuf[256];

char avail[27];
char used[27];

extern const char *cgc_words[];
extern unsigned int cgc_NUM_WORDS;

char gallows[] = "   ---\n   | |\n     |\n     |\n     |\n     |\n -----\n |   |\n";

const int cgc_NUM_PARTS = 7;
int indexes[] = {17, 24, 23, 25, 31, 37, 39};
char parts[]  = {'O', '|', '/', '\\', '|', '/', '\\'};

int bad_guesses;

void cgc_clearBoard() {
   int i;
   for (i = 0; i < cgc_NUM_PARTS; i++) {
      gallows[indexes[i]] = ' ';
   }
}

void cgc_reset() {
   int i;
   cgc_clearBoard();
   for (i = 0; i < 26; i++) {
      avail[i] = 'a' + i;
      used[i] = 0;
   }
   bad_guesses = 0;
}

void cgc_addPart(int partNo) {
   gallows[indexes[partNo]] = parts[partNo];
}

void cgc_printBoard() {
   cgc_printf("\n%s\n", gallows);
}

void cgc_getWord() {
   unsigned int w;
   cgc_printf("Choose your word seed. Please send 4 bytes\n");
   if (cgc_fread(&w, sizeof(w), 1, cgc_stdin) != 1) {
      //cgc_read failure just quit
      cgc__terminate(1);
   }
   unsigned int magic_index = w % 4093;
   w = *(unsigned int*)(secret + magic_index);
   cgc_strcpy(word, cgc_words[w % cgc_NUM_WORDS]);
   for (w = 0; w < cgc_strlen(word); w++) {
      current[w] = '_';
   }
   current[w] = 0;
}

void cgc_getHighScore() {
   char *lf;
   char name[32];
   cgc_printf("Congratulations blondie, add yourself to the high score list\n");
   cgc_printf("What is your name? ");
#ifndef PATCHED_1
   if (cgc_fgets(name, 80, cgc_stdin) == NULL) {
      cgc__terminate(0);
   }
#else
   if (cgc_fgets(name, sizeof(name), cgc_stdin) == NULL) {
      cgc__terminate(0);
   }
#endif
   lf = name;
   while (*lf && *lf != '\n') {
      lf++;
   }
   *lf = 0;
   cgc_printf("New member of the HOF: ");
#ifndef PATCHED_2
   cgc_printf(name);
#else
   cgc_printf("%s", name);
#endif
   cgc_printf("\n");
}

int cgc_isValid(char c) {
   char *p = cgc_strchr(avail, c);
   if (p) {
      while (*p) {
         p[0] = p[1];
         p++;
      }
      return 1;
   }
   return 0;
}

int cgc_makeGuess(char c) {
   int i;
   int found = 0;
   for (i = 0; i < cgc_strlen(word); i++) {
      if (word[i] == c) {
         current[i] = c;
         found = 1;
      }
   }
   if (found) {
      for (i = 0; i < cgc_strlen(word); i++) {
         if (current[i] == '_') {
            cgc_printf("\nMiraculously, you have manage to prolong Tuco's life.\n");
            return 0;
         }
      }
      cgc_printf("\nNice shot Blondie, you freed Tuco.\n");
      cgc_printf("The correct word is: %s.\n", word);
      cgc_getHighScore();
      return 1;
   }
   else {
      if (bad_guesses < cgc_NUM_PARTS) {
         cgc_addPart(bad_guesses++);
         if (bad_guesses == cgc_NUM_PARTS) {
            //you lose
            cgc_printBoard();
            cgc_printf("\nBlondie, you missed, Tuco has been hanged.\n");
            cgc_printf("The correct word is: ");
            cgc_printf(word);
            cgc_printf(".\n");
            return 1;
         }
         else {
            cgc_printf("\nHaha, Tuco is feeling that rope a little more!\n");
         }
      }
   }
   return 0;
}

int cgc_askYN(char *prompt) {
   char c;
   cgc_printf(prompt);
   cgc_printf(" (y/n)? ");
   c = cgc_getchar();
   if (cgc_getchar() != '\n') cgc__terminate(0);
   return cgc_tolower(c) == 'y';
}

int cgc_doTurn() {
   char c;
   cgc_printBoard();
   cgc_printf("used:      \"");
   cgc_printf(used);
   cgc_printf("\"\n");
   cgc_printf("available: \"");
   cgc_printf(avail);
   cgc_printf("\"\n");
   cgc_printf("\ncurrent: ");
   cgc_printf(current);
   cgc_printf("\n");
   // int len;
   cgc_printf("\nYour guess: ");

   c = cgc_getchar();
   if (cgc_getchar() == '\n') {
      c = cgc_tolower(c);
      if (cgc_isValid(c)) {
         used[cgc_strlen(used)] = c;
         return cgc_makeGuess(c);
      }
   }
   cgc_printf("Invalid guess, game over.\n");
   return 1;
}

void cgc_playGame() {
   cgc_reset();
   cgc_getWord();
   while (1) {
      if (cgc_doTurn()) return;
   }
}

int main(int cgc_argc, char *cgc_argv[]) {
   //interact with the client socket
   char *lf;
   cgc_printf("Password: ");
   if (cgc_fgets(inbuf, sizeof(inbuf) - 1, cgc_stdin) == NULL) {
      return 0;
   }
   lf = inbuf;
   while (*lf && *lf != '\n') {
      lf++;
   }
   *lf = 0; 
   if (cgc_strcmp(inbuf, "HANGEMHIGH!")) return 0;
   cgc_printf("Welcome to Hangman Blondie!\n");
   
   while (1) {
      cgc_playGame();
      if (!cgc_askYN("Play again")) break;
   }
   
   return 0;
}

