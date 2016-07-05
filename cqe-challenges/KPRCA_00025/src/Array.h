#ifndef ARRAY_H_
#define ARRAY_H_

#include "oo.h"

DeclareClass(Array, Object)
    void **m_elements;
    size_t m_size;
    size_t m_count;
EndDeclareClass(Array, Object)

DeclareClassFunctions(Array, Object)
    DeclareFunction(Array, void, push, void *)
    DeclareFunction(Array, void *, pop)
    DeclareFunction(Array, void, set, size_t, void *)
    DeclareFunction(Array, void *, get, size_t)
    DeclareFunction(Array, void, enlarge, size_t)
    DeclareFunction(Array, void *, remove, size_t)
EndDeclareClassFunctions(Array)

#endif
