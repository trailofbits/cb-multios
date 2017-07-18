/*
 * Author: Andrew Wesie <andrew.wesie@kapricasecurity.com>
 *
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
#include "libcgc.h"
#include "cgc_stdarg.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

cgc_size_t cgc_root64_encode(char *output, const char *input);
cgc_size_t cgc_root64_decode(char *output, const char *input);
void cgc_parcour_init(const char *key, cgc_size_t size);
unsigned char cgc_parcour_byte();

#define TOKEN_HELLO "HELLO"
#define TOKEN_AUTH "AUTH"
#define TOKEN_SET "SET"
#define TOKEN_CALL "CALL"
#define TOKEN_BYE "BYE"

#define DECLARE_HANDLER(name) static int cgc_handle_##name(char *input);
#define DECLARE_PAGE(name) static int cgc_page_##name(char *input);
DECLARE_HANDLER(hello)
DECLARE_HANDLER(auth)
DECLARE_HANDLER(set)
DECLARE_HANDLER(call)
DECLARE_PAGE(home)
DECLARE_PAGE(root64)
DECLARE_PAGE(parcour)

typedef int (*handler_t)(char *input);
typedef struct {
    const char *name;
    handler_t handler;
} handler_map_t;
typedef struct {
    const char *name;
    const char *desc;
    handler_t handler;
    int stats_count;
} cgc_page_map_t;
typedef struct variable {
    struct variable *next;
    const char *name;
    char *value;
    char data[];
} variable_t;

static handler_map_t commands[] = {
    { TOKEN_HELLO, cgc_handle_hello },
    { TOKEN_AUTH, cgc_handle_auth },
    { TOKEN_SET, cgc_handle_set },
    { TOKEN_CALL, cgc_handle_call },
    { NULL, NULL}
};

static cgc_page_map_t functions[] = {
    { "/", "Home page", cgc_page_home, 0 },
    { "/root64", "Root64 conversion tool", cgc_page_root64, 0 },
    { "/parcour", "Parcour obfuscator", cgc_page_parcour, 0 },
    { NULL, NULL },
};

static variable_t *variables = NULL;

#define INVALID_TOKEN 0
static unsigned int g_token = INVALID_TOKEN;
static int g_auth = 0;
#define MAX_OUTPUT (64*1024)
static char *g_output_buf = NULL;
static cgc_size_t g_output_len = 0;

static void output_clear()
{
    g_output_len = 0;
}

static void cgc_output_write(char *s, cgc_size_t n)
{
    cgc_size_t bytes_remaining = MAX_OUTPUT - g_output_len - 1;
    if (bytes_remaining < n)
        n = bytes_remaining;
    if (n > 0)
    {
        cgc_memcpy(g_output_buf + g_output_len, s, n);
        g_output_len += n;
    }
}

static void cgc_output_append(const char *fmt, ...)
{
    va_list ap;
    cgc_size_t bytes_remaining = MAX_OUTPUT - g_output_len - 1;

    va_start(ap, fmt);
    int n = cgc_vsnprintf(g_output_buf + g_output_len, bytes_remaining, fmt, ap);
    va_end(ap);

    if (n > 0)
        g_output_len += n;
}

static int output_transmit()
{
    if (cgc_fdprintf(STDOUT, "OK %u\n", g_output_len) < 4)
        return 1;

    cgc_size_t tx;
    if (cgc_writeall(STDOUT, g_output_buf, g_output_len) == g_output_len)
        return 0;
    else
        return 1;
}

static int send_error(int code)
{
    if (cgc_fdprintf(STDOUT, "ERROR %3d\n", code) < 10)
        return 1;
    return 0;
}

int main(int cgc_argc, char *cgc_argv[])
{
    char buf[1024];
    g_output_buf = cgc_malloc(MAX_OUTPUT);
    while (cgc_readuntil(STDIN, buf, sizeof(buf), '\n') == 0)
    {
        char *tok, *input = buf;
        if (cgc_strlen(buf) == 0)
            break;
        buf[cgc_strlen(buf)-1] = '\0'; /* remove newline */
        tok = cgc_strsep(&input, " ");
        if (tok == NULL)
            break;
        if (cgc_strcmp(tok, TOKEN_BYE) == 0)
            break;

        handler_map_t *hm;
        for (hm = commands; hm->name != NULL; hm++)
            if (cgc_strcmp(hm->name, tok) == 0)
                break;

        if (hm->name == NULL)
        {
            if (send_error(400) != 0)
                break;
        }
        else
        {
            if (hm->handler(input) != 0)
                break;
        }
    }
    cgc_fdprintf(STDOUT, "BYE\n");
    return 0;
}

static int cgc_handle_hello(char *input)
{
    if (input != NULL)
        return send_error(500);
    while (g_token == INVALID_TOKEN)
        cgc_random(&g_token, sizeof(g_token), NULL);
    if (cgc_fdprintf(STDOUT, "OK %08X\n", g_token) < 12)
        return 1;
    return 0;
}

static int cgc_handle_auth(char *input)
{
    char *arg = cgc_strsep(&input, " ");
    if (arg == NULL)
        return send_error(500);
    unsigned int token = cgc_strtoul(arg, NULL, 16);
    if (token != g_token)
        return send_error(403);
    g_auth = 1;
    if (cgc_fdprintf(STDOUT, "OK\n") < 3)
        return 1;
    return 0;
}

static int cgc_handle_set(char *input)
{
    if (!g_auth)
        return send_error(403);
    char *arg_name = cgc_strsep(&input, " ");
    char *arg_value = input;
    if (arg_value == NULL)
        return send_error(500);
    variable_t *var = cgc_malloc(sizeof(variable_t) + cgc_strlen(arg_name) + cgc_strlen(arg_value) + 2);
    if (var == NULL)
        return send_error(500);
    char *data = var->data;
    cgc_strcpy(data, arg_name);
    var->name = data;
    data += cgc_strlen(var->name) + 1;
    cgc_strcpy(data, arg_value);
    var->value = data;
    var->next = variables;
    variables = var;
    if (cgc_fdprintf(STDOUT, "OK\n") < 3)
        return 1;
    return 0;
}

static int cgc_handle_call(char *input)
{
    if (!g_auth)
        return send_error(403);
    input = cgc_strsep(&input, " ");
    if (input == NULL)
        return send_error(500);

    cgc_page_map_t *hm;
    for (hm = functions; hm->name != NULL; hm++)
        if (cgc_strcmp(hm->name, input) == 0)
            break;

    if (hm->name == NULL)
        return send_error(404);

    output_clear();
    hm->handler(input);
    hm->stats_count++;
    return output_transmit();
}

static char *cgc_variable_get(const char *name)
{
    variable_t *var;
    for (var = variables; var != NULL; var = var->next)
        if (cgc_strcmp(name, var->name) == 0)
            return var->value;
    return NULL;
}

static int cgc_page_home(char *input)
{
    cgc_page_map_t *hm;
    cgc_output_append("Directory listing\n");
    for (hm = functions; hm->name != NULL; hm++)
        cgc_output_append("\t%s (called %d times)\t\t%s\n", hm->name, hm->stats_count, hm->desc);
    cgc_output_append("\n");
    return 0;
}

static int cgc_page_root64(char *input)
{
    char buf[256];
    const char *mode = cgc_variable_get("mode");
    const char *data = cgc_variable_get("data");
    if (mode == NULL || data == NULL)
    {
        send_error(500);
        return 1;
    }

    if (cgc_strcmp(mode, "encode") == 0)
    {
#if PATCHED
        if (cgc_strlen(data) * 4 / 3 <= sizeof(buf))
#else
        if (cgc_strlen(data) / 3 * 4 <= sizeof(buf))
#endif
        {
            cgc_size_t n = cgc_root64_encode(buf, data);
            cgc_output_write(buf, n);
        }
        else
        {
            send_error(501);
            return 1;
        }
    }
    else if (cgc_strcmp(mode, "decode") == 0)
    {
        if (cgc_strlen(data) <= sizeof(buf))
        {
            cgc_size_t n = cgc_root64_decode(buf, data);
            cgc_output_write(buf, n);
        }
        else
        {
            send_error(501);
            return 1;
        }
    }
    else
    {
        send_error(500);
        return 1;
    }

    return 0;
}

static int cgc_page_parcour(char *input)
{
    char *key = cgc_variable_get("key");
    char *data = cgc_variable_get("data");
    if (key == NULL || data == NULL)
    {
        send_error(500);
        return 1;
    }
    int keylen = cgc_strlen(key);
    if (keylen > 2)
        keylen = 2;
    cgc_parcour_init(key, keylen);
    cgc_size_t i, n = cgc_strlen(data);
    for (i = 0; i < n; i++)
        data[i] ^= cgc_parcour_byte();
    cgc_output_write(data, n);

    cgc_parcour_init(key, keylen);
    for (i = 0; i < n; i++)
        data[i] ^= cgc_parcour_byte();
    return 0;
}
