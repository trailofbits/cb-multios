#ifndef PLAYER_H_
#define PLAYER_H_

#include "oo.h"
#include "Array.h"
#include "Buffer.h"

#define TEAM_SIZE 6
#define BANK_SIZE 9

DeclareClass(Player, Object)
    // read by Map
    unsigned int m_x;
    unsigned int m_y;
    char m_icon;

    Array *m_bank;
    Array *m_team;

    unsigned int m_money;
EndDeclareClass(Player, Object)

#include "Monster.h"

DeclareClassFunctions(Player, Object)
    DeclareFunction(Player, void, init, unsigned int x, unsigned int y);
    DeclareFunction(Player, void, move, unsigned int x, unsigned int y);
    DeclareFunction(Player, void, heal);
    DeclareFunction(Player, void, capture, Monster *m);
    DeclareFunction(Player, int, is_alive);

    DeclareFunction(Player, void, serialize, Buffer *);
    DeclareFunction(Player, void, deserialize, Buffer *);

    DeclareFunction(Player, void, team_menu);
    DeclareFunction(Player, void, vet_menu);
    DeclareFunction(Player, void, name_change_menu);
EndDeclareClassFunctions(Player)

#endif
