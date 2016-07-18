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

#include <libcgc.h>
#include <stdlib.h>
#include <string.h>

#include "readuntil.h"
#include "printer.h"

#define NUM_PRINTERS 10

printer_t *printers = NULL;

printer_t* find_printer(char *queue)
{
    int i;
    for (i = 0; i < NUM_PRINTERS; ++i)
    {
        if (strcmp(printers[i].queue, queue) == 0)
            return &printers[i];
    }
    return NULL;
}

void set_name(printer_t *printer, int index)
{
    static const int name_len = 32;
    static const unsigned char *secrets = (void *)0x4347C000;
    for (unsigned int i = 0; i < name_len; i++)
    {
        printer->queue[i] = 0x41 + (secrets[i + index * name_len] & 0x3f);
    }
    printer->queue[name_len] = 0;
}

int main()
{
    int i, recv_mode = 0;
    char buf[2048];
    char *tmp, *queue;
    printer_t *printer = NULL;

    /* Initialize printers */
    printers = (printer_t *) malloc(NUM_PRINTERS * sizeof(printer_t));
    memset(printers, 0, NUM_PRINTERS * sizeof(printer_t));
    for (i = 0; i < NUM_PRINTERS; ++i)
    {
        if (i == 0)
            strcpy(printers[i].queue, "DEFAULT");
        else
            set_name(&printers[i], i);
        printers[i].state = PS_IDLE;
        printers[i].tick_func = printer_tick;
        printers[i].self = &printers[i];
    }

    /* Process commands */
    while (read_until(STDIN, buf, sizeof(buf), '\n') > 0)
    {
        switch (buf[0])
        {
            case 0:
                if (recv_mode)
                    recv_mode = 0;
                transmit(STDOUT, "\x00", 1, NULL);
                break;
            case 1:
                if (recv_mode)
                {
                    if (cmd_abort_job(printer) == 0)
                    {
                        transmit(STDOUT, "\x00", 1, NULL);
                        break;
                    }
                    transmit(STDOUT, "\xFF", 1, NULL);
                    break;
                }
                else
                {
                    printer = find_printer(&buf[1]);
                    if (printer)
                    {
                        if (cmd_print_jobs(printer) == 0)
                        {
                            transmit(STDOUT, "\x00", 1, NULL);
                            break;
                        }
                    }
                    transmit(STDOUT, "\xFF", 1, NULL);
                }
                break;
            case 2:
                if (recv_mode)
                {
                    if (cmd_recv_control_file(printer, &buf[1]) == 0)
                    {
                        transmit(STDOUT, "\x00", 1, NULL);
                        break;
                    }
                    transmit(STDOUT, "\xFF", 1, NULL);
                    break;
                }
                else
                {
                    printer = find_printer(&buf[1]);
                    if (printer)
                    {
                        if (cmd_recv_job(printer) == 0)
                        {
                            recv_mode = 1;
                            transmit(STDOUT, "\x00", 1, NULL);
                            break;
                        }
                    }
                    transmit(STDOUT, "\xFF", 1, NULL);
                }
                break;
            case 3:
                if (recv_mode)
                {
                    if (cmd_recv_data_file(printer, &buf[1]) == 0)
                    {
                        transmit(STDOUT, "\x00", 1, NULL);
                        break;
                    }
                    transmit(STDOUT, "\xFF", 1, NULL);
                    break;
                }
            case 4:
                if (recv_mode)
                {
                    transmit(STDOUT, "\xFF", 1, NULL);
                    break;
                }
                tmp = &buf[1];
                queue = strsep(&tmp, " ");
                printer = find_printer(queue);
                if (printer)
                {
                    if (cmd_send_queue_state(printer) == 0)
                    {
                        transmit(STDOUT, "\x00", 1, NULL);
                        break;
                    }
                }
                transmit(STDOUT, "\xFF", 1, NULL);
                break;
            case 5:
                if (recv_mode)
                {
                    transmit(STDOUT, "\xFF", 1, NULL);
                    break;
                }
                tmp = &buf[1];
                queue = strsep(&tmp, " ");
                printer = find_printer(queue);
                if (printer)
                {
                    char *agent = strsep(&tmp, " ");
                    unsigned int job_id = 0;
                    if (strlen(tmp) > 0)
                        job_id = strtoul(tmp, NULL, 10);
                    if (cmd_remove_jobs(printer, agent, job_id) == 0)
                    {
                        transmit(STDOUT, "\x00", 1, NULL);
                        break;
                    }
                }
                transmit(STDOUT, "\xFF", 1, NULL);
                break;
            case 7:
                exit(0);
                break;
            default:
                transmit(STDOUT, "\xFF", 1, NULL);
                break;
        }

        /* Tick */
        for (i = 0; i < NUM_PRINTERS; ++i)
        {
            printers[i].tick_func(printers[i].self);
        }
    }

    return 0;
}
