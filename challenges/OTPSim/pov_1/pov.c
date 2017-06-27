#include "libpov.h"

int main(int cgc_argc, char *cgc_argv[]) {
    cgc_negotiate_type2();

    int i;
    unsigned char out[8192];
    unsigned int challenge[2];
    unsigned char *c = (unsigned char *) &challenge;

    cgc_transmit_all(STDOUT, "SHAK", 4);
    cgc_length_read(STDIN, (unsigned char *)challenge, sizeof(challenge));
    for (i = 0; i < sizeof(challenge); ++i, ++c)
        *c = ((*c & 0x0F) << 4 | (*c & 0xF0) >> 4);
    cgc_transmit_all(STDOUT, (char *)challenge, sizeof(challenge));
    cgc_transmit_all(STDOUT, "haha", 4);
    cgc_length_read(STDIN, out, 5);

    cgc_transmit_all(STDOUT, "GENO", 4);
    cgc_transmit_all(STDOUT, "\x04\x00\x00\x00", 4);
    cgc_length_read(STDIN, out, 9);

    cgc_transmit_all(STDOUT, "XTND", 4);
    cgc_transmit_all(STDOUT, "\x40\x1F", 2);
    cgc_transmit_all(STDOUT, "\xAA\x00", 2);
    cgc_length_read(STDIN, out, 1);
    if (out[0] == 0)
        cgc_length_read(STDIN, out + 1, 0x1003);
    else
        cgc_transmit_all(STDOUT, "QUIT", 4);

    cgc_assign_from_slice("TYPE2_VALUE", out + 0xFFF, 4, 0, 0, 1);
    cgc_submit_type2("TYPE2_VALUE");

    return 0;
}
