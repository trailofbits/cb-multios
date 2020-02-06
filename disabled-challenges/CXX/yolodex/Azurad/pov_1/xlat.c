#include "cgc_xlat.h"

#undef delimited_read
#undef length_read
#undef transmit_all

static unsigned int xlat_init = 0;
static unsigned char xlat_map[256];
static unsigned char xlat_map_inv[256];

int cgc_xlat_delimited_read(int fd, unsigned char **buf, unsigned int *size, unsigned char *delim, unsigned int delim_len)
{
    unsigned char tmp[delim_len];
    unsigned int i;
    int retval;

    if (xlat_init)
    {
        for (i = 0; i < delim_len; i++)
            tmp[i] = xlat_map[delim[i]];
        retval = cgc_delimited_read(fd, buf, size, tmp, delim_len);
        for (i = 0; i < *size; i++)
            (*buf)[i] = xlat_map_inv[(*buf)[i]];
        return retval;
    }
    else
    {
        return cgc_delimited_read(fd, buf, size, delim, delim_len);
    }
}

int cgc_xlat_length_read(int fd, unsigned char *buf, unsigned int len)
{
    unsigned int i;
    int retval;

    if (xlat_init)
    {
        retval = cgc_length_read(fd, buf, len);
        for (i = 0; i < len; i++)
            buf[i] = xlat_map_inv[buf[i]];
        return retval;
    }
    else
    {
        return cgc_length_read(fd, buf, len);
    }
}

int cgc_xlat_transmit_all(int fd, const void *buf, const cgc_size_t size)
{
    const unsigned char *ucbuf = buf;
    unsigned char tmp[1024];
    unsigned int i;
    int retval;

    for (i = 0; i < size; )
    {
        unsigned int cnt = size - i;
        if (cnt > sizeof(tmp)) cnt = sizeof(tmp);
        cgc_memcpy(tmp, ucbuf + i, cnt);
        for (i = 0; i < cnt; i++)
            tmp[i] = xlat_map[tmp[i]];
        retval = cgc_transmit_all(fd, tmp, cnt);
        i += cnt;
    }

    return retval;
}

static unsigned int cgc_hash_seed(const char *seed)
{
    unsigned int i;
    unsigned int H = 0x314abc86;

    for (i = 0; seed[i] != 0; i++)
    {
        H *= 37;
        H ^= seed[i];
        H = (H << 13) ^ (H >> 19);
    }

    return H;
}

void cgc_xlat_seed(const char *seed)
{
    unsigned int state, i;
    unsigned char *map, *map_inv;

    if (seed == NULL)
    {
        xlat_init = 0;
        return;
    }

    xlat_init = 1;
    map = xlat_map;
    map_inv = xlat_map_inv;
    state = cgc_hash_seed(seed);

    /* initialize map with identity */
    for (i = 0; i < 256; i++)
        map[i] = i;

    /* shuffle using Fisher-Yates */
    for (i = 255; i >= 1; i--)
    {
        unsigned int j = state % i, tmp;

        /* iterate state */
        state *= 3;
        state = (state << 13) ^ (state >> 19) ^ (state >> 21);

        /* exchange elements */
        tmp = map[i];
        map[i] = map[j];
        map[j] = tmp;
    }

    /* initialize inverse mapping */
    for (i = 0; i < 256; i++)
    {
        map_inv[map[i]] = i;
    }
}
