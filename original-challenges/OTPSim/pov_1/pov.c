#include <libpov.h>

int main(void) {
    negotiate_type2();

    int i;
    unsigned char out[8192];
    unsigned int challenge[2];
    unsigned char *c = (unsigned char *) &challenge;

    transmit_all(STDOUT, "SHAK", 4);
    length_read(STDIN, (unsigned char *)challenge, sizeof(challenge));
    for (i = 0; i < sizeof(challenge); ++i, ++c)
        *c = ((*c & 0x0F) << 4 | (*c & 0xF0) >> 4);
    transmit_all(STDOUT, (char *)challenge, sizeof(challenge));
    transmit_all(STDOUT, "haha", 4);
    length_read(STDIN, out, 5);

    transmit_all(STDOUT, "GENO", 4);
    transmit_all(STDOUT, "\x04\x00\x00\x00", 4);
    length_read(STDIN, out, 9);

    transmit_all(STDOUT, "XTND", 4);
    transmit_all(STDOUT, "\x40\x1F", 2);
    transmit_all(STDOUT, "\xAA\x00", 2);
    length_read(STDIN, out, 1);
    if (out[0] == 0)
        length_read(STDIN, out + 1, 0x1003);
    else
        transmit_all(STDOUT, "QUIT", 4);

    assign_from_slice("TYPE2_VALUE", out + 0xFFF, 4, 0, 0, 1);
    submit_type2("TYPE2_VALUE");

    return 0;
}
