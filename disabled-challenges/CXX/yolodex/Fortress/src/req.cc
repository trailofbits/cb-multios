/*
 * Copyright (c) 2015 Kaprica Security, Inc.
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

#include "cgc_cstdio.h"
#include "cgc_cstring.h"
#include "cgc_req.h"

CRequirement::CRequirement(CRequirement::Type type, int level, int supply, int duration, int group)
    : m_type(type), m_level(level), m_supply(supply), m_duration(duration), m_group(group)
{
}

CRequirement::~CRequirement()
{
}

char* CRequirement::ReqTypeToString(CRequirement::Type type)
{
    char *typeString = static_cast<char *>(cgc_malloc(512));
    char *p = typeString;
    cgc_memset(typeString, 0, 512);
    if ((type & CRequirement::Type::GROUND_OP) == CRequirement::Type::GROUND_OP)
    {
        cgc_strcpy(p, "GROUND,");
        p += cgc_strlen("GROUND,");
    }
    if ((type & CRequirement::Type::AERIAL_OP) == CRequirement::Type::AERIAL_OP)
    {
        cgc_strcpy(p, "AERIAL,");
        p += cgc_strlen("AERIAL,");
    }
    if ((type & CRequirement::Type::NAVAL_OP) == CRequirement::Type::NAVAL_OP)
    {
        cgc_strcpy(p, "NAVAL,");
        p += cgc_strlen("NAVAL,");
    }
    if ((type & CRequirement::Type::INTEL_OP) == CRequirement::Type::INTEL_OP)
    {
        cgc_strcpy(p, "INTEL,");
        p += cgc_strlen("INTEL,");
    }
    if ((type & CRequirement::Type::SPECIAL_OP) == CRequirement::Type::SPECIAL_OP)
    {
        cgc_strcpy(p, "SPECIAL,");
        p += cgc_strlen("SPECIAL,");
    }
    if ((type & CRequirement::Type::RESCUE_OP) == CRequirement::Type::RESCUE_OP)
    {
        cgc_strcpy(p, "RESCUE,");
        p += cgc_strlen("RESCUE,");
    }
    typeString[cgc_strlen(typeString) - 1] = '\0';
    return typeString;
}
