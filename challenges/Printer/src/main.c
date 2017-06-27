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

#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_readuntil.h"
#include "cgc_printer.h"

#define NUM_PRINTERS 10

printer_t *cgc_printers = NULL;

printer_t* cgc_find_printer(char *queue)
{
    int i;
    for (i = 0; i < NUM_PRINTERS; ++i)
    {
        if (cgc_strcmp(cgc_printers[i].queue, queue) == 0)
            return &cgc_printers[i];
    }
    return NULL;
}

void cgc_set_name(printer_t *printer, int index)
{
    static const int name_len = 32;
    static const unsigned char *secrets = (void *)0x4347C000;
    for (unsigned int i = 0; i < name_len; i++)
    {
        printer->queue[i] = 0x41 + (secrets[i + index * name_len] & 0x3f);
    }
    printer->queue[name_len] = 0;
}

int main(int cgc_argc, char *cgc_argv[])
{
    int i, recv_mode = 0;
    char buf[2048];
    char *tmp, *queue;
    printer_t *printer = NULL;

    /* Initialize printers */
    cgc_printers = (printer_t *) cgc_malloc(NUM_PRINTERS * sizeof(printer_t));
    cgc_memset(cgc_printers, 0, NUM_PRINTERS * sizeof(printer_t));
    for (i = 0; i < NUM_PRINTERS; ++i)
    {
        if (i == 0)
            cgc_strcpy(cgc_printers[i].queue, "DEFAULT");
        else
            cgc_set_name(&cgc_printers[i], i);
        cgc_printers[i].state = PS_IDLE;
        cgc_printers[i].tick_func = cgc_printer_tick;
        cgc_printers[i].self = &cgc_printers[i];
    }

    /* Process commands */
    while (cgc_read_until(STDIN, buf, sizeof(buf), '\n') > 0)
    {
        switch (buf[0])
        {
            case 0:
                if (recv_mode)
                    recv_mode = 0;
                cgc_transmit(STDOUT, "\x00", 1, NULL);
                break;
            case 1:
                if (recv_mode)
                {
                    if (cgc_cmd_abort_job(printer) == 0)
                    {
                        cgc_transmit(STDOUT, "\x00", 1, NULL);
                        break;
                    }
                    cgc_transmit(STDOUT, "\xFF", 1, NULL);
                    break;
                }
                else
                {
                    printer = cgc_find_printer(&buf[1]);
                    if (printer)
                    {
                        if (cgc_cmd_print_jobs(printer) == 0)
                        {
                            cgc_transmit(STDOUT, "\x00", 1, NULL);
                            break;
                        }
                    }
                    cgc_transmit(STDOUT, "\xFF", 1, NULL);
                }
                break;
            case 2:
                if (recv_mode)
                {
                    if (cgc_cmd_recv_control_file(printer, &buf[1]) == 0)
                    {
                        cgc_transmit(STDOUT, "\x00", 1, NULL);
                        break;
                    }
                    cgc_transmit(STDOUT, "\xFF", 1, NULL);
                    break;
                }
                else
                {
                    printer = cgc_find_printer(&buf[1]);
                    if (printer)
                    {
                        if (cgc_cmd_recv_job(printer) == 0)
                        {
                            recv_mode = 1;
                            cgc_transmit(STDOUT, "\x00", 1, NULL);
                            break;
                        }
                    }
                    cgc_transmit(STDOUT, "\xFF", 1, NULL);
                }
                break;
            case 3:
                if (recv_mode)
                {
                    if (cgc_cmd_recv_data_file(printer, &buf[1]) == 0)
                    {
                        cgc_transmit(STDOUT, "\x00", 1, NULL);
                        break;
                    }
                    cgc_transmit(STDOUT, "\xFF", 1, NULL);
                    break;
                }
            case 4:
                if (recv_mode)
                {
                    cgc_transmit(STDOUT, "\xFF", 1, NULL);
                    break;
                }
                tmp = &buf[1];
                queue = cgc_strsep(&tmp, " ");
                printer = cgc_find_printer(queue);
                if (printer)
                {
                    if (cgc_cmd_send_queue_state(printer) == 0)
                    {
                        cgc_transmit(STDOUT, "\x00", 1, NULL);
                        break;
                    }
                }
                cgc_transmit(STDOUT, "\xFF", 1, NULL);
                break;
            case 5:
                if (recv_mode)
                {
                    cgc_transmit(STDOUT, "\xFF", 1, NULL);
                    break;
                }
                tmp = &buf[1];
                queue = cgc_strsep(&tmp, " ");
                printer = cgc_find_printer(queue);
                if (printer)
                {
                    char *agent = cgc_strsep(&tmp, " ");
                    unsigned int job_id = 0;
                    if (cgc_strlen(tmp) > 0)
                        job_id = cgc_strtoul(tmp, NULL, 10);
                    if (cgc_cmd_remove_jobs(printer, agent, job_id) == 0)
                    {
                        cgc_transmit(STDOUT, "\x00", 1, NULL);
                        break;
                    }
                }
                cgc_transmit(STDOUT, "\xFF", 1, NULL);
                break;
            case 7:
                cgc_exit(0);
                break;
            default:
                cgc_transmit(STDOUT, "\xFF", 1, NULL);
                break;
        }

        /* Tick */
        for (i = 0; i < NUM_PRINTERS; ++i)
        {
            cgc_printers[i].tick_func(cgc_printers[i].self);
        }
    }

    return 0;
}
