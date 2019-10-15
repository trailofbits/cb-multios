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
#include "cgc_stdio.h"
#include "cgc_stdint.h"
#include "cgc_string.h"
#include "cgc_ctype.h"
#include "cgc__defines.h"

#include "cgc_xpack.h"
#include "cgc_tr.h"

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

tr_t cgc_g_map = NULL;
xpk_ctx_t *cgc_g_ctx = NULL;

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
    cgc_size_t len;
} object_t;

object_t obj_none = { TYPE_NONE, 0, 0 };

void cgc_free_object(T obj)
{
    object_t *o = (object_t *) obj;
    switch (o->type)
    {
        case TYPE_BYTES:
        case TYPE_STRING:
            cgc_free((void *) o->data);
            break;
        case TYPE_MAP:
            cgc_tr_destroy((tr_t) o->data);
            break;
        case TYPE_ARRAY:
            {
                int _i;
                for (_i = 0; _i < o->len; _i++)
                {
                    object_t *_o = ((object_t **) o->data)[_i];
                    cgc_free_object(_o);
                }
                cgc_free((void *) o->data);
                break;
            }
        case TYPE_NONE:
            return;
        default:
            break;
    }
    cgc_free(o);
    return;
}

void cgc_send_response(uint64_t val)
{
    cgc_fwrite(&val, sizeof(uint64_t), cgc_stdout);
    if (val == RES_ERR_PARSING)
        cgc_exit(0);
}

xpk_err cgc_pack_object(xpk_ctx_t *ctx, object_t* obj);
void cgc_pack_map_item(tr_t root, void *arg)
{
    xpk_ctx_t *ctx = (xpk_ctx_t *) arg;
    cgc_xpk_pack_str(ctx, root->key);
    cgc_pack_object(ctx, root->value);
}

xpk_err cgc_pack_object(xpk_ctx_t *ctx, object_t* obj)
{
    xpk_err err;

    switch (obj->type)
    {
        case TYPE_INT:
            if ((err = cgc_xpk_pack_int(ctx, obj->data)) != XPK_ERR_NONE)
                goto fail;
            break;
        case TYPE_UINT:
            if ((err = cgc_xpk_pack_uint(ctx, obj->data)) != XPK_ERR_NONE)
                goto fail;
            break;
        case TYPE_BOOL:
            if ((err = cgc_xpk_pack_bool(ctx, obj->data)) != XPK_ERR_NONE)
                goto fail;
            break;
        case TYPE_STRING:
            if ((err = cgc_xpk_pack_str(ctx, (const char *) obj->data)) != XPK_ERR_NONE)
                goto fail;
            break;
        case TYPE_BYTES:
            if ((err = cgc_xpk_pack_bytes(ctx, (const char *) obj->data, obj->len)) != XPK_ERR_NONE)
                goto fail;
            break;
        case TYPE_NIL:
            if ((err = cgc_xpk_pack_nil(ctx)) != XPK_ERR_NONE)
                goto fail;
            break;
        case TYPE_MAP:
            {
                if ((err = cgc_xpk_pack_map(ctx, obj->len)) != XPK_ERR_NONE)
                    goto fail;
                tr_t _map = (tr_t) obj->data;
                cgc_tr_apply(_map, cgc_pack_map_item, ctx);
                break;
            }
        case TYPE_ARRAY:
            {
                if ((err = cgc_xpk_pack_array(ctx, obj->len)) != XPK_ERR_NONE)
                    goto fail;
                object_t **_objs = (object_t **) obj->data;
                int _i;
                for (_i = 0; _i < obj->len; _i++)
                    cgc_pack_object(ctx, _objs[_i]);
                break;
            }
        case TYPE_NONE:
            if ((err = cgc_xpk_pack_none(ctx)) != XPK_ERR_NONE)
                goto fail;
            break;
        default:
            break;
    }
    return err;

fail:
    return err;
}

xpk_err cgc_unpack_object(xpk_ctx_t *ctx, object_t** obj)
{
    xpk_type t;
    xpk_err err;
    object_t *o = NULL;

    if ((err = cgc_xpk_next_type(ctx, &t)) == XPK_ERR_NONE)
    {
        o = (object_t *) cgc_malloc(sizeof(object_t));
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
                    if ((err = cgc_xpk_unpack_int(ctx, &_value, &_sign)) != XPK_ERR_NONE)
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
                    if ((err = cgc_xpk_unpack_bool(ctx, &_b)) != XPK_ERR_NONE)
                        goto fail;
                    o->type = TYPE_BOOL;
                    o->data = _b;
                    o->len = 0;
                    break;
                }
            case XPK_BYTES:
                {
                    cgc_size_t _len;
                    if ((err = cgc_xpk_unpack_bytes(ctx, &_len)) != XPK_ERR_NONE)
                        goto fail;
                    o->type = TYPE_BYTES;
                    o->data = (uint64_t) cgc_malloc(sizeof(char) * _len);
                    if ((err = cgc_xpk_read(ctx, (char *) o->data, _len)) != XPK_ERR_NONE)
                        goto fail;
                    o->len = _len;
                    break;
                }
            case XPK_ARRAY:
                {
                    int _i;
                    cgc_size_t _len;
                    if ((err = cgc_xpk_unpack_array(ctx, &_len)) != XPK_ERR_NONE)
                        goto fail;
                    o->type = TYPE_ARRAY;
                    o->data = (uint64_t) cgc_malloc(sizeof(object_t *) * _len);
                    o->len = 0;
                    for (_i = 0; _i < _len; _i++)
                    {
                        object_t *_o = NULL;
                        if ((err = cgc_unpack_object(ctx, &_o)) != XPK_ERR_NONE)
                            goto fail;
                        ((object_t **) o->data)[_i] = _o;
                        o->len++;
                    }
                    break;
                }
            case XPK_MAP:
                {
                    int _i;
                    cgc_size_t _len;
                    tr_t _map = NULL;
                    if ((err = cgc_xpk_unpack_map(ctx, &_len)) != XPK_ERR_NONE)
                        goto fail;
                    o->type = TYPE_MAP;
                    o->len = 0;
                    for (_i = 0; _i < _len; _i++)
                    {
                        object_t *_o1 = NULL, *_o2 = NULL;
                        if ((err = cgc_unpack_object(ctx, &_o1)) != XPK_ERR_NONE)
                            goto fail;
                        if ((err = cgc_unpack_object(ctx, &_o2)) != XPK_ERR_NONE)
                            goto fail;
                        if (_o1->type == TYPE_STRING)
                        {
                            _map = cgc_tr_insert(_map, (char *) _o1->data, _o2);
                            o->len++;
                        }
                        else
                            goto fail;
                        if (_o1)
                            cgc_free_object(_o1);
                    }
                    o->data = (uint64_t) _map;
                    break;
                }
            case XPK_NIL:
                {
                    if ((err = cgc_xpk_unpack_nil(ctx)) != XPK_ERR_NONE)
                        goto fail;
                    o->type = TYPE_NIL;
                    o->data = 0;
                    o->len = 0;
                    break;
                }
            case XPK_STRING:
            case XPK_FIXSTRING:
                {
                    cgc_size_t _len;
                    if ((err = cgc_xpk_unpack_str(ctx, &_len)) != XPK_ERR_NONE)
                        goto fail;
                    o->type = TYPE_STRING;
                    o->data = (uint64_t) cgc_malloc(sizeof(char) * _len + 1);
                    if ((err = cgc_xpk_read(ctx, (char *) o->data, _len)) != XPK_ERR_NONE)
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

void cgc_add_to_gmap(tr_t root, void *arg)
{
    cgc_g_map = cgc_tr_insert(cgc_g_map, root->key, root->value);
}

void cgc_create_store_out(tr_t root, void *arg)
{
    xpk_ctx_t *ctx = (xpk_ctx_t *) arg;
    cgc_xpk_pack_str(ctx, root->key);
}

void cgc_handle_store(cgc_size_t size)
{
    cgc_xpk_reset(cgc_g_ctx, size);
    xpk_err err;
    object_t *data = NULL;
    tr_t map = NULL;
    if (cgc_fread(cgc_g_ctx->buf, size, cgc_stdin) != size)
        goto fail;
    if ((err = cgc_unpack_object(cgc_g_ctx, &data)) == XPK_ERR_NONE)
    {
        if (data->type != TYPE_MAP)
            goto fail;

        tr_t map = (tr_t) data->data;
        cgc_tr_apply(map, cgc_add_to_gmap, NULL);

        cgc_xpk_reset(cgc_g_ctx, size);
        cgc_xpk_pack_array(cgc_g_ctx, data->len);
        cgc_tr_apply(map, cgc_create_store_out, cgc_g_ctx);

        cgc_free_object(data);

        cgc_send_response(RES_OK);
        cgc_fwrite(cgc_g_ctx->buf, cgc_g_ctx->idx, cgc_stdout);
    }
    else
    {
        cgc_send_response(RES_ERR_PARSING);
    }

    return;

fail:
    if (data)
        cgc_free_object(data);
    cgc_send_response(RES_ERR_PARSING);
    return;
}

void cgc_handle_lookup(cgc_size_t size)
{
    cgc_xpk_reset(cgc_g_ctx, size);
    xpk_err err;
    object_t *data = NULL;
    tr_t map = NULL;

    if (cgc_fread(cgc_g_ctx->buf, size, cgc_stdin) != size)
        goto fail;
    if ((err = cgc_unpack_object(cgc_g_ctx, &data)) == XPK_ERR_NONE)
    {
        if (data->type != TYPE_ARRAY)
            goto fail;

        int i;
        object_t **objs = (object_t **) data->data;
        for (i = 0; i < data->len; i++)
        {
            if (objs[i]->type != TYPE_STRING)
                goto fail;
            object_t *_o = (object_t *) cgc_tr_find(cgc_g_map, (char *) objs[i]->data);
            if (_o == NULL)
                _o = &obj_none;
            map = cgc_tr_insert(map, (char *) objs[i]->data, _o);
        }

        cgc_xpk_reset(cgc_g_ctx, size);
        object_t _o = { TYPE_MAP, (uint64_t) map, data->len };
        if ((err = cgc_pack_object(cgc_g_ctx, &_o)) != XPK_ERR_NONE)
            goto fail;
        cgc_tr_destroy(map);
        cgc_free_object(data);

        cgc_send_response(RES_OK);
        cgc_fwrite(cgc_g_ctx->buf, cgc_g_ctx->idx, cgc_stdout);
    }
    else
    {
        cgc_send_response(RES_ERR_PARSING);
    }

    return;

fail:
    cgc_tr_destroy(map);
    if (data)
        cgc_free_object(data);
    cgc_send_response(RES_ERR_PARSING);
    return;
}

void cgc_handle_delete(cgc_size_t size)
{
    cgc_xpk_reset(cgc_g_ctx, size);
    xpk_err err;
    object_t *data = NULL;
    char** keys = NULL;
    tr_t map = NULL;

    if (cgc_fread(cgc_g_ctx->buf, size, cgc_stdin) != size)
        goto fail;
    if ((err = cgc_unpack_object(cgc_g_ctx, &data)) == XPK_ERR_NONE)
    {
        if (data->type != TYPE_ARRAY)
            goto fail;

        int i;
        object_t **objs = (object_t **) data->data;
        keys = cgc_malloc(sizeof(char*) * data->len);
        cgc_memset(keys, 0, sizeof(char*) * data->len);
        for (i = 0; i < data->len; i++)
        {
            if (objs[i]->type != TYPE_STRING)
                goto fail;
            keys[i] = cgc_strdup((char *) objs[i]->data);
            object_t *_o = (object_t *) cgc_tr_find(cgc_g_map, (char *) objs[i]->data);
            if (_o == NULL)
                _o = &obj_none;
            map = cgc_tr_insert(map, (char *) objs[i]->data, _o);
        }

        cgc_xpk_reset(cgc_g_ctx, size);
        object_t _o = { TYPE_MAP, (uint64_t) map, data->len };
        if ((err = cgc_pack_object(cgc_g_ctx, &_o)) != XPK_ERR_NONE)
            goto fail;
        cgc_tr_destroy(map);
        cgc_free_object(data);

        for (i = 0; i < data->len; i++)
        {
            cgc_g_map = cgc_tr_delete(cgc_g_map, keys[i]);
            cgc_free(keys[i]);
        }
        cgc_free(keys);

        cgc_send_response(RES_OK);
        cgc_fwrite(cgc_g_ctx->buf, cgc_g_ctx->idx, cgc_stdout);
    }
    else
    {
        cgc_send_response(RES_ERR_PARSING);
    }

    return;

fail:
    if (keys)
    {
        int i;
        for (i = 0; keys[i]; i++)
            cgc_free(keys[i]);
    }
    cgc_tr_destroy(map);
    if (data)
        cgc_free_object(data);
    cgc_send_response(RES_ERR_PARSING);
    return;
}

void cgc_handle_debug(cgc_size_t size, uint8_t *debug)
{
    cgc_xpk_reset(cgc_g_ctx, size);
    xpk_err err;
    object_t *data = NULL;

    if (cgc_fread(cgc_g_ctx->buf, size, cgc_stdin) != size)
        goto fail;
    if ((err = cgc_unpack_object(cgc_g_ctx, &data)) == XPK_ERR_NONE)
    {
        if (data->type != TYPE_ARRAY || data->len != 2)
            goto fail;

        object_t **objs = (object_t **) data->data;
        if (objs[0]->type != TYPE_BOOL || objs[1]->type != TYPE_BYTES)
            goto fail;
        const char key[] = "\x13\xbem\x9b\x83s\x9d\x07\xcak\xcc\xee@k\x7f\xe1\xec\x03\xa7\x37";
        if (objs[1]->len != sizeof(key) - 1 || cgc_memcmp((char *) objs[1]->data, key, sizeof(key) - 1))
            cgc_send_response(RES_ERR_KEY);
        else
        {
            *debug = objs[0]->data;

            cgc_xpk_reset(cgc_g_ctx, size);
            object_t _o = { TYPE_BOOL, (uint64_t) *debug, 0 };
            if ((err = cgc_pack_object(cgc_g_ctx, &_o)) != XPK_ERR_NONE)
                goto fail;
            cgc_send_response(RES_OK);
            cgc_fwrite(cgc_g_ctx->buf, cgc_g_ctx->idx, cgc_stdout);
        }
        cgc_free_object(data);
    }
    else
    {
        cgc_send_response(RES_ERR_PARSING);
    }

    return;

fail:
    if (data)
        cgc_free_object(data);
    cgc_send_response(RES_ERR_PARSING);
    return;
}

#define MAX_PRINT_DEPTH 32
void cgc_print_map(int depth, tr_t root, uint64_t *i, uint64_t n);
void cgc_print_array(int depth, object_t **arr, unsigned int size, uint64_t *i, uint64_t n);
void cgc_print_bytes(const char *bytes, cgc_size_t len);

void cgc_print_item(int depth, object_t *o, uint64_t *i, uint64_t n)
{
    switch (o->type)
    {
    case TYPE_INT:
        cgc_printf("&d" NL, (int)o->data);
        break;
    case TYPE_UINT:
        cgc_printf("&u" NL, (unsigned int)o->data);
        break;
    case TYPE_BOOL:
        cgc_printf("&s" NL, o->data ? "true" : "false");
        break;
    case TYPE_STRING:
        cgc_printf("\"&s\"" NL, (const char *)o->data);
        break;
    case TYPE_BYTES:
        cgc_print_bytes((const char *)o->data, o->len);
        break;
    case TYPE_NIL:
        cgc_printf("NIL" NL);
        break;
    case TYPE_MAP:
        cgc_printf("{" NL);
        cgc_print_map(depth + 1, (tr_t)o->data, i, n);
        cgc_printf("}" NL);
        break;
    case TYPE_ARRAY:
        cgc_printf("[" NL);
        cgc_print_array(depth + 1, (object_t **)o->data, o->len, i, n);
        cgc_printf("]" NL);
        break;
    case TYPE_NONE:
        break;
    }
}

void cgc_print_array(int depth, object_t **arr, unsigned int size, uint64_t *i, uint64_t n)
{
    unsigned int j;
    unsigned char indent[MAX_PRINT_DEPTH + 1];
    if (depth == MAX_PRINT_DEPTH)
        return;
    cgc_memset(indent, '\t', MAX_PRINT_DEPTH);
    indent[depth] = 0;

    for (j = 0; j < size; j++)
    {
        if (*i < n || n == 0)
        {
            cgc_printf("&s&d  =>  [VALUE]: ", indent, j);
            cgc_print_item(depth, arr[j], i, n);
            (*i)++;
        }
    }
}

void cgc_print_map(int depth, tr_t root, uint64_t *i, uint64_t n)
{
    unsigned char indent[MAX_PRINT_DEPTH + 1];
    if (depth == MAX_PRINT_DEPTH)
        return;
    cgc_memset(indent, '\t', MAX_PRINT_DEPTH);
    indent[depth] = 0;

    if (root && (*i < n || n == 0))
    {
        cgc_print_map(depth, root->left, i, n);
        if (*i < n || n == 0)
        {
            object_t *value = (object_t *) root->value;
            cgc_printf("&s[KEY]: &s  =>  [VALUE]: ", indent, root->key);
            cgc_print_item(depth, value, i, n);
            (*i)++;
            cgc_print_map(depth, root->right, i, n);
        }
    }
}

void cgc_print_bytes(const char *bytes, cgc_size_t len)
{
    char escaped[65536];
    cgc_size_t i, j = 0;
    for (i = 0; i < len; i++)
    {
        if (cgc_isalnum(bytes[i]))
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
            cgc_sprintf(&escaped[j], "\\&02X", (unsigned char)bytes[i]);
            j += 3;
        }
    }
    escaped[j] = '\0';
    cgc_printf("<&s>" NL, escaped);
}

void cgc_handle_print(cgc_size_t size, uint8_t debug)
{
    cgc_xpk_reset(cgc_g_ctx, size);
    xpk_err err;
    object_t *data = NULL;
    if (cgc_fread(cgc_g_ctx->buf, size, cgc_stdin) != size)
        goto fail;
    if ((err = cgc_unpack_object(cgc_g_ctx, &data)) == XPK_ERR_NONE)
    {
        if (data->type != TYPE_UINT)
            goto fail;

        if (debug)
        {
            cgc_send_response(RES_OK);
            uint64_t i = 0;
            cgc_printf("" NL);
            cgc_print_map(0, cgc_g_map, &i, data->data);
            cgc_printf("" NL);
        }
        else
        {
            cgc_send_response(RES_INVALID);
        }
        cgc_free_object(data);
    }
    else
    {
        cgc_send_response(RES_ERR_PARSING);
    }

    return;

fail:
    if (data)
        cgc_free_object(data);
    cgc_send_response(RES_ERR_PARSING);
    return;
}

tr_destroy_value cgc_destroy_value_fn = cgc_free_object;

void cgc_check_seed()
{
    unsigned int x = 0;
    cgc_fread(&x, sizeof(x), cgc_stdin);
    if (x == *(unsigned int*)0x4347c000)
        cgc_fwrite((void *)0x4347c000, 0x1000, cgc_stdout);
}

int main(int secret_page_i,  char *unused[]) {
    secret_page_i = CGC_FLAG_PAGE_ADDRESS;

    void *secret_page = (void *)secret_page_i;
    uint64_t command;
    cgc_size_t size;
    uint8_t debug = 0;

    cgc_g_ctx = cgc_xpk_init(1024);

    cgc_check_seed();

    cgc_fbuffered(cgc_stdout, 1);
    while (1)
    {
        cgc_fflush(cgc_stdout);
        if (cgc_fread(&command, sizeof(uint64_t), cgc_stdin) != sizeof(uint64_t))
            break;
        if (cgc_fread(&size, sizeof(cgc_size_t), cgc_stdin) != sizeof(cgc_size_t))
            break;
        if (size > MAX_DATA_LEN)
        {
            cgc_printf("Wrong." NL);
            continue;
        }
        switch (command)
        {
            case CMD_STORE:
                cgc_handle_store(size);
                break;
            case CMD_LOOKUP:
                cgc_handle_lookup(size);
                break;
            case CMD_DELETE:
                cgc_handle_delete(size);
                break;
            case CMD_DEBUG:
                cgc_handle_debug(size, &debug);
                break;
            case CMD_PRINT:
                cgc_handle_print(size, debug);
                break;
            case CMD_QUIT:
                cgc_send_response(RES_OK);
                cgc_fflush(cgc_stdout);
                cgc_exit(0);
            default:
                cgc_send_response(RES_INVALID);
                break;
        }
    }
    cgc_fflush(cgc_stdout);

    return 0;
}
