#ifndef SILK_H_
#define SILK_H_

#include <stdlib.h>
#include <stdint.h>

typedef struct {
    void *priv;
} silk_t;

typedef struct {
    uint32_t codes;
} __attribute__((packed)) silk_negotiate_t;

typedef struct {
    uint16_t plen;
    uint16_t glen;
    uint16_t qlen;
    uint16_t alen;
    uint8_t data[];
} __attribute__((packed)) silk_kx_param_t;

typedef struct {
    uint16_t blen;
    uint8_t data[];
} __attribute__((packed)) silk_kx_reply_t;

typedef struct {
    uint16_t datalen;
    uint8_t data[];
} __attribute__((packed)) silk_data_t;

enum {
    PKT_ERROR,
    PKT_NEGOTIATE,
    PKT_KX_PARAM,
    PKT_KX_REPLY,
    PKT_DATA
};

int silk_init(silk_t *silk);

// high-level API
int silk_prepare(silk_t *silk);
int silk_send(silk_t *silk, const unsigned char *data, unsigned int cnt);
int silk_recv(silk_t *silk, unsigned char *out, unsigned int cnt);

// low-level API
int silk_negotiate(silk_t *silk);
int silk_kx(silk_t *silk);

#endif
