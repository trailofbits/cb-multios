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

#include <cstdio.h>
#include <cstring.h>

#include "explorer.h"

CExplorer::CExplorer(const char *name) : m_exp(1000), m_level(1), m_skills(), m_avail(true), m_hired(false)
{
    char *tmp = strndup(name, k_maxNameLength);
    strcpy(m_name, tmp);
}

int CExplorer::GetNextExp()
{
    int i, exp = k_baseExp;
    double mult = 1.0;
    for (i = 0; i < m_level; i++)
        mult *= k_nextExpMultiplier;
    exp = static_cast<int>(exp * mult);
    return (exp - m_exp);
}

bool CExplorer::GainExp(int exp)
{
    if (m_level == k_maxLevel)
        return false;
    int oldLevel = m_level;
    while (m_level < k_maxLevel)
    {
        int nextExp = GetNextExp();
        if (exp >= nextExp)
        {
            m_level++;
            exp -= nextExp;
            m_exp += nextExp;
        }
        else
            break;
    }
    m_exp += exp;
    return oldLevel < m_level;
}

void CExplorer::ReplaceSkill(CSkill* skill, int idx)
{
    if (idx != 0 && idx != 1)
        return;
    m_skills[idx] = skill;
}

CRequirement::Type CExplorer::GetCounters()
{
    int i;
    CRequirement::Type type = CRequirement::Type::NOTHING;
    for (i = 0; i < 2; i++)
    {
        if (m_skills[i])
        {
            type |= m_skills[i]->GetCounter();
        }
    }
    return type;
}

void CExplorer::ChangeName(const char *name)
{
    strcpy(m_name, name);
}
