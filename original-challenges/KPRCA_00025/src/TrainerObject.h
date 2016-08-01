#ifndef TRAINER_OBJECT_H_
#define TRAINER_OBJECT_H_

#include "oo.h"
#include "Array.h"
#include "MapObject.h"

#define TRAINER_NAME_LEN 10

DeclareClass(TrainerObject, MapObject)
    char m_name[TRAINER_NAME_LEN];
    int m_player_won;
    unsigned int m_level;
    unsigned int m_reward;

    Array *m_team;
EndDeclareClass(TrainerObject, MapObject)

DeclareClassFunctions(TrainerObject, MapObject)
    DeclareFunction(TrainerObject, void, init, unsigned int level);
EndDeclareClassFunctions(TrainerObject)

#endif
