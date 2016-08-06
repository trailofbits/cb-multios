/*
 * Copyright (c) 2014 Jason L. Wright (jason@thought.net)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * C++ constructor handling
 */

extern "C" {
#include "libcgc.h"
#include "cgc_libc.h"
};

#define __hidden __attribute__((__visibility__("hidden")))

extern "C" {
	extern void (*__init_array_start[])(int, char **, char **) __hidden;
	extern void (*__init_array_end[])(int, char **, char **) __hidden;
};

/*
 * call static constructors
 */
void
call_inits(void) {
	size_t asize, n;
	void (*fn)(int, char **, char **);

	printf("ctors called...\n");
	for (asize = __init_array_end - __init_array_start, n = 0;
	     n < asize; n++) {
		fn = __init_array_start[n];
		if (fn && (long)fn != 1)
			fn(0, (char **)NULL, (char **)NULL);
	}
}
