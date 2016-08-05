#pragma once

#include "types.h"


void protocol_send_str(char* str);
void protocol_with_recv_string(void (^block)(uint16 len, char* str));
void protocol_consume_str();
