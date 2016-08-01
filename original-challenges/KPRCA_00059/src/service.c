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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"

typedef struct {
    unsigned int timestamp;
    unsigned int flags;
    float x, y, z;
    float speed;
    float rpm;
} state_t;

DEFINE_QUEUE(state_t, stateq)

typedef struct {
    unsigned char type;
    unsigned int timestamp;

    union {
        struct {
            float x;
            float y;
            float z;
        } loc;
        struct {
            float speed;
        } speed;
        struct {
            float rpm;
        } rpm;
        struct {
            unsigned int code;
            unsigned int extra;
        } error;
    };
} __attribute__((__packed__)) pkt_t;

enum {
    TYPE_ERROR = 0,
    TYPE_RESET,
    TYPE_LOCATION,
    TYPE_SPEED,
    TYPE_RPM,
};

enum {
    FLAG_LOCATION = 0x00000001,
    FLAG_SPEED = 0x00000002,
    FLAG_RPM = 0x00000004,
    FLAG_TENTATIVE = 0x80000000
};

enum {
    EC_ERROR,
    EC_TIMESTAMP,
    EC_DROPPED,
    EC_INVALID
};

static const int hist_size = 100;
static const float max_rpm = 10000.0;
static const float min_rpm = 0.0;
static const float max_speed = 250.0;
static const float min_speed = 0.0;
static const unsigned int max_time_delta = 100;

static stateq_t *g_history;

static unsigned char txbuf[1024];
static unsigned int txcnt;
static int txfd;

void writeflush()
{
    size_t i = 0, n;

    while (i < txcnt)
    {
        if (transmit(txfd, &txbuf[i], txcnt - i, &n) != 0 || n == 0)
            break;
        i += n;
    }

    txcnt = 0;
}

void write(int fd, void *data, size_t len)
{
    if (len + txcnt > sizeof(txbuf) || txfd != fd)
        writeflush();
    txfd = fd;
    memcpy(&txbuf[txcnt], data, len);
    txcnt += len;
}

void send_error(unsigned int ec, unsigned int extra)
{
    pkt_t pkt;

    memset(&pkt, 0, sizeof(pkt));
    pkt.type = TYPE_ERROR;
    pkt.error.code = ec;
    pkt.error.extra = extra;

    write(STDOUT, &pkt, sizeof(pkt));
}

void send_aggregate(unsigned int timestamp)
{
    unsigned int i;
    pkt_t pkt;
    state_t state;

    if (stateq_empty(g_history))
        return;

    memset(&state, 0, sizeof(state_t));
    state.timestamp = timestamp;

    /* aggregate history into a complete state */
    for (i = stateq_length(g_history); i > 0; i--)
    {
        unsigned int flags;
        state_t *pstate = stateq_get(g_history, i - 1);

        flags = pstate->flags & ~state.flags;

        if (flags & FLAG_LOCATION)
        {
            state.x = pstate->x;
            state.y = pstate->y;
            state.z = pstate->z;
            state.flags |= FLAG_LOCATION;
        }
        if (flags & FLAG_SPEED)
        {
            state.speed = pstate->speed;
            state.flags |= FLAG_SPEED;
        }
        if (flags & FLAG_RPM)
        {
            state.rpm = pstate->rpm;
            state.flags |= FLAG_RPM;
        }
    }

    memset(&pkt, 0, sizeof(pkt));
    pkt.timestamp = state.timestamp;

    if (state.flags & FLAG_SPEED)
    {
        pkt.type = TYPE_SPEED;
        pkt.speed.speed = state.speed;
        write(STDOUT, &pkt, sizeof(pkt));
    }
    if (state.flags & FLAG_RPM)
    {
        pkt.type = TYPE_RPM;
        pkt.rpm.rpm = state.rpm;
        write(STDOUT, &pkt, sizeof(pkt));
    }
    if (state.flags & FLAG_LOCATION)
    {
        pkt.type = TYPE_LOCATION;
        pkt.loc.x = state.x;
        pkt.loc.y = state.y;
        pkt.loc.z = state.z;
        write(STDOUT, &pkt, sizeof(pkt));
    }
}

float calculate_speed(pkt_t *pkt)
{
    unsigned int i;

    for (i = stateq_length(g_history); i > 0; i--)
    {
        state_t *pstate = stateq_get(g_history, i - 1);
        if (pstate->timestamp == pkt->timestamp)
            continue;

        if (pstate->flags & FLAG_LOCATION)
        {
            return sqrtf(exp2f(pstate->x - pkt->loc.x) +
                    exp2f(pstate->y - pkt->loc.y) +
                    exp2f(pstate->z - pkt->loc.z)) / (pkt->timestamp - pstate->timestamp);
        }
    }
    
    return 0.0;
}

int do_mix(state_t *state, pkt_t *pkt)
{
    state_t *prev;

    /* verify in absolute bounds */
    switch (pkt->type)
    {
    case TYPE_LOCATION:
        break;
    case TYPE_SPEED:
        if (pkt->speed.speed < min_speed || pkt->speed.speed >= max_speed)
        {
            send_error(EC_INVALID, TYPE_SPEED);
            return 0;
        }
        break;
    case TYPE_RPM:
        if (pkt->rpm.rpm < min_rpm || pkt->rpm.rpm >= max_rpm)
        {
            send_error(EC_INVALID, TYPE_RPM);
            return 0;
        }
        break;
    default:
        return 0;
    }

    /* get previous state */
    if (!stateq_empty(g_history) && stateq_tail(g_history)->timestamp != pkt->timestamp)
        prev = stateq_tail(g_history);
    else if (stateq_length(g_history) >= 2)
        prev = stateq_get(g_history, stateq_length(g_history) - 2);
    else
        prev = NULL;

    if (prev != NULL)
    {
        /* verify data against previous state */
        switch (pkt->type)
        {
        case TYPE_LOCATION:
            if (calculate_speed(pkt) > max_speed)
            {
                send_error(EC_INVALID, TYPE_LOCATION);
                return 0;
            }
            break;
        }
    }

    /* add data to state */
    switch (pkt->type)
    {
    case TYPE_LOCATION:
        state->x = pkt->loc.x;
        state->y = pkt->loc.y;
        state->z = pkt->loc.z;
        state->flags |= FLAG_LOCATION;
        break;
    case TYPE_SPEED:
        state->speed = pkt->speed.speed;
        state->flags |= FLAG_SPEED;
        break;
    case TYPE_RPM:
        state->rpm = pkt->rpm.rpm;
        state->flags |= FLAG_RPM;
        break;
    }

    return 1;
}

static unsigned int do_hash(const unsigned char *_data, unsigned int len)
{
    unsigned char *data = malloc(len);
    unsigned int i, hash = 0, xform = 0x12345678;

    memcpy(data, _data, len);

    /* transform */
    for (i = 0; i < len - 3; i += 4)
    {
        *(unsigned int *)(data + i) ^= xform;
        xform ^= xform >> 13;
        xform ^= xform << 7;
        xform ^= xform >> 17;
    }

    /* hash */
    for (i = 0; i < len - 3; i += 4)
        hash += *(unsigned int *)(data + i);

    free(data);
    return hash;
}

int __attribute__((fastcall)) main(int secret_page_i, char *unused[]) {
    pkt_t pkt;
    state_t cur_state;
    void *secret_page = (void *)secret_page_i;
    unsigned int secret_hash;

    secret_hash = do_hash(secret_page, 0x1000);

    stateq_init(&g_history, hist_size);

    memset(&cur_state, 0, sizeof(cur_state));
    cur_state.timestamp = secret_hash;
    stateq_push(g_history, &cur_state);

    while (1)
    {
        state_t *last_state;

        writeflush();
        if (fread((char *)&pkt, sizeof(pkt), stdin) != sizeof(pkt))
            break;

        if (pkt.type == TYPE_RESET)
        {
            stateq_clear(g_history);
            continue;
        }

        last_state = stateq_tail(g_history);
        if (last_state && pkt.timestamp < last_state->timestamp)
        {
            unsigned int len = stateq_length(g_history);
            if (len < 2
                /* check if last packet might be invalid */
                || (last_state->timestamp - stateq_get(g_history, len - 2)->timestamp) < max_time_delta
                /* check that current packet would be valid if last packet dropped */
                || pkt.timestamp < stateq_get(g_history, len - 2)->timestamp)
            {
                send_error(EC_TIMESTAMP, last_state->timestamp);
                continue;
            }
            
            /* last packet was bad, drop it */
            stateq_pop_tail(g_history, &cur_state);
#ifdef PATCHED_1
            cur_state = *stateq_tail(g_history);
#endif
            send_error(EC_DROPPED, cur_state.timestamp);

            last_state = stateq_tail(g_history);
        }

        if (last_state && (last_state->flags & FLAG_TENTATIVE))
        {
            last_state->flags &= ~FLAG_TENTATIVE;
        }

        if (last_state && pkt.timestamp == last_state->timestamp)
        {
            if (do_mix(last_state, &pkt))
                send_aggregate(pkt.timestamp);
        }
        else
        {
            memset(&cur_state, 0, sizeof(cur_state));
            cur_state.timestamp = pkt.timestamp;
            if (last_state && pkt.timestamp >= last_state->timestamp + max_time_delta)
                cur_state.flags |= FLAG_TENTATIVE;

            /* add it to history, dropping old one if needed */
            if (stateq_full(g_history))
                stateq_pop(g_history, NULL);
            stateq_push(g_history, &cur_state);

            if (do_mix(stateq_tail(g_history), &pkt))
                send_aggregate(pkt.timestamp);
        }
    }

    writeflush();
    stateq_destroy(&g_history);

    return 0;
}
