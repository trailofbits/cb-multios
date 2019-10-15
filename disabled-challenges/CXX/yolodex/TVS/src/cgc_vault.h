#ifndef VAULT_H_
#define VAULT_H_

#include "cgc_stdint.h"

void cgc_init_vault();
uint32_t cgc_store_in_vault(uint32_t id, void *data, unsigned int n);
void* cgc_retrieve_from_vault(uint32_t id, unsigned int *outlen);
int cgc_handle_msg_vault(void *data, unsigned int n);

#endif
