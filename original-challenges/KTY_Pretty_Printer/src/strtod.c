#include <libcgc.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

double strtod(const char *str, char **endptr)
{
    const char *orig = str;
    char c;
    int n, neg = 0, point = 0;
    double val = 0, under = 1;

    while (*str && isspace(*str))
        str++;

    if (*str == '-')
    {
        neg = 1;
        str++;
    }
    else if (*str == '+')
    {
        str++;
    }

    /* TODO: maybe handle hexdecimal format */

    const char *begin = str;

    while ((c = *str))
    {
        if (c == '.')
        {
            point = 1;
            str++;
        }
        else if (c >= '0' && c <= '9')
        {
            n = c - '0';
            if (point)
            {
                under /= 10.0;
                val = val + (under * (double) n);
            }
            else
            {
                val = val * 10.0 + (double) n;
            }
            str++;
        }
        else
            break;
    }

    /* HACK */
    val += 0.00001;

    if (begin == str)
    {
        str = orig;
        val = 0;
    }

    if (endptr)
        *endptr = (char *)str;
    if (neg)
        return -val;
    else
        return val;
}
