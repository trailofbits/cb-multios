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
#include "cgc_stdint.h"
#include "cgc_errno.h"
#include "cgc_libc.h"
#include "cgc_memcmp.h"
#include "cgc_memcpy.h"

#include "cgc_comms.h"


void cgc_session_append(Session **s_list, Session *s) {
	Session *tmp = *s_list;
	Session *prev = *s_list;
	Session *new = cgc_calloc(sizeof(Session));
	MALLOC_OK(new);
	cgc_memcpy(new, s, sizeof(Session) - 2*sizeof(char *));

	if (NULL == tmp) {
		*s_list = new;
	} else {
		while (NULL != tmp) {
			prev = tmp;
			tmp = tmp->next;
		}
		prev->next = new;
	}
}

Session *cgc_session_remove(Session **s_list, Session *s) {
	Session *tmp = *s_list;
	Session *prev = *s_list;
	while (NULL != tmp) {

	    if (0 == cgc_memcmp(s->login.key, tmp->login.key, sizeof(tmp->login.key))) {

	    	if (tmp == prev) { // first node in list
	    		*s_list = tmp->next;
	    	} else {
	    		prev->next = tmp->next;
	    	}
	    	
			return tmp;
	    }

		prev = tmp;
		tmp = tmp->next;
	}

	return NULL;
}

Session *cgc_session_get_by_username(Session *s_list, Session *s) {
    Session *s_result = NULL;
    Session *tmp = s_list;
	while (NULL != tmp) {
	    if (0 == cgc_memcmp(s->login.username, tmp->login.username, sizeof(tmp->login.username))) {
	    	s_result = tmp;
			break;
	    }

		tmp = tmp->next;
    }
    return s_result;
}

