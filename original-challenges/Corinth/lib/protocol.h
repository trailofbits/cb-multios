#pragma once

#include "types.h"

typedef struct {
  uint8 id;
  uint16 length;
  void* value;
} protocol_frame;

void protocol_send(protocol_frame* frame);
void protocol_with_recv_frame(uint8 (^block)(protocol_frame* frame));
