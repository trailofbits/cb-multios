#ifndef MSC_H_
#define MSC_H_

typedef struct {
    uint32_t magic;
    uint32_t tag;
    uint32_t data_length;
    uint8_t flags;
    uint8_t lun;
    uint8_t cb_length;
    uint8_t cb[0x10];
} __attribute__ ((__packed__)) cbw_t;

typedef struct {
    uint32_t magic;
    uint32_t tag;
    uint32_t residue;
    uint8_t status;
} __attribute__ ((__packed__)) csw_t;

typedef struct {
    cbw_t cbw;
    csw_t csw;
    int state;
#define MSC_ST_IDLE 0
#define MSC_ST_OUT 1
#define MSC_ST_IN 2
#define MSC_ST_STATUS 3
    int status;
    size_t count;
    uint8_t *memory;

    size_t out_length;
    const uint8_t *out_buffer;
    unsigned int out_flags;
#define MSC_F_DYNAMIC 0x01
    uint8_t out_static[4096];

    union {
        struct {
            uint32_t lba;
            uint32_t length;
        } write;
    } in_state;
} msc_t;

#include "usb.h"

int msc_init(msc_t *msc);
int msc_handle_ep0(usb_t *usb, urb_t *urb);
int msc_handle_urb(usb_t *usb, urb_t *urb);

#endif /* MSC_H_ */
