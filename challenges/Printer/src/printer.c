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

#include "cgc_stdio.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_printer.h"
#include "cgc_readuntil.h"

int cgc_cmd_print_jobs(printer_t *printer)
{
    int i;
    job_t *jobs = printer->jobs;

    for (i = 0; i < NUM_MAX_JOBS; ++i)
    {
        if (jobs[i].state == JS_QUEUED)
        {
            jobs[i].state = JS_PRINTING;
            if (printer->state != PS_PRINTING)
                printer->state = PS_PRINTING;
        }
    }

    return 0;
}

int cgc_cmd_recv_job(printer_t *printer)
{
    if (printer->state == PS_PRINTING)
        return -1;
    printer->state = PS_RECEIVING;
    return 0;
}

int cgc_cmd_abort_job(printer_t *printer)
{
    int i, busy = 0;
    job_t *jobs = printer->jobs;
    for (i = 0; i < NUM_MAX_JOBS; ++i)
    {
        if (jobs[i].state == JS_WAITING || jobs[i].state == JS_QUEUED)
        {
            if (jobs[i].data)
                cgc_free(jobs[i].data);
            cgc_memset(&jobs[i], 0, sizeof(job_t));
            jobs[i].state = JS_INVALID;
        }
        else if (jobs[i].state == JS_PRINTING)
            busy = 1;
    }

    if (!busy)
        printer->state = PS_IDLE;

    return 0;
}

int cgc_cmd_recv_control_file(printer_t *printer, char *buf)
{
    job_t *job;
    unsigned int count, job_id, nread, n;
    char tmp[4];
    char *count_s = NULL, *name = NULL, *host = NULL, *line = NULL;
    char control[1024], *ptr, *device_s, *c;

    count_s = cgc_strsep(&buf, " ");
    name = buf;

    if (!count_s || !name)
        return -1;

    /* Count */
    count = cgc_strtoul(count_s, NULL, 10);
    if (count > sizeof(control))
        return -1;

    /* "cfA" */
    if (cgc_strncmp(name, "cfA", 3) != 0)
        return -1;

    /* Job ID */
    cgc_strncpy(tmp, name + 3, 3);
    tmp[3] = '\0';
    job_id = cgc_strtoul(tmp, NULL, 10);
    if (job_id > 999)
        return -1;

    /* Host */
    host = &buf[6];

    /* Create or update a job */
    job = &printer->jobs[job_id];
    job->width = 132;
    job->ticks = 10;
    if (cgc_read_n(STDIN, control, count) <= 0)
        return -1;
    c = control;
    while ((line = cgc_strsep(&c, "\n")) && c)
    {
        switch (line[0])
        {
            case 'C':
                if (cgc_strlen(line) - 1 < sizeof(job->cls))
                    cgc_strcpy(job->cls, &line[1]);
                break;
            case 'H':
                if (cgc_strlen(line) - 1 < sizeof(job->host))
                    cgc_strcpy(job->host, &line[1]);
                break;
            case 'I':
                job->indent = cgc_strtoul(&line[1], NULL, 10);
                if (job->indent >= job->width)
                    job->indent = 0;
                break;
            case 'J':
                if (cgc_strlen(line) - 1 < sizeof(job->name))
                    cgc_strcpy(job->name, &line[1]);
                break;
            case 'L':
                if (cgc_strlen(line) - 1 < sizeof(job->banner_user))
                    cgc_strcpy(job->banner_user, &line[1]);
                job->banner_flag = 1;
                break;
            case 'M':
                if (cgc_strlen(line) - 1 < sizeof(job->mail_user))
                    cgc_strcpy(job->mail_user, &line[1]);
                job->mail_flag = 1;
                break;
            case 'N':
                if (cgc_strlen(line) - 1 < sizeof(job->source))
                    cgc_strcpy(job->source, &line[1]);
                break;
            case 'P':
                if (cgc_strlen(line) - 1 < sizeof(job->owner))
                    cgc_strcpy(job->owner, &line[1]);
                break;
            case 'S':
                ptr = line;
                device_s = cgc_strsep(&ptr, " ");
                if (device_s && ptr && cgc_strlen(device_s) > 1 && cgc_strlen(ptr) > 1)
                {
                    job->device_num = cgc_strtoul(&device_s[1], NULL, 10);
                    job->inode_num = cgc_strtoul(ptr, NULL, 10);
                }
                break;
            case 'T':
#ifdef PATCHED_1
                if (cgc_strlen(line) - 1 < sizeof(job->title))
#endif
                    cgc_strcpy(job->title, &line[1]);
                break;
            case 'U':
                /* Not implemented */
                break;
            case 'W':
                job->width = cgc_strtoul(&line[1], NULL, 10);
                break;
            case 'c': case 'd': case 'f': case 'g':
            case 'l': case 'n': case 'o': case 'p':
            case 'r':
                job->format = line[0];
                break;
            default:
                break;
        }
    }

    if (cgc_strlen(job->host) < 1 || cgc_strlen(job->owner) < 1)
        return -1;

    if (job->state == JS_INVALID)
    {
        /* No data or control; New */
        job->state = JS_WAITING;
    }
    else if (job->state == JS_WAITING)
    {
        /* Data received, waiting for control */
        job->state = JS_QUEUED;
    }
    else
        return -1;

    return 0;
}

int cgc_cmd_recv_data_file(printer_t *printer, char *buf)
{
    unsigned int count = 0, job_id;
    char tmp[4];
    char *count_s = NULL, *name = NULL, *data = NULL, *host;
    job_t *job;

    count_s = cgc_strsep(&buf, " ");
    name = buf;

    if (!count_s || !name)
        return -1;

    /* Count */
    count = cgc_strtoul(count_s, NULL, 10);

    /* "dfA" */
    if (cgc_strncmp(name, "dfA", 3) != 0)
        return -1;

    /* Job ID */
    cgc_strncpy(tmp, name + 3, 3);
    tmp[3] = '\0';
    job_id = cgc_strtoul(tmp, NULL, 10);
    if (job_id > 999)
        return -1;

    /* Host */
    host = &buf[6];

    /* Data */
    data = cgc_malloc(count + 1);
    cgc_memset(data, 0, count + 1);
    if (cgc_read_n(STDIN, data, count + 1) <= 0 || data[count])
    {
        cgc_free(data);
        return -1;
    }

    job = &printer->jobs[job_id];
    if (job->data)
        cgc_free(job->data);
    job->data = data;
    job->data_len = count;

    if (job->state == JS_INVALID)
    {
        /* No data or control; New */
        job->state = JS_WAITING;
    }
    else if (job->state == JS_WAITING)
    {
        /* Control received, waiting for data */
        job->state = JS_QUEUED;
    }
    else
        return -1;

    return 0;
}

int cgc_cmd_send_queue_state(printer_t *printer)
{
    int i;
    char num[4], buf[1024];
    job_t *jobs = printer->jobs;

    cgc_printf("Queue State for %s\n\n", printer->queue);
    cgc_printf("Owner       Status      Jobname             Job-ID      Size  \n");
    cgc_printf("==============================================================\n");
    for (i = 0; i < NUM_MAX_JOBS; ++i)
    {
        if (jobs[i].state != JS_INVALID)
        {
            cgc_strcpy(buf, jobs[i].owner);
            buf[10] = '\0';
            cgc_printf("%s", buf);
            cgc_print_ws(12 - cgc_strlen(buf));
            cgc_printf("%s", cgc_jstate_str(jobs[i].state));
            cgc_print_ws(12 - cgc_strlen(cgc_jstate_str(jobs[i].state)));
            cgc_strcpy(buf, jobs[i].source);
            buf[18] = '\0';
            cgc_printf("%s", buf);
            cgc_print_ws(20 - cgc_strlen(buf));
            cgc_sprintf(num, "%03d", i);
            cgc_printf("%s", num);
            cgc_print_ws(12 - cgc_strlen(num));
            cgc_printf("%d\n", jobs[i].data_len);
        }
    }
    cgc_printf("\n\n");

    return 0;
}

int cgc_cmd_remove_jobs(printer_t *printer, char *agent, unsigned int job_id)
{
    int i, busy = 0;
    job_t *jobs = printer->jobs;

    if (jobs[job_id].state != JS_INVALID &&
        (cgc_strcmp(jobs[job_id].owner, agent) == 0 ||
         cgc_strcmp(agent, "root") == 0))
    {
        if (jobs[job_id].data)
            cgc_free(jobs[job_id].data);
        cgc_memset(&jobs[job_id], 0, sizeof(job_t));
        jobs[job_id].state = JS_INVALID;
        return 0;
    }

    return -1;

}

void cgc_printer_tick(printer_t *printer)
{
    int i, sum = 0;
    job_t *jobs = printer->jobs;

    if (printer->state != PS_IDLE)
    {
        for (i = 0; i < NUM_MAX_JOBS; ++i)
        {
            if (jobs[i].state == JS_PRINTING)
            {
                jobs[i].ticks--;
                sum += jobs[i].ticks;
                if (jobs[i].ticks == 0)
                {
                    if (jobs[i].data)
                        cgc_free(jobs[i].data);
                    cgc_memset(&jobs[i], 0, sizeof(job_t));
                    jobs[i].state = JS_INVALID;
                }
            }
        }
        if (sum == 0)
            printer->state = PS_IDLE;
    }
}

void cgc_print_ws(int n)
{
    char tmp[n+1];
    int i;
    cgc_memset(tmp, ' ', n);
    tmp[n] = 0;
    cgc_printf(tmp);
}

char* cgc_jstate_str(enum jstate_t s)
{
    switch(s)
    {
        case JS_INVALID:
            return "Invalid";
        case JS_WAITING:
            return "Waiting";
        case JS_QUEUED:
            return "Queued";
        case JS_PRINTING:
            return "Printing";
        default:
            return "Unknown";
    }
}
