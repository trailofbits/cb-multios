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

#include "link.h"
#include "session.h"

typedef struct psm {
    struct psm *next;
    unsigned int id;
    connect_handler_t handler;
} psm_t;

typedef struct {
#define CLOSED 0
#define CONFIG 1
#define OPEN 2
#define WAIT_DISCONNECT 3
    unsigned char state;
#define WAIT_CONFIG 0
#define WAIT_CONFIG_RSP 1
    unsigned char config_state;
    unsigned short local;
    unsigned short remote;
    event_handler_t handler;
    void *userdata;
    unsigned int remote_mtu;
    unsigned int local_mtu;
} channel_t;

static union {
    session_hdr_t hdr;
    unsigned char rawdata[SESSION_MAX_PACKET_SIZE];
} g_current_packet, g_temp_packet;
static channel_t *g_channels[0x10000];
static unsigned int g_dynamic_id = 0x0040;
static psm_t *g_psm_head;
static unsigned char g_config_req_id = 1;

static void _session_send(unsigned short dest_channel, unsigned short length, unsigned char *data)
{
    size_t full_length = length + 4, offset = 0;
    g_temp_packet.hdr.length = length;
    g_temp_packet.hdr.channel = dest_channel;
    memcpy(g_temp_packet.hdr.payload, data, length);

    while (offset < full_length)
    {
        size_t payload_length = full_length - offset;
        if (payload_length > LINK_PAYLOAD_SIZE)
            payload_length = LINK_PAYLOAD_SIZE;
        link_send(offset == 0 ? LINK_CH_START : LINK_CH_CONTINUE, payload_length, &g_temp_packet.rawdata[offset]);
        offset += payload_length;
    }
}

static psm_t *session_find_psm(unsigned int id)
{
    psm_t *psm;
    for (psm = g_psm_head; psm != NULL; psm = psm->next)
        if (psm->id == id)
            return psm;
    return NULL;
}

static channel_t *session_new_channel(unsigned short id)
{
    if (id == 0)
    {
        id = g_dynamic_id++;
        if (id > 0xFFFF)
            return NULL;
    }

    channel_t *ch = malloc(sizeof(channel_t));
    ch->state = CLOSED;
    ch->local = id;
    ch->local_mtu = 672;
    ch->remote_mtu = 672;

    g_channels[id] = ch;
    return ch;
}

static void session_send_reject(unsigned int id, unsigned int reason)
{
    struct __attribute__ ((__packed__)) command_reject {
        control_hdr_t hdr;
        unsigned reason : 16;
        unsigned char data[];
    } rej;
    
    rej.hdr.code = COMMAND_REJECT;
    rej.hdr.id = id;
    rej.hdr.length = sizeof(struct command_reject) - sizeof(control_hdr_t);
    rej.reason = reason;
    _session_send(0x0001, rej.hdr.length + sizeof(control_hdr_t), (unsigned char *)&rej);
}

static void session_send_config(channel_t *ch)
{
    struct __attribute__ ((__packed__)) configuration_request {
        control_hdr_t hdr;
        unsigned remote : 16;
        unsigned flags : 16;
        unsigned char config[];
    } req;

    req.hdr.code = CONFIGURATION_REQUEST;
    req.hdr.id = g_config_req_id;
    req.hdr.length = sizeof(struct configuration_request) - sizeof(control_hdr_t);
    req.remote = ch->remote;
    req.flags = 0;
    _session_send(0x0001, req.hdr.length + sizeof(control_hdr_t), (unsigned char *)&req);

    ch->config_state = WAIT_CONFIG_RSP;
}

static void session_connection_request(command_t *cmd)
{
    struct __attribute__ ((__packed__)) connection_request {
        unsigned psm : 16;
        unsigned remote : 16;
    } *req = (void *)cmd->payload;

    struct __attribute__ ((__packed__)) connection_response {
        control_hdr_t hdr;
        unsigned local : 16;
        unsigned remote : 16;
        unsigned result : 16;
        unsigned status : 16;
    } resp;

    if (cmd->hdr.length != sizeof(struct connection_request))
    {
        session_send_reject(cmd->hdr.id, 0);
        return;
    }

    psm_t *psm = session_find_psm(req->psm);
    if (psm == NULL)
    {
        resp.local = 0;
        resp.remote = req->remote;
        resp.result = 2;
        resp.status = 0;
    }
    else
    {
        channel_t *ch = session_new_channel(0);
        if (ch == NULL)
        {
            session_send_reject(cmd->hdr.id, 0);
            return;
        }
        ch->remote = req->remote;
        ch->state = CONFIG;
        ch->config_state = WAIT_CONFIG;

        if (psm->handler)
            psm->handler(ch);

        resp.local = ch->local;
        resp.remote = ch->remote;
        resp.result = 0;
        resp.status = 0;
    }

    resp.hdr.code = CONNECTION_RESPONSE;
    resp.hdr.id = cmd->hdr.id;
    resp.hdr.length = sizeof(resp) - sizeof(control_hdr_t);
    _session_send(0x0001, resp.hdr.length + sizeof(control_hdr_t), (unsigned char *)&resp);
}

static void session_configuration_request(command_t *cmd)
{
    struct __attribute__ ((__packed__)) configuration_request {
        unsigned local : 16;
        unsigned flags : 16;
        unsigned char config[];
    } *req = (void *)cmd->payload;

    struct __attribute__ ((__packed__)) configuration_response {
        control_hdr_t hdr;
        unsigned remote : 16;
        unsigned flags : 16;
        unsigned result : 16;
        unsigned char config[];
    } *resp;

    unsigned int req_offset = 0, resp_offset = 0;

    if (cmd->hdr.length < sizeof(struct configuration_request))
    {
        session_send_reject(cmd->hdr.id, 0);
        return;
    }

    channel_t *ch = g_channels[req->local];
    if (ch == NULL || ch->state == CLOSED)
    {
        session_send_reject(cmd->hdr.id, 2);
        return;
    }

    if (ch->state == CONFIG && ch->config_state != WAIT_CONFIG)
    {
        session_send_reject(cmd->hdr.id, 2);
        return;
    }

    resp = malloc(sizeof(struct configuration_response) + cmd->hdr.length); // allocate enough for option data
    if (resp == NULL)
    {
        session_send_reject(cmd->hdr.id, 0);
        return;
    }
    resp->hdr.code = CONFIGURATION_RESPONSE;
    resp->hdr.id = cmd->hdr.id;
    resp->remote = ch->remote;
    resp->flags = req->flags & 1;
    resp->result = 0;

    while (req_offset < cmd->hdr.length - sizeof(struct configuration_request))
    {
        unsigned char type, length;
        type = req->config[req_offset];
        length = req->config[req_offset+1];

#ifdef PATCHED
        if (req_offset + length > cmd->hdr.length - sizeof(struct configuration_request))
            break;
#endif

        if ((type & 0x7F) == 0x01)
        {
            if (length == 2)
            {
                unsigned short mtu = *(unsigned short *)&req->config[req_offset+2];
                if (mtu < 48)
                {
                    resp->result = 1;
                    resp->config[resp_offset] = type;
                    resp->config[resp_offset+1] = 2;
                    *(unsigned short*)&resp->config[resp_offset+2] = 48;
                    resp_offset += 4;
                }
                else
                {
                    ch->remote_mtu = mtu;
                    resp->config[resp_offset] = type;
                    resp->config[resp_offset+1] = 2;
                    *(unsigned short*)&resp->config[resp_offset+2] = mtu;
                    resp_offset += 4;
                }
            }
            else
                resp->result = 2;
        }
        else if ((type & 0x80) == 0)
        {
            resp->result = 3;
            resp->config[resp_offset] = type;
            resp->config[resp_offset+1] = length;
            memcpy(&resp->config[resp_offset+2], &req->config[req_offset+2], length);
        }

        req_offset += 2 + length;
    }

    resp->hdr.length = sizeof(*resp) - sizeof(control_hdr_t) + resp_offset;
    _session_send(0x0001, resp->hdr.length + sizeof(control_hdr_t), (unsigned char *)resp);
    free(resp);

    if (resp->result == 0)
        if ((resp->flags & 1) == 0 && ch->state != OPEN)
            session_send_config(ch);
}

void session_configuration_response(command_t *cmd)
{
    struct __attribute__ ((__packed__)) configuration_response {
        unsigned local : 16;
        unsigned flags : 16;
        unsigned result : 16;
        unsigned char config[];
    } *resp = (void *)cmd->payload;

    channel_t *ch = g_channels[resp->local];
    if (ch == NULL || ch->state != CONFIG || ch->config_state != WAIT_CONFIG_RSP)
    {
        return;
    }

    // XXX process response

    ch->state = OPEN;
}

static void session_disconnection_request(command_t *cmd)
{
    struct __attribute__ ((__packed__)) disconnection_request {
        unsigned local : 16;
        unsigned remote : 16;
    } *req = (void *)cmd->payload;

    struct __attribute__ ((__packed__)) disconnection_response {
        control_hdr_t hdr;
        unsigned local : 16;
        unsigned remote : 16;
    } resp;

    if (cmd->hdr.length != sizeof(struct disconnection_request))
    {
        session_send_reject(cmd->hdr.id, 0);
        return;
    }

    channel_t *ch = g_channels[req->local];
    if (ch == NULL || ch->state == CLOSED || ch->remote != ch->remote)
    {
        session_send_reject(cmd->hdr.id, 2);
        return;
    }

    event_t evt;
    evt.type = DISCONNECT_EVENT;
    if (ch->handler)
        ch->handler(ch, ch->userdata, &evt);

    resp.hdr.code = DISCONNECTION_RESPONSE;
    resp.hdr.id = cmd->hdr.id;
    resp.hdr.length = sizeof(resp) - sizeof(control_hdr_t);
    resp.local = req->local;
    resp.remote = req->remote;

    _session_send(0x0001, resp.hdr.length + sizeof(control_hdr_t), (unsigned char *)&resp);

    ch->state = CLOSED;
}

static void session_disconnection_response(command_t *cmd)
{
    struct __attribute__ ((__packed__)) disconnection_request {
        unsigned local : 16;
        unsigned remote : 16;
    } *req = (void *)cmd->payload;

    if (cmd->hdr.length != sizeof(struct disconnection_request))
    {
        session_send_reject(cmd->hdr.id, 0);
        return;
    }

    channel_t *ch = g_channels[req->local];
    if (ch == NULL || ch->state != WAIT_DISCONNECT || ch->remote != ch->remote)
    {
        session_send_reject(cmd->hdr.id, 2);
        return;
    }

    ch->state = CLOSED;
}

static void session_echo_request(command_t *cmd)
{
    // just change the code and resend
    cmd->hdr.code = ECHO_RESPONSE;
    
    _session_send(0x0001, cmd->hdr.length + sizeof(control_hdr_t), (unsigned char *)cmd);
}

static void session_information_request(command_t *cmd)
{
    // we don't support any info types
    unsigned short *req = (void *)cmd->payload;
    struct __attribute__ ((__packed__)) {
        control_hdr_t hdr;
        unsigned info_type : 16;
        unsigned result : 16;
    } resp;

    if (cmd->hdr.length != sizeof(unsigned short))
    {
        session_send_reject(cmd->hdr.id, 0);
        return;
    }

    resp.hdr.id = cmd->hdr.id;
    resp.hdr.code = INFORMATION_RESPONSE;
    resp.hdr.length = 4;
    resp.info_type = *req;
    resp.result = 1; // not supported

    _session_send(0x0001, resp.hdr.length + sizeof(control_hdr_t), (unsigned char *)&resp);
}

static void session_handle_command(command_t *cmd)
{
    switch (cmd->hdr.code)
    {
    case CONNECTION_REQUEST:
        session_connection_request(cmd);
        break;
    case CONFIGURATION_REQUEST:
        session_configuration_request(cmd);
        break;
    case DISCONNECTION_REQUEST:
        session_disconnection_request(cmd);
        break;
    case ECHO_REQUEST:
        session_echo_request(cmd);
        break;
    case INFORMATION_REQUEST:
        session_information_request(cmd);
        break;
    case CONFIGURATION_RESPONSE:
        session_configuration_response(cmd);
        break;
    case DISCONNECTION_RESPONSE:
        session_disconnection_response(cmd);
        break;
    case COMMAND_REJECT:
    case CONNECTION_RESPONSE:
    case ECHO_RESPONSE:
    case INFORMATION_RESPONSE:
        // discard
        break;
    default:
        session_send_reject(cmd->hdr.id, 0);
        break;
    }
}

static int session_handle_control()
{
    size_t offset = 0;
    while (offset + sizeof(command_t) <= g_current_packet.hdr.length)
    {
        command_t *cmd = (command_t *)&g_current_packet.hdr.payload[offset];
        offset += sizeof(command_t);
        if (offset + cmd->hdr.length > g_current_packet.hdr.length)
            break;
        offset += cmd->hdr.length;

        session_handle_command(cmd);        
    }
    return 0;
}

static int session_handle_packet()
{
    if (g_current_packet.hdr.channel == 1)
        return session_handle_control();

    channel_t *ch = g_channels[g_current_packet.hdr.channel];
    if (ch == NULL || ch->state != OPEN)
    {
        // XXX ignore? 
        return 0;
    }

    // handle other packet
    event_t evt;
    evt.type = RX_EVENT;
    evt.rx.data = g_current_packet.hdr.payload;
    evt.rx.length = g_current_packet.hdr.length;
    if (ch->handler)
        ch->handler(ch, ch->userdata, &evt);
    return 0;
}

void session_loop()
{
    int offset = -1;
    unsigned char link_packet[LINK_PAYLOAD_SIZE];
    unsigned int channel, length;

    while (link_recv(&channel, &length, link_packet) == 0)
    {
        if (channel == LINK_CH_START)
        {
            offset = 0;
            memset(g_current_packet.rawdata, 0, SESSION_MAX_PACKET_SIZE);
        }
        else if (channel == LINK_CH_CONTINUE)
        {
        }
        else
        {
            // bad packet, ignore it
            offset = -1;
            continue;
        }

        if (offset == -1)
            continue;

        if (offset + length > SESSION_MAX_PACKET_SIZE)
        {
            // bad packet
            offset = -1;
            continue;
        }

        memcpy(g_current_packet.rawdata + offset, link_packet, length);
        offset += length;

        if (offset >= sizeof(g_current_packet.hdr))
        {
            if (g_current_packet.hdr.length + sizeof(g_current_packet.hdr) == offset)
            {
                offset = -1;

                // complete packet
                if (session_handle_packet() != 0)
                    break;
            }
        }
    }
}

void session_register_psm(unsigned int id, connect_handler_t handler)
{
    psm_t *psm;
    psm = session_find_psm(id);
    if (psm == NULL)
    {
        psm = malloc(sizeof(psm_t));
        if (psm == NULL)
            return;
        psm->id = id;
        psm->next = g_psm_head;
        g_psm_head = psm;
    }

    psm->handler = handler;
}

void session_register_events(void *channel, event_handler_t handler)
{
    channel_t *ch = channel;
    ch->handler = handler;
}

void session_register_userdata(void *channel, void *userdata)
{
    channel_t *ch = channel;
    ch->userdata = userdata;
}

void session_send(void *channel, unsigned int length, unsigned char *data)
{
    channel_t *ch = channel;
    _session_send(ch->remote, length, data);
}
