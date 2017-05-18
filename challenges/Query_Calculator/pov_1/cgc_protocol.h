#pragma once

#include "cgc_types.h"


void cgc_protocol_send_str(char* str);
void cgc_protocol_with_recv_string(void (^block)(uint16 len, char* str));
void cgc_protocol_consume_str();
