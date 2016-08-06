#ifndef PROCESS_H
#define PROCESS_H
#include "proto.h"

#define MAXQS 2048

typedef struct qs {
    char key[128];
    char data[256];
} qs;

int load_data();
int process_next_dgram();
tfttp_pkt* do_put();
tfttp_pkt* do_get();
tfttp_pkt* do_rand();
#endif
