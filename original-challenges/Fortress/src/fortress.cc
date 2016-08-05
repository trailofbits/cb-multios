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

#include "fortress.h"

CFortress::CFortress() : m_supply(50), m_day(1), m_numSuccessfulMissions(0), m_numTotalMissions(0),
                         m_totalSupplySpent(0), m_totalSupplyEarned(0)
{
    memset(m_owner, 0, sizeof(m_owner));
}

CFortress::~CFortress()
{
}

int CFortress::GetSupply()
{
    return m_supply;
}

bool CFortress::AddSupply(int n)
{
    if (n < 0 && m_supply + n > k_maxSupply)
        return false;
    m_supply += n;
    return true;
}

bool CFortress::SubSupply(int n)
{
    if (n < 0 || m_supply - n < 0)
        return false;
    m_supply -= n;
    return true;
}

int CFortress::GetDay()
{
    return m_day;
}

void CFortress::NextDay(int n)
{
    m_day += n;
    int i;
    CList<CMission *> toRemove;
    for (i = 0; i < m_missions.GetSize(); i++)
    {
        CMission *m = m_missions.GetAt(i);
        if (!m->IsAvail())
        {
            m->SubDuration(n);
            if (m->GetDuration() <= 0)
            {
                if (m->Complete())
                {
                    fprintf(stdout, "\n### MISSION SUCCESS :) ###\n");
                    fprintf(stdout, "+ + %s + +\n", m->GetName());
                    AddSupply(m->GetRewardSupply());
                    fprintf(stdout, " => +%d Supply\n", m->GetRewardSupply());
                    int j;
                    CList<CExplorer *>* exps = m->GetExplorers();
                    for (j = 0; j < exps->GetSize(); j++)
                    {
                        CExplorer *e = exps->GetAt(j);
                        bool lvlUp = e->GainExp(m->GetRewardExp());
                        fprintf(stdout, " => <%s> +%d Experience %s\n", e->GetName(), m->GetRewardExp(), lvlUp ? "[LEVEL UP!]" : "");
                    }
                }
                else
                {
                    fprintf(stdout, "\n### MISSION FAILED :( ###\n");
                    fprintf(stdout, "- - %s - -\n", m->GetName());
                }
                toRemove.Append(m);
            }
        }
    }
    for (i = 0; i < toRemove.GetSize(); i++)
    {
        CMission *m = toRemove.GetAt(i);
        m_missions.Remove(m);
        delete m;
    }
    if (m_supply < 1000)
        m_supply += 100;
}

CList<CMission *>& CFortress::GetMissions()
{
    return m_missions;
}

CList<CExplorer *>& CFortress::GetExplorers()
{
    return m_explorers;
}

CList<CSkill *>& CFortress::GetSkills()
{
    return m_skills;
}

int CFortress::GetNumAvailableMissions()
{
    int i, n = 0;
    for (i = 0; i < m_missions.GetSize(); i++)
        n += (m_missions.GetAt(i)->IsAvail() ? 1 : 0);
    return n;
}

int CFortress::GetNumAvailableExplorers()
{
    int i, n = 0;
    for (i = 0; i < m_explorers.GetSize(); i++)
        n += (m_explorers.GetAt(i)->IsAvail() && m_explorers.GetAt(i)->IsHired() ? 1 : 0);
    return n;
}

int CFortress::GetNumHiredExplorers()
{
    int i, n = 0;
    for (i = 0; i < m_explorers.GetSize(); i++)
        n += (m_explorers.GetAt(i)->IsHired() ? 1 : 0);
    return n;
}

int CFortress::GetAvgLevel()
{
    int i, n = 0, levelSum = 0;
    for (i = 0; i < m_explorers.GetSize(); i++)
    {
        if (m_explorers.GetAt(i)->IsHired())
        {
            levelSum += m_explorers.GetAt(i)->GetLevel();
            n++;
        }
    }
    if (n == 0 || levelSum / n == 0)
        return 1;
    return levelSum / n;
}

void CFortress::SetOwner(char *owner)
{
    owner[k_maxOwnerLen] = '\0';
    strcpy(m_owner, owner);
}
