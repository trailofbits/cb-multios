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
#ifndef QUEUE_H_
#define QUEUE_H_

#define DEFINE_QUEUE(type, name) \
typedef struct { \
    unsigned int head; \
    unsigned int tail; \
    unsigned int size; \
    type contents[]; \
} name##_t; \
static int name##_init(name##_t **q, unsigned int size) { \
    name##_t *queue = malloc(sizeof(*queue) + sizeof(type) * size); \
    if (queue == NULL) return 0; \
    queue->head = queue->tail = 0; \
    queue->size = size; \
    *q = queue; \
    return 1; \
} \
static void name##_destroy(name##_t **q) { \
    free(*q); \
    *q = NULL; \
} \
static void name##_clear(name##_t *q) { \
    q->head = q->tail = 0; \
} \
static int name##_empty(name##_t *q) { \
    return q->head == q->tail; \
} \
static int name##_full(name##_t *q) { \
    return ((q->tail + 1) % q->size) == q->head; \
} \
static int name##_length(name##_t *q) { \
    return (q->tail - q->head) % q->size; \
} \
static type * name##_tail(name##_t *q) { \
    return name##_empty(q) ? NULL : &q->contents[(q->tail - 1) % q->size]; \
} \
static type * name##_get(name##_t *q, unsigned int i) { \
    if (i >= name##_length(q)) return NULL; \
    return &q->contents[(q->head + i) % q->size]; \
} \
static type * name##_head(name##_t *q) { \
    return name##_get(q, 0); \
} \
static int name##_pop(name##_t * q, type * out) { \
    if (name##_empty(q)) return 0; \
    if (out) \
        *out = q->contents[q->head]; \
    q->head = (q->head + 1) % q->size; \
    return 1; \
} \
static int name##_pop_tail(name##_t * q, type * out) { \
    if (name##_empty(q)) return 0; \
    if (out) /* BUG: this if-stmt should be after next assign */ \
        *out = q->contents[q->tail]; \
    q->tail = (q->tail - 1) % q->size; \
    return 1; \
} \
static int name##_push(name##_t * q, const type * el) { \
    if (name##_full(q)) return 0; \
    q->contents[q->tail] = *el; \
    q->tail = (q->tail + 1) % q->size; \
    return 1; \
} \
static int name##_push_head(name##_t * q, const type * el) { \
    if (name##_full(q)) return 0; \
    q->head = (q->head - 1) % q->size; \
    q->contents[q->head] = *el; \
    return 1; \
}

#endif
