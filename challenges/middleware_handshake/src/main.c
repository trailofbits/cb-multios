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
#include "cgc_stdlib.h"
#include "cgc_ctype.h"
#include "cgc_string.h"
#include "cgc_common.h"
#include "cgc_ht.h"
#include "cgc_silk.h"

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

char *cgc_read_line(silk_t *silk)
{
    cgc_size_t cnt = 0, idx = 0;
    char *result = NULL;
    
    do {
        if (cnt == idx)
        {
            if (cnt >= MAX_LINE)
                goto fail;
            char *tmp;
            cnt += 1024;
            tmp = cgc_realloc(result, cnt);
            if (tmp == NULL)
                goto fail;
            result = tmp;
        }

        if (cgc_silk_recv(silk, (unsigned char *)&result[idx], 1) != SUCCESS)
            goto fail;
    } while (result[idx++] != '\b');

    if (cnt == idx)
    {
        char *tmp;
        cnt++;
        tmp = cgc_realloc(result, cnt);
        if (tmp == NULL)
            goto fail;
        result = tmp;
    }
    result[idx] = 0; 
    return result;

fail:
    cgc_free(result);
    return NULL;
}

static int parse_request(char *line, char **method, char **resource)
{
    char *tmp;
    tmp = cgc_strchr(line, '\t');
    if (tmp == NULL)
    {
        tmp = cgc_strchr(line, '\b');
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

    tmp = cgc_strchr(line, '\b');
    if (tmp != NULL)
        *tmp = 0;
    *resource = line;
    return SUCCESS;
}

static void free_product(product_t *p)
{
    cgc_free(p->seller);
    cgc_free(p->name);
    cgc_free(p);
}

static int cgc_send_response(priv_t *priv, unsigned int code, char *text)
{
    char tmp[1024];
    if (cgc_strlen(text) + 64 < sizeof(tmp))
    {
        cgc_sprintf(tmp, "%d\t%s\b", code, text);
        return cgc_silk_send(&priv->silk, (unsigned char *)tmp, cgc_strlen(tmp));
    }
    else
    {
        char *tmp2 = cgc_malloc(cgc_strlen(text) + 64);
        int result;

#ifndef PATCHED
        cgc_fdprintf(STDERR, "WARNING text is too long: ");
        cgc_fdprintf(STDERR, text);
        cgc_fdprintf(STDERR, "\n");
#else
        cgc_fdprintf(STDERR, "WARNING text is too long: %s\n", text);
#endif

        if (tmp2 == NULL)
            return FAILURE;

        cgc_sprintf(tmp2, "%d\t%s\b", code, text);
        result = cgc_silk_send(&priv->silk, (unsigned char *)tmp2, cgc_strlen(tmp2));
        cgc_free(tmp2);
        return result;
    }
}

/* convert %XX to \xXX */
static void cgc_unescape(char *s)
{
    unsigned int i, j, len = cgc_strlen(s);
    for (i = 0, j = 0; i < len; i++, j++)
    {
        if (s[i] == '%' && i + 2 < len && cgc_isxdigit(s[i+1]) && cgc_isxdigit(s[i+2]))
        {
            int s1 = cgc_isdigit(s[i+1]) ? s[i+1] - '0' : cgc_tolower(s[i+1]) - 'a' + 10;
            int s2 = cgc_isdigit(s[i+2]) ? s[i+2] - '0' : cgc_tolower(s[i+2]) - 'a' + 10;
            s[j] = (s1 << 4) | s2;
            i += 2;
        }
        else
            s[j] = s[i];
    }
    s[j] = 0;
}

int cgc_do_buy(priv_t *priv, char *resource)
{
    product_t *p;
    ht_node_t *node;

    cgc_unescape(resource);

    if (cgc_ht_lookup(&priv->products, resource, &node) != SUCCESS)
    {
        return cgc_send_response(priv, RESP_NOT_FOUND, "Name not found");
    }
    p = ht_node_value(node);
    if (p->quantity < 1)
    {
        return cgc_send_response(priv, RESP_NOT_FOUND, "Name not found");
    }
    p->quantity--;
    if (p->quantity == 0)
    {
        cgc_ht_delete(&priv->products, resource, (void **)&p);
        free_product(p);
    }
    return cgc_send_response(priv, RESP_SUCCESS, "Success");
}

int cgc_do_sell(priv_t *priv, char *resource)
{
    char *name, *seller, *s_price, *s_quantity;
    unsigned int price, quantity;
    ht_node_t *node;
    product_t *p;

    name = resource;
    
    seller = cgc_strchr(name, ';');
    if (seller == NULL)
        goto bad_request;
    *seller++ = 0;

    s_price = cgc_strchr(seller, ';');
    if (s_price == NULL)
        goto bad_request;
    *s_price++ = 0;
    price = cgc_strtoul(s_price, NULL, 10);

    s_quantity = cgc_strchr(s_price, ';');
    if (s_quantity == NULL)
        goto bad_request;
    *s_quantity++ = 0;
    quantity = cgc_strtoul(s_quantity, NULL, 10);

    cgc_unescape(seller);
    cgc_unescape(name);

    if (cgc_ht_lookup(&priv->products, name, &node) == SUCCESS)
    {
        p = ht_node_value(node);
        if (cgc_strcasecmp(p->seller, seller) != 0)
        {
            return cgc_send_response(priv, RESP_NAME_IN_USE, "Name already in-use");
        }

        p->price = price;
        p->quantity += quantity;
        return cgc_send_response(priv, RESP_UPDATED, "Record updated");
    }
    
    p = cgc_malloc(sizeof(product_t));
    if (p == NULL)
        goto internal_error;

    p->price = price;
    p->quantity = quantity;
    p->name = cgc_strdup(name);
    p->seller = cgc_strdup(seller);

    if (p->name == NULL || p->seller == NULL)
    {
        free_product(p);
        goto internal_error;
    }

    if (cgc_ht_insert(&priv->products, p->name, p) != SUCCESS)
    {
        free_product(p);
        goto internal_error;
    }

    return cgc_send_response(priv, RESP_SUCCESS, "Success");

bad_request:
    return cgc_send_response(priv, RESP_BAD_REQUEST, "Invalid request");

internal_error:
    return cgc_send_response(priv, RESP_INTERNAL_ERROR, "Internal error");
}

int cgc_do_list(priv_t *priv, char *resource)
{
    char tmp[64], *buf = NULL;
    unsigned int buf_size = 0;
    ht_node_t *iter;

    cgc_sprintf(tmp, "%d", priv->products.tbl_count);
    if (cgc_send_response(priv, RESP_SUCCESS, tmp) != SUCCESS)
        return FAILURE;
    for (iter = cgc_ht_first(&priv->products); iter != NULL; iter = cgc_ht_next(&priv->products, iter))
    {
        product_t *p = ht_node_value(iter);
        unsigned int new_buf_size = cgc_strlen(p->name) + cgc_strlen(p->seller) + 128;
        if (new_buf_size > buf_size)
        {
            char *new_buf = cgc_realloc(buf, new_buf_size);
            if (new_buf == NULL)
                break;
            buf = new_buf;
            buf_size = new_buf_size;
        }
        cgc_sprintf(buf, "%s;%s;%d;%d", p->name, p->seller, p->price, p->quantity);
        if (cgc_send_response(priv, RESP_CONTINUE, buf) != SUCCESS)
            break;
        //if (silk_send(&priv->silk, (unsigned char *)buf, cgc_strlen(buf)) != SUCCESS)
        //    break;
    }
    cgc_free(buf);

    if (iter != NULL)
        return cgc_send_response(priv, RESP_INTERNAL_ERROR, "Internal error");

    return SUCCESS;
}

int cgc_do_quit(priv_t *priv, char *resource)
{
    cgc_send_response(priv, RESP_SUCCESS, "Success");
    return FAILURE;
}

int main(int cgc_argc, char *cgc_argv[])
{
    ht_node_t *node;
    priv_t priv;

    if (cgc_ht_init(&priv.products) != SUCCESS)
        return 1;

    if (cgc_ht_init(&priv.handlers) != SUCCESS)
        return 1;

    if (cgc_ht_insert(&priv.handlers, "BUY", cgc_do_buy) != SUCCESS)
        return 1;

    if (cgc_ht_insert(&priv.handlers, "SELL", cgc_do_sell) != SUCCESS)
        return 1;

    if (cgc_ht_insert(&priv.handlers, "LIST", cgc_do_list) != SUCCESS)
        return 1;

    if (cgc_ht_insert(&priv.handlers, "QUIT", cgc_do_quit) != SUCCESS)
        return 1;

    if (cgc_silk_init(&priv.silk) != SUCCESS)
        return 1;

    if (cgc_silk_prepare(&priv.silk) != SUCCESS)
        return 1;

    while (1)
    {
        char *line, *method, *resource;
        handler_t handler;
        ht_node_t *node;

        line = cgc_read_line(&priv.silk);
        if (line == NULL)
            break;

        if (parse_request(line, &method, &resource) == SUCCESS)
        {
            if (cgc_ht_lookup(&priv.handlers, method, &node) == SUCCESS)
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

        cgc_free(line);
    }

    return 0;
}
