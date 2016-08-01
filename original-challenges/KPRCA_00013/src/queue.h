#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct queue queue_t;
struct queue {
    char *data;
    queue_t *next;
};

char *peek_front(queue_t *queue);
int enqueue(queue_t **queue, char *data);
int enqueue_copy(queue_t **queue, char *data, size_t size);
char *dequeue_copy(queue_t **queue);
void clear_queue(queue_t **queue);

#endif /* QUEUE_H */
