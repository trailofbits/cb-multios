#ifndef NEW_H_
#define NEW_H_

// placement new
inline void * operator new(unsigned int length, void *ptr)
{
    if (ptr == NULL)
        _terminate(1);
    return ptr;
}

#endif
