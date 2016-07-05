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
#include <stdlib.h>
#include <string.h>

#include "session.h"

#define PSM_CONTROL 0x1011
#define PSM_INTERRUPT 0x1013

#define CONTROL_USERDATA ((void *)0)
#define INTERRUPT_USERDATA ((void *)1)

static unsigned char g_protocol = 0;
static int g_incoming_report_type = -1;
static unsigned char g_incoming_report[600];

int main();

static void send_data(void *channel, unsigned int type, unsigned int length, unsigned char *data)
{
    unsigned char *hdrdata = malloc(length + 1);
    hdrdata[0] = (10 << 4) | type;
    memcpy(&hdrdata[1], data, length);
    session_send(channel, length+1, hdrdata);
    free(hdrdata);
}

static void send_handshake(void *channel, unsigned int result)
{
    unsigned char hdr = result;
    session_send(channel, 1, &hdr);
}

static void send_report(void *channel)
{
    unsigned char data[800];
    size_t bytes;
    random(data, sizeof(data), &bytes);
    send_data(channel, 1, g_protocol == 0 ? 200 : 700, data);
}

static void handle_control_packet(void *channel, unsigned int length, unsigned char *data)
{
    if (length < 1)
        return;

    unsigned char type = data[0] >> 4, param = data[0] & 0xf;

    if (g_incoming_report_type != -1 && type != 10)
    {
        g_incoming_report_type = -1;
        send_handshake(channel, 1);
        return;
    }

    switch (type)
    {
    case 1: // CONTROL
        if (param == 5) // UNPLUG
            exit(0);
        break;
    case 4: // GET REPORT
        if (param == 1)
            send_report(channel);
        else if (param == 2)
            send_data(channel, 2, sizeof(g_incoming_report), g_incoming_report);
        else
            send_handshake(channel, 4);
        break;
    case 5: // SET REPORT
        if (param == 2)
            g_incoming_report_type = 2;
        else
            send_handshake(channel, 4);
        break;
    case 6: // GET PROTOCOL
        send_data(channel, 0, 1, &g_protocol);
        break;
    case 7: // SET PROTOCOL
        g_protocol = param & 1;
        send_handshake(channel, 0);
        break;
    case 10: // DATA
        if (g_incoming_report_type == -1)
            send_handshake(channel, 1);
        else
        {
            if (length > 1)
                memcpy(g_incoming_report, data+1, length-1 > sizeof(g_incoming_report) ? sizeof(g_incoming_report) : length-1);
            send_handshake(channel, 0);
            g_incoming_report_type = -1;
        }
        break;
    case 11: // INTEGRITY CHECK
        send_data(channel, 0, 0x35, (unsigned char *)main);
        break;
    default:
        send_handshake(channel, 3);
        break;
    }
    return;
}

static void handle_event(void *channel, void *userdata, event_t *evt)
{
    if (userdata == CONTROL_USERDATA)
    {
        if (evt->type == RX_EVENT)
        {
            handle_control_packet(channel, evt->rx.length, evt->rx.data);
        }
        else if (evt->type == DISCONNECT_EVENT)
        {
            // XXX clear state
        }
    }
}

static void handle_control_connect(void *channel)
{
    session_register_userdata(channel, CONTROL_USERDATA);
    session_register_events(channel, handle_event);
}

static void handle_interrupt_connect(void *channel)
{
    session_register_userdata(channel, INTERRUPT_USERDATA);
    session_register_events(channel, handle_event);
}

int main()
{
    session_register_psm(PSM_CONTROL, handle_control_connect);
    session_register_psm(PSM_INTERRUPT, handle_interrupt_connect);
    session_loop();
    return 0;
}

