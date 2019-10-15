#include "libpov.h"
int main(int cgc_argc, char *cgc_argv[]) {
    unsigned char pkt[17];
    unsigned char pkt2[17];
    cgc_size_t n;

    cgc_negotiate_type2();

    cgc_memcpy(pkt, "\x02\x00\x00\x00\x00", 5);
    cgc_random(pkt + 5, 12, &n);
    cgc_transmit_all(STDOUT, pkt, 17);
    cgc_length_read(STDIN, pkt, 17);

    cgc_memcpy(pkt2, "\x02\xff\xff\xff\xff", 5);
    cgc_random(pkt2 + 5, 12, &n);
    cgc_transmit_all(STDOUT, pkt2, 17);
    cgc_length_read(STDIN, pkt2, 17);

    pkt[0] = 2;
    *(unsigned int *)(&pkt[1]) = *(unsigned int *)(&pkt[9]) + 1;
    cgc_transmit_all(STDOUT, pkt, 17);

    cgc_length_read(STDIN, pkt, 17);

    *(unsigned int *)(&pkt[9]) ^= 0x5bb1a6e2;
    cgc_assign_from_slice("TYPE2_VALUE", pkt + 9, 4, 0, 0, 1);

    cgc_submit_type2("TYPE2_VALUE");

    return 0;
}
