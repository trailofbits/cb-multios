/*
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
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_queue.h"

char *cgc_peek_front(queue_t *queue)
{
    if (queue == NULL)
        return NULL;

    return queue->data;
}

int cgc_enqueue(queue_t **queue, char *data)
{
    if (data == NULL)
        return -1;

    queue_t *back = cgc_malloc(sizeof(queue_t));
    back->data = data;
    back->next = NULL;

    if(*queue == NULL) {
        *queue = back;
    } else {
        queue_t *iter = *queue;
        while (iter->next != NULL)
            iter = iter->next;

        iter->next = back;
    }

    return 0;
}

int cgc_enqueue_copy(queue_t **queue, char *data, cgc_size_t size)
{
    if (data == NULL)
        return -1;

    int data_len = cgc_strlen(data) + 1;
    if (data_len > size)
        return -1;

    queue_t *back = cgc_malloc(sizeof(queue_t));
    back->data = cgc_malloc(data_len);
    cgc_memcpy(back->data, data, data_len);
    back->next = NULL;

    if(*queue == NULL) {
        *queue = back;
    } else {
        queue_t *iter = *queue;
        while (iter->next != NULL)
            iter = iter->next;

        iter->next = back;
    }

    return 0;
}

char *cgc_dequeue_copy(queue_t **queue)
{
    if(*queue == NULL)
        return NULL;

    queue_t *front = *queue;
    char *popped_data = front->data;
    *queue = front->next;
    cgc_free(front);

    return popped_data;
}


void cgc_clear_queue(queue_t **queue)
{
    if (*queue == NULL)
        return;

    queue_t *front = *queue, *old_front;
    while(front->next != NULL) {
        cgc_free(front->data);
        old_front = front;
        front = front->next;
        cgc_free(old_front);
    }
    cgc_free(front->data);
    cgc_free(front);
    *queue = NULL;
}
