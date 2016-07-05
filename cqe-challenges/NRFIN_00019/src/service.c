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

// This calculation implements the challenge #1 from README.md: 
// Ignore / Throw Out Most Input
int entanglement_razzmatazz(void) {

    int ret = SUCCESS;
    size_t MIN_RX_BYTES = 1337;

    size_t SZ_IRRELEVANT_BYTES = 100;

    size_t GATE_OFF = 200;
    size_t ALLOC_OFF = 300;
    size_t OOB_OFF = 400;

    size_t SZ_PAGE = 0x1000;
    size_t MAX_ALLOC = 0x4000;
    size_t MIN_ALLOC = 2;

    size_t GATE_MAGIC = 0xCAFEBABE;

#ifdef DEBUG
    fprintf(stderr, "[D] entanglement_razzmatazz() | init\n");
#endif

    // Do complex & irrelevant operations with the majority of the input.  
    // Throw result out.
    size_t garbage = 1;
    for (size_t i = 1; i < SZ_IRRELEVANT_BYTES; i++) {
        garbage = (rx_buf[i] ^ (rx_buf[i+1] + rx_buf[i+2])) / 
            (garbage | 1); // avoids div by 0
    }

    // Limit maximum allocation to MAX_ALLOC
    size_t sz_alloc =  (rx_buf[ALLOC_OFF+0] << 0 | 
                        rx_buf[ALLOC_OFF+1] << 8);
    if (MAX_ALLOC < sz_alloc || MIN_ALLOC > sz_alloc ) { sz_alloc = MAX_ALLOC; }

    // Calculate how much space will actually be alloc'ed (round up).
    size_t sz_alloc_align = (sz_alloc + SZ_PAGE-1) & 0xFFFFF000;

    // Do the allocation.
    unsigned char *map = NULL;
    unsigned char *origmap = NULL;
    if (SUCCESS != (ret = allocate(sz_alloc, 0, (void **)&map))) {
#ifdef DEBUG
        fprintf(stderr, "[E] entanglement | allocate() of size 0x%02x failed\n", sz_alloc);
#endif
        goto _bail_razzmatazz;
    }
    origmap = map;

    // So we should now have memory mapped: 
    // [map, map + sz_alloc_align)
    // ex: sz_alloc = 0x2300; [map, map + 0x3000)

    // We advance 'map' by the difference between a page-aligned mapping and 
    // the precise amount requested in order to emulate a precisely -
    // controlled mapping size.
    // ex: sz_alloc = 0x2300; we need to advance by 0x3000 - 0x2300 = 0xD00
    map += (sz_alloc_align - sz_alloc);

    // Relative to the new map location, the following is now alloc'ed: 
    // [map, map + sz_alloc)

    size_t len = 0;
#ifdef PATCHED
    len = sz_alloc;
#else
    len = sz_alloc_align;
#endif
    size_t gate =   rx_buf[GATE_OFF+0] <<  0 | 
                    rx_buf[GATE_OFF+1] <<  8 | 
                    rx_buf[GATE_OFF+2] << 16 | 
                    rx_buf[GATE_OFF+3] << 24;

    size_t i = 0;
    unsigned char response = 0;
    if (GATE_MAGIC == gate) {
#ifdef DEBUG
        fprintf(stderr, "[D] entanglement | gate check PASSED\n");
#endif
        map[0] = rx_buf[OOB_OFF+0];
        map[1] = rx_buf[OOB_OFF+1];

        for (i = 0; i < len-2; i++) {
            // OOB access here when requested allocation is not page aligned.
            // (When sz_alloc != sz_alloc_align)
            map[i+2] = map[i+1] + map[i] + i;
        }
        response = map[len-1];
    } else {
        ret = ERRNO_BAD_GATE;
        response = 0; // A guess will be correct 1/255 times.
    }

    if (SUCCESS != (ret = transmit_all(STDOUT, &response, 1, NULL))) { 
        ret = ERRNO_TRANSMIT;
        goto _bail_razzmatazz;
    }

_bail_razzmatazz:
    if (origmap) { deallocate(origmap, sz_alloc); }
    return ret;
}


// This calculation implements the challenge #2 from README.md: 
// Sanitize Input
int causality_poppycock(void) {

    int ret = SUCCESS;
    size_t MIN_RX_BYTES = 1337;

    size_t SKIP_PRIME = 13;
    size_t GATE_PRIME = 37;

    #define SZ_VULN_BUF 20
    unsigned char vuln_buf[SZ_VULN_BUF] = {0};

    unsigned char GATE_MAGIC = 0xAA;

#ifdef DEBUG
        fprintf(stderr, "[D] causality_poppycock() | init\n");
#endif

#ifdef DEBUG
        fprintf(stderr, 
            "[D] poppycock | before sanitize; rx_buf[SKIP_PRIME * GATE_PRIME] = 0x%02x\n", 
            rx_buf[SKIP_PRIME * GATE_PRIME]);
#endif 

    // Take in a lot of binary input, but "sanitize" much of it 
    // (e.g. modulo the input some limit to prevent later OOB access).
    for (size_t i = 1; i < rx_bytes; i++) {   

        // Fail to sanitize some small subset of the binary input...
#ifdef PATCHED
        // The proper way to patch is to just sanitize all input.
        rx_buf[i] = rx_buf[i] % SZ_VULN_BUF;
#else
        // The vulnerability is the failure to sanitize some (SKIP_PRIME indices).
        if (0 != i % SKIP_PRIME) { rx_buf[i] = rx_buf[i] % SZ_VULN_BUF; } 
#endif

        // Do complex, seemingly dangerous operations with the sanitized input 
        // - things that would be dangerous if it weren't sanitized.
        // vuln_buf, indexed at rx_buf[i], is assigned rx_buf[i] XORed with 
        // the next modulo element in vuln_buf, modulo SZ_VULN_BUF 
        unsigned char tmp1, tmp2;
        tmp1 = rx_buf[i];
        tmp2 = ( tmp1 ^ vuln_buf[ (tmp1 + 1) % SZ_VULN_BUF ] ) % SZ_VULN_BUF;

        // This can't go OOB, but the gated one later can.
        vuln_buf[tmp1 % SZ_VULN_BUF] = tmp2;
    }

#ifdef DEBUG
        fprintf(stderr, 
            "[D] poppycock | after sanitize; rx_buf[SKIP_PRIME * GATE_PRIME] = 0x%02x\n", 
            rx_buf[SKIP_PRIME * GATE_PRIME]);
#endif 

    // Construct gate answer with default-unsanitized input.
    // Yes, even if patch is applied, sanitized input can sum to the gate.
    unsigned char gate = 0;
    for (size_t i = 0; i < rx_bytes; i+=GATE_PRIME) {
        gate += rx_buf[i];
    }

#ifdef DEBUG
        fprintf(stderr, "[D] poppycock | gate = 0x%02x\n", gate);
#endif 

    // ...do dangerous things with (the unsanitized) subset.
    if (GATE_MAGIC == gate) {
        // If we failed to sanitize all of the input, then this is a dangerous 
        // operation.  vuln_buf is only 20B long, but rx_buf[13 * 37] can 
        // take on a value in [0, 255].  Chosen carefully, this should crash.

        // We can force execution into the gate (deter cheeseball defense) by 
        // overwriting a value that will go into output here.

#ifdef DEBUG
        fprintf(stderr, 
            "[D] poppycock | gate PASSED, going to write 0x42 to: vuln_buf[%d]\n", 
            rx_buf[SKIP_PRIME * GATE_PRIME]);
#endif        
        vuln_buf[rx_buf[SKIP_PRIME * GATE_PRIME]] = 0xAA;
    } else {
#ifdef DEBUG
        fprintf(stderr, "[D] poppycock | gate FAILED\n");
#endif 
    }

    // We construct output from vuln_buf, so they can't just throw out / ignore 
    // all these operations.
    size_t output = 0;
    size_t i = 0;
    for (i = 0; i < SZ_VULN_BUF-3; i+=4) {

        output +=   vuln_buf[i+0] <<  0 |
                    vuln_buf[i+1] <<  8 |
                    vuln_buf[i+2] << 16 |
                    vuln_buf[i+3] << 24;

#ifdef DEBUG
        fprintf(stderr, "[D] poppycock | output, round %d = 0x%08x\n", i, output);
#endif 
    }

#ifdef DEBUG
    fprintf(stderr, "[D] poppycock | final output: 0x%08x\n", output);
#endif

    if (SUCCESS != (ret = transmit_all(STDOUT, &output, sizeof(output), NULL))) { 
#ifdef DEBUG
        fprintf(stderr, "[E] poppycock | during transmit_all()\n");
#endif
        ret = ERRNO_TRANSMIT;
        goto _bail_poppycock;
    }

_bail_poppycock:
    return ret;
}


// This calculation implements the challenge #3 from README.md: 
// Use "Unusual" Means to Terminate or Propagate Taint
int heisenberg_hooey(void) {

    int ret = SUCCESS;
    size_t MIN_RX_BYTES = 1337;

    size_t XOR_CONST_OFF = 1+100;
    size_t XOR_CONST_OFF_PTR = 1+350;

    size_t SYSCALL_CONST_OFF = 1+500;
    size_t SYSCALL_PROP_OFF = 1+600;

    size_t FLOAT_CONST_OFF = 1+300;
    size_t FLOAT_PROP_OFF = 1+400;

    size_t BE_OFF = 1+800;
    size_t EF_OFF = 1+900;
    size_t VULN_OFF = 1+1000;

    size_t GATE_MAGIC = 0xDEADBEEF;

#ifdef DEBUG
        fprintf(stderr, "[D] heisenberg_hooey() | init\n");
#endif

    unsigned char garbage[rx_buf[SYSCALL_PROP_OFF]+1];

    ///////////////// XOR

    // XOR, Easy: Constify via taint XORed with itself.
    rx_buf[XOR_CONST_OFF] = rx_buf[XOR_CONST_OFF] ^ rx_buf[XOR_CONST_OFF];

    // XOR, Medium: now the constified index is symbolic.
    // The taint engine must properly alias memory in the trivial case.
    rx_buf[1+rx_buf[XOR_CONST_OFF_PTR]] = 
        rx_buf[1+rx_buf[XOR_CONST_OFF_PTR]] ^ 
        rx_buf[1+rx_buf[XOR_CONST_OFF_PTR]];

    // XOR, Medium-ish: the constified memory is symbolic, but it's not 
    // immediately obvious that the two memory accesses are aliased.  
    rx_buf[1+rx_buf[XOR_CONST_OFF_PTR*2]] = 
        rx_buf[1+rx_buf[XOR_CONST_OFF_PTR*2]] ^ 
        rx_buf[1+rx_buf[(XOR_CONST_OFF_PTR*2)+0xFFFFFFFF+1]];

    ///////////////// FLOAT

    // Constify via float
    float infinity = 1.0 / 0.0;
    // NOTE: this should always constify to 0, but *technically* the behavior 
    // is undefined.
    rx_buf[FLOAT_CONST_OFF] = (unsigned char)((float)rx_buf[FLOAT_CONST_OFF] * infinity);

    // Propagate via float
    // This doesn't have to be complicated because many analysis programs can't 
    // handle floats at all.
    // REM: I have confirmed this retains value in simple test.
    rx_buf[FLOAT_PROP_OFF] = 2*(unsigned char)((float)rx_buf[FLOAT_PROP_OFF] * 1.0);

    ///////////////// SYSCALL

    // Constify via syscall: deallocate()
    // Because rx_buf[CONST_SYSCALL_OFFSET] must be in [0, 255], any 
    // deallocation would fail, resulting in a write of EINVAL into 
    // rx_buf[1+CONST_SYSCALL_OFFSET], constifying it.
    // Failsafe: deallocate() of length 0 should cause EINVAL.
    rx_buf[SYSCALL_CONST_OFF] = deallocate((void *)rx_buf[SYSCALL_CONST_OFF], 0);

    // Propagate (reflect) via syscall: random()
    // We use a tainted value as the count argument to a random() syscall.
    // If the random() syscall is successful, count number of random bytes will 
    // be written into a garbage buffer and ignored, but rnd_bytes will take on 
    // the same value as count.
    size_t rnd_bytes = 0;
    if (SUCCESS != (ret = random(&garbage, rx_buf[SYSCALL_PROP_OFF], &rnd_bytes))) {
#ifdef DEBUG
        fprintf(stderr, "[E] hooey | error during random() call\n");
#endif
        ret = ERRNO_RANDOM;
        goto _bail_hooey;
    }

    // Verify proper reflection (this may give hint to CRSs).
    if (rnd_bytes != rx_buf[SYSCALL_PROP_OFF]) {
#ifdef DEBUG
        fprintf(stderr, "[E] hooey | error during random(); insufficient bytes\n");
#endif
        ret = ERRNO_INSUFFICIENT_BYTES;
        goto _bail_hooey;
    }

    // The actual number of returned bytes is written back into the tainted 
    // memory location, amounting to a reflection of the taint via a syscall.
    rx_buf[SYSCALL_PROP_OFF] = 1+(2*(unsigned char)rnd_bytes);

    
    ///////////////////////////////////////////////////////////////////////////

    // The following rx_buf indices should be CONSTIFIED:
    //      XOR_CONST_OFF
    //          - index is always: 101
    //          - value is always 0
    //      1+rx_buf[XOR_CONST_OFF_PTR]
    //          - index in range, stride 1: [1, 256]
    //          - value is always 0
    //      1+rx_buf[XOR_CONST_OFF_PTR*2]
    //          - index in range, stride 2: [1, 511]
    //          - value is always 0
    //      FLOAT_CONST_OFF
    //          - value is always 0 (NOTE: BEHAVIOR IS UNDEFINED)
    //      SYSCALL_CONST_OFF
    //          - value is always EINVAL (currently 3)
    //      
    // There is potential these have been overtainted.
    // For these, we do some complex but irrelevant operations.

    // This conditional should never be satisfied, but it's not terribly 
    // obvious that it won't be, so if any of these values are overtainted, 
    // the engine must reason about the code in the conditional, leading to 
    // potential DoS.
    if (rx_buf[XOR_CONST_OFF] != 0 || 
        rx_buf[1+rx_buf[XOR_CONST_OFF_PTR]] != 0 ||
        rx_buf[1+rx_buf[XOR_CONST_OFF_PTR*2]] != 0 ||
        rx_buf[FLOAT_CONST_OFF] != 0 ||
        rx_buf[SYSCALL_CONST_OFF] != EINVAL) {

#ifdef DEBUG
        if (0 == DEBUG_THIS_HAPPENED) {
            fprintf(stderr, 
                "[E] hooey | got inside the CONSTIFY'ed gate; THIS SHOULD NEVER HAPPEN;\n"
                "    rx_buf[XOR_CONST_OFF] = 0x%02x\n"
                "    rx_buf[1+rx_buf[XOR_CONST_OFF_PTR]] = 0x%02x\n"
                "    rx_buf[1+rx_buf[XOR_CONST_OFF_PTR*2]] = 0x%02x\n"
                "    rx_buf[FLOAT_CONST_OFF] = 0x%02x\n"
                "    rx_buf[SYSCALL_CONST_OFF] = 0x%02x\n",
                rx_buf[XOR_CONST_OFF],
                rx_buf[1+rx_buf[XOR_CONST_OFF_PTR]],
                rx_buf[1+rx_buf[XOR_CONST_OFF_PTR*2]],
                rx_buf[FLOAT_CONST_OFF],
                rx_buf[SYSCALL_CONST_OFF]);
            DEBUG_THIS_HAPPENED = 1;
        }  
#endif
        
        // Annoying enough?
        heisenberg_hooey();
    }

    // The following rx_buf indices should be PROPAGATED:
    //      FLOAT_PROP_OFF
    //      SYSCALL_PROP_OFF
    // There is potential these have been undertainted.
    // We use these and other bytes as a gate to guard vulnerability, forcing 
    // symexec reasoning on these potential undertaints.
    size_t gate =   rx_buf[EF_OFF]            <<  0 | // EF
                    rx_buf[BE_OFF]            <<  8 | // BE (even)
                    rx_buf[SYSCALL_PROP_OFF]  << 16 | // AD (odd)
                    rx_buf[FLOAT_PROP_OFF]    << 24;  // DE (even)
                   
    size_t output = 0;
    // The 2 bytes are the easily-reasoned-about ones.
    if ((GATE_MAGIC & 0x0000FFFF) == (gate & 0x0000FFFF)) {

#ifdef DEBUG
        fprintf(stderr, "[D] hooey | gate PASSED\n");
#endif   

        output = 0xDEADBEEF;
        if (SUCCESS != (ret = transmit_all(STDOUT, &output, sizeof(output), NULL))) { 
#ifdef DEBUG
            fprintf(stderr, "[E] hooey | during transmit_all()\n");
#endif
            ret = ERRNO_TRANSMIT;
            goto _bail_hooey;
        }

        // Vuln: if the GATE_MAGIC is satisfied, mult is 0, otherwise 1.
        // We attempt a write to rx_buf[VULN_OFF] * mult, which will cause an 
        // attempt to write to the NULL page if the gate is satisfied.
        size_t mult = !!(GATE_MAGIC ^ gate);

        unsigned char *ptr = (unsigned char *)((size_t)&(rx_buf[VULN_OFF]) * mult);
#ifdef PATCHED
        if (0 != mult) { *ptr = 0x42; }
#else
        *ptr = 0x42;
#endif
    }
    
    output = rx_buf[FLOAT_PROP_OFF] ^ (rx_buf[SYSCALL_PROP_OFF] + rx_buf[VULN_OFF]);
#ifdef DEBUG
        fprintf(stderr, 
            "[D] hooey | rx_buf[SYSCALL_PROP_OFF] = 0x%02x, rx_buf[FLOAT_PROP_OFF] = 0x%02x, rx_buf[VULN_OFF] = 0x%02x, output = 0x%02x\n",
            rx_buf[SYSCALL_PROP_OFF], rx_buf[FLOAT_PROP_OFF], rx_buf[VULN_OFF], output);
#endif

    if (SUCCESS != (ret = transmit_all(STDOUT, &output, sizeof(output), NULL))) { 
#ifdef DEBUG
        fprintf(stderr, "[E] hooey | during transmit_all()\n");
#endif
        ret = ERRNO_TRANSMIT;
        goto _bail_hooey;
    }

_bail_hooey:
    return ret;
}


// This calculation implements the challenge #4 from README.md: 
// Symbolic Memory Accesses
int relativistic_jabberwock(void) {

    int ret = SUCCESS;
    size_t MIN_RX_BYTES = 1337;

    size_t SYM_PROP_PTR_1 = 1+100;
    size_t SYM_PROP_PTR_2 = 1+200;
    size_t SYM_PROP_VAL = 1+70;

    size_t SYM_CONST_PTR_1 = 1+50;
    size_t SYM_CONST_PTR_2 = 1+60;

    size_t VULN_OFF = 1+400;
    
    size_t GATE_MAGIC = 0xd00000d5;

    size_t output;

#ifdef DEBUG
    fprintf(stderr, "[D] relativistic_jabberwock() | init\n");
#endif

    ///////////////// PROPAGATE via aliasing.

    // Taint CONSTIFIED at rx_buf[SYM_PROP_PTR_1] (and underneath).
    rx_buf[SYM_PROP_PTR_1] = 0;
    rx_buf[rx_buf[SYM_PROP_PTR_1]+0] = 0;
    rx_buf[rx_buf[SYM_PROP_PTR_1]+1] = 0;
    rx_buf[rx_buf[SYM_PROP_PTR_1]+2] = 0;
    rx_buf[rx_buf[SYM_PROP_PTR_1]+3] = 0; 
    // There's a lot of indirection here:
    // rx_buf[SYM_PROP_PTR_1]: controlled offset into rx_buf, CONSTIFIED to 0
    // rx_buf[rx_buf[SYM_PROP_PTR_1]]: the value beneath this CONSTIFIED offset

    // Taint PROPAGATED to rx_buf[rx_buf[SYM_PROP_PTR_2]].
    rx_buf[rx_buf[SYM_PROP_PTR_2]] = rx_buf[SYM_PROP_VAL];
    // iff rx_buf[SYM_PROP_PTR_2] == SYM_PROP_PTR_1, taint propagated to:
    // rx_buf[SYM_PROP_PTR_1], PROPAGATING rx_buf[SYM_PROP_PTR_VAL].

    // rx_buf[SYM_PROP_PTR_1] will ultimately be referenced one final time to 
    // point to a size_t that will be gate key.


    ///////////////// CONSTIFY via aliasing.

    // Taint CONSTIFIED at rx_buf[rx_buf[SYM_CONST_PTR_1]].
    rx_buf[rx_buf[SYM_CONST_PTR_1]] = 0;

    // Taint CONSTIFIED (w/ new value) at rx_buf[rx_buf[SYM_CONST_PTR_1]].
    rx_buf[rx_buf[SYM_CONST_PTR_2]] = 0x42;

    // Our gate requires rx_buf[rx_buf[SYM_CONST_PTR_1]] == 42.
    // This will happen iff rx_buf[SYM_CONST_PTR_1] == rx_buf[SYM_CONST_PTR_2].


    ///////////////////////////////////////////////////////////////////////////

    // We gate the vulnerability by forcing propagation in one situation and 
    // forcing constification in another.

    // This forces reasoning about the propagation piece.
    size_t gate =   rx_buf[rx_buf[SYM_PROP_PTR_1]+0] <<  0 |
                    rx_buf[rx_buf[SYM_PROP_PTR_1]+1] <<  8 |
                    rx_buf[rx_buf[SYM_PROP_PTR_1]+2] << 16 |
                    rx_buf[rx_buf[SYM_PROP_PTR_1]+3] << 24;

#ifdef DEBUG
        fprintf(stderr, 
            "[D] jabberwock | "
            "rx_buf[SYM_CONST_PTR_1] = 0x%02x, "
            "rx_buf[rx_buf[SYM_CONST_PTR_1]] = 0x%02x, "
            "rx_buf[SYM_PROP_PTR_1] = 0x%02x, "
            "rx_buf[SYM_PROP_PTR_2] = 0x%02x, "
            "gate = 0x%08x\n", 
            rx_buf[SYM_CONST_PTR_1], 
            rx_buf[rx_buf[SYM_CONST_PTR_1]], 
            rx_buf[SYM_PROP_PTR_1], 
            rx_buf[SYM_PROP_PTR_2], 
            gate);
#endif 

    // This forces reasoning about the constification piece.
    if (0x42 == rx_buf[rx_buf[SYM_CONST_PTR_1]] && 
        GATE_MAGIC == gate) {

#ifdef DEBUG
        fprintf(stderr, "[D] jabberwock | gate PASSED\n");
#endif 

        // VULN: this can cause write outside of rx_buf, but can also affect 
        // something that goes into output.
        size_t offset = 0;
#ifdef PATCHED
        offset = (rx_buf[VULN_OFF] * 1000) % 1001;
#else
        offset = rx_buf[VULN_OFF] * 1000;
#endif
        // Non-exploitative example:
        // rx_buf[VULN_OFF] = 1
        // rx_buf[1000] = 42;

        // Exploitative example:
        // rx_buf[VULN_OFF] = 66
        // rx_buf[66000] = 42; // CRASH
        rx_buf[offset] = 0x42;

        output =    rx_buf[offset]                  <<  0 |
                    rx_buf[SYM_CONST_PTR_1]         <<  8 |
                    rx_buf[rx_buf[SYM_CONST_PTR_1]] << 16 |
                    rx_buf[SYM_PROP_VAL]            << 24;
    } else {

#ifdef DEBUG
        fprintf(stderr, "[D] jabberwock | gate FAILED\n");
#endif 
        output =  ~(0                               <<  0 |
                    rx_buf[SYM_CONST_PTR_1]         <<  8 |
                    rx_buf[rx_buf[SYM_CONST_PTR_1]] << 16 |
                    rx_buf[SYM_PROP_VAL]            << 24);
    }

    if (SUCCESS != (ret = transmit_all(STDOUT, &output, sizeof(output), NULL))) { 
#ifdef DEBUG
        fprintf(stderr, "[E] jabberwock | during transmit_all()\n");
#endif
        ret = ERRNO_TRANSMIT;
        goto _bail_jabberwock;
    }

_bail_jabberwock:
    return ret;
}


// Exit the quantum calculator with provided exit code.
void exit(void) {

    int ret = SUCCESS;
    size_t MIN_RX_BYTES = 1;

#ifdef DEBUG
    fprintf(stderr, "[D] exit() | got %d bytes\n", rx_bytes);
#endif

    unsigned char exit_code = rx_buf[1];

    // Reflect the exit code
    if (SUCCESS != (ret = transmit_all(STDOUT, &exit_code, 1, NULL))) { 
#ifdef DEBUG
        fprintf(stderr, "[E] exit | during transmit_all()\n");
#endif
        ret = ERRNO_TRANSMIT;
        goto _bail_exit;
    }

_bail_exit:
    _terminate(exit_code);
}


int dispatch(void) {

    int ret = SUCCESS;

    unsigned char op = rx_buf[0];
    switch(op) {
        case '\x01': entanglement_razzmatazz(); break;
        case '\x07': causality_poppycock(); break;
        case '\x03': heisenberg_hooey(); break;
        case '\x04': relativistic_jabberwock(); break;
        case '\x00': exit(); break;
        default:
#ifdef DEBUG
            fprintf(stderr, "[D] invalid operation: 0x%02x\n", op);
#endif
            ret = ERRNO_INVALID_OPERATION;
            break;
    }

    return ret;
}

int main(void) {

    int ret = SUCCESS;

    // Get op (1st byte), dispatch to function.
    while(1) {

        rx_bytes = 0;
        memset(rx_buf, 0, BUF_RX_SZ);

        if (SUCCESS != (ret = receive_all(STDIN, (void *)&rx_buf, BUF_RX_SZ, &rx_bytes))) { 
#ifdef DEBUG
            fprintf(stderr, "[E] main | during receive_all()\n");
#endif
            ret = ERRNO_RECV;
            goto _bail_main;
        }

        // "zero indicates nothing was received or end-of-file"
        // Not sending any more calculations is a way to exit the calculator.
        if (0 == rx_bytes) {
#ifdef DEBUG
            fprintf(stderr, "[E] main | got no bytes; bailing...\n", rx_bytes);
#endif
            goto _bail_main;
        }

        dispatch();
    }

_bail_main:
    return ret;
}  



