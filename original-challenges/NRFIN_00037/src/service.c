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

#include "service.h"

// Decode instruction.  
// Do not access beyond bytecode+len.  
//      Assumes at least 1 byte is available.
// If an instruction is INVALID, return non-SUCCESS.  
//      INVALID inst contents are undefined.
// IN: pointer to bytes, len (number of bytes left to safely consume)
// OUT: populated inst struct
// RET: status
int inst_decode(uint8_t *bytes, uint16_t len, inst_t *inst) {

    int ret = SUCCESS;
    uint32_t cursor = 0;
    inst->opcode = bytes[cursor];
    
    // Determine how long the instruction is.
    // For each offset, add 2B, for each immediate, add 4B.
    uint8_t inst_len = 1;
    if (inst->opcode & INST_MASK_OP1) { inst_len += INST_OFF_SZ; } else { inst_len += INST_IMM_SZ; }
    if (inst->opcode & INST_MASK_OP2) { inst_len += INST_OFF_SZ; } else { inst_len += INST_IMM_SZ; }

    // If we would read off the end of the bytecode, bail.
    if (inst_len > len) {
#ifdef DEBUG
        fprintf(stderr, 
            "[D] decode() | insufficient bytes provided; "
            "required: 0x%02x (%d), available: 0x%02x (%d)\n", 
            inst_len, inst_len, len, len);
#endif
        ret = ERRNO_INSUFFICIENT_BYTES;
        goto bail;
    }

    // We have sufficient space; decode the instruction.
    inst->len = inst_len;
    if (inst->opcode & INST_MASK_OP1) { 
        inst->op1 = bytes[cursor+1] << 24 |
                    bytes[cursor+2] << 16 |
                    bytes[cursor+3] << 8|
                    bytes[cursor+4] << 0;  
#ifdef DEBUG
        fprintf(stderr, 
            "[D] decode() | op1 (off) | bytes[cursor+1:cursor+4] = 0x%02x 0x%02x 0x%02x 0x%02x\n", 
            bytes[cursor+1], bytes[cursor+2], bytes[cursor+3], bytes[cursor+4]);
#endif  
        cursor += 4;  
    } else { 
        inst->op1 = bytes[cursor+1] << 8 |
                    bytes[cursor+2] << 0;
#ifdef DEBUG
        fprintf(stderr, 
            "[D] decode() | op1 (imm) | bytes[cursor+1:cursor+2] = 0x%02x 0x%02x\n", 
            bytes[cursor+1], bytes[cursor+2]);
#endif
        cursor += 2;
    }

    if (inst->opcode & INST_MASK_OP2) { 
        inst->op2 = bytes[cursor+1] << 24 |
                    bytes[cursor+2] << 16 |
                    bytes[cursor+3] << 8|
                    bytes[cursor+4] << 0;
#ifdef DEBUG
        fprintf(stderr, 
            "[D] decode() | op2 (off) | bytes[cursor+1:cursor+4] = 0x%02x 0x%02x 0x%02x 0x%02x\n", 
            bytes[cursor+1], bytes[cursor+2], bytes[cursor+3], bytes[cursor+4]);
#endif
    } else { 
        inst->op2 = bytes[cursor+1] << 8 |
                    bytes[cursor+2] << 0;
#ifdef DEBUG
        fprintf(stderr, 
            "[D] decode() | op2 (imm) | bytes[cursor+1:cursor+2] = 0x%02x 0x%02x\n", 
            bytes[cursor+1], bytes[cursor+2]);
#endif
    }

#ifdef DEBUG
    fprintf(stderr, 
        "[D] decode() | successfully decoded instruction:\n"
        "    inst->len = %d\n"
        "    inst->opcode = 0x%02x\n"
        "    inst->op1 = 0x%08x\n"
        "    inst->op2 = 0x%08x\n",
        inst->len, inst->opcode, inst->op1, inst->op2);
#endif

bail:
    return ret;
}


int bytecode_vrfy(uint8_t *bytes, uint16_t len) {

    int ret = SUCCESS;

#ifdef DEBUG
    fprintf(stderr, "[D] bytecode_vrfy() | init\n");
    uint32_t inst_count = 0;
#endif

    uint8_t *cursor = bytes;
    inst_t inst;
    uint8_t *dst = NULL;

    // Loop over the opcodes, verify offset within each one.
    while (len) {

#ifdef DEBUG
        fprintf(stderr, 
            "\n[D] bytecode_vrfy() | instruction #%d\n", inst_count);
#endif

        if (SUCCESS != (ret = inst_decode(cursor, len, &inst))) {
#ifdef DEBUG
            fprintf(stderr, 
                "[D] bytecode_vrfy() | non-SUCCESS from inst_decode' bailing...\n");
#endif
            ret = ERRNO_INST_DECODE;
            goto bail;
        }

        // Verify offsets fall within allowed bounds.
#ifdef PATCHED
        if (inst.opcode & INST_MASK_OP1 && (SCRATCH_SZ - sizeof(uint32_t) < inst.op1)) {
#else
        if (inst.opcode & INST_MASK_OP1 && (SCRATCH_SZ + BYTECODE_SZ - sizeof(uint32_t) < inst.op1)) {
#endif
            ret = ERRNO_VFRY_REJECT_OFF;
            goto bail;
        }

#ifdef PATCHED
        if (inst.opcode & INST_MASK_OP2 && (SCRATCH_SZ - sizeof(uint32_t) < inst.op2)) {
#else
        if (inst.opcode & INST_MASK_OP2 && (SCRATCH_SZ + BYTECODE_SZ - sizeof(uint32_t) < inst.op2)) {
#endif 
            ret = ERRNO_VFRY_REJECT_OFF;
            goto bail;
        }

        // These *shouldn't* under/overflow due to (inst_len > len) check in inst_decode().
        cursor += inst.len;
        len -= inst.len;

#ifdef DEBUG
        fprintf(stderr, "[D] bytecode_vrfy() | len = %d\n", len);
        inst_count++;
#endif
    }

bail:
#ifdef DEBUG
    if (ERRNO_VFRY_REJECT_OFF == ret) {
        fprintf(stderr, 
            "[D] bytecode_vrfy() | REJECT due to offset check\n");
    }
#endif

    return ret;
}


// We've verified the bytecode for safety, now we execute it.
int bytecode_exec(uint8_t *bytes, uint16_t len, uint8_t *scratch, uint32_t *out) {

    int ret = SUCCESS;

#ifdef DEBUG
    fprintf(stderr, "[D] bytecode_exec() | init\n");
    uint32_t inst_count = 0;
#endif

    inst_t inst;
    uint8_t *cursor = bytes;
    uint32_t acc = 0;
    uint32_t op1 = 0;
    uint32_t op2 = 0;
    uint32_t *dst = NULL;

    while (len) {

#ifdef DEBUG
        fprintf(stderr, 
            "\n[D] bytecode_exec() | instruction #%d\n", inst_count);
#endif

        if (SUCCESS != (ret = inst_decode(cursor, len, &inst))) {
#ifdef DEBUG
            fprintf(stderr, 
                "[D] bytecode_exec() | non-SUCCESS from inst_decode; bailing...\n");
#endif
            ret = ERRNO_INST_DECODE;
            goto bail;
        }

        ////
        // Error Tree
        ////
        // INST_MASK_DST
        //  +- INST_MASK_ACC
        //      +- INST_MASK_OP1
        //      +- !INST_MASK_OP1: ERROR
        //  +- !INST_MASK_ACC: ERROR

        ////
        // Get dst.
        ////
        if (inst.opcode & INST_MASK_DST) {
            dst = (uint32_t *)(scratch + inst.op1);
        } else {
            dst = &acc;
        }

        ////
        // Get op1.
        ////
        if (inst.opcode & INST_MASK_DST && inst.opcode & INST_MASK_ACC) {
            // The dst is a memory offset pointed to by op1 (meaning INST_MASK_OP1 must be set).
            // The arith operands are ACC and op2.
            if (!(inst.opcode & INST_MASK_OP1)) {
#ifdef DEBUG
                fprintf(stderr, 
                "[D] bytecode_exec() | INVALID opcode: mem dst & immediate op1; bailing...\n");
#endif       
                ret = ERRNO_INVALID_OPCODE;
                goto bail;
            }
            op1 = acc;

        } else if (inst.opcode & INST_MASK_DST && !(inst.opcode & INST_MASK_ACC)) {
            // The dst is a memory offset pointed to by op1.
            // The arith operands are op1 and op2.
            // This is ILLEGAL; op1 cannot specify both dst offset and operand.
#ifdef DEBUG
            fprintf(stderr, 
                "[D] bytecode_exec() | INVALID opcode: mem dst & not ACC as op1; bailing...\n");
#endif       
            ret = ERRNO_INVALID_OPCODE;
            goto bail;

        } else if (!(inst.opcode & INST_MASK_DST) && inst.opcode & INST_MASK_ACC) {
            // The dst is ACC.
            // The arith operands are ACC and op2.
            op1 = acc;

        } else if (!(inst.opcode & INST_MASK_DST) && !(inst.opcode & INST_MASK_ACC)) {
            // The dst is ACC.
            // The arith operands are op1 and op2.
            if (inst.opcode & INST_MASK_OP1) {
                op1 =   scratch[inst.op1+0] << 0 |
                        scratch[inst.op1+1] << 8 |
                        scratch[inst.op1+2] << 16|
                        scratch[inst.op1+3] << 24;
#ifdef DEBUG
                fprintf(stderr, 
                    "[D] bytecode_exec() | scratch + inst.op1 = 0x%08x; op1 = *(scratch + inst.op1) = 0x%08x\n", 
                    scratch + inst.op1, op1);
#endif  
            } else {
                // op1 is an immediate.
                op1 = inst.op1;
            }
        }

        ////
        // Get op2.
        ////
        if (inst.opcode & INST_MASK_OP2) {
            op2 =   scratch[inst.op2+0] << 0 |
                    scratch[inst.op2+1] << 8 |
                    scratch[inst.op2+2] << 16|
                    scratch[inst.op2+3] << 24;
#ifdef DEBUG
            fprintf(stderr, 
                "[D] bytecode_exec() | scratch + inst.op2 = 0x%08x; op2 = *(scratch + inst.op2) = 0x%08x\n", 
                scratch + inst.op2, op2);
#endif  
        } else {
            op2 = inst.op2;
        }

        ////
        // Do the operation.
        ////
        switch(inst.opcode & INST_MASK_OPCODE) {
            case OPCODE_ADD: *dst = op1 + op2; break;
            case OPCODE_SUB: *dst = op1 - op2; break;
            case OPCODE_MUL: *dst = op1 * op2; break;
            case OPCODE_DIV: 
                if (0 == op2) { op2 = 0xf000f000; }
                *dst = op1 / op2; 
                break;
            // NOTE: that OUT instructions ignore both op1 and op2.
            case OPCODE_OUT: *out = acc; break;
            default:
#ifdef DEBUG
                fprintf(stderr, 
                    "[D] bytecode_exec() | INVALID opcode; bailing...\n");
#endif  
                ret = ERRNO_INVALID_OPCODE;
                goto bail;
                break;
        }

#ifdef DEBUG
        fprintf(stderr, 
            "[D] bytecode_exec() | dst = 0x%08x; *dst = 0x%08x\n", dst, *dst);
#endif  

        // These *shouldn't* under/overflow due to (inst_len > len) check in inst_decode().
        cursor += inst.len;
        len -= inst.len;

#ifdef DEBUG
        fprintf(stderr, "[D] bytecode_exec() | #%04d: acc = 0x%08x\n", inst_count++, acc);
        fprintf(stderr, "[D] bytecode_exec() | len = %d\n", len);
#endif
    }
    
bail:
    return ret;
}


int main(void) {

    int ret = SUCCESS;
    size_t rx_bytes = 0;
    size_t tx_bytes = 0;

    // Allocate scratch + bytecode space.
    // Per man, allocate()d memory is zero-filled.
    uint8_t *space = NULL;
    if (SUCCESS != (ret = allocate(SCRATCH_SZ + BYTECODE_SZ, FALSE, (void **)&space))) {
#ifdef DEBUG
        fprintf(stderr, "[E] allocate()\n");
#endif
        return ret;
    }
#ifdef DEBUG
        fprintf(stderr, "[D] allocate() | space = 0x%08x\n", space);
#endif

    // Get length of bytecode (2B).
    uint16_t bytecode_len = 0;
    rx_bytes = 0;
    if (SUCCESS != (ret = receive_all(STDIN, (void *)&bytecode_len, sizeof(bytecode_len), &rx_bytes))) { 
#ifdef DEBUG
        fprintf(stderr, "[E] during receive_all() of bytecode_len\n");
#endif
        ret = ERRNO_RECV;
        goto bail;
    }

    // Verify bytecode_len.
    // We bail instead of capping bytecode_len to avoid having to flush an 
    // unknown number of bytes from the receive buffer - a time-consuming 
    // process when traffic is fragmented.
    if (BYTECODE_SZ - sizeof(uint32_t) < bytecode_len) {
#ifdef DEBUG
        fprintf(stderr, "[D] BYTECODE_SZ < bytecode_len; bailing...\n");
#endif
        goto bail;
    }

    // Read in the bytecode itself.
    rx_bytes = 0;
    if (SUCCESS != (ret = receive_all(STDIN, (void *)(space+SCRATCH_SZ), bytecode_len, &rx_bytes))) { 
#ifdef DEBUG
        fprintf(stderr, "[E] during receive_all() of bytecode\n");
#endif
        ret = ERRNO_RECV;
        goto bail;
    }

    // Verify bytecode.
    if (SUCCESS != (ret = bytecode_vrfy(space+SCRATCH_SZ, bytecode_len))) { 
#ifdef DEBUG
        fprintf(stderr, "[D] bytecode_vrfy(): REJECT\n");
#endif
        goto bail;
    }

#ifdef DEBUG
    fprintf(stderr, "[D] bytecode_vrfy(): PASS\n");
#endif

    // Execute bytecode.
    uint32_t out = OUT_DEFAULT;
    if (SUCCESS != (ret = bytecode_exec(space+SCRATCH_SZ, bytecode_len, space, &out))) { 
#ifdef DEBUG
        fprintf(stderr, "[D] bytecode execution failed; bailing...\n");
#endif
        goto bail;
    }

    // Send answer back to CRS.
    tx_bytes = 0;
    if (SUCCESS != (ret = transmit_all(STDOUT, &out, sizeof(out), &tx_bytes))) { 
#ifdef DEBUG
        fprintf(stderr, "[E] transmit_all(answer)\n");
#endif
        ret = ERRNO_TRANSMIT;
        goto bail;
    }

bail:
    if (space) { deallocate(space, SCRATCH_SZ + BYTECODE_SZ); }
    return ret;
}

