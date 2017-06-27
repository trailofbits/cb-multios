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

#include "libcgc.h"
#include "cgc_libc.h"

#include "cgc_adler32.h"
#include "cgc_md5.h"

#define MAX_NAME_LENGTH 16
const char cgc_secret[] = "s00pEr5eCretsAUc3";

static char *
cgc_make_token(char *name)
{
    cgc_size_t size = 1;
    unsigned int *counter;
    char *token;

    if ((counter = cgc_calloc(sizeof(unsigned int))) == NULL)
        return NULL;

    size += cgc_strlen("counter=") + 2 * sizeof(unsigned int *) + 1;
    size += cgc_strlen("name=") + cgc_strlen(name);

    if ((token = cgc_calloc(size)) == NULL) {
        cgc_free(counter);
        return NULL;
    }

    cgc_strcpy(token, "counter=");
    cgc_bin_to_hex(token + cgc_strlen(token), &counter, sizeof(unsigned int *));
    cgc_strcat(token, "|name=");
    cgc_strcat(token, name);

    return token;
}

static cgc_size_t
cgc_xor_sig(const char *token, cgc_size_t token_size, char *sig)
{
    cgc_size_t sig_size = MIN(token_size, sizeof(cgc_secret) - 1);
    cgc_size_t i;

    for (i = 0; i < sig_size; i++)
        sig[i] = token[i] ^ cgc_secret[i];

    return sig_size;
}

static int
cgc_xor_login(char *name)
{
    cgc_size_t secret_size = sizeof(cgc_secret) - 1;
    cgc_size_t token_size, sig_size, signed_token_size;
    char *token, *signed_token;
    char sig[secret_size];

    if ((token = cgc_make_token(name)) == NULL)
        return -1;

    token_size = cgc_strlen(token);
    signed_token_size = token_size + 2 * secret_size + 2;

    if ((signed_token = cgc_realloc(token, signed_token_size)) == NULL) {
        cgc_free(token);
        return -1;
    }

    if ((sig_size = cgc_xor_sig(signed_token, token_size, sig)) == 0) {
        cgc_free(signed_token);
        return -1;
    }

    signed_token[token_size] = '|';
    cgc_bin_to_hex(signed_token + token_size + 1, sig, sig_size);
    signed_token[signed_token_size - 1] = '\n';

    if (cgc_write_all(STDOUT, signed_token, signed_token_size) != signed_token_size)
        return -1;

    cgc_memset(sig, '\x00', sig_size);
    cgc_memset(signed_token, '\x00', signed_token_size);
    cgc_free(signed_token);

    return 0;
}

static cgc_size_t
cgc_adler32_sig(const char *token, cgc_size_t token_size, char *sig)
{
    cgc_size_t secret_token_size = sizeof(cgc_secret) + token_size;
    char *secret_token;

    if ((secret_token = cgc_calloc(secret_token_size)) == NULL)
        return 0;

    cgc_strcpy(secret_token, cgc_secret);
    cgc_strcat(secret_token, token);
    *(unsigned int *)sig = cgc_adler32ish((unsigned char *)secret_token, secret_token_size - 1);
    
    cgc_memset(secret_token, '\x00', secret_token_size);
    cgc_free(secret_token);

    return sizeof(unsigned int);
}

static int
cgc_adler32_login(char *name)
{
    cgc_size_t token_size, sig_size, signed_token_size;
    char *token, *signed_token;
    unsigned int sig;

    if ((token = cgc_make_token(name)) == NULL)
        return -1;

    token_size = cgc_strlen(token);
    signed_token_size = token_size + 2 * sizeof(sig) + 2;

    if ((signed_token = cgc_realloc(token, signed_token_size)) == NULL) {
        cgc_free(token);
        return -1;
    }

    if ((sig_size = cgc_adler32_sig(signed_token, token_size, (char *)(&sig))) == 0) {
        cgc_free(signed_token);
        return -1;
    }

    signed_token[token_size] = '|';
    cgc_bin_to_hex(signed_token + token_size + 1, &sig, sig_size);
    signed_token[signed_token_size - 1] = '\n';

    if (cgc_write_all(STDOUT, signed_token, signed_token_size) != signed_token_size)
        return -1;

    sig = 0;
    cgc_memset(signed_token, '\x00', signed_token_size);
    cgc_free(signed_token);

    return 0;
}

static cgc_size_t
cgc_md5_sig(const char *token, cgc_size_t token_size, char *sig)
{
    cgc_size_t secret_token_size = sizeof(cgc_secret) + token_size;
    char *secret_token;

    if ((secret_token = cgc_calloc(secret_token_size)) == NULL)
        return 0;

    cgc_strcpy(secret_token, cgc_secret);
    cgc_strcat(secret_token, token);
    cgc_md5((const unsigned char *)secret_token, secret_token_size - 1, (unsigned char *)sig);
    
    cgc_memset(secret_token, '\x00', secret_token_size);
    cgc_free(secret_token);

    return 16;
}

static int
cgc_md5_login(char *name)
{
    cgc_size_t token_size, sig_size, signed_token_size;
    char *token, *signed_token;
    unsigned char sig[16];

    if ((token = cgc_make_token(name)) == NULL)
        return -1;

    token_size = cgc_strlen(token);
    signed_token_size = token_size + 2 * sizeof(sig) + 2;

    if ((signed_token = cgc_realloc(token, signed_token_size)) == NULL) {
        cgc_free(token);
        return -1;
    }

    if ((sig_size = cgc_md5_sig(signed_token, token_size, (char *)sig)) == 0) {
        cgc_free(signed_token);
        return -1;
    }

    signed_token[token_size] = '|';
    cgc_bin_to_hex(signed_token + token_size + 1, sig, sig_size);
    signed_token[signed_token_size - 1] = '\n';

    if (cgc_write_all(STDOUT, signed_token, signed_token_size) != signed_token_size)
        return -1;

    cgc_memset(sig, '\x00', sig_size);
    cgc_memset(signed_token, '\x00', signed_token_size);
    cgc_free(signed_token);

    return 0;
}

static cgc_size_t
md5_hmac_sig(const char *token, cgc_size_t token_size, char *sig)
{
    cgc_md5_hmac((const unsigned char *)cgc_secret, sizeof(cgc_secret) - 1,
            (const unsigned char *)token, token_size,
            (unsigned char *)sig);

    return 16;
}

static int
md5_hmac_login(char *name)
{
    cgc_size_t token_size, sig_size, signed_token_size;
    char *token, *signed_token;
    unsigned char sig[16];

    if ((token = cgc_make_token(name)) == NULL)
        return -1;

    token_size = cgc_strlen(token);
    signed_token_size = token_size + 2 * sizeof(sig) + 2;

    if ((signed_token = cgc_realloc(token, signed_token_size)) == NULL) {
        cgc_free(token);
        return -1;
    }

    if ((sig_size = md5_hmac_sig(signed_token, token_size, (char *)sig)) == 0) {
        cgc_free(signed_token);
        return -1;
    }

    signed_token[token_size] = '|';
    cgc_bin_to_hex(signed_token + token_size + 1, sig, sig_size);
    signed_token[signed_token_size - 1] = '\n';

    if (cgc_write_all(STDOUT, signed_token, signed_token_size) != signed_token_size)
        return -1;

    cgc_memset(sig, '\x00', sig_size);
    cgc_memset(signed_token, '\x00', signed_token_size);
    cgc_free(signed_token);

    return 0;
}
    
static int
cgc_login(char *args)
{
    int ret;
    static unsigned int cur = 0;

    int (*methods[])(char *) = {
#ifndef PATCHED
        cgc_xor_login,
        cgc_adler32_login,
        cgc_md5_login
#else
        md5_hmac_login
#endif
    };

#ifndef PATCHED
    if (cgc_strlen(args) > MAX_NAME_LENGTH)
        return -1;
#else
    if (cgc_strlen(args) > MAX_NAME_LENGTH || strchr(args, '|') != NULL)
        return -1;
#endif

    cgc_size_t num_methods = sizeof(methods) / sizeof(methods[0]);

    ret = methods[cur](args);

    if (++cur == num_methods)
        cur = 0;

    return ret;
}

static int
cgc_greet(char *token)
{
    char *user_sig, *tok;
    char calc_sig[32], hex_sig[64], message[200];
    char name[MAX_NAME_LENGTH + 1];
    unsigned int *counter = NULL;
    cgc_size_t sig_size, i;
    int matched = 0;

    cgc_size_t (*sig_methods[])(const char *, cgc_size_t, char *) = {
#ifndef PATCHED
        cgc_xor_sig,
        cgc_adler32_sig,
        cgc_md5_sig
#else
        md5_hmac_sig
#endif
    };

    if ((user_sig = cgc_strrchr(token, '|')) == NULL)
        return -1;
    *user_sig++ = '\0';

    for (i = 0; i < sizeof(sig_methods) / sizeof(sig_methods[0]); i++) {
        sig_size = sig_methods[i](token, cgc_strlen(token), calc_sig);
        cgc_bin_to_hex(hex_sig, calc_sig, sig_size);

        if (cgc_strncmp(user_sig, hex_sig, 2 * sig_size) == 0) {
            matched = 1;
            break;
        }
    }

    if (!matched)
        return -1;

    cgc_memset(name, '\x00', MAX_NAME_LENGTH + 1);
    for (tok = cgc_strtok(token, '|'); tok != NULL; tok = cgc_strtok(NULL, '|')) {
        if (cgc_strncmp(tok, "name=", 5) == 0) {
#ifndef PATCHED
            cgc_strcpy(name, tok + 5);
#else
            strncpy(name, tok + 5, MAX_NAME_LENGTH);
#endif
        } else if (cgc_strncmp(tok, "counter=", 8) == 0) {
            if (cgc_strlen(tok + 8) == 8)
                counter = (unsigned int *)cgc_hex_to_uint(tok + 8);
        }
    }

    if (cgc_strlen(name) == 0 || counter == NULL)
        return -1;

    cgc_memset(message, '\x00', sizeof(message));
    (*counter)++;

    cgc_strcpy(message, "Hello ");
    cgc_strcat(message, name);
    cgc_strcat(message, ", we've seen you ");
    cgc_itoa(*counter, message + cgc_strlen(message));
    cgc_strcat(message, " times!\n");

    if (cgc_write_all(STDOUT, message, cgc_strlen(message)) != cgc_strlen(message))
        return -1;

    return 0;
}

static int
cgc_quit(char *args)
{
    (void)(args);
    cgc__terminate(0);
}

int
main(int cgc_argc, char *cgc_argv[]) {
    char *line;
    cgc_ssize_t cgc_read;
    int ret;
    char ret_buffer[9];
    cgc_size_t i;

    struct command {
        const char *name;
        int (*cmd)(char *);
    } cmds[] = {
        { "login ", cgc_login },
        { "greet ", cgc_greet },
        { "quit", cgc_quit }
    };

    while (1) {
        if ((cgc_read = cgc_read_line(STDIN, &line)) < 0)
            return -1;

        if (line[cgc_read - 1] == '\n')
            line[cgc_read - 1] = '\0';

        ret = -1;
        for (i = 0; i < sizeof(cmds) / sizeof(cmds[0]); i++) {
            if (cgc_strncmp(line, cmds[i].name, cgc_strlen(cmds[i].name)) == 0) {
                ret = cmds[i].cmd(line + cgc_strlen(cmds[i].name));
                break;
            }
        }

        cgc_memset(line, '\0', cgc_read);
        cgc_free(line);

        cgc_bin_to_hex(ret_buffer, &ret, sizeof(ret));
        ret_buffer[2 * sizeof(ret)] = '\n';

        if (cgc_write_all(STDOUT, ret_buffer, sizeof(ret_buffer)) != sizeof(ret_buffer))
            return -1;
    }

    return 0;
}

