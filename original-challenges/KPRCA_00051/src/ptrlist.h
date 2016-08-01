#ifndef PTRLIST_H_
#define PTRLIST_H_

#include <stdlib.h>

typedef struct
{
    size_t size;
    size_t length;

    void **datalist;
} ptrlist_t;

ptrlist_t *create_ptrlist();
int add_item(ptrlist_t *ptrlist, void *pdata);
void *get_pdata(ptrlist_t *ptrlist, size_t idx);
#define get_item(_type, _ptrlist, idx) ((_type*) get_pdata((_ptrlist), (idx)))

#endif
