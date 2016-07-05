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
#include <ctype.h>
#include <string.h>
#include "common.h"
#include "ht.h"
#include "silk.h"

#define MAX_LINE 65536

enum {
    RESP_SUCCESS        = 0x1000,
    RESP_UPDATED        = 0x1001,
    RESP_CONTINUE       = 0x1002,
    RESP_ERROR          = 0x2000,
    RESP_NAME_IN_USE    = 0x2001,
    RESP_NOT_FOUND      = 0x2002,
    RESP_BAD_REQUEST    = 0x2003,
    RESP_INTERNAL_ERROR = 0xA000
};

typedef struct {
    ht_t handlers;
    silk_t silk;
    ht_t products;
} priv_t;

typedef struct {
    char *name;
    char *seller;
    unsigned int price;
    unsigned int quantity;
} product_t;

typedef int (*handler_t)(priv_t *priv, char *resource);

char *read_line(silk_t *silk)
{
    size_t cnt = 0, idx = 0;
    char *result = NULL;
    
    do {
        if (cnt == idx)
        {
            if (cnt >= MAX_LINE)
                goto fail;
            char *tmp;
            cnt += 1024;
            tmp = realloc(result, cnt);
            if (tmp == NULL)
                goto fail;
            result = tmp;
        }

        if (silk_recv(silk, (unsigned char *)&result[idx], 1) != SUCCESS)
            goto fail;
    } while (result[idx++] != '\b');

    if (cnt == idx)
    {
        char *tmp;
        cnt++;
        tmp = realloc(result, cnt);
        if (tmp == NULL)
            goto fail;
        result = tmp;
    }
    result[idx] = 0; 
    return result;

fail:
    free(result);
    return NULL;
}

static int parse_request(char *line, char **method, char **resource)
{
    char *tmp;
    tmp = strchr(line, '\t');
    if (tmp == NULL)
    {
        tmp = strchr(line, '\b');
        if (tmp == NULL)
            return FAILURE;
        *tmp = 0;
        *method = line;
        *resource = NULL;
        return SUCCESS;
    }

    *tmp = 0;
    *method = line;
    line = tmp+1;

    tmp = strchr(line, '\b');
    if (tmp != NULL)
        *tmp = 0;
    *resource = line;
    return SUCCESS;
}

static void free_product(product_t *p)
{
    free(p->seller);
    free(p->name);
    free(p);
}

static int send_response(priv_t *priv, unsigned int code, char *text)
{
    char tmp[1024];
    if (strlen(text) + 64 < sizeof(tmp))
    {
        sprintf(tmp, "%d\t%s\b", code, text);
        return silk_send(&priv->silk, (unsigned char *)tmp, strlen(tmp));
    }
    else
    {
        char *tmp2 = malloc(strlen(text) + 64);
        int result;

#ifndef PATCHED
        fdprintf(STDERR, "WARNING text is too long: ");
        fdprintf(STDERR, text);
        fdprintf(STDERR, "\n");
#else
        fdprintf(STDERR, "WARNING text is too long: %s\n", text);
#endif

        if (tmp2 == NULL)
            return FAILURE;

        sprintf(tmp2, "%d\t%s\b", code, text);
        result = silk_send(&priv->silk, (unsigned char *)tmp2, strlen(tmp2));
        free(tmp2);
        return result;
    }
}

/* convert %XX to \xXX */
static void unescape(char *s)
{
    unsigned int i, j, len = strlen(s);
    for (i = 0, j = 0; i < len; i++, j++)
    {
        if (s[i] == '%' && i + 2 < len && isxdigit(s[i+1]) && isxdigit(s[i+2]))
        {
            int s1 = isdigit(s[i+1]) ? s[i+1] - '0' : tolower(s[i+1]) - 'a' + 10;
            int s2 = isdigit(s[i+2]) ? s[i+2] - '0' : tolower(s[i+2]) - 'a' + 10;
            s[j] = (s1 << 4) | s2;
            i += 2;
        }
        else
            s[j] = s[i];
    }
    s[j] = 0;
}

int do_buy(priv_t *priv, char *resource)
{
    product_t *p;
    ht_node_t *node;

    unescape(resource);

    if (ht_lookup(&priv->products, resource, &node) != SUCCESS)
    {
        return send_response(priv, RESP_NOT_FOUND, "Name not found");
    }
    p = ht_node_value(node);
    if (p->quantity < 1)
    {
        return send_response(priv, RESP_NOT_FOUND, "Name not found");
    }
    p->quantity--;
    if (p->quantity == 0)
    {
        ht_delete(&priv->products, resource, (void **)&p);
        free_product(p);
    }
    return send_response(priv, RESP_SUCCESS, "Success");
}

int do_sell(priv_t *priv, char *resource)
{
    char *name, *seller, *s_price, *s_quantity;
    unsigned int price, quantity;
    ht_node_t *node;
    product_t *p;

    name = resource;
    
    seller = strchr(name, ';');
    if (seller == NULL)
        goto bad_request;
    *seller++ = 0;

    s_price = strchr(seller, ';');
    if (s_price == NULL)
        goto bad_request;
    *s_price++ = 0;
    price = strtoul(s_price, NULL, 10);

    s_quantity = strchr(s_price, ';');
    if (s_quantity == NULL)
        goto bad_request;
    *s_quantity++ = 0;
    quantity = strtoul(s_quantity, NULL, 10);

    unescape(seller);
    unescape(name);

    if (ht_lookup(&priv->products, name, &node) == SUCCESS)
    {
        p = ht_node_value(node);
        if (strcasecmp(p->seller, seller) != 0)
        {
            return send_response(priv, RESP_NAME_IN_USE, "Name already in-use");
        }

        p->price = price;
        p->quantity += quantity;
        return send_response(priv, RESP_UPDATED, "Record updated");
    }
    
    p = malloc(sizeof(product_t));
    if (p == NULL)
        goto internal_error;

    p->price = price;
    p->quantity = quantity;
    p->name = strdup(name);
    p->seller = strdup(seller);

    if (p->name == NULL || p->seller == NULL)
    {
        free_product(p);
        goto internal_error;
    }

    if (ht_insert(&priv->products, p->name, p) != SUCCESS)
    {
        free_product(p);
        goto internal_error;
    }

    return send_response(priv, RESP_SUCCESS, "Success");

bad_request:
    return send_response(priv, RESP_BAD_REQUEST, "Invalid request");

internal_error:
    return send_response(priv, RESP_INTERNAL_ERROR, "Internal error");
}

int do_list(priv_t *priv, char *resource)
{
    char tmp[64], *buf = NULL;
    unsigned int buf_size = 0;
    ht_node_t *iter;

    sprintf(tmp, "%d", priv->products.tbl_count);
    if (send_response(priv, RESP_SUCCESS, tmp) != SUCCESS)
        return FAILURE;
    for (iter = ht_first(&priv->products); iter != NULL; iter = ht_next(&priv->products, iter))
    {
        product_t *p = ht_node_value(iter);
        unsigned int new_buf_size = strlen(p->name) + strlen(p->seller) + 128;
        if (new_buf_size > buf_size)
        {
            char *new_buf = realloc(buf, new_buf_size);
            if (new_buf == NULL)
                break;
            buf = new_buf;
            buf_size = new_buf_size;
        }
        sprintf(buf, "%s;%s;%d;%d", p->name, p->seller, p->price, p->quantity);
        if (send_response(priv, RESP_CONTINUE, buf) != SUCCESS)
            break;
        //if (silk_send(&priv->silk, (unsigned char *)buf, strlen(buf)) != SUCCESS)
        //    break;
    }
    free(buf);

    if (iter != NULL)
        return send_response(priv, RESP_INTERNAL_ERROR, "Internal error");

    return SUCCESS;
}

int do_quit(priv_t *priv, char *resource)
{
    send_response(priv, RESP_SUCCESS, "Success");
    return FAILURE;
}

int main()
{
    ht_node_t *node;
    priv_t priv;

    if (ht_init(&priv.products) != SUCCESS)
        return 1;

    if (ht_init(&priv.handlers) != SUCCESS)
        return 1;

    if (ht_insert(&priv.handlers, "BUY", do_buy) != SUCCESS)
        return 1;

    if (ht_insert(&priv.handlers, "SELL", do_sell) != SUCCESS)
        return 1;

    if (ht_insert(&priv.handlers, "LIST", do_list) != SUCCESS)
        return 1;

    if (ht_insert(&priv.handlers, "QUIT", do_quit) != SUCCESS)
        return 1;

    if (silk_init(&priv.silk) != SUCCESS)
        return 1;

    if (silk_prepare(&priv.silk) != SUCCESS)
        return 1;

    while (1)
    {
        char *line, *method, *resource;
        handler_t handler;
        ht_node_t *node;

        line = read_line(&priv.silk);
        if (line == NULL)
            break;

        if (parse_request(line, &method, &resource) == SUCCESS)
        {
            if (ht_lookup(&priv.handlers, method, &node) == SUCCESS)
            {
                handler = ht_node_value(node);
                if (handler(&priv, resource) != SUCCESS)
                    break;
            }
            else
            {
                // XXX
            }
        }
        else
        {
            // XXX
        }

        free(line);
    }

    return 0;
}
