#include "cgc_string.h"

char *cgc_strncpy(char *dest, const char *src, cgc_size_t n)
{
    cgc_size_t i;
    for (i = 0; i < n; i++)
    {
        dest[i] = src[i];
        if (dest[i] == '\0')
            break;
    }

    for (; i < n; i++)
        dest[i] = 0;

    return dest;
}
