#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "oo.h"
#include "IO.h"
#include "Map.h"
#include "Random.h"

DeclareClass(Program, Object)
    IO *m_io;
    Map *m_map;
    Random *m_random;
EndDeclareClass(Program, Object)

DeclareClassFunctions(Program, Object)
    DeclareFunction(Program, void, run)
    DeclareFunction(Program, void, load_game)
    DeclareFunction(Program, void, save_game)
EndDeclareClassFunctions(Program)

extern Program *$g;
extern IO *$io;

#endif
