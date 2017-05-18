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

#pragma once

class CRequirement
{
    friend class CMission;

    public:
        enum class Type : int
        {
            NOTHING = 0x0,
            GROUND_OP = 0x1,
            AERIAL_OP = 0x2,
            NAVAL_OP = 0x4,
            INTEL_OP = 0x8,
            SPECIAL_OP = 0x10,
            RESCUE_OP = 0x20
        };

        CRequirement(CRequirement::Type type, int level, int supply, int duration, int group);
        ~CRequirement();
        static char* ReqTypeToString(CRequirement::Type type);

    private:
        CRequirement::Type m_type;
        int m_level;
        int m_supply;
        int m_duration;
        int m_group;
};

inline CRequirement::Type operator | (CRequirement::Type lhs, CRequirement::Type rhs)
{
    return (CRequirement::Type)(static_cast<int>(lhs) | static_cast<int>(rhs));
}

inline CRequirement::Type& operator |= (CRequirement::Type& lhs, CRequirement::Type rhs)
{
    lhs = (CRequirement::Type)(static_cast<int>(lhs) | static_cast<int>(rhs));
    return lhs;
}

inline CRequirement::Type operator & (CRequirement::Type lhs, CRequirement::Type rhs)
{
    return (CRequirement::Type)(static_cast<int>(lhs) & static_cast<int>(rhs));
}

inline CRequirement::Type operator ~ (CRequirement::Type type)
{
    return (CRequirement::Type)(~static_cast<int>(type));
}
