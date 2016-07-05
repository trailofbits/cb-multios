#ifndef TRAINER_BATTLE_H_
#define TRAINER_BATTLE_H_

#include "Battle.h"
#include "TrainerObject.h"

DeclareClass(TrainerBattle, Battle)
    TrainerObject *m_trainer;
EndDeclareClass(TrainerBattle, Battle)

DeclareClassFunctions(TrainerBattle, Battle)
    DeclareFunction(TrainerBattle, void, init, TrainerObject *);
EndDeclareClassFunctions(TrainerBattle)

#endif
