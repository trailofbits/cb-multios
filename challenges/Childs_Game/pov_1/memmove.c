#include "libpov.h"

void *cgc_memmove(void *dst, const void *src, cgc_size_t n)
{
    unsigned char *udst = dst;
    const unsigned char *usrc = src;
    cgc_size_t i;

    if (dst > src)
    {
        for (i = 0; i < n; i++)
            udst[n - i - 1] = usrc[n - i - 1];
    }
    else
    {
        for (i = 0; i < n; i++)
            udst[i] = usrc[i];
    }

    return dst;
}
