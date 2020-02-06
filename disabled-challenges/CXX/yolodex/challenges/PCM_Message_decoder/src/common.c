/*

Author: Joe Rogers <joe@cromulence.com>

Copyright (c) 2014 Cromulence LLC

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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_common.h"
#include "cgc_service.h"
#include "cgc_language.h"

int cgc_FindCode(char *s) {
    int i;

    for (i = 0; i < 91; i++) {
      if (cgc_strcmp(l[i].code, s) == 0) {
        return(i);
      }
    }
    return(-1);
}

void cgc_InitLang(struct language *lp, char *old_code) {
  int index;
  char new_code[MAX_CODE];

  // end of the tree
  if (lp == NULL) {
    return;
  }

  // recursively look up the next code in the sequence
  cgc_bzero(new_code, MAX_CODE);
  cgc_strncat(new_code, old_code, MAX_CODE);
  cgc_strncat(new_code, ".", MAX_CODE);
  if ((index = cgc_FindCode(new_code)) == -1) {
    return;
  }
  lp->dit = &l[index];
  cgc_InitLang(&l[index], new_code);

  cgc_bzero(new_code, MAX_CODE);
  cgc_strncat(new_code, old_code, MAX_CODE);
  cgc_strncat(new_code, "-", MAX_CODE);
  if ((index = cgc_FindCode(new_code)) == -1) {
    return;
  }
  lp->dah = &l[index];
  cgc_InitLang(&l[index], new_code);

}
