/*
 * Copyright (c) 2014 Kaprica Security, Inc.
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
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_session.h"

#define PSM_CONTROL 0x1011
#define PSM_INTERRUPT 0x1013

#define CONTROL_USERDATA ((void *)0)
#define INTERRUPT_USERDATA ((void *)1)

static unsigned char g_protocol = 0;
static int g_incoming_report_type = -1;
static unsigned char g_incoming_report[600];

int main(int cgc_argc, char *cgc_argv[]);

static void cgc_send_data(void *channel, unsigned int type, unsigned int length, unsigned char *data)
{
    unsigned char *hdrdata = cgc_malloc(length + 1);
    hdrdata[0] = (10 << 4) | type;
    cgc_memcpy(&hdrdata[1], data, length);
    cgc_session_send(channel, length+1, hdrdata);
    cgc_free(hdrdata);
}

static void cgc_send_handshake(void *channel, unsigned int result)
{
    unsigned char hdr = result;
    cgc_session_send(channel, 1, &hdr);
}

static void cgc_send_report(void *channel)
{
    unsigned char data[800];
    cgc_size_t bytes;
    cgc_random(data, sizeof(data), &bytes);
    cgc_send_data(channel, 1, g_protocol == 0 ? 200 : 700, data);
}

static void cgc_handle_control_packet(void *channel, unsigned int length, unsigned char *data)
{
    if (length < 1)
        return;

    unsigned char type = data[0] >> 4, param = data[0] & 0xf;

    if (g_incoming_report_type != -1 && type != 10)
    {
        g_incoming_report_type = -1;
        cgc_send_handshake(channel, 1);
        return;
    }

    switch (type)
    {
    case 1: // CONTROL
        if (param == 5) // UNPLUG
            cgc_exit(0);
        break;
    case 4: // GET REPORT
        if (param == 1)
            cgc_send_report(channel);
        else if (param == 2)
            cgc_send_data(channel, 2, sizeof(g_incoming_report), g_incoming_report);
        else
            cgc_send_handshake(channel, 4);
        break;
    case 5: // SET REPORT
        if (param == 2)
            g_incoming_report_type = 2;
        else
            cgc_send_handshake(channel, 4);
        break;
    case 6: // GET PROTOCOL
        cgc_send_data(channel, 0, 1, &g_protocol);
        break;
    case 7: // SET PROTOCOL
        g_protocol = param & 1;
        cgc_send_handshake(channel, 0);
        break;
    case 10: // DATA
        if (g_incoming_report_type == -1)
            cgc_send_handshake(channel, 1);
        else
        {
            if (length > 1)
                cgc_memcpy(g_incoming_report, data+1, length-1 > sizeof(g_incoming_report) ? sizeof(g_incoming_report) : length-1);
            cgc_send_handshake(channel, 0);
            g_incoming_report_type = -1;
        }
        break;
    case 11: // INTEGRITY CHECK
        cgc_send_data(channel, 0, 0x35, (unsigned char *)main);
        break;
    default:
        cgc_send_handshake(channel, 3);
        break;
    }
    return;
}

static void cgc_handle_event(void *channel, void *userdata, event_t *evt)
{
    if (userdata == CONTROL_USERDATA)
    {
        if (evt->type == RX_EVENT)
        {
            cgc_handle_control_packet(channel, evt->rx.length, evt->rx.data);
        }
        else if (evt->type == DISCONNECT_EVENT)
        {
            // XXX clear state
        }
    }
}

static void cgc_handle_control_connect(void *channel)
{
    cgc_session_register_userdata(channel, CONTROL_USERDATA);
    cgc_session_register_events(channel, cgc_handle_event);
}

static void cgc_handle_interrupt_connect(void *channel)
{
    cgc_session_register_userdata(channel, INTERRUPT_USERDATA);
    cgc_session_register_events(channel, cgc_handle_event);
}

int main(int cgc_argc, char *cgc_argv[])
{
    cgc_session_register_psm(PSM_CONTROL, cgc_handle_control_connect);
    cgc_session_register_psm(PSM_INTERRUPT, cgc_handle_interrupt_connect);
    cgc_session_loop();
    return 0;
}

