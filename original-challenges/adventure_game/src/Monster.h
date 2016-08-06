#ifndef MONSTER_H_
#define MONSTER_H_

#include "oo.h"
#include "Buffer.h"
#include "MonsterData.h"

#define MONSTER_NAME_LEN 100

DeclareClass(Monster, Object)
    char m_name[MONSTER_NAME_LEN];
    const kind_data_t *m_kind;

    unsigned int m_level;
    unsigned int m_xp;
    unsigned int m_health;
    unsigned int m_max_health;
    unsigned int m_attack;
    unsigned int m_defense;
EndDeclareClass(Monster, Object)

DeclareClassFunctions(Monster, Object)
    DeclareFunction(Monster, void, init, const kind_data_t *kind, unsigned int level)
    DeclareFunction(Monster, void, copy, Monster *)
    DeclareFunction(Monster, void, set_name, const char *name)
    DeclareFunction(Monster, void, level_up)
    DeclareFunction(Monster, int, gain_xp, unsigned int xp)

    DeclareFunction(Monster, void, serialize, Buffer *buf)
    DeclareFunction(Monster, void, deserialize, Buffer *buf)
EndDeclareClassFunctions(Monster)

#include "Array.h"

// static functions
void Monster_print_array(Array *);
void Monster_serialize_array(Array *arr, Buffer *buf);
void Monster_deserialize_array(Array *arr, Buffer *buf);
Monster *Monster_new_random(unsigned int level);

#endif
