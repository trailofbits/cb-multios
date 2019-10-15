#include "cgc_filaments.h"
#include "cgc_mutex.h"

void cgc_mutex_lock(mutex_t *m)
{
    while (m->locked)
    {
        // XXX filaments_switch to locker instead?
        m->waiter = cgc_filaments_current();
        cgc_filaments_yield();
    }

    m->locked = 1;
    m->locker = cgc_filaments_current();
    m->waiter = NULL;
}

void cgc_mutex_unlock(mutex_t *m)
{
    m->locked = 0;

    if (m->waiter)
        cgc_filaments_switch(m->waiter);
}

