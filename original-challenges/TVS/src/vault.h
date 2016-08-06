#ifndef VAULT_H_
#define VAULT_H_

#include <stdint.h>

void init_vault();
uint32_t store_in_vault(uint32_t id, void *data, unsigned int n);
void* retrieve_from_vault(uint32_t id, unsigned int *outlen);
int handle_msg_vault(void *data, unsigned int n);

#endif
