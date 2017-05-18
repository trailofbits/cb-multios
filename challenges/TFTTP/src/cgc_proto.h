#ifndef PROTO_H
#define PROTO_H
#include "cgc_stdint.h" 
#include "libcgc.h"
#include "cgc_libc.h"
#define ERRQUIT "Mkay"
#define SENDM(b,s) if(sendmsg(STDOUT,b,s)<0) cgc__terminate(23);
#define RECVM(b,s,ss) if(cgc_recvmsg(STDIN,b,s,ss)<0){\
     cgc_create_resp_pkt(curpkt,ERRQUIT);\
     SENDD(curpkt,curpkt->hdr.size);\
    cgc__terminate(24);}
#define RECVD() if(cgc_recvdgram(STDIN)<0){\
     cgc_create_resp_pkt(curpkt,ERRQUIT);\
     SENDD(curpkt,curpkt->hdr.size);\
    cgc__terminate(25);}
#define SENDD(m,s) if(cgc_senddgram(STDOUT,m,s)<0) cgc__terminate(26);
#define MAX_FRAG 256
#define MAX_DATA_LEN 256+128
#define MAX_FRAG_DATA_LEN (MAX_DATA_LEN-8)
#define MAX_PKT_SIZE MAX_FRAG_DATA_LEN*MAX_FRAG
#define TFTTP_STRUCT_SIZE sizeof(tfttp_hdr)+MAX_PKT_SIZE
#define MAX_RETRANS 5

enum pkttype {
    PUT,
    GET,
    RAND,
    RESP,
    FRAG,
    UNKNOWN
};

typedef struct tfttp_hdr {
    cgc_size_t size; //size of trailing data
    enum pkttype code;
} tfttp_hdr;

typedef struct tfttp_pkt {
    tfttp_hdr hdr;
    uint8_t data[0];
} tfttp_pkt;

typedef struct tfttp_frag {
    uint8_t seqid;
    uint8_t numfrag;
    uint16_t unused;
    enum pkttype code;
    uint8_t data[MAX_FRAG_DATA_LEN]; //6 less for the header
} tfttp_frag;

tfttp_pkt *curpkt;

int sendmsg(int fd, uint8_t *data, cgc_size_t size); 
int cgc_recvmsg(int fd, uint8_t *data, cgc_size_t maxsize, cgc_size_t minsize);
int cgc_recvdgram(int fd);
int cgc_senddgram(int fd, tfttp_pkt *msg, cgc_size_t size);
void cgc_create_resp_pkt(tfttp_pkt* pkt, char *resp);
#endif
