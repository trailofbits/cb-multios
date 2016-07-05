/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <libcgc.h>
#include "libc.h"

#include "adler32.h"
#include "md5.h"

#define MAX_NAME_LENGTH 16
const char secret[] = "s00pEr5eCretsAUc3";

static char *
make_token(char *name)
{
    size_t size = 1;
    unsigned int *counter;
    char *token;

    if ((counter = calloc(sizeof(unsigned int))) == NULL)
        return NULL;

    size += strlen("counter=") + 2 * sizeof(unsigned int *) + 1;
    size += strlen("name=") + strlen(name);

    if ((token = calloc(size)) == NULL) {
        free(counter);
        return NULL;
    }

    strcpy(token, "counter=");
    bin_to_hex(token + strlen(token), &counter, sizeof(unsigned int *));
    strcat(token, "|name=");
    strcat(token, name);

    return token;
}

static size_t
xor_sig(const char *token, size_t token_size, char *sig)
{
    size_t sig_size = MIN(token_size, sizeof(secret) - 1);
    size_t i;

    for (i = 0; i < sig_size; i++)
        sig[i] = token[i] ^ secret[i];

    return sig_size;
}

static int
xor_login(char *name)
{
    size_t secret_size = sizeof(secret) - 1;
    size_t token_size, sig_size, signed_token_size;
    char *token, *signed_token;
    char sig[secret_size];

    if ((token = make_token(name)) == NULL)
        return -1;

    token_size = strlen(token);
    signed_token_size = token_size + 2 * secret_size + 2;

    if ((signed_token = realloc(token, signed_token_size)) == NULL) {
        free(token);
        return -1;
    }

    if ((sig_size = xor_sig(signed_token, token_size, sig)) == 0) {
        free(signed_token);
        return -1;
    }

    signed_token[token_size] = '|';
    bin_to_hex(signed_token + token_size + 1, sig, sig_size);
    signed_token[signed_token_size - 1] = '\n';

    if (write_all(STDOUT, signed_token, signed_token_size) != signed_token_size)
        return -1;

    memset(sig, '\x00', sig_size);
    memset(signed_token, '\x00', signed_token_size);
    free(signed_token);

    return 0;
}

static size_t
adler32_sig(const char *token, size_t token_size, char *sig)
{
    size_t secret_token_size = sizeof(secret) + token_size;
    char *secret_token;

    if ((secret_token = calloc(secret_token_size)) == NULL)
        return 0;

    strcpy(secret_token, secret);
    strcat(secret_token, token);
    *(unsigned int *)sig = adler32ish((unsigned char *)secret_token, secret_token_size - 1);
    
    memset(secret_token, '\x00', secret_token_size);
    free(secret_token);

    return sizeof(unsigned int);
}

static int
adler32_login(char *name)
{
    size_t token_size, sig_size, signed_token_size;
    char *token, *signed_token;
    unsigned int sig;

    if ((token = make_token(name)) == NULL)
        return -1;

    token_size = strlen(token);
    signed_token_size = token_size + 2 * sizeof(sig) + 2;

    if ((signed_token = realloc(token, signed_token_size)) == NULL) {
        free(token);
        return -1;
    }

    if ((sig_size = adler32_sig(signed_token, token_size, (char *)(&sig))) == 0) {
        free(signed_token);
        return -1;
    }

    signed_token[token_size] = '|';
    bin_to_hex(signed_token + token_size + 1, &sig, sig_size);
    signed_token[signed_token_size - 1] = '\n';

    if (write_all(STDOUT, signed_token, signed_token_size) != signed_token_size)
        return -1;

    sig = 0;
    memset(signed_token, '\x00', signed_token_size);
    free(signed_token);

    return 0;
}

static size_t
md5_sig(const char *token, size_t token_size, char *sig)
{
    size_t secret_token_size = sizeof(secret) + token_size;
    char *secret_token;

    if ((secret_token = calloc(secret_token_size)) == NULL)
        return 0;

    strcpy(secret_token, secret);
    strcat(secret_token, token);
    md5((const unsigned char *)secret_token, secret_token_size - 1, (unsigned char *)sig);
    
    memset(secret_token, '\x00', secret_token_size);
    free(secret_token);

    return 16;
}

static int
md5_login(char *name)
{
    size_t token_size, sig_size, signed_token_size;
    char *token, *signed_token;
    unsigned char sig[16];

    if ((token = make_token(name)) == NULL)
        return -1;

    token_size = strlen(token);
    signed_token_size = token_size + 2 * sizeof(sig) + 2;

    if ((signed_token = realloc(token, signed_token_size)) == NULL) {
        free(token);
        return -1;
    }

    if ((sig_size = md5_sig(signed_token, token_size, (char *)sig)) == 0) {
        free(signed_token);
        return -1;
    }

    signed_token[token_size] = '|';
    bin_to_hex(signed_token + token_size + 1, sig, sig_size);
    signed_token[signed_token_size - 1] = '\n';

    if (write_all(STDOUT, signed_token, signed_token_size) != signed_token_size)
        return -1;

    memset(sig, '\x00', sig_size);
    memset(signed_token, '\x00', signed_token_size);
    free(signed_token);

    return 0;
}

static size_t
md5_hmac_sig(const char *token, size_t token_size, char *sig)
{
    md5_hmac((const unsigned char *)secret, sizeof(secret) - 1,
            (const unsigned char *)token, token_size,
            (unsigned char *)sig);

    return 16;
}

static int
md5_hmac_login(char *name)
{
    size_t token_size, sig_size, signed_token_size;
    char *token, *signed_token;
    unsigned char sig[16];

    if ((token = make_token(name)) == NULL)
        return -1;

    token_size = strlen(token);
    signed_token_size = token_size + 2 * sizeof(sig) + 2;

    if ((signed_token = realloc(token, signed_token_size)) == NULL) {
        free(token);
        return -1;
    }

    if ((sig_size = md5_hmac_sig(signed_token, token_size, (char *)sig)) == 0) {
        free(signed_token);
        return -1;
    }

    signed_token[token_size] = '|';
    bin_to_hex(signed_token + token_size + 1, sig, sig_size);
    signed_token[signed_token_size - 1] = '\n';

    if (write_all(STDOUT, signed_token, signed_token_size) != signed_token_size)
        return -1;

    memset(sig, '\x00', sig_size);
    memset(signed_token, '\x00', signed_token_size);
    free(signed_token);

    return 0;
}
    
static int
login(char *args)
{
    int ret;
    static unsigned int cur = 0;

    int (*methods[])(char *) = {
#ifndef PATCHED
        xor_login,
        adler32_login,
        md5_login
#else
        md5_hmac_login
#endif
    };

#ifndef PATCHED
    if (strlen(args) > MAX_NAME_LENGTH)
        return -1;
#else
    if (strlen(args) > MAX_NAME_LENGTH || strchr(args, '|') != NULL)
        return -1;
#endif

    size_t num_methods = sizeof(methods) / sizeof(methods[0]);

    ret = methods[cur](args);

    if (++cur == num_methods)
        cur = 0;

    return ret;
}

static int
greet(char *token)
{
    char *user_sig, *tok;
    char calc_sig[32], hex_sig[64], message[200];
    char name[MAX_NAME_LENGTH + 1];
    unsigned int *counter = NULL;
    size_t sig_size, i;
    int matched = 0;

    size_t (*sig_methods[])(const char *, size_t, char *) = {
#ifndef PATCHED
        xor_sig,
        adler32_sig,
        md5_sig
#else
        md5_hmac_sig
#endif
    };

    if ((user_sig = strrchr(token, '|')) == NULL)
        return -1;
    *user_sig++ = '\0';

    for (i = 0; i < sizeof(sig_methods) / sizeof(sig_methods[0]); i++) {
        sig_size = sig_methods[i](token, strlen(token), calc_sig);
        bin_to_hex(hex_sig, calc_sig, sig_size);

        if (strncmp(user_sig, hex_sig, 2 * sig_size) == 0) {
            matched = 1;
            break;
        }
    }

    if (!matched)
        return -1;

    memset(name, '\x00', MAX_NAME_LENGTH + 1);
    for (tok = strtok(token, '|'); tok != NULL; tok = strtok(NULL, '|')) {
        if (strncmp(tok, "name=", 5) == 0) {
#ifndef PATCHED
            strcpy(name, tok + 5);
#else
            strncpy(name, tok + 5, MAX_NAME_LENGTH);
#endif
        } else if (strncmp(tok, "counter=", 8) == 0) {
            if (strlen(tok + 8) == 8)
                counter = (unsigned int *)hex_to_uint(tok + 8);
        }
    }

    if (strlen(name) == 0 || counter == NULL)
        return -1;

    memset(message, '\x00', sizeof(message));
    (*counter)++;

    strcpy(message, "Hello ");
    strcat(message, name);
    strcat(message, ", we've seen you ");
    itoa(*counter, message + strlen(message));
    strcat(message, " times!\n");

    if (write_all(STDOUT, message, strlen(message)) != strlen(message))
        return -1;

    return 0;
}

static int
quit(char *args)
{
    (void)(args);
    _terminate(0);
}

int
main(void) {
    char *line;
    ssize_t read;
    int ret;
    char ret_buffer[9];
    size_t i;

    struct command {
        const char *name;
        int (*cmd)(char *);
    } cmds[] = {
        { "login ", login },
        { "greet ", greet },
        { "quit", quit }
    };

    while (1) {
        if ((read = read_line(STDIN, &line)) < 0)
            return -1;

        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        ret = -1;
        for (i = 0; i < sizeof(cmds) / sizeof(cmds[0]); i++) {
            if (strncmp(line, cmds[i].name, strlen(cmds[i].name)) == 0) {
                ret = cmds[i].cmd(line + strlen(cmds[i].name));
                break;
            }
        }

        memset(line, '\0', read);
        free(line);

        bin_to_hex(ret_buffer, &ret, sizeof(ret));
        ret_buffer[2 * sizeof(ret)] = '\n';

        if (write_all(STDOUT, ret_buffer, sizeof(ret_buffer)) != sizeof(ret_buffer))
            return -1;
    }

    return 0;
}

