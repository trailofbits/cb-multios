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
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "xpack.h"
#include "tr.h"

#define CMD_STORE   0x4414803BA52CB50DULL
#define CMD_LOOKUP  0xF0CEC4CA602CCFF8ULL
#define CMD_DELETE  0x0842ABE098A0D38EULL
#define CMD_DEBUG   0x7B7947D03E5DF85DULL
#define CMD_PRINT   0xEDB20325B2A3505BULL
#define CMD_QUIT    0xB483456220FC57CCULL

#define RES_OK          0x0
#define RES_ERR_PARSING 0x12B3AC854AF56710ULL
#define RES_ERR_KEY     0xDFF50A123E5949EAULL
#define RES_INVALID     0x5C60BEF967440470ULL

#define MAX_DATA_LEN 0x12000

tr_t g_map = NULL;
xpk_ctx_t *g_ctx = NULL;

typedef enum {
/* 0 */    TYPE_INT,
/* 1 */    TYPE_UINT,
/* 2 */    TYPE_BOOL,
/* 3 */    TYPE_STRING,
/* 4 */    TYPE_BYTES,
/* 5 */    TYPE_NIL,
/* 6 */    TYPE_MAP,
/* 7 */    TYPE_ARRAY,
/* 8 */    TYPE_NONE
} obj_type;

typedef struct {
    obj_type type;
    uint64_t data;
    size_t len;
} object_t;

object_t obj_none = { TYPE_NONE, 0, 0 };

void free_object(T obj)
{
    object_t *o = (object_t *) obj;
    switch (o->type)
    {
        case TYPE_BYTES:
        case TYPE_STRING:
            free((void *) o->data);
            break;
        case TYPE_MAP:
            tr_destroy((tr_t) o->data);
            break;
        case TYPE_ARRAY:
            {
                int _i;
                for (_i = 0; _i < o->len; _i++)
                {
                    object_t *_o = ((object_t **) o->data)[_i];
                    free_object(_o);
                }
                free((void *) o->data);
                break;
            }
        case TYPE_NONE:
            return;
        default:
            break;
    }
    free(o);
    return;
}

void send_response(uint64_t val)
{
    fwrite(&val, sizeof(uint64_t), stdout);
    if (val == RES_ERR_PARSING)
        exit(0);
}

xpk_err pack_object(xpk_ctx_t *ctx, object_t* obj);
void pack_map_item(tr_t root, void *arg)
{
    xpk_ctx_t *ctx = (xpk_ctx_t *) arg;
    xpk_pack_str(ctx, root->key);
    pack_object(ctx, root->value);
}

xpk_err pack_object(xpk_ctx_t *ctx, object_t* obj)
{
    xpk_err err;

    switch (obj->type)
    {
        case TYPE_INT:
            if ((err = xpk_pack_int(ctx, obj->data)) != XPK_ERR_NONE)
                goto fail;
            break;
        case TYPE_UINT:
            if ((err = xpk_pack_uint(ctx, obj->data)) != XPK_ERR_NONE)
                goto fail;
            break;
        case TYPE_BOOL:
            if ((err = xpk_pack_bool(ctx, obj->data)) != XPK_ERR_NONE)
                goto fail;
            break;
        case TYPE_STRING:
            if ((err = xpk_pack_str(ctx, (const char *) obj->data)) != XPK_ERR_NONE)
                goto fail;
            break;
        case TYPE_BYTES:
            if ((err = xpk_pack_bytes(ctx, (const char *) obj->data, obj->len)) != XPK_ERR_NONE)
                goto fail;
            break;
        case TYPE_NIL:
            if ((err = xpk_pack_nil(ctx)) != XPK_ERR_NONE)
                goto fail;
            break;
        case TYPE_MAP:
            {
                if ((err = xpk_pack_map(ctx, obj->len)) != XPK_ERR_NONE)
                    goto fail;
                tr_t _map = (tr_t) obj->data;
                tr_apply(_map, pack_map_item, ctx);
                break;
            }
        case TYPE_ARRAY:
            {
                if ((err = xpk_pack_array(ctx, obj->len)) != XPK_ERR_NONE)
                    goto fail;
                object_t **_objs = (object_t **) obj->data;
                int _i;
                for (_i = 0; _i < obj->len; _i++)
                    pack_object(ctx, _objs[_i]);
                break;
            }
        case TYPE_NONE:
            if ((err = xpk_pack_none(ctx)) != XPK_ERR_NONE)
                goto fail;
            break;
        default:
            break;
    }
    return err;

fail:
    return err;
}

xpk_err unpack_object(xpk_ctx_t *ctx, object_t** obj)
{
    xpk_type t;
    xpk_err err;
    object_t *o = NULL;

    if ((err = xpk_next_type(ctx, &t)) == XPK_ERR_NONE)
    {
        o = (object_t *) malloc(sizeof(object_t));
        switch (t)
        {
            case XPK_POSITIVE_FIXINT:
            case XPK_NEGATIVE_FIXINT:
            case XPK_INT8:
            case XPK_INT16:
            case XPK_INT32:
            case XPK_INT64:
            case XPK_UINT8:
            case XPK_UINT16:
            case XPK_UINT32:
            case XPK_UINT64:
                {
                    uint8_t _sign;
                    uint64_t _value;
                    if ((err = xpk_unpack_int(ctx, &_value, &_sign)) != XPK_ERR_NONE)
                        goto fail;
                    o->type = _sign ? TYPE_INT : TYPE_UINT;
                    o->data = _value;
                    o->len = 0;
                    break;
                }
            case XPK_TRUE:
            case XPK_FALSE:
                {
                    uint8_t _b;
                    if ((err = xpk_unpack_bool(ctx, &_b)) != XPK_ERR_NONE)
                        goto fail;
                    o->type = TYPE_BOOL;
                    o->data = _b;
                    o->len = 0;
                    break;
                }
            case XPK_BYTES:
                {
                    size_t _len;
                    if ((err = xpk_unpack_bytes(ctx, &_len)) != XPK_ERR_NONE)
                        goto fail;
                    o->type = TYPE_BYTES;
                    o->data = (uint64_t) malloc(sizeof(char) * _len);
                    if ((err = xpk_read(ctx, (char *) o->data, _len)) != XPK_ERR_NONE)
                        goto fail;
                    o->len = _len;
                    break;
                }
            case XPK_ARRAY:
                {
                    int _i;
                    size_t _len;
                    if ((err = xpk_unpack_array(ctx, &_len)) != XPK_ERR_NONE)
                        goto fail;
                    o->type = TYPE_ARRAY;
                    o->data = (uint64_t) malloc(sizeof(object_t *) * _len);
                    o->len = 0;
                    for (_i = 0; _i < _len; _i++)
                    {
                        object_t *_o = NULL;
                        if ((err = unpack_object(ctx, &_o)) != XPK_ERR_NONE)
                            goto fail;
                        ((object_t **) o->data)[_i] = _o;
                        o->len++;
                    }
                    break;
                }
            case XPK_MAP:
                {
                    int _i;
                    size_t _len;
                    tr_t _map = NULL;
                    if ((err = xpk_unpack_map(ctx, &_len)) != XPK_ERR_NONE)
                        goto fail;
                    o->type = TYPE_MAP;
                    o->len = 0;
                    for (_i = 0; _i < _len; _i++)
                    {
                        object_t *_o1 = NULL, *_o2 = NULL;
                        if ((err = unpack_object(ctx, &_o1)) != XPK_ERR_NONE)
                            goto fail;
                        if ((err = unpack_object(ctx, &_o2)) != XPK_ERR_NONE)
                            goto fail;
                        if (_o1->type == TYPE_STRING)
                        {
                            _map = tr_insert(_map, (char *) _o1->data, _o2);
                            o->len++;
                        }
                        else
                            goto fail;
                        if (_o1)
                            free_object(_o1);
                    }
                    o->data = (uint64_t) _map;
                    break;
                }
            case XPK_NIL:
                {
                    if ((err = xpk_unpack_nil(ctx)) != XPK_ERR_NONE)
                        goto fail;
                    o->type = TYPE_NIL;
                    o->data = 0;
                    o->len = 0;
                    break;
                }
            case XPK_STRING:
            case XPK_FIXSTRING:
                {
                    size_t _len;
                    if ((err = xpk_unpack_str(ctx, &_len)) != XPK_ERR_NONE)
                        goto fail;
                    o->type = TYPE_STRING;
                    o->data = (uint64_t) malloc(sizeof(char) * _len + 1);
                    if ((err = xpk_read(ctx, (char *) o->data, _len)) != XPK_ERR_NONE)
                        goto fail;
                    ((char *) o->data)[_len] = '\0';
                    o->len = _len;
                    break;
                }
            default:
                break;
        }
        *obj = o;
    }
    return err;

fail:
    return err;
}

void add_to_gmap(tr_t root, void *arg)
{
    g_map = tr_insert(g_map, root->key, root->value);
}

void create_store_out(tr_t root, void *arg)
{
    xpk_ctx_t *ctx = (xpk_ctx_t *) arg;
    xpk_pack_str(ctx, root->key);
}

void handle_store(size_t size)
{
    xpk_reset(g_ctx, size);
    xpk_err err;
    object_t *data = NULL;
    tr_t map = NULL;
    if (fread(g_ctx->buf, size, stdin) != size)
        goto fail;
    if ((err = unpack_object(g_ctx, &data)) == XPK_ERR_NONE)
    {
        if (data->type != TYPE_MAP)
            goto fail;

        tr_t map = (tr_t) data->data;
        tr_apply(map, add_to_gmap, NULL);

        xpk_reset(g_ctx, size);
        xpk_pack_array(g_ctx, data->len);
        tr_apply(map, create_store_out, g_ctx);

        free_object(data);

        send_response(RES_OK);
        fwrite(g_ctx->buf, g_ctx->idx, stdout);
    }
    else
    {
        send_response(RES_ERR_PARSING);
    }

    return;

fail:
    if (data)
        free_object(data);
    send_response(RES_ERR_PARSING);
    return;
}

void handle_lookup(size_t size)
{
    xpk_reset(g_ctx, size);
    xpk_err err;
    object_t *data = NULL;
    tr_t map = NULL;

    if (fread(g_ctx->buf, size, stdin) != size)
        goto fail;
    if ((err = unpack_object(g_ctx, &data)) == XPK_ERR_NONE)
    {
        if (data->type != TYPE_ARRAY)
            goto fail;

        int i;
        object_t **objs = (object_t **) data->data;
        for (i = 0; i < data->len; i++)
        {
            if (objs[i]->type != TYPE_STRING)
                goto fail;
            object_t *_o = (object_t *) tr_find(g_map, (char *) objs[i]->data);
            if (_o == NULL)
                _o = &obj_none;
            map = tr_insert(map, (char *) objs[i]->data, _o);
        }

        xpk_reset(g_ctx, size);
        object_t _o = { TYPE_MAP, (uint64_t) map, data->len };
        if ((err = pack_object(g_ctx, &_o)) != XPK_ERR_NONE)
            goto fail;
        tr_destroy(map);
        free_object(data);

        send_response(RES_OK);
        fwrite(g_ctx->buf, g_ctx->idx, stdout);
    }
    else
    {
        send_response(RES_ERR_PARSING);
    }

    return;

fail:
    tr_destroy(map);
    if (data)
        free_object(data);
    send_response(RES_ERR_PARSING);
    return;
}

void handle_delete(size_t size)
{
    xpk_reset(g_ctx, size);
    xpk_err err;
    object_t *data = NULL;
    char** keys = NULL;
    tr_t map = NULL;

    if (fread(g_ctx->buf, size, stdin) != size)
        goto fail;
    if ((err = unpack_object(g_ctx, &data)) == XPK_ERR_NONE)
    {
        if (data->type != TYPE_ARRAY)
            goto fail;

        int i;
        object_t **objs = (object_t **) data->data;
        keys = malloc(sizeof(char*) * data->len);
        memset(keys, 0, sizeof(char*) * data->len);
        for (i = 0; i < data->len; i++)
        {
            if (objs[i]->type != TYPE_STRING)
                goto fail;
            keys[i] = strdup((char *) objs[i]->data);
            object_t *_o = (object_t *) tr_find(g_map, (char *) objs[i]->data);
            if (_o == NULL)
                _o = &obj_none;
            map = tr_insert(map, (char *) objs[i]->data, _o);
        }

        xpk_reset(g_ctx, size);
        object_t _o = { TYPE_MAP, (uint64_t) map, data->len };
        if ((err = pack_object(g_ctx, &_o)) != XPK_ERR_NONE)
            goto fail;
        tr_destroy(map);
        free_object(data);

        for (i = 0; i < data->len; i++)
        {
            g_map = tr_delete(g_map, keys[i]);
            free(keys[i]);
        }
        free(keys);

        send_response(RES_OK);
        fwrite(g_ctx->buf, g_ctx->idx, stdout);
    }
    else
    {
        send_response(RES_ERR_PARSING);
    }

    return;

fail:
    if (keys)
    {
        int i;
        for (i = 0; keys[i]; i++)
            free(keys[i]);
    }
    tr_destroy(map);
    if (data)
        free_object(data);
    send_response(RES_ERR_PARSING);
    return;
}

void handle_debug(size_t size, uint8_t *debug)
{
    xpk_reset(g_ctx, size);
    xpk_err err;
    object_t *data = NULL;

    if (fread(g_ctx->buf, size, stdin) != size)
        goto fail;
    if ((err = unpack_object(g_ctx, &data)) == XPK_ERR_NONE)
    {
        if (data->type != TYPE_ARRAY || data->len != 2)
            goto fail;

        object_t **objs = (object_t **) data->data;
        if (objs[0]->type != TYPE_BOOL || objs[1]->type != TYPE_BYTES)
            goto fail;
        const char key[] = "\x13\xbem\x9b\x83s\x9d\x07\xcak\xcc\xee@k\x7f\xe1\xec\x03\xa7\x37";
        if (objs[1]->len != sizeof(key) - 1 || memcmp((char *) objs[1]->data, key, sizeof(key) - 1))
            send_response(RES_ERR_KEY);
        else
        {
            *debug = objs[0]->data;

            xpk_reset(g_ctx, size);
            object_t _o = { TYPE_BOOL, (uint64_t) *debug, 0 };
            if ((err = pack_object(g_ctx, &_o)) != XPK_ERR_NONE)
                goto fail;
            send_response(RES_OK);
            fwrite(g_ctx->buf, g_ctx->idx, stdout);
        }
        free_object(data);
    }
    else
    {
        send_response(RES_ERR_PARSING);
    }

    return;

fail:
    if (data)
        free_object(data);
    send_response(RES_ERR_PARSING);
    return;
}

#define MAX_PRINT_DEPTH 32
void print_map(int depth, tr_t root, uint64_t *i, uint64_t n);
void print_array(int depth, object_t **arr, unsigned int size, uint64_t *i, uint64_t n);
void print_bytes(const char *bytes, size_t len);

void print_item(int depth, object_t *o, uint64_t *i, uint64_t n)
{
    switch (o->type)
    {
    case TYPE_INT:
        printf("&d" NL, (int)o->data);
        break;
    case TYPE_UINT:
        printf("&u" NL, (unsigned int)o->data);
        break;
    case TYPE_BOOL:
        printf("&s" NL, o->data ? "true" : "false");
        break;
    case TYPE_STRING:
        printf("\"&s\"" NL, (const char *)o->data);
        break;
    case TYPE_BYTES:
        print_bytes((const char *)o->data, o->len);
        break;
    case TYPE_NIL:
        printf("NIL" NL);
        break;
    case TYPE_MAP:
        printf("{" NL);
        print_map(depth + 1, (tr_t)o->data, i, n);
        printf("}" NL);
        break;
    case TYPE_ARRAY:
        printf("[" NL);
        print_array(depth + 1, (object_t **)o->data, o->len, i, n);
        printf("]" NL);
        break;
    case TYPE_NONE:
        break;
    }
}

void print_array(int depth, object_t **arr, unsigned int size, uint64_t *i, uint64_t n)
{
    unsigned int j;
    unsigned char indent[MAX_PRINT_DEPTH + 1];
    if (depth == MAX_PRINT_DEPTH)
        return;
    memset(indent, '\t', MAX_PRINT_DEPTH);
    indent[depth] = 0;

    for (j = 0; j < size; j++)
    {
        if (*i < n || n == 0)
        {
            printf("&s&d  =>  [VALUE]: ", indent, j);
            print_item(depth, arr[j], i, n);
            (*i)++;
        }
    }
}

void print_map(int depth, tr_t root, uint64_t *i, uint64_t n)
{
    unsigned char indent[MAX_PRINT_DEPTH + 1];
    if (depth == MAX_PRINT_DEPTH)
        return;
    memset(indent, '\t', MAX_PRINT_DEPTH);
    indent[depth] = 0;

    if (root && (*i < n || n == 0))
    {
        print_map(depth, root->left, i, n);
        if (*i < n || n == 0)
        {
            object_t *value = (object_t *) root->value;
            printf("&s[KEY]: &s  =>  [VALUE]: ", indent, root->key);
            print_item(depth, value, i, n);
            (*i)++;
            print_map(depth, root->right, i, n);
        }
    }
}

void print_bytes(const char *bytes, size_t len)
{
    char escaped[65536];
    size_t i, j = 0;
    for (i = 0; i < len; i++)
    {
        if (isalnum(bytes[i]))
        {
#ifdef PATCHED_1
            if (j >= 65534)
                break;
#endif
            escaped[j++] = bytes[i];
        }
        else
        {
#ifdef PATCHED_1
            if (j >= 65532)
                break;
#endif
            sprintf(&escaped[j], "\\&02X", (unsigned char)bytes[i]);
            j += 3;
        }
    }
    escaped[j] = '\0';
    printf("<&s>" NL, escaped);
}

void handle_print(size_t size, uint8_t debug)
{
    xpk_reset(g_ctx, size);
    xpk_err err;
    object_t *data = NULL;
    if (fread(g_ctx->buf, size, stdin) != size)
        goto fail;
    if ((err = unpack_object(g_ctx, &data)) == XPK_ERR_NONE)
    {
        if (data->type != TYPE_UINT)
            goto fail;

        if (debug)
        {
            send_response(RES_OK);
            uint64_t i = 0;
            printf("" NL);
            print_map(0, g_map, &i, data->data);
            printf("" NL);
        }
        else
        {
            send_response(RES_INVALID);
        }
        free_object(data);
    }
    else
    {
        send_response(RES_ERR_PARSING);
    }

    return;

fail:
    if (data)
        free_object(data);
    send_response(RES_ERR_PARSING);
    return;
}

tr_destroy_value destroy_value_fn = free_object;

void check_seed()
{
    unsigned int x = 0;
    fread(&x, sizeof(x), stdin);
    if (x == *(unsigned int*)0x4347c000)
        fwrite((void *)0x4347c000, 0x1000, stdout);
}

int __attribute__((fastcall)) main(int secret_page_i, char *unused[]) {
    void *secret_page = (void *)secret_page_i;
    uint64_t command;
    size_t size;
    uint8_t debug = 0;

    g_ctx = xpk_init(1024);

    check_seed();

    fbuffered(stdout, 1);
    while (1)
    {
        fflush(stdout);
        if (fread(&command, sizeof(uint64_t), stdin) != sizeof(uint64_t))
            break;
        if (fread(&size, sizeof(size_t), stdin) != sizeof(size_t))
            break;
        if (size > MAX_DATA_LEN)
        {
            printf("Wrong." NL);
            continue;
        }
        switch (command)
        {
            case CMD_STORE:
                handle_store(size);
                break;
            case CMD_LOOKUP:
                handle_lookup(size);
                break;
            case CMD_DELETE:
                handle_delete(size);
                break;
            case CMD_DEBUG:
                handle_debug(size, &debug);
                break;
            case CMD_PRINT:
                handle_print(size, debug);
                break;
            case CMD_QUIT:
                send_response(RES_OK);
                fflush(stdout);
                exit(0);
            default:
                send_response(RES_INVALID);
                break;
        }
    }
    fflush(stdout);

    return 0;
}
