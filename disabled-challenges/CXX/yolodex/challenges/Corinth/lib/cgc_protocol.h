#pragma once

#include "cgc_types.h"

typedef struct {
  uint8 id;
  uint16 length;
  void* value;
} protocol_frame;

void cgc_protocol_send(protocol_frame* frame);
void cgc_protocol_with_recv_frame(uint8 (^block)(protocol_frame* frame));
