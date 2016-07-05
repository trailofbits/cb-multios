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
#include <libcgc.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

size_t root64_encode(char *output, const char *input);
size_t root64_decode(char *output, const char *input);
void parcour_init(const char *key, size_t size);
unsigned char parcour_byte();

#define TOKEN_HELLO "HELLO"
#define TOKEN_AUTH "AUTH"
#define TOKEN_SET "SET"
#define TOKEN_CALL "CALL"
#define TOKEN_BYE "BYE"

#define DECLARE_HANDLER(name) static int handle_##name(char *input);
#define DECLARE_PAGE(name) static int page_##name(char *input);
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
} page_map_t;
typedef struct variable {
    struct variable *next;
    const char *name;
    char *value;
    char data[];
} variable_t;

static handler_map_t commands[] = {
    { TOKEN_HELLO, handle_hello },
    { TOKEN_AUTH, handle_auth },
    { TOKEN_SET, handle_set },
    { TOKEN_CALL, handle_call },
    { NULL, NULL}
};

static page_map_t functions[] = {
    { "/", "Home page", page_home, 0 },
    { "/root64", "Root64 conversion tool", page_root64, 0 },
    { "/parcour", "Parcour obfuscator", page_parcour, 0 },
    { NULL, NULL },
};

static variable_t *variables = NULL;

#define INVALID_TOKEN 0
static unsigned int g_token = INVALID_TOKEN;
static int g_auth = 0;
#define MAX_OUTPUT (64*1024)
static char *g_output_buf = NULL;
static size_t g_output_len = 0;

static void output_clear()
{
    g_output_len = 0;
}

static void output_write(char *s, size_t n)
{
    size_t bytes_remaining = MAX_OUTPUT - g_output_len - 1;
    if (bytes_remaining < n)
        n = bytes_remaining;
    if (n > 0)
    {
        memcpy(g_output_buf + g_output_len, s, n);
        g_output_len += n;
    }
}

static void output_append(const char *fmt, ...)
{
    va_list ap;
    size_t bytes_remaining = MAX_OUTPUT - g_output_len - 1;

    va_start(ap, fmt);
    int n = vsnprintf(g_output_buf + g_output_len, bytes_remaining, fmt, ap);
    va_end(ap);

    if (n > 0)
        g_output_len += n;
}

static int output_transmit()
{
    if (fdprintf(STDOUT, "OK %u\n", g_output_len) < 4)
        return 1;

    size_t tx;
    if (writeall(STDOUT, g_output_buf, g_output_len) == g_output_len)
        return 0;
    else
        return 1;
}

static int send_error(int code)
{
    if (fdprintf(STDOUT, "ERROR %3d\n", code) < 10)
        return 1;
    return 0;
}

int main()
{
    char buf[1024];
    g_output_buf = malloc(MAX_OUTPUT);
    while (readuntil(STDIN, buf, sizeof(buf), '\n') == 0)
    {
        char *tok, *input = buf;
        if (strlen(buf) == 0)
            break;
        buf[strlen(buf)-1] = '\0'; /* remove newline */
        tok = strsep(&input, " ");
        if (tok == NULL)
            break;
        if (strcmp(tok, TOKEN_BYE) == 0)
            break;

        handler_map_t *hm;
        for (hm = commands; hm->name != NULL; hm++)
            if (strcmp(hm->name, tok) == 0)
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
    fdprintf(STDOUT, "BYE\n");
    return 0;
}

static int handle_hello(char *input)
{
    if (input != NULL)
        return send_error(500);
    while (g_token == INVALID_TOKEN)
        random(&g_token, sizeof(g_token), NULL);
    if (fdprintf(STDOUT, "OK %08X\n", g_token) < 12)
        return 1;
    return 0;
}

static int handle_auth(char *input)
{
    char *arg = strsep(&input, " ");
    if (arg == NULL)
        return send_error(500);
    unsigned int token = strtoul(arg, NULL, 16);
    if (token != g_token)
        return send_error(403);
    g_auth = 1;
    if (fdprintf(STDOUT, "OK\n") < 3)
        return 1;
    return 0;
}

static int handle_set(char *input)
{
    if (!g_auth)
        return send_error(403);
    char *arg_name = strsep(&input, " ");
    char *arg_value = input;
    if (arg_value == NULL)
        return send_error(500);
    variable_t *var = malloc(sizeof(variable_t) + strlen(arg_name) + strlen(arg_value) + 2);
    if (var == NULL)
        return send_error(500);
    char *data = var->data;
    strcpy(data, arg_name);
    var->name = data;
    data += strlen(var->name) + 1;
    strcpy(data, arg_value);
    var->value = data;
    var->next = variables;
    variables = var;
    if (fdprintf(STDOUT, "OK\n") < 3)
        return 1;
    return 0;
}

static int handle_call(char *input)
{
    if (!g_auth)
        return send_error(403);
    input = strsep(&input, " ");
    if (input == NULL)
        return send_error(500);

    page_map_t *hm;
    for (hm = functions; hm->name != NULL; hm++)
        if (strcmp(hm->name, input) == 0)
            break;

    if (hm->name == NULL)
        return send_error(404);

    output_clear();
    hm->handler(input);
    hm->stats_count++;
    return output_transmit();
}

static char *variable_get(const char *name)
{
    variable_t *var;
    for (var = variables; var != NULL; var = var->next)
        if (strcmp(name, var->name) == 0)
            return var->value;
    return NULL;
}

static int page_home(char *input)
{
    page_map_t *hm;
    output_append("Directory listing\n");
    for (hm = functions; hm->name != NULL; hm++)
        output_append("\t%s (called %d times)\t\t%s\n", hm->name, hm->stats_count, hm->desc);
    output_append("\n");
    return 0;
}

static int page_root64(char *input)
{
    char buf[256];
    const char *mode = variable_get("mode");
    const char *data = variable_get("data");
    if (mode == NULL || data == NULL)
    {
        send_error(500);
        return 1;
    }

    if (strcmp(mode, "encode") == 0)
    {
#if PATCHED
        if (strlen(data) * 4 / 3 <= sizeof(buf))
#else
        if (strlen(data) / 3 * 4 <= sizeof(buf))
#endif
        {
            size_t n = root64_encode(buf, data);
            output_write(buf, n);
        }
        else
        {
            send_error(501);
            return 1;
        }
    }
    else if (strcmp(mode, "decode") == 0)
    {
        if (strlen(data) <= sizeof(buf))
        {
            size_t n = root64_decode(buf, data);
            output_write(buf, n);
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

static int page_parcour(char *input)
{
    char *key = variable_get("key");
    char *data = variable_get("data");
    if (key == NULL || data == NULL)
    {
        send_error(500);
        return 1;
    }
    int keylen = strlen(key);
    if (keylen > 2)
        keylen = 2;
    parcour_init(key, keylen);
    size_t i, n = strlen(data);
    for (i = 0; i < n; i++)
        data[i] ^= parcour_byte();
    output_write(data, n);

    parcour_init(key, keylen);
    for (i = 0; i < n; i++)
        data[i] ^= parcour_byte();
    return 0;
}
