#ifndef WILD_BATTLE_H_
#define WILD_BATTLE_H_

#include "Battle.h"
#include "Monster.h"

DeclareClass(WildBattle, Battle)
    unsigned int m_level;
    Monster *m_monster;
EndDeclareClass(WildBattle, Battle)

DeclareClassFunctions(WildBattle, Battle)
    DeclareFunction(WildBattle, void, init, unsigned int level);
EndDeclareClassFunctions(WildBattle)

#endif

