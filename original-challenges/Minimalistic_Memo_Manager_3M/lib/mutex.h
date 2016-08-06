#ifndef MUTEX_H_
#define MUTEX_H_

#include <filaments.h>

typedef struct {
    unsigned int locked;
    fib_t *locker;
    fib_t *waiter;
} mutex_t;

static inline void mutex_init(mutex_t *m)
{
    m->locked = 0;
    m->locker = 0;
    m->waiter = 0;
}

void mutex_lock(mutex_t *mutex);
void mutex_unlock(mutex_t *mutex);

#endif
