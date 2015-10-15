/*
 * Author: Brian Pak <brian.pak@kapricasecurity.com>
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
#define IS_SPACE(c) ((c == ' ') || (c == '\t') || (c == '\f') || (c == '\n') || (c == '\v'))
#define IS_NUM(c) ((c >= '0') && (c <= '9'))
#define IS_ALPHA(c) (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')))
#define IS_UPPER(c) ((c >= 'A') && (c <= 'Z'))

long int strtol(const char *nptr, char **endptr, int base)
{
    int limit;
    int neg = 0, val = 0, consumed = 0, n, a;
    const char *p = nptr;

    /* Check validity of base */
    if (base == 1 || base > 36 || base < 0)
        goto done;

    /* Skip white space */
    while (1)
    {
        if (IS_SPACE(*p))
            ++p;
        else
            break;
    }

    /* Check sign symbol */
    if (*p == '-')
    {
        neg = 1;
        ++p;
    }
    if (*p == '+')
        ++p;

    /* Handle the base & its syntax */
    switch (base)
    {
        case 0:
            if (*p == '0')
            {
                if (p[1] == 'x' || p[1] == 'X')
                {
                    p += 2;
                    base = 16;
                }
                else
                {
                    ++p;
                    base = 8;
                }
            }
            else
                base = 10;
            break;
        case 16:
            if (*p == '0' && (p[1] == 'x' || p[1] == 'X'))
            {
                p += 2;
                base = 16;
            }
            break;
    }

    /* Convert the rest of the string into int */
    while ((n = IS_NUM(*p)) || (a = IS_ALPHA(*p)))
    {
        if (n)
            n = *p - '0';
        else if (a)
        {
            if (IS_UPPER(*p))
                n = *p - 'A';
            else
                n = *p - 'a';
            // "... In bases above 10, the letter 'A' in either upper  or  lower case represents 10,
            //      'B' represents 11, and so forth, with 'Z' representing 35. ..."
            n += 10;
        }

        // "... stopping at the first character which is not a valid digit in the given base. ..."
        if (n >= base)
            break;

        val *= base;
        val += n;
        ++consumed;
        ++p;
    }

    if (neg)
        val = -val;

done:
    if (endptr)
        *endptr = (char *)(consumed > 0 ? p : nptr);

    return val;

}

long unsigned int strtoul(const char *nptr, char **endptr, int base)
{
    return (long unsigned int)strtol(nptr, endptr, base);
}
