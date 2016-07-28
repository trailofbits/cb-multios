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
 * C++ static destructor handling.
 */

extern "C" {
#include "libcgc.h"
#include "cgc_malloc.h"
};

#undef NULL
#define NULL 0L

extern "C" {
	int __cxa_atexit(void (*func)(void *), void *, void *);
	void *__dso_handle;
};

struct __cxa_exits {
	struct __cxa_exits *next;
	void (*func)(void *);
	void *arg;
	void *dso;
} *__cxa_exits;

/*
 * a function with this signature is required for static destructors to
 * work properly
 */
int
__cxa_atexit(void (*func)(void *), void *arg, void *dso) {
	struct __cxa_exits *p, *q;

	q = (struct __cxa_exits *)malloc(sizeof(*q));
	if (q == NULL)
		return (-1);
	q->next = NULL;
	q->func = func;
	q->arg = arg;
	q->dso = dso;

	if (__cxa_exits == NULL)
		__cxa_exits = q;
	else {
		for (p = __cxa_exits; p->next != NULL; p = p->next)
			/* EMPTY */;
		p->next = q;
	}

	return (0);
}

void
terminate(int ex) {
	struct __cxa_exits *p;
	void (*fn)(void *), *arg;

	while (__cxa_exits != NULL) {
		p = __cxa_exits->next;
		fn = __cxa_exits->func;
		arg = __cxa_exits->arg;
		free(__cxa_exits);
		__cxa_exits = p;
		fn(arg);
	}
	_terminate(ex);
}
