/*
 * Author: Andrew Wesie <andrew.wesie@kapricasecurity.com>
 * 
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
#include <libcgc.h>

static int root64_decode_char(char input)
{
    if (input >= '0' && input <= '9')
        return input - '0';
    else if (input >= 'A' && input <= 'Z')
        return input - 'A' + 10;
    else if (input >= 'a' && input <= 'z')
        return input - 'a' + 36;
    else if (input == ':')
        return 62;
    else if (input == ';')
        return 63;
    else
        return -1;
}

size_t root64_decode(char *output, const char *input)
{
    size_t n = 0;
    int byte = 0;
    int bits_needed = 8;
    while (*input != 0)
    {
        int decoded = root64_decode_char(*input++);
        if (decoded == -1)
            break;
        int new_bits = 6;
        if (bits_needed <= new_bits)
        {
            byte |= decoded >> (new_bits - bits_needed);
            output[n++] = byte;
            new_bits -= bits_needed;
            decoded &= 0xFF >> (8 - new_bits);
            byte = 0;
            bits_needed = 8;
        }

        byte |= decoded << (bits_needed - new_bits);
        bits_needed -= new_bits;
    }
    return n;
}

size_t root64_encode(char *output, const char *input)
{
    const static char map[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz:;";

    size_t n = 0;
    int byte = 0;
    int leftover_bits = 0;
    while (*input != 0)
    {
        int ch = (unsigned char)*input++;
        byte |= (ch >> (2 + leftover_bits));
        output[n++] = map[byte];
        byte = (ch << (4 - leftover_bits)) & 0x3F;
        leftover_bits = 8 - (6 - leftover_bits);
        if (leftover_bits == 6)
        {
            output[n++] = map[byte];
            byte = 0;
            leftover_bits = 0;
        }
    }

    if (leftover_bits > 0)
        output[n++] = map[byte];
    while (n % 4)
        output[n++] = '=';

    return n;
}

