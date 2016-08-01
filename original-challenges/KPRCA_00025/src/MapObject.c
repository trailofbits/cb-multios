/*
 * Copyright (c) 2014 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#include "MapObject.h"
#include "NameChangeObject.h"
#include "TrainerObject.h"
#include "TreasureObject.h"
#include "VetObject.h"

DefineClass(MapObject, Object)

DefineFunction(MapObject, int, on_collide, Player *p)
{
    return 1;
}

DefineFunction(MapObject, void, deserialize, Buffer *buf)
{
    raise(EXC_NOT_IMPLEMENTED);
}

DefineFunction(MapObject, void, serialize, Buffer *buf)
{
    raise(EXC_NOT_IMPLEMENTED);
}

MapObject *MapObject_deserialize(Buffer *buf)
{
    MapObject *o = NULL;
    size_t pos = $(buf, tell);
    int type = $(buf, read_number);
    $(buf, seek, pos);

    switch(type)
    {
    case 0:
        o = new(VetObject)->super;
        break;
    case 1:
        o = new(TreasureObject)->super;
        break;
    case 2:
        o = new(TrainerObject)->super;
        break;
    case 3:
        o = new(NameChangeObject)->super;
        break;
    }

    ASSERT_OR_RAISE(o != NULL, EXC_BAD_STATE);

    $(o, deserialize, buf);
    return o;
}
