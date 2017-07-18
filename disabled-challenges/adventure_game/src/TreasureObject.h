#ifndef TREASURE_OBJECT_H_
#define TREASURE_OBJECT_H_

#include "oo.h"
#include "MapObject.h"

DeclareClass(TreasureObject, MapObject)
    unsigned int m_value;
EndDeclareClass(TreasureObject, MapObject)

DeclareClassFunctions(TreasureObject, MapObject)
EndDeclareClassFunctions(TreasureObject)

#endif
