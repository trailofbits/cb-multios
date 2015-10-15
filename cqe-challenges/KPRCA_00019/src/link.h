#ifndef LINK_H_
#define LINK_H_

#define LINK_PACKET_SIZE 341 // includes header
#define LINK_PAYLOAD_SIZE 339

#define LINK_CH_START 0b10
#define LINK_CH_CONTINUE 0b01

typedef struct __attribute__ ((__packed__)) {
    unsigned channel : 2;
    unsigned flow : 1;
    unsigned length : 9;
    unsigned sbz : 4;
    unsigned char payload[];
} link_hdr_t;

void link_send(unsigned channel, unsigned length, const unsigned char *payload);
// sizeof payload buffer should be >= LINK_PACKET_SIZE
int link_recv(unsigned *channel, unsigned *length, unsigned char *payload);

#endif
