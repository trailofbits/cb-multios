#include "msc.h"

#ifndef USB_H_
#define USB_H_

#define VERSION_CODE 0x0111

typedef struct {
    uint8_t intf_class;
    uint8_t intf_subclass;
    uint8_t intf_proto;
    uint8_t padding;
} intf_t;

typedef struct {
    char path[256];
    char busid[32];
    uint32_t busnum;
    uint32_t devnum;
    uint32_t speed;
    uint16_t vendor;
    uint16_t product;
    uint16_t device;
    uint8_t dev_class;
    uint8_t dev_subclass;
    uint8_t dev_proto;
    uint8_t current_config;
    uint8_t num_configs;
    uint8_t num_intf;
    intf_t interfaces[0];
} devinfo_t;

/* metadata commands */
typedef struct {
    uint16_t version;
    uint16_t command;
#define DEVLIST_REQ 0x8008
#define DEVLIST_REP 0x0008
#define IMPORT_REQ 0x8009
#define IMPORT_REP 0x0009
    uint32_t status;
} metadata_hdr_t;

typedef struct {
    metadata_hdr_t hdr;
    uint32_t length;
    devinfo_t devices[0];
} devlist_rep_t;

typedef struct {
    char busid[32];
} import_req_t;

typedef struct {
    metadata_hdr_t hdr;
    devinfo_t device;
} import_rep_t;

/* data commands */
typedef struct {
    uint32_t command;
#define SUBMIT_REQ 0x00000001
#define SUBMIT_REP 0x00000003
#define UNLINK_REQ 0x00000002
#define UNLINK_REP 0x00000004
    uint32_t seqnum;
    uint32_t devid;
    uint32_t direction;
#define DIR_OUT 0
#define DIR_IN 1
    uint32_t endpoint;
} data_hdr_t;

typedef struct {
    uint32_t flags;
    uint32_t length;
    uint32_t start_frame;
    uint32_t number_of_packets;
    uint32_t interval;
    uint8_t setup[8];
} submit_req_t;

typedef struct {
    data_hdr_t hdr;
    uint32_t status;
    uint32_t length;
    uint32_t start_frame;
    uint32_t number_of_packets;
    uint32_t error_length;
    uint8_t setup[8];
} submit_rep_t;

typedef struct {
    uint32_t seqnum;
} unlink_req_t;

typedef struct {
    data_hdr_t hdr;
    uint32_t status;
} unlink_rep_t;

typedef struct {
    uint32_t devid;
    uint32_t seqnum;
    uint32_t direction;
    uint32_t endpoint;
    uint32_t flags;
    uint32_t length;
    uint32_t interval;
    uint8_t setup[8];
    uint8_t data[0] __attribute__((__aligned__(16)));
} urb_t;

typedef struct {
    size_t (*recv) (void *buf, size_t len);
    size_t (*send) (const void *buf, size_t len);

    int attached;
    msc_t msc;
} usb_t;

typedef struct {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t bcdUSB;
    uint8_t bDeviceClass;
    uint8_t bDeviceSubClass;
    uint8_t bDeviceProtocol;
    uint8_t bMaxPacketSize0;
    uint16_t idVendor;
    uint16_t idProduct;
    uint16_t bcdDevice;
    uint8_t iManufacturer;
    uint8_t iProduct;
    uint8_t iSerialNumber;
    uint8_t bNumConfigurations;
} __attribute__((__packed__)) device_desc_t;

typedef struct {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t wTotalLength;
    uint8_t bNumInterfaces;
    uint8_t bConfigurationValue;
    uint8_t iConfiguration;
    uint8_t bmAttributes;
    uint8_t bMaxPower;
} __attribute__((__packed__)) config_desc_t;

typedef struct {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bInterfaceNumber;
    uint8_t bAlternateSetting;
    uint8_t bNumEndpoints;
    uint8_t bInterfaceClass;
    uint8_t bInterfaceSubClass;
    uint8_t bInterfaceProtocol;
    uint8_t iInterface;
} __attribute__((__packed__)) intf_desc_t;

typedef struct {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bEndpointAddress;
    uint8_t bmAttributes;
    uint16_t wMaxPacketSize;
    uint8_t bInterval;
} __attribute__((__packed__)) ep_desc_t;

int usb_init(usb_t *self);
int usb_handle_packet(usb_t *self);
int usb_send_reply(usb_t *self, urb_t *urb, uint32_t status, uint32_t length);
#endif /* USB_H_ */
