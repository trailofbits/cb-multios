#include "libcgc.h"
/* #include "cgc_string.h" */
#include "libpov.h"

#include "cgc_protocol.h"

void cgc_tx(char* bytes, cgc_size_t count);
void cgc_rx(char* byte_buf, cgc_size_t count);

void cgc_fail() {
  unsigned char x[4];
  const unsigned char* x_addr = (unsigned char*) &x;
  cgc_type2_submit(x_addr, 4);
  cgc__terminate(-1);
}

void cgc_protocol_send_str(char* str) {
  uint16 len = cgc_strlen(str);
  
  cgc_tx((char*)&(len), sizeof(len));
  cgc_tx(str, len);
}

void cgc_protocol_consume_str() {
  char  len_buf[sizeof(uint16)];
  char* len_buf_ptr = (char*)&len_buf;

  cgc_rx(len_buf_ptr, sizeof(uint16));

  uint16 len = *((uint16*) len_buf_ptr);
  
  char  str_buf[len];
  char* str_buf_ptr = (char*)&str_buf;

  cgc_rx(str_buf_ptr, len);
}

void cgc_protocol_with_recv_string(void (^block)(uint16 len, char* str)) {
  char  len_buf[sizeof(uint16)];
  char* len_buf_ptr = (char*)&len_buf;

  cgc_rx(len_buf_ptr, sizeof(uint16));

  uint16 len = *((uint16*) len_buf_ptr);
  
  char  str_buf[len];
  char* str_buf_ptr = (char*)&str_buf;

  cgc_rx(str_buf_ptr, len);

  block(len, str_buf_ptr);
}

void cgc_tx(char* bytes, cgc_size_t count) {
  cgc_size_t total_sent = 0;

  while(total_sent < count) {
    cgc_size_t sent_this_time = 0;

    int status = cgc_transmit(STDOUT,
                          bytes + total_sent,
                          count - total_sent,
                          &sent_this_time);

    if (status != 0) cgc_fail();
    if (sent_this_time == 0) cgc_fail();

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

    if (status != 0) cgc_fail();
    if (rcvd_this_time == 0) cgc_fail();

    total_rcvd += rcvd_this_time;
  }
}
