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


#include <stdint.h>
#ifndef ACTIONS_H
#define ACTIONS_H

#define MAX_NAME_SIZE 127


typedef struct video {
    struct video *next;
    struct video *prev;
    char name[MAX_NAME_SIZE+1];
    uint8_t *encbuf;
    uint32_t elen;
    uint8_t *decbuf;
    uint32_t dlen: 24; //gotta save space :)
    uint32_t key : 8;
    uint32_t csum;
    bool can_delete;
} video;

video *vhead;

static video *get_video_by_name(char *);
void list(char*);
void play(char*);
void add(char*);
void remove(char*);
void quit(char*);

#endif
