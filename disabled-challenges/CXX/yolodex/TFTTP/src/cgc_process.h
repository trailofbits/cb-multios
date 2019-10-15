#ifndef PROCESS_H
#define PROCESS_H
#include "cgc_proto.h"

#define MAXQS 2048

typedef struct qs {
    char key[128];
    char data[256];
} qs;

int load_data();
int cgc_process_next_dgram();
tfttp_pkt* cgc_do_put();
tfttp_pkt* cgc_do_get();
tfttp_pkt* cgc_do_rand();
#endif
