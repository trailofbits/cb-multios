/*

Author: Debbie Nuttall <debbie@cromulence.co>

Copyright (c) 2015 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include <libcgc.h>
#include "stdlib.h"
#include "stdint.h"
#include "prng.h"

#define MAX_ROUNDS 256
#define DIFFERENCE 20
#define BREAK_ROUND 100

enum colors {RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET, NUM_COLORS};
char *color_names[NUM_COLORS] = {"RED", "ORANGE", "YELLOW", "GREEN", "BLUE", "INDIGO", "VIOLET"};

int keep_receiving_until(char *dst, char delim, size_t max) {
  char c;
  size_t rx;
  size_t len = 0;
  do {
    if ( receive( STDIN, &c, 1, &rx ) != 0 ) {
      len = 0;
      break;
    }
    if (rx == 0) {
      len = 0;
      break;
    }

    if (len < max) {
      if (c == delim) {
        dst[len] = '\0';
        break;
      }
      dst[len++] = c;
    }
  } while (c != delim);
  return len;
}


void simon_command(char *t) {
#ifdef PATCHED
  char response[MAX_ROUNDS + 1];
#else
  char response[MAX_ROUNDS + 1 - DIFFERENCE];
#endif
  char sequence[MAX_ROUNDS];

  if (t == NULL) {
    return;
  }

  if (strlen(t) < 8) {
    return;
  }

  uint64_t seed = *(uint64_t *)t;
  sprng(seed);

  int rounds = 0;

  while (rounds < MAX_ROUNDS) {

    if (rounds == BREAK_ROUND) {
      printf("You're doing great! Continue?(y/n):");
      char response;
      if (keep_receiving_until(&response, '\n', 1) != 1) {
        return;
      }
      if (!((response == 'y') || (response == 'Y'))) {
        printf("Good game\n");
        return;
      }
    }

    int new_color = random_in_range(0, NUM_COLORS - 1);
    sequence[rounds++] = new_color;

    // Print sequence
    printf("Simon says: ");
    for (int i = 0; i < rounds; i++) {
      printf("@s ", color_names[sequence[i]]);
    }
    printf(":\n");
    // Read response
    if (keep_receiving_until(response, '\n', rounds + 1) != rounds) {
      return;
    }

    // Check response
    for (int i = 0; i < rounds; i++) {
      if (sequence[i] != (response[i] - '0')) {
        printf("Simon says no fuzzing\n");
        if (rounds >= 8) {
          seed = *(uint64_t *)(response + i - 8);
        }
        sprng(seed);
        rounds = 0;
      }
    }
  }
  printf("You Win!\n");
}