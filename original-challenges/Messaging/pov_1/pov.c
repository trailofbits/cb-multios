#include <libpov.h>

// \x00\xffHDR\x05\x00\x00\x00\x01\x00ALBM\x00\x00\x00\x38\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bAAAAAAAAAAAA\x20\xc0\x47\x43CCCCAAAAAAAAAAAATITL\x00\x00\x00\x38\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\bAAAAAAAAAAAA\x30\xc0\x47\x43CCCCAAAAAAAAAAAA\x7f

int main()
{
    type2_vals t2;
    unsigned char buf[200];
    int i;
    size_t bytes;

    memcpy(buf, "\x00\xff""HDR\x05\x00\x00\x00\x01\x00"
                "ALBM\x00\x00\x00\x38\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b""AAAAAAAAAAAA\x20\xc0\x47\x43""CCCCAAAAAAAAAAAA"
                "TITL\x00\x00\x00\x38\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b""AAAAAAAAAAAA\x30\xc0\x47\x43""CCCCAAAAAAAAAAAA\x7f", 140);

    random(buf + 11 + 8 + 24, 12, &bytes);
    random(buf + 11 + 8 + 24 + 16, 16, &bytes);
    random(buf + 11 + 0x40 + 8 + 24, 12, &bytes);
    random(buf + 11 + 0x40 + 8 + 24 + 16, 16, &bytes);

    for (i = 0; i < 139; i++)
    {
        // make sure we didn't introduce any bad chars
        if (i >= 11 + 0x20 && i < 11 + 0x40 && buf[i] < 0x10) buf[i] ^= 0x55;
        if (i >= 11 + 0x60 && i < 11 + 0x80 && buf[i] < 0x10) buf[i] ^= 0x55;
        if (buf[i] == 0x7f) buf[i] = 0x3f;
        if (buf[i] == 0x7e) buf[i] = 0x3e;
    }

    type2_negotiate(&t2);
    transmit_all(STDOUT, buf, 140);
    length_read(STDIN, buf, 0x58);
    length_read(STDIN, buf, 16);
    // buf contains: "Album: ?????????"
    // as long as buf does not contain "Arti", we have won
    for (i = 7; i < 16; i++)
        if (memcmp(&buf[i], "Arti", 4) == 0)
            break;
    if (i == 16)
    {
        type2_submit(buf + 7, 4);
        return 0;
    }

    // we found "Arti", so look some more
    length_read(STDIN, buf, 8);
    type2_submit(buf + 4, 4);
    return 0;
}
