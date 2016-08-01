#ifndef SESSION_H_
#define SESSION_H_

#define SESSION_MAX_PACKET_SIZE (0xFFFF + 4)

#define COMMAND_REJECT 0x01
#define CONNECTION_REQUEST 0x02
#define CONNECTION_RESPONSE 0x03
#define CONFIGURATION_REQUEST 0x04
#define CONFIGURATION_RESPONSE 0x05
#define DISCONNECTION_REQUEST 0x06
#define DISCONNECTION_RESPONSE 0x07
#define ECHO_REQUEST 0x08
#define ECHO_RESPONSE 0x09
#define INFORMATION_REQUEST 0xA
#define INFORMATION_RESPONSE 0xB

typedef struct __attribute__ ((__packed__)) {
    unsigned length : 16;
    unsigned channel : 16;
    unsigned char payload[];
} session_hdr_t;

typedef struct __attribute__ ((__packed__)) {
    unsigned code : 8;
    unsigned id : 8;
    unsigned length : 16;
} control_hdr_t;

typedef struct {
    control_hdr_t hdr;
    unsigned char payload[];
} command_t;

typedef union {
    int type;
#define RX_EVENT 0
#define DISCONNECT_EVENT 1
    struct {
        int type;
        unsigned char *data;
        unsigned int length;
    } rx;
} event_t;

typedef void (*connect_handler_t) (void *channel);
typedef void (*event_handler_t) (void *channel, void *userdata, event_t *event);

void session_loop();
void session_register_psm(unsigned int psm, connect_handler_t handler);
void session_register_events(void *channel, event_handler_t handler);
void session_register_userdata(void *channel, void *userdata);
void session_send(void *channel, unsigned int length, unsigned char *data);

#endif
