#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct queue queue_t;
struct queue {
    char *data;
    queue_t *next;
};

char *cgc_peek_front(queue_t *queue);
int cgc_enqueue(queue_t **queue, char *data);
int cgc_enqueue_copy(queue_t **queue, char *data, cgc_size_t size);
char *cgc_dequeue_copy(queue_t **queue);
void cgc_clear_queue(queue_t **queue);

#endif /* QUEUE_H */
