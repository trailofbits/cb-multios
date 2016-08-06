#include <filaments.h>
#include <mutex.h>

void mutex_lock(mutex_t *m)
{
    while (m->locked)
    {
        // XXX filaments_switch to locker instead?
        m->waiter = filaments_current();
        filaments_yield();
    }

    m->locked = 1;
    m->locker = filaments_current();
    m->waiter = NULL;
}

void mutex_unlock(mutex_t *m)
{
    m->locked = 0;

    if (m->waiter)
        filaments_switch(m->waiter);
}

