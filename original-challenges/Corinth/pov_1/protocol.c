#include <libcgc.h>

#include "protocol.h"

void tx(char* bytes, size_t count);
void rx(char* byte_buf, size_t count);

void protocol_send(protocol_frame* frame) {
  size_t frame_size = sizeof(frame->id) + sizeof(frame->length);

  tx((char*)&(frame->id), sizeof(frame->id));
  tx((char*)&(frame->length), sizeof(frame->length));

  /* tx((char*)(void*)frame, frame_size); */

  if (frame->length == 0) return;

  tx((char*)frame->value, frame->length);
}

void protocol_with_recv_frame(uint8 (^block)(protocol_frame* frame)) {
  protocol_frame frame;
  char header_buf[sizeof(frame.id) + sizeof(frame.length)];
  char* header_buf_ptr = (char*)&header_buf;

  rx(header_buf_ptr, sizeof(frame.id) + sizeof(frame.length));
  frame.id = *(uint8*)(&header_buf[0]);
  frame.length = *(uint16*)(&header_buf[1]);

  char buf[frame.length];

  rx((char*)&buf, frame.length);

  frame.value = (void*)&buf;

  block(&frame);
}

void tx(char* bytes, size_t count) {
  size_t total_sent = 0;

  while(total_sent < count) {
    size_t sent_this_time = 0;

    int status = transmit(STDOUT,
                          bytes + total_sent,
                          count - total_sent,
                          &sent_this_time);

    if (status != 0) _terminate(-1);
    if (sent_this_time == 0) _terminate(-1);

    total_sent += sent_this_time;
  }
}

void rx(char* byte_buf, size_t count) {
  size_t total_rcvd = 0;

  while(total_rcvd < count) {
    size_t rcvd_this_time = 0;

    int status = receive(STDIN,
                         byte_buf + total_rcvd,
                         count - total_rcvd,
                         &rcvd_this_time);

    if (status != 0) _terminate(-1);
    if (rcvd_this_time == 0) _terminate(-1);

    total_rcvd += rcvd_this_time;
  }
}
