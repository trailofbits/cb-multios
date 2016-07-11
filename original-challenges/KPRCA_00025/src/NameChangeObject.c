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
#include "NameChangeObject.h"

DefineClass(NameChangeObject, MapObject)

DefineFunction(NameChangeObject, void, $init)
{
    this->m_icon = 'N';
}

DefineFunction(NameChangeObject, int, on_collide, Player *p)
{
    $(p, name_change_menu);
    return 1;
}

DefineFunction(NameChangeObject, void, serialize, Buffer *buf)
{
    $(buf, write_number, 3); // used by MapObject_deserialize
    // do nothing
}

DefineFunction(NameChangeObject, void, deserialize, Buffer *buf)
{
    unsigned int type = $(buf, read_number);
    ASSERT_OR_RAISE(type == 3, EXC_BAD_STATE);
    // do nothing
}
