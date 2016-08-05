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
#include <libc.h>
#include "list.h"
#include "adjectives.h"
#include "adverbs.h"
#include "nouns.h"
#include "verbs.h"
#include "malloc.h"
#include "crc32.h"

#define WELCOME "Welcome to EternalPass! Please enter your last password: "
#define HOWMANY "\nHow many new passwords do you need? "
#define SEED "\nWhat seed to use for pw generation (0 for system seed)? "
#define PRNG "\nAddress of custom PRNG (ALPHA, unsupported, 0 for default)? "
#define SECUREMODE "\nTry experimental secure mode (1 for yes)? "
#define SECUREMODESEEDS "\nEnter secure mode seeds: "
#define PLZWAIT "\nPlease wait while we build your password file. While you wait, here are your plaintext passwords:\n"
#define HEREITIS "\nThanks for waiting! Here is your password file. Welcome!\n"
#define MAX_NUM_PW 512
#define MAX_PW_LEN 512

#define NOUN(o,t,r,c) t = nouns_list[r](); strcat(o, t); c = (crc32(t,strlen(t))&0xff<<24)|(c>>8); free(t);
#define VERB(o,t,r,c) t = verbs_list[r](); strcat(o, t);  c = (crc32(t,strlen(t))&0xff<<24)|(c>>8); free(t);
#define ADJ(o,t,r,c) t = adjectives_list[r](); strcat(o, t); c = (crc32(t,strlen(t))&0xff<<24)|(c>>8); free(t);
#define ADV(o,t,r,c) t = adverbs_list[r](); strcat(o, t); c = (crc32(t,strlen(t))&0xff<<24)|(c>>8); free(t);

#define NOUNS(o,t,r,c) t = nouns_list[r%4096](); strcat(o, t); c = (crc32(t,strlen(t))&0xff<<24)|(c>>8); free(t);
#define VERBS(o,t,r,c) t = verbs_list[r%4096](); strcat(o, t);  c = (crc32(t,strlen(t))&0xff<<24)|(c>>8); free(t);
#define ADJS(o,t,r,c) t = adjectives_list[r%4096](); strcat(o, t); c = (crc32(t,strlen(t))&0xff<<24)|(c>>8); free(t);
#define ADVS(o,t,r,c) t = adverbs_list[r%4096](); strcat(o, t); c = (crc32(t,strlen(t))&0xff<<24)|(c>>8); free(t);

unsigned int seed;
unsigned int sseeds[4];
unsigned int (*custom_prng)(unsigned int, unsigned int);

unsigned int prng(unsigned int crc, unsigned int last) {
    //super secure PRNG
    last ^= crc;
    return last;
}

unsigned int another_prng(unsigned int crc, unsigned int last) {
    last ^= crc+0x41414141;
    return last;
}

char *gen_rand_pass() {
    unsigned int rand = 0, choice = 0, crc = 0;
    char *temp;
    unsigned int (*get_next)(unsigned int, unsigned int) = prng;
    char *out = calloc(MAX_PW_LEN);
    #ifndef PATCHED_1
    if (custom_prng)
    #else
    if (custom_prng && (custom_prng == prng || custom_prng == another_prng))
    #endif
        get_next = custom_prng;

    rand = seed;

    choice = rand % 4;

    switch(choice) {
        case 0:
            //Noun Verb Adj Noun
            NOUN(out, temp, rand>>24, crc);
            VERB(out, temp, rand>>16&0xff, crc);
            ADJ(out, temp, rand>>8&0xff, crc);
            NOUN(out, temp, rand&0xff, crc);
            break;
        case 1:
            //Adj Noun Verb Noun
            ADJ(out, temp, rand>>24, crc);
            NOUN(out, temp, rand>>16&0xff, crc);
            VERB(out, temp, rand>>8&0xff, crc);
            NOUN(out, temp, rand&0xff, crc);
            break;
        case 2:
            //Noun Verb Noun Adv
            NOUN(out, temp, rand>>24, crc);
            VERB(out, temp, rand>>16&0xff, crc);
            NOUN(out, temp, rand>>8&0xff, crc);
            ADV(out, temp, rand&0xff, crc);
            break;
        case 3:
            //Adj Noun Verb Adv
            ADJ(out, temp, rand>>24, crc);
            NOUN(out, temp, rand>>16&0xff, crc);
            VERB(out, temp, rand>>8&0xff, crc);
            ADV(out, temp, rand&0xff, crc);
            break;
    }

    seed = get_next(crc, seed);

    return out;
}

char *gen_rand_pass_secure() {
    unsigned int rand = 0, choice = 0, crc = 0;
    char *temp;
    int i;
    unsigned int (*get_next)(unsigned int, unsigned int) = prng;
    char *out = calloc(MAX_PW_LEN);
    #ifndef PATCHED_2
    if (custom_prng)
    #else
    if (custom_prng && (custom_prng == prng || custom_prng == another_prng))
    #endif
        get_next = custom_prng;

    rand = sseeds[0];

    choice = rand % 4;

    switch(choice) {
        case 0:
            //Noun Verb Adj Noun
            NOUNS(out, temp, sseeds[0], crc);
            VERBS(out, temp, sseeds[1], crc);
            ADJS(out, temp, sseeds[2], crc);
            NOUNS(out, temp, sseeds[3], crc);
            break;
        case 1:
            //Adj Noun Verb Noun
            ADJS(out, temp, sseeds[0], crc);
            NOUNS(out, temp, sseeds[1], crc);
            VERBS(out, temp, sseeds[2], crc);
            NOUNS(out, temp, sseeds[3], crc);
            break;
        case 2:
            //Noun Verb Noun Adv
            NOUNS(out, temp, sseeds[0], crc);
            VERBS(out, temp, sseeds[1], crc);
            NOUNS(out, temp, sseeds[2], crc);
            ADVS(out, temp, sseeds[3], crc);
            break;
        case 3:
            //Adj Noun Verb Adv
            ADJS(out, temp, sseeds[0], crc);
            NOUNS(out, temp, sseeds[1], crc);
            VERBS(out, temp, sseeds[2], crc);
            ADVS(out, temp, sseeds[3], crc);
            break;
    }
    
    for (i = 0; i < 4; i++) {
        RANDOM(sizeof(sseeds[0]),&sseeds[i]);
        sseeds[i] = get_next(crc, sseeds[i]);
    }

    return out;
}

void rc4init(unsigned char *s, unsigned char *k) {
    int i, j = 0, t = 0;
    int len = strlen((char*)k);

    for (i = 0; i < 256; i++)
        s[i] = i;

    for (i = 0; i < 256; i++) {
        t = s[i];
        j = (j + t + k[i % len]) % 256;
        s[i] = s[j];
        s[j] = t;
    }
}

void rc4crypt(unsigned char *s, unsigned char *d, int len) {
    int i, t, j = 0, k = 0;
    char xor[len];
    memset(xor, 0, len);

    for (i=0; i < len; i++) {
        j = (j+1) % 256;
        k = (k+s[j]) % 256;
        t = s[j];
        s[j] = s[k];
        s[k] = t;
        xor[i] = s[(s[j]+s[k]) % 256];
    }

    for (i=0; i < len; i++)
        d[i] ^= xor[i];
}

int main(void) {

    unsigned char masterpw[256] = {0};
    unsigned char rc4state[256] = {0};
    char temp[16] = {0};
    unsigned char *pwstore;
    unsigned char *out;
    unsigned int total_len;
    unsigned int count;
    int i;
    char *(*genpass)();

    if (!SENDSTR(WELCOME))
        return 1;

    if (fread_until(masterpw, '\n', sizeof(masterpw), stdin) == EXIT_FAILURE)
        return 2;

    if (!SENDSTR(HOWMANY))
        return 3;

    if (fread_until(temp, '\n', sizeof(temp), stdin) == EXIT_FAILURE)
        return 4;

    count = atoi(temp);
    fdprintf(STDERR, "count = @b\n", temp);

    if (!count)
        count = 1;

    if (count > MAX_NUM_PW)
        return 5;

    if (!SENDSTR(SEED))
        return 6;

    if (fread_until(temp, '\n', sizeof(temp), stdin) == EXIT_FAILURE)
        return 7;

    seed = atoi(temp);

    if (!seed)
        RANDOM(sizeof(seed),&seed);

    if (!SENDSTR(PRNG))
        return 8;

    if (fread_until(temp, '\n', sizeof(temp), stdin) == EXIT_FAILURE)
        return 9;

    custom_prng = (unsigned int (*)(unsigned int, unsigned int))atoi(temp);

    if (custom_prng && (unsigned int)custom_prng < 0x08000000)
        return 10;

    if (!SENDSTR(SECUREMODE))
        return 11;

    if (fread_until(temp, '\n', sizeof(temp), stdin) == EXIT_FAILURE)
        return 12;

    if (atoi(temp) == 1) {
        genpass = gen_rand_pass_secure;

        if (!SENDSTR(SECUREMODESEEDS))
            return 13;

        for (i = 0; i < 4; i++) {
            if (fread_until(temp, '\n', sizeof(temp), stdin) == EXIT_FAILURE)
                return 14;
            
            sseeds[i] = atoi(temp);
        }

    } else {
        genpass = gen_rand_pass;
    }


    if (!SENDSTR(PLZWAIT))
        return 15;

    pwstore = calloc(count*MAX_PW_LEN);
    out = pwstore;

    rc4init(rc4state, masterpw);

    for (i=0; i < count; i++) {
        int len;
        char *pw;

        if (!(pw = genpass()))
            return 16;

        if (!SENDLINE(pw))
            return 17;

        len = strlen(pw);

        rc4crypt(rc4state, (unsigned char*)pw, len);

        memcpy(out, pw, len);

        free(pw);

        out += len;
        total_len += len;
    }

    if (!SENDSTR(HEREITIS))
        return 18;

    if (sendall(STDOUT,(char*)&total_len,sizeof(total_len)) != sizeof(total_len))
        return 19;

    if (sendall(STDOUT,(char*)pwstore,total_len) != total_len)
        return 20;

    return 0;
}
