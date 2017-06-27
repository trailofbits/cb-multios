/*
 * Copyright (c) 2014 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "libpov.h"
#include "libcgc.h"

int main(int cgc_argc, char *cgc_argv[])
{
    unsigned int pov_type = 2;
    cgc_transmit_all(3, &pov_type, sizeof(pov_type));
    unsigned int type2_resp[2];
    if (cgc_length_read(3, (unsigned char *)type2_resp, sizeof(type2_resp)) != sizeof(type2_resp)) {
        cgc__terminate(0);
    }
    unsigned int secret_page_address = type2_resp[0];
    unsigned int num_secret_bytes = type2_resp[1];

    char *setup_m1= "1\n1\n16\n16\n"
                    "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
                    "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
                    "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
                    "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
                    "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
                    "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 17431 32767\n";

    char *setup_m2= "1\n2\n16\n16\n"
                    "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
                    "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
                    "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
                    "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
                    "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 "
                    "0 0 0 0 0 0 0 0 0 3161 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 32767\n";

    char *multiply= "5\n";
    char *gen_random= "10\n1\n1\n2\n";
    char *print_secret= "2\n";
    char *cgc_exit= "11\n";

    cgc_transmit_all(STDOUT, setup_m1, cgc_strlen(setup_m1));
    cgc_transmit_all(STDOUT, setup_m2, cgc_strlen(setup_m2));
    cgc_transmit_all(STDOUT, multiply, cgc_strlen(multiply));
    cgc_transmit_all(STDOUT, gen_random, cgc_strlen(gen_random));
    cgc_transmit_all(STDOUT, print_secret, cgc_strlen(print_secret));
    cgc_transmit_all(STDOUT, cgc_exit, cgc_strlen(cgc_exit));

    unsigned char buf[64];
    cgc_memset(buf, 0, 64);

    int i;
    for (i = 0; i < 2780; i++)
    {
        if ((cgc_length_read(STDIN, buf, 1)) == 1)
            cgc_transmit_all(STDERR, buf, 1);
    }

    for (i = 0; i < sizeof(buf) ; i++)
    {
        if ((cgc_length_read(STDIN, &buf[i], 1)) == 1)
            cgc_transmit_all(STDERR, &buf[i], 1);

        if (buf[i] == ' ')
        {
            buf[i] = '\0';
            break;
        }
    }
    short first_half = cgc_strtol((char *)buf, NULL, 10);

    for (i = 0; i < 2; i++)
    {
        if ((cgc_length_read(STDIN, buf, 1)) == 1)
            cgc_transmit_all(STDERR, buf, 1);
    }

    for (i = 0; i < sizeof(buf) ; i++)
    {
        if ((cgc_length_read(STDIN, &buf[i], 1)) == 1)
            cgc_transmit_all(STDERR, &buf[i], 1);

        if (buf[i] == ' ')
        {
            buf[i] = '\0';
            break;
        }
    }
    short second_half = cgc_strtol((char *)buf, NULL, 10);

    cgc_transmit_all(3, (void *) &first_half, sizeof(short));
    cgc_transmit_all(3, (void *) &second_half, sizeof(short));
    return 0;
}
