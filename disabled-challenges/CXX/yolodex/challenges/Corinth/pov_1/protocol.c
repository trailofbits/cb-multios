#include "libcgc.h"

#include "cgc_protocol.h"

void cgc_tx(char* bytes, cgc_size_t count);
void cgc_rx(char* byte_buf, cgc_size_t count);

void cgc_protocol_send(protocol_frame* frame) {
  cgc_size_t frame_size = sizeof(frame->id) + sizeof(frame->length);

  cgc_tx((char*)&(frame->id), sizeof(frame->id));
  cgc_tx((char*)&(frame->length), sizeof(frame->length));

  /* tx((char*)(void*)frame, frame_size); */

  if (frame->length == 0) return;

  cgc_tx((char*)frame->value, frame->length);
}

void cgc_protocol_with_recv_frame(uint8 (^block)(protocol_frame* frame)) {
  protocol_frame frame;
  char header_buf[sizeof(frame.id) + sizeof(frame.length)];
  char* header_buf_ptr = (char*)&header_buf;

  cgc_rx(header_buf_ptr, sizeof(frame.id) + sizeof(frame.length));
  frame.id = *(uint8*)(&header_buf[0]);
  frame.length = *(uint16*)(&header_buf[1]);

  char buf[frame.length];

  cgc_rx((char*)&buf, frame.length);

  frame.value = (void*)&buf;

  block(&frame);
}

void cgc_tx(char* bytes, cgc_size_t count) {
  cgc_size_t total_sent = 0;

  while(total_sent < count) {
    cgc_size_t sent_this_time = 0;

    int status = cgc_transmit(STDOUT,
                          bytes + total_sent,
                          count - total_sent,
                          &sent_this_time);

    if (status != 0) cgc__terminate(-1);
    if (sent_this_time == 0) cgc__terminate(-1);

    total_sent += sent_this_time;
  }
}

void cgc_rx(char* byte_buf, cgc_size_t count) {
  cgc_size_t total_rcvd = 0;

  while(total_rcvd < count) {
    cgc_size_t rcvd_this_time = 0;

    int status = cgc_receive(STDIN,
                         byte_buf + total_rcvd,
                         count - total_rcvd,
                         &rcvd_this_time);

    if (status != 0) cgc__terminate(-1);
    if (rcvd_this_time == 0) cgc__terminate(-1);

    total_rcvd += rcvd_this_time;
  }
}
