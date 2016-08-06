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

/* 	The FRAG Protocol:
	---------------------------------------------------------------------------

	Background:
	----------
	The point of this CB isn't to test understanding of a complex fragmentation 
	routine, but rather test reasoning about excessive stack consumption and 
	control over consumption via function recursion. The fragmentation routine 
	employed here is therefore a toy, used only as a means to an end and would 
	probably make for a very bad fragmentation routine in any real protocol.

	The biggest potential problem with this toy de-fragmentation algorithm is 
	that a viable optimization would be to just drop all bytes with the 
	fragment bit set and append all others to CT.  This would require a either 
	a substantial static understanding of the algorithm or a probabilistic 
	dynamic heuristic.  In either case, it's probably a somewhat impressive feat 
	for a CRS so we allow for the possibility of this optimization, essentially 
	rewarding CRSs who figure it out.

	How it Works:
	------------
	The most significant bit in each byte signifies whether the other 7 bits in 
	the byte represent the number of fragments (immediately following, possibly 
	nested), or raw ciphertext (CT) data that should be appended to ct[].

	Execution can expand in breadth (many loop iterations due to a high number
	of fragmented packets) or depth (many bytes indicating fragmentation, 
	triggering recursion). The vulnerability (stack exhaustion) will only be 
	triggered due to excessive depth (excessive recursion).  

	The ability to execute "wide" / high-breadth execution traces distracts 
	from the problematic logic and allows for somewhat non-trivial pollers.

	In other words, for each byte:
	bit 0: do the other 7 bits represent fragment count?
		the bit is set:
			bit 1-7: # of fragments, call it X
			triggers recursion into defrag(X)
				next X bytes are looped over, appended to ct[] if not 
				fragmented or further recursed if fragmented
		not fragmented:
			bit 1-7: ciphertext
			These bits are appended to a ciphertext buffer to be XOR'ed at end.
			These bits are not packed, so they still occupy 8 bits in ct[].

	Examples:
	--------
	example0 (no fragment):
	0AAA AAAA | 0BBB BBBB | 0CCC CCCC | ...
	- 0AAA AAAA: not fragmented, ct[ct_index++] = 0AAA AAAA; rx_index++
	- 0BBB BBBB: not fragmented, ct[ct_index++] = 0BBB BBBB; rx_index++
	- 0CCC CCCC: not fragmented, ct[ct_index++] = 0CCC CCCC; rx_index++ 
	end ct[] = 0AAA AAAA 0BBB BBBB 0CCC CCCC ...

	example1 (empty fragment):
	1000 0000 | 0AAA AAAA | 0BBB BBBB | ...
	- 1000 0000: 0 frags, recurse defrag(0)
		(return from defrag)
	- 0AAA AAAA: not fragmented, ct[ct_index++] = 0AAA AAAA; rx_index++
	- 0BBB BBBB: not fragmented, ct[ct_index++] = 0BBB BBBB; rx_index++
	end ct[] = 0AAA AAAA 0BBB BBBB ...

	example2 (single fragment):
	1000 0001 | 0AAA AAAA | 0BBB BBBB | ...
	- 1000 0001: 1 frags, recurse degrag(1)
		1) 0AAA AAAA: not fragmented ct[ct_index++] = 0AAA AAAA; rx_index++
		(return from defrag)
	- 0BBB BBBB: not fragmented, ct[ct_index++] = 0BBB BBBB; rx_index++
	end ct[] = 0AAA AAAA 0BBB BBBB ...

	example3 (breadth fragment):
	1000 0011 | 0AAA AAAA | 0BBB BBBB | 0CCC CCCC | ...
	- 1000 0011: 3 frags, recurse into defrag(3)
		1) 0AAA AAAA: not fragmented, ct[ct_index++] = 0AAA AAAA; rx_index++
		2) 0BBB BBBB: not fragmented, ct[ct_index++] = 0BBB BBBB; rx_index++
		3) 0CCC CCCC: not fragmented, ct[ct_index++] = 0CCC CCCC; rx_index++
		(return from defrag)
	end ct[]: 0AAA AAAA 0BBB BBBB 0CCC CCCC ...

	example4 (nested fragment):
	1000 0010 | 1000 0001 | 0AAA AAAA | 0BBB BBBB
	- 1000 0010: 2 frags, recurse into defrag(2)
		1) 1000 0001: 1 frags, recurse into defrag(1) 
			1) 0AAA AAAA: not fragmented, append 0AAA AAAA to ct[]; rx_index++
			(return from defrag)
		2) 0BBB BBBB: not fragmented, append 0BBB BBBB to ct[]; rx_index++
		(return from defrag)
	end ct[] = 0AAA AAAA 0BBB BBBB ...

	example5 (nested, more complex):
	1000 0010 | 0AAA AAAA | 1000 0001 | 1000 0001 | 0BBB BBBB
	- 1000 0010: 2 frags, recurse into defrag(2)
		1) 0AAA AAAA: not fragmented; append 0AAA AAAA to ct[]; rx_index++
		2) 1000 0001: 1 frags, recurse defrag(1)
			1) 1000 0001: 1 frags, recurse defrag(1)
				1) 0BBB BBBB: not fragmented, append 0BBB BBBB to ct[]; rx_index++
				(return from defrag)
			(return from defrag)
		(return from defrag)
	end ct[] = 0AAA AAAA 0BBB BBBB ...
 */
	

#ifdef DEBUG
static inline unsigned int getesp() {
	unsigned int esp;
	__asm__("movl %%esp, %0\n" : "=g" (esp));
	return esp;
}
#endif
// ^ DEBUG

int defrag(size_t fragments) {

	int ret = SUCCESS;
	unsigned char byte;
	size_t i = 0;

	depth++;

#ifdef PATCHED
	if (MAX_DEPTH < depth) {
#ifdef DEBUG
	    fprintf(stderr, 
	    	"[D] defrag(%03d) | exceeded MAX_DEPTH (%03d); depth = %03d\n", 
	    	fragments, MAX_DEPTH, depth);
#endif
	    ret = ERRNO_EXCEEDED_MAX_DEPTH;
	    goto bail_defrag;
	}
#endif

	// Per CGC kernel source, the stack is hard-coded to:
	// 1) Grow down from 0xbaaab000
	// 2) Have a maximum length is 0x800000 bytes
	// We should therefore expect #PF beyond 0xBA2AB000.
	// From core: 
	// 0xba3a9000->0xbaaab000 at 0x00002000: load3 ALLOC LOAD CODE HAS_CONTENTS

	// Let's trigger this condition with 128 or more recursions.
	// Each recursion would therefore need to consume: 
	// 0x800000 / 128 = 0x10000 bytes
	unsigned char bogus[SZ_BOGUS] = { 0 };
	// Empirically, this function occupies about SZ_BOGUS + 0x70 bytes total.

#ifdef DEBUG
	// Keep it the same over the lifespan of a recursion.
	unsigned int esp = getesp();
#endif

#ifdef DEBUG
    fprintf(stderr, 
    	"[D] ENTER: defrag(%03d) | (depth, esp) = (%03d, 0x%08x) | rx_index = %03d; ct_index = %03d\n", 
    	fragments, depth, esp, rx_index, ct_index);
#endif

    // Loop over fragments.
    for (i = 0; i < fragments; i++) {

    	// Bail if we're about to go off the end of the RX buffer.
		if (BUF_RX_SZ <= rx_index) {
#ifdef DEBUG
	    	fprintf(stderr, 
	    		"[D] defrag(%03d) | exhausted RX_BUF; bailing...\n", 
	    		fragments);
#endif
			ret = ERRNO_EXHAUSTED_RX;
			goto bail_defrag;
		}

    	byte = rx_buf[rx_index];
    	rx_index++;

		if (IS_FRAGMENTED(byte)) {

			// If it's fragmented, we recurse, passing in the number of 
			// fragments as argument.
			if (SUCCESS != (ret = defrag(GET_DATA(byte)))) {		
				goto bail_defrag;
			}
			
		} else {	

			// If it's not fragmented, we append the byte to ct[].
			ct[ct_index] = byte;

#ifdef DEBUG
		    fprintf(stderr, 
		    	"[D] defrag(%03d) | not fragged; (before XOR) ct[%03d] = 0x%02x\n", 
		    	fragments, ct_index, byte);
#endif

		    ct_index++;
			
			// NOTE: We don't need to check ct_index bounds so long as 
			// sizeof(ct) == sizeof(rx_buf) because ct_index is incremented a 
			// subset of the times rx_index is incremented.  
			// Revisit this if this assumption changes.
    	}

	} // END: fragment loop

bail_defrag:
    depth--;
	return ret;
}

void exercise_stack(void){
	// We need to force mapping of the entirety (or most) of the stack space
	// because the kernel is lazy and near the bottom of the stack probably 
	// isn't accessible without this.
	unsigned char bogus[STACK_SZ-0x1000] = { 0 };
}


int main(void) {

    int ret = SUCCESS;
    size_t state = STATE_CONNTERM;
    size_t expected_rx_bytes = CONNTERM_SZ; 
    size_t i = 0;

#ifdef DEBUG
	fprintf(stderr, "[D] main | --------------- new run ---------------\n");
#endif

	exercise_stack();

	// From the README, we store a pointer to the OTP at a low stack address.
	void *ppotp = (void *)(STACK_LIMIT + 0x10000);
	unsigned char *potp = otp;
	((void **)ppotp)[0] = potp;
	// Henceforth, when we reference OTP, we do so via a double-dereference 
	// that passes through STACK_LIMIT + 0x10000.

    // Main loop.
    while(1) {

    	////
    	// STATE-AGNOSTIC GET-THE-PACKET CODE
    	////

        rx_bytes = 0;
        memset(rx_buf, 0, BUF_RX_SZ);
        if (SUCCESS != (ret = receive_all(STDIN, (void *)&rx_buf, BUF_RX_SZ, &rx_bytes))) { 
#ifdef DEBUG
            fprintf(stderr, "[E] main | failed pkt receive\n");
#endif
            ret = ERRNO_RECV;
            goto bail_main;
        }

        // If we got the EXIT packet, bail gracefully.
        if (sizeof(PKT_EXIT)-1 == rx_bytes && 
        	0 == memcmp((const char *)&rx_buf, (const char *)&PKT_EXIT, sizeof(PKT_EXIT)-1)) {

        	if (SUCCESS != (ret = transmit_all(STDOUT, &PKT_EXIT_ACK, sizeof(PKT_EXIT_ACK)-1, NULL))) { 
#ifdef DEBUG
	            fprintf(stderr, "[E] main | failed transmitting PKT_EXIT_ACK\n");
#endif
                ret = ERRNO_TRANSMIT;
                goto bail_main;
	        }

#ifdef DEBUG
	       	fprintf(stderr, 
	       		"[D] main | just sent PKT_EXIT_ACK; it starts with: 0x%02x 0x%02x\n", 
	       		PKT_EXIT_ACK[0], PKT_EXIT_ACK[1]);
#endif

        	goto bail_main;
        }

        // Verify we received enough bytes for the type of message we expect.
        if (rx_bytes != expected_rx_bytes) {
#ifdef DEBUG
	        fprintf(stderr, 
	        	"[D] main | rx_bytes == %d != %d; transmit ()ing PKT_INVALID_SZ...\n", 
	        	rx_bytes, expected_rx_bytes);
#endif
	        if (SUCCESS != (ret = transmit_all(STDOUT, &PKT_INVALID_SZ, sizeof(PKT_INVALID_SZ)-1, NULL))) { 
#ifdef DEBUG
	            fprintf(stderr, "[E] main | failed transmitting PKT_INVALID_SZ\n");
#endif
	            ret = ERRNO_TRANSMIT;
	            goto bail_main;
	        }

#ifdef DEBUG
	       	fprintf(stderr, 
	       		"[D] main | just sent PKT_INVALID_SZ; it starts with: 0x%02x 0x%02x\n", 
	       		PKT_INVALID_SZ[0], PKT_INVALID_SZ[1]);
#endif

	        continue; // Get the next packet.
        }

        ////
        // PACKET LOOKS LEGIT; PROCESS ACCORDING TO STATE
        ////

        switch(state) {

        	////
        	// STATE_CONNTERM
        	////

        	// In STATE_CONNTERM, we look for MSG_CONNTERM and advance state
			// when we see it.  If we see anything else, we send an ERROR message.
        	case STATE_CONNTERM:

        		// We DON'T get CONNTERM, then send error packet, listen for 
        		// next packet.
	            if (0 != memcmp((const char *)&rx_buf, (const char *)&PKT_CONNTERM, sizeof(PKT_CONNTERM)-1)) {

	                if (SUCCESS != (ret = transmit_all(STDOUT, &PKT_CONNTERM_ERR, sizeof(PKT_CONNTERM_ERR)-1, NULL))) { 
#ifdef DEBUG
	                    fprintf(stderr, "[E] main | failed transmitting PKT_CONNTERM_ERR\n");
#endif
	                    ret = ERRNO_TRANSMIT;
	                    goto bail_main;
	                }

#ifdef DEBUG
		       	fprintf(stderr, 
		       		"[D] main | just sent PKT_CONNTERM_ERR; it starts with: 0x%02x 0x%02x\n", 
		       		PKT_CONNTERM_ERR[0], PKT_CONNTERM_ERR[1], sizeof(PKT_CONNTERM_ERR));
		       	fprintf(stderr, 
	            	"[D] main | STATE_CONNTERM: expected CONNTERM, didn't get it.\n");
#endif      

	            	continue; // Get the next packet.
	        	}

	        	// If we haven't continued, we got CONNTERM; we need to ACK.
				if (SUCCESS != (ret = transmit_all(STDOUT, &PKT_CONNTERM_ACK, sizeof(PKT_CONNTERM_ACK)-1, NULL))) { 
#ifdef DEBUG
                    fprintf(stderr, "[E] main | failed transmitting PKT_CONNTERM_ACK\n");
#endif
                    ret = ERRNO_TRANSMIT;
                    goto bail_main;
                }

#ifdef DEBUG
		       	fprintf(stderr, 
		       		"[D] main | just sent PKT_CONNTERM_ACK; it starts with: 0x%02x 0x%02x\n", 
		       		PKT_CONNTERM_ACK[0], PKT_CONNTERM_ACK[1]);
#endif  

	            state = STATE_OTP;
	            expected_rx_bytes = OTP_SZ;
#ifdef DEBUG
	            fprintf(stderr, 
	            	"[D] main | STATE_CONNTERM: got CONNTERM; state advanced to STATE_OTP.\n");
#endif 
        		break; // STATE_CONNTERM

        	////
        	// STATE_OTP
        	////

        	// STATE_OTP simply copies buffer into OTP, advances to STATE_MSG.
        	case STATE_OTP:

	            memcpy(((unsigned char **)ppotp)[0], rx_buf, sizeof(otp));
	            state = STATE_MSG;
	            expected_rx_bytes = MSG_SZ;

#ifdef DEBUG
	            fprintf(stderr, 
	            	"[D] main | STATE_OTP: memcpy()ed into OTP; advanced to STATE_MSG\n");
#endif 

				if (SUCCESS != (ret = transmit_all(STDOUT, &PKT_OTP_ACK, sizeof(PKT_OTP_ACK)-1, NULL))) { 
#ifdef DEBUG
                    fprintf(stderr, "[E] main | failed transmitting PKT_OTP_ACK; ret = %d\n", ret);
#endif
                    ret = ERRNO_TRANSMIT;
                    goto bail_main;
                }

#ifdef DEBUG
		       	fprintf(stderr, 
		       		"[D] main | just sent PKT_OTP_ACK; it starts with: 0x%02x 0x%02x\n", 
		       		PKT_OTP_ACK[0], PKT_OTP_ACK[1]);
#endif

        		break;

        	////
        	// STATE_MSG
        	////

        	case STATE_MSG:

        		// If we get the CONNTERM message, reset state to OTP.
        		if (0 == memcmp((const char *)&rx_buf, (const char *)&PKT_CONNTERM, sizeof(PKT_CONNTERM)-1)) {
#ifdef DEBUG
	            	fprintf(stderr, 
	            		"[D] main | STATE_MSG: got CONNTERM; resetting to STATE_OTP\n");
#endif 
        			state = STATE_OTP;
        			expected_rx_bytes = OTP_SZ;
        			continue; // Get the next packet.
        		}

        		// Error message; we should be generating not receive()ing them.
        		// This makes the protocol *slightly* more complicated.  In such 
        		// cases, we just mirror the error message back to the CRS.
        		if (0xFF == rx_buf[0]) {
#ifdef DEBUG
            		fprintf(stderr, "[D] main | got error msg; reflecting...\n");
#endif    			
            		if (SUCCESS != (ret = transmit_all(STDOUT, &rx_buf, sizeof(rx_buf)-1, NULL))) { 
#ifdef DEBUG
	                    fprintf(stderr, "[E] main | during error reflection transmit ()\n");
#endif
	            	}

#ifdef DEBUG
			       	fprintf(stderr, 
			       		"[D] main | just sent rx_buf; it starts with: 0x%02x 0x%02x\n", 
			       		rx_buf[0], rx_buf[1]);
#endif

	            	continue; // Get the next packet.
        		}

        		// Okay, so we have a packet that is neither CONNTERM nor ERROR.
        		// We actually have to handle this one.
	        	rx_index = 0;
	        	ct_index = 0;
	        	memset(ct, 0, sizeof(ct));
	        	// Base condition: entire message is treated as fragments.
	        	defrag(BUF_RX_SZ); 

	        	// defrag() will have the affect of dropping all bytes with 
	        	// fragment flags.  A discussion on the implications of this 
	        	// algorithmic reduction can be found at the top of this file.

	        	// Once they're dropped, we need to XOR with OTP (looped over).
	        	for (i = 0; i < ct_index; i++) {
	        		ct[i] = ct[i] ^ (((unsigned char **)ppotp)[0])[i % OTP_SZ];
	        	}

	        	tx_bytes = 0;
	            if (SUCCESS != (ret = transmit_all(STDOUT, &ct, ct_index, &tx_bytes))) { 
#ifdef DEBUG
                    fprintf(stderr, "[E] main | failed transmitting response to MSG\n");
#endif
                    ret = ERRNO_TRANSMIT;
                    goto bail_main;
	            }

#ifdef DEBUG
		       	fprintf(stderr, 
		       		"[D] main | just sent XOR'ed ct (%03d bytes); it starts with: 0x%02x 0x%02x 0x%02x 0x%02x\n", 
		       		tx_bytes, ct[0], ct[1], ct[2], ct[3]);
#endif

        		break; // STATE_MSG

        	////
        	// INVALID STATE
        	////
        	// Should never happen.
        	default:
#ifdef DEBUG
            	fprintf(stderr, "[E] main | invalid state; bailing...\n");
#endif
            	ret = ERRNO_INVALID_STATE;
            	goto bail_main;
            	break;
        }
    }

bail_main:
    return ret;
}  
