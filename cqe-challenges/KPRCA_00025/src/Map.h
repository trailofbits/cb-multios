#ifndef MAP_H_
#define MAP_H_

#include "oo.h"
#include "Buffer.h"
#include "MapObject.h"
#include "Player.h"

#define MAP_WALL_ID 0xFF
#define MAP_EMPTY_ID 0xFE

DeclareClass(Map, Object)
    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_start_x;
    unsigned int m_start_y;
    unsigned char *m_map;
    MapObject *m_objects[256];
    unsigned int m_next_id;
    Player *m_player;
EndDeclareClass(Map, Object)

DeclareClassFunctions(Map, Object)
    DeclareFunction(Map, void, init, unsigned int w, unsigned int h);
    DeclareFunction(Map, void, _generate);
    DeclareFunction(Map, unsigned int, distance, int x, int y);
    DeclareFunction(Map, unsigned int, get_level, int x, int y);
    DeclareFunction(Map, unsigned char, new_id, MapObject *obj);
    DeclareFunction(Map, void, display);
    DeclareFunction(Map, void, move, int diffx, int diffy);
    DeclareFunction(Map, void, deserialize, Buffer *);
    DeclareFunction(Map, void, serialize, Buffer *);
EndDeclareClassFunctions(Map)

#endif
