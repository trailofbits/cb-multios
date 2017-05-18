#ifndef RANDOM_H_
#define RANDOM_H_

#include "oo.h"

DeclareClass(Random, Object)
    unsigned int m_state0;
    unsigned int m_state1;
EndDeclareClass(Random, Object)

DeclareClassFunctions(Random, Object)
    DeclareFunction(Random, void, init, unsigned int seed);
    DeclareFunction(Random, unsigned int, randint, unsigned int upper);
    DeclareFunction(Random, unsigned int, _rand);
    DeclareFunction(Random, void, _update);
EndDeclareClassFunctions(Random)

#endif
