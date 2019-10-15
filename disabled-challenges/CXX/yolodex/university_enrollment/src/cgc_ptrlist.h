#ifndef PTRLIST_H_
#define PTRLIST_H_

#include "cgc_stdlib.h"

typedef struct
{
    cgc_size_t size;
    cgc_size_t length;

    void **datalist;
} ptrlist_t;

ptrlist_t *cgc_create_ptrlist();
int cgc_add_item(ptrlist_t *ptrlist, void *pdata);
void *cgc_get_pdata(ptrlist_t *ptrlist, cgc_size_t idx);
#define get_item(_type, _ptrlist, idx) ((_type*) cgc_get_pdata((_ptrlist), (idx)))

#endif
