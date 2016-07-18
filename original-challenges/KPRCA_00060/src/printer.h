/*
 * Copyright (c) 2015 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef PRINTER_H
#define PRINTER_H

#define NUM_MAX_JOBS    1000

enum pstate_t {
    PS_IDLE,
    PS_QUEUED,
    PS_RECEIVING,
    PS_PRINTING
};

enum jstate_t {
    JS_INVALID,
    JS_WAITING,
    JS_QUEUED,
    JS_PRINTING
};

typedef struct job {
    enum jstate_t state;
    char *data;
    unsigned int data_len;
    unsigned int ticks;

    /* Configuration */
    char cls[32];
    char host[32];
    unsigned int indent;
    char name[100];
    char banner_flag;
    char banner_user[32];
    char owner[32];
    char mail_flag;
    char mail_user[32];
    char source[131];
    unsigned int device_num;
    unsigned int inode_num;
    char title[80];
    unsigned int width;
    char format;
} job_t;

typedef struct printer {
    enum pstate_t state;
    char queue[256];
    job_t jobs[NUM_MAX_JOBS];
    void (*tick_func) (struct printer *);
    struct printer *self;
} printer_t;

int cmd_print_jobs(printer_t *printer);
int cmd_recv_job(printer_t *printer);
int cmd_abort_job(printer_t *printer);
int cmd_recv_control_file(printer_t *printer, char *buf);
int cmd_recv_data_file(printer_t *printer, char *buf);
int cmd_send_queue_state(printer_t *printer);
int cmd_remove_jobs(printer_t *printer, char *agent, unsigned int job_id);

void printer_tick(printer_t *printer);

void print_ws(int n);
char* jstate_str(enum jstate_t s);

#endif
