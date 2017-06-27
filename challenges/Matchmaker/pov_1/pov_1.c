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

#include "libpov.h"

#define STDIN 0
#define STDOUT 1

#define EXIT_FAILURE (-1)
#define EXIT_SUCCESS (0)

char
cgc_todigit(unsigned int value, unsigned int base)
{
    if (base < 2 || base > 16 || value >= base)
        return '\0';

    if (value < 10)
        return value + '0';
    else
        return (value - 10) + 'a';
}

int
cgc_utostr(unsigned int value, unsigned int base, int uppercase, char *str, cgc_size_t num)
{
    unsigned int i, tmp;
    cgc_size_t len = 1;

    if (base < 2 || base > 16 || num < 1)
        return EXIT_FAILURE;

    tmp = value;
    while (tmp /= base)
        len++;

    if (len >= num)
        return EXIT_FAILURE;

    for (i = 0; i < len; i++) {
        str[len - i - 1] = cgc_todigit(value % base, base);
        value /= base;

        if (uppercase)
            str[len - i - 1] = cgc_toupper(str[len - i - 1]);
    }

    str[len] = '\0';
    return EXIT_SUCCESS;
}

unsigned char
cgc_play_game(void)
{
    unsigned char guess, lo = 0, hi = 255;
    unsigned char *cgc_read;
    unsigned int len;
    char buf[10];

    // I'm thinking of a magic number, can you guess it ?!?!\n
    cgc_delimited_read(STDIN, &cgc_read, &len, (unsigned char *)"\n", 1);
    cgc_free(cgc_read);

    while (1) {
        guess = (lo + hi) / 2;
        cgc_utostr(guess, 10, 0, buf, sizeof(buf));

        cgc_transmit_all(STDOUT, buf, cgc_strlen(buf));
        cgc_transmit_all(STDOUT, "\n", 1);

        cgc_delimited_read(STDIN, &cgc_read, &len, (unsigned char *)"\n", 1);
        if (cgc_strncmp((char *)cgc_read, "Just right!\n", len) == 0)
            break;
        else if (cgc_strncmp((char *)cgc_read, "Haha, too small!\n", len) == 0)
            lo = guess + 1;
        else if (cgc_strncmp((char *)cgc_read, "Whoa, too big\n", len) == 0)
            hi = guess - 1;
        cgc_free(cgc_read);

        // WRONG!\n
        cgc_delimited_read(STDIN, &cgc_read, &len, (unsigned char *)"\n", 1);
        cgc_free(cgc_read);
    }

    cgc_free(cgc_read);
    return guess;
}

unsigned char
cgc_get_byte(unsigned int byte)
{
    unsigned char ret;
    char index = 'a' + byte;
    char buf[] = "transition % 1\n";
    unsigned char *cgc_read;
    unsigned int len;

    cgc_transmit_all(STDOUT, "reset\n", sizeof("reset\n") - 1);
    // Please re-enter state machine\n
    cgc_delimited_read(STDIN, &cgc_read, &len, (unsigned char *)"\n", 1);
    cgc_free(cgc_read);

    cgc_transmit_all(STDOUT, "onmatch magic\n", sizeof("onmatch magic\n") - 1);
    // Match action updated\n
    cgc_delimited_read(STDIN, &cgc_read, &len, (unsigned char *)"\n", 1);
    cgc_free(cgc_read);

    cgc_transmit_all(STDOUT, "state\n", sizeof("state\n") - 1);
    buf[sizeof("transition ") - 1] = index;
    cgc_transmit_all(STDOUT, buf, sizeof(buf) - 1);
    cgc_transmit_all(STDOUT, "state accept\n", sizeof("state accept\n") - 1);
    cgc_transmit_all(STDOUT, "done\n", sizeof("done\n") - 1);

    // Ok, matching input now\n
    cgc_delimited_read(STDIN, &cgc_read, &len, (unsigned char *)"\n", 1);
    cgc_free(cgc_read);

    cgc_transmit_all(STDOUT, &index, 1);
    cgc_transmit_all(STDOUT, "\n", 1);

    ret = cgc_play_game();
    cgc_delimited_read(STDIN, &cgc_read, &len, (unsigned char *)"\n", 1);
    return ret;
}

int
main(int cgc_argc, char *cgc_argv[])
{
    unsigned int i;
    unsigned char flag[4] = {0, 0, 0, 0};

    cgc_negotiate_type2();

    for (i = 0; i < sizeof(flag); i++)
        flag[i] = cgc_get_byte(i);

    cgc_type2_submit(flag, sizeof(flag));
    cgc_transmit_all(STDOUT, "quit\n", sizeof("quit\n") - 1);

    return 0;
}

