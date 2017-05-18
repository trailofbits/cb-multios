#include "libcgc.h"
#include "cgc_libc.h"

int cgc_transmit_all(int fd, const char *buf, const cgc_size_t size) {
    cgc_size_t sent = 0;
    cgc_size_t sent_now = 0;
    int ret;

    if (!buf) 
        return 1;

    if (!size)
        return 2;

    while (sent < size) {
        ret = cgc_transmit(fd, buf + sent, size - sent, &sent_now);
        if (sent_now == 0) {
            //should never return until at least something was transmitted
            //so consider this an error too
            return 3;
        }
        if (ret != 0) {
            return 3;
        }
        sent += sent_now;
    }

    return 0;
}

int cgc_receive_delim(int fd, char *buf, const cgc_size_t size, char delim) {
    cgc_size_t rx = 0;
    cgc_size_t rx_now = 0;
    int ret;

    if (!buf) 
        return 1;

    if (!size)
        return 2;

    while (rx < size) {
        ret = cgc_receive(fd, buf + rx, 1, &rx_now);
        if (rx_now == 0) {
            //should never return until at least something was received
            //so consider this an error too
            return 3;
        }
        if (ret != 0) {
            return 3;
        }
        if (buf[rx] == delim) {
           break;
        }
        rx += rx_now;
    }

    return 0;
}
