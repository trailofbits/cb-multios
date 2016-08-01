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

#include <libcgc.h>
#include "libc.h"
#include "service.h"

uint32_t outstanding = 0;
lms_sess_t *head = NULL;

lms_sess_t *find_session(uint32_t sid) {
    lms_sess_t *cur = head;
    while (cur) {
        if (cur->sid == sid)
            return cur;
        cur = cur->next;
    }
    return NULL;
}

lms_sess_t *new_session(lms_msg_t *msg) {
    lms_sess_t *new_s = NULL;

    if (!(new_s = calloc(sizeof(lms_sess_t)))) {
       TERM(LMSERR,90); 
    }

    if (!(new_s->received = calloc(sizeof(uint8_t)*msg->count))) {
       TERM(LMSERR,90); 
    }

    new_s->sid = msg->sid;
    new_s->count = msg->count;
    return new_s;
}

lms_sess_t *add_session(lms_msg_t *msg) {
    lms_sess_t *cur = head;

    if (!head) {
        head = new_session(msg);
        return head;
    }

    cur->next = new_session(msg);
    return cur->next;
}

void delete_session(uint32_t sid) {
    /*
     * Our vulnerable function. If unpatched, we leave a dangling pointer in head.
     */
    lms_sess_t *cur = head;
    lms_msg_list_t *list, *listnext = NULL;
    lms_sess_t *last = NULL;

    while (cur) {
        if (cur->sid == sid) {
            #ifdef PATCHED
            if (cur == head) 
                head = cur->next;
            #endif
            //remove from list
            if (last)
                last->next = cur->next;

            //free all our messages and the list
            listnext = cur->head;
            while ((list = listnext)) {
                listnext = list->next;
                free(list->msg->data);
                free(list->msg);
                free(list);
            }

            //free the session
            free(cur->received);
            free(cur);
            outstanding--;
            return;
        }
        #ifdef PATCHED
        last = cur;
        #endif
        cur = cur->next;
    }   
}

uint8_t *add_msg(lms_msg_t *msg, lms_sess_t *sess) {
    lms_msg_list_t *cur = NULL;
    lms_msg_list_t *node = NULL;
    uint8_t *res = NULL;
    uint32_t i,idx = 0;

#ifndef PATCHED
    if (msg->mid > sess->count || sess->received[msg->mid]) {
#else
    if (msg->mid >= sess->count || sess->received[msg->mid]) {
#endif
        free(msg->data);
        free(msg);
        return NULL;
    }

    if (!(node = calloc(sizeof(lms_msg_list_t)))) {
       TERM(LMSERR,90); 
    }
    
    node->msg = msg;
    node->next = NULL;

    if (!sess->head) {
        sess->head = node;
    } else {
        cur = sess->head;

        while (cur->next)
            cur = cur->next;

        cur->next = node;
    }

    sess->received[msg->mid] = 1;
    sess->total += msg->size;

    //check if session is complete
    //
    for (i=0; i < sess->count && sess->received[i]; i++);

    if (i == sess->count) {
        //reassembly time
        if (!(res = calloc(sess->total))) {
            TERM(LMSERR,95);
        }

        for (i=0; i < sess->count; i++) {
            cur = sess->head;
            while (cur) {
                if (cur->msg->mid == i) {
                    memcpy(res+idx,cur->msg->data,cur->msg->size);
                    idx += cur->msg->size;
                    break;
                }
                cur = cur->next;
            }
        }
        return res;
    } else {
        return NULL;
    }
}

void process_msg(lms_msg_t *msg) {
    lms_sess_t *sess = NULL;
    uint8_t *res;

    if (!(sess = find_session(msg->sid))) {
        sess = add_session(msg);
    }

    if ((res = add_msg(msg, sess))) {
        SSEND(sess->total,(char *)res);
        free(res);
        delete_session(sess->sid);
    }

}

lms_msg_t *recv_msg() {
    lms_msg_t *msg;

    if (!(msg = calloc(sizeof(lms_msg_t)))) {
        TERM(LMSERR,93);
    }

    RECV(sizeof(lms_msg_t)-sizeof(uint8_t*),(char *)msg);

    if (msg->size < 1 || msg->size > MAX_LMS_SIZE) {
        TERM(LMSERR,91);
    }

    if (!(msg->data = calloc(msg->size))) {
        TERM(LMSERR,94);
    }

    RECV(msg->size,(char *)msg->data);

    return msg;
}

bool check_number(tel_num_t *n1, tel_num_t *n2) {
    //intentionally silly check to force the use of bitfields
    return n1->d0 == n2->d0 && n1->d1 == n2->d1 && n1->d2 == n2->d2 && n1->d3 == n2->d3 &&
            n1->d4 == n2->d4 && n1->d5 == n2->d5 && n1->d6 == n2->d6 &&
            n1->d7 == n2->d7 && n1->d8 == n2->d8 && n1->d9 == n2->d9 &&
            n1->d10 == n2->d10 && n1->d11 == n2->d11 && n1->d12 == n2->d12 &&
            n1->d13 == n2->d13 && n1->d14 == n2->d14;
}
int main(void) {
    lms_msg_t *msg = NULL; 
    tel_num_t pnum = {1,3,3,7,1,3,3,7,0,0,0,0,0,0,3};

    msg = recv_msg();
    outstanding = msg->to.outstanding;
    do {
        //only accept packets to us
        if (check_number(&msg->to, &pnum)) {
            process_msg(msg);
        }
    } while (outstanding && (msg = recv_msg()));

    return 0;
}
