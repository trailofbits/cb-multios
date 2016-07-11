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
#include <stdint.h>
#include "endian.h"
#include "protocols.h"
#include "io.h"
#include "time.h"
#include "vault.h"

int handle_msg_ping(void *data, unsigned int n);
typedef int (*msg_handler_t) (void *data, unsigned int len);
const msg_handler_t handlers[] = {
    [PROTOCOL_PING] = handle_msg_ping,
    [PROTOCOL_TIME] = handle_msg_time,
    [PROTOCOL_VAULT] = handle_msg_vault
};
static int is_supported(unsigned int id)
{
    return id == PROTOCOL_PING || id == PROTOCOL_TIME || id == PROTOCOL_VAULT;
}

static int consume_bytes(unsigned int n)
{
    uint8_t tmp[512];
    unsigned int len;

    while (n > 0)
    {
        len = sizeof(tmp);
        if (len > n)
            len = n;

        if (read_bytes(tmp, len) == 0)
            return 0;

        n -= len;
    }

    return 1;
}

static int handle_msg(uint16_t id, void *data, unsigned int len)
{
    if (id >= sizeof(handlers) / sizeof(handlers[0]))
        return 0;
    if (handlers[id] == NULL)
        return 0;
    return handlers[id](data, len);
}

int main()
{
    uint8_t *data = NULL;
    init_vault();
    store_in_vault(0, (void *)handlers, sizeof(handlers));
    while (1)
    {
        uint8_t msg[6], *newdata;
        uint16_t id;
        uint32_t len;

        if (read_bytes(&msg[0], 4) == 0)
            break;

        id = betoh16(*(uint16_t *)&msg[0]);
        len = betoh16(*(uint16_t *)&msg[2]);
        if (len & 0x8000)
        {
            if (read_bytes(&msg[4], 2) == 0)
                break;
            len = betoh32(*(uint32_t *)&msg[2]) & 0x7fffffff;
        }

        if (!is_supported(id))
        {
ignore:
            if (consume_bytes(len) == 0)
                break;
            continue;
        }

        newdata = realloc(data, len);
        if (newdata == NULL)
            goto ignore;
        data = newdata;

        if (read_bytes(data, len) == 0)
            break;

        handle_msg(id, data, len);
    }

    free(data);
    return 0;
}

int handle_msg_ping(void *data, unsigned int n)
{
    uint8_t hdr[6];
    *(uint16_t *)&hdr[0] = htobe16(PROTOCOL_PING);
    if (n < 0x8000)
    {
        *(uint16_t *)&hdr[2] = htobe16(n);
        write_bytes(hdr, 4);
    }
    else
    {
        *(uint32_t *)&hdr[2] = htobe32(n | 0x80000000);
        write_bytes(hdr, 6);
    }

    write_bytes(data, n);
    return 1;
}
