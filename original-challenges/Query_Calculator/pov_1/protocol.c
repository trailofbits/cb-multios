#include <libcgc.h>
/* #include <string.h> */
#include <libpov.h>

#include "protocol.h"

void tx(char* bytes, size_t count);
void rx(char* byte_buf, size_t count);

void fail() {
  unsigned char x[4];
  const unsigned char* x_addr = (unsigned char*) &x;
  type2_submit(x_addr, 4);
  _terminate(-1);
}

void protocol_send_str(char* str) {
  uint16 len = strlen(str);
  
  tx((char*)&(len), sizeof(len));
  tx(str, len);
}

void protocol_consume_str() {
  char  len_buf[sizeof(uint16)];
  char* len_buf_ptr = (char*)&len_buf;

  rx(len_buf_ptr, sizeof(uint16));

  uint16 len = *((uint16*) len_buf_ptr);
  
  char  str_buf[len];
  char* str_buf_ptr = (char*)&str_buf;

  rx(str_buf_ptr, len);
}

void protocol_with_recv_string(void (^block)(uint16 len, char* str)) {
  char  len_buf[sizeof(uint16)];
  char* len_buf_ptr = (char*)&len_buf;

  rx(len_buf_ptr, sizeof(uint16));

  uint16 len = *((uint16*) len_buf_ptr);
  
  char  str_buf[len];
  char* str_buf_ptr = (char*)&str_buf;

  rx(str_buf_ptr, len);

  block(len, str_buf_ptr);
}

void tx(char* bytes, size_t count) {
  size_t total_sent = 0;

  while(total_sent < count) {
    size_t sent_this_time = 0;

    int status = transmit(STDOUT,
                          bytes + total_sent,
                          count - total_sent,
                          &sent_this_time);

    if (status != 0) fail();
    if (sent_this_time == 0) fail();

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

    if (status != 0) fail();
    if (rcvd_this_time == 0) fail();

    total_rcvd += rcvd_this_time;
  }
}
