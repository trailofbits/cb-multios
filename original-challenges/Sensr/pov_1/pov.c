#include <libpov.h>
int main(void) {
    unsigned char pkt[17];
    unsigned char pkt2[17];
    size_t n;

    negotiate_type2();

    memcpy(pkt, "\x02\x00\x00\x00\x00", 5);
    random(pkt + 5, 12, &n);
    transmit_all(STDOUT, pkt, 17);
    length_read(STDIN, pkt, 17);

    memcpy(pkt2, "\x02\xff\xff\xff\xff", 5);
    random(pkt2 + 5, 12, &n);
    transmit_all(STDOUT, pkt2, 17);
    length_read(STDIN, pkt2, 17);

    pkt[0] = 2;
    *(unsigned int *)(&pkt[1]) = *(unsigned int *)(&pkt[9]) + 1;
    transmit_all(STDOUT, pkt, 17);

    length_read(STDIN, pkt, 17);

    *(unsigned int *)(&pkt[9]) ^= 0x5bb1a6e2;
    assign_from_slice("TYPE2_VALUE", pkt + 9, 4, 0, 0, 1);

    submit_type2("TYPE2_VALUE");

    return 0;
}
