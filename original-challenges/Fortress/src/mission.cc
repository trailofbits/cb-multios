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
#include "mission.h"

extern int g_randIdx;
extern char *g_rand;

CMission::CMission(const char *name, const CRequirement &req, const CReward &reward) : m_req(req), m_reward(reward), m_avail(true), m_successRate(0)
{
    m_name = strndup(name, k_maxNameLength);
}

CMission::~CMission()
{
    free(m_name);
    delete m_exps;
}

void CMission::SetRequirement(const CRequirement &req)
{
    m_req = req;
}

CRequirement& CMission::GetRequirement()
{
    return m_req;
}

void CMission::SetReward(const CReward &reward)
{
    m_reward = reward;
}

CReward& CMission::GetReward()
{
    return m_reward;
}

bool CMission::IsAvail()
{
    return m_avail;
}

const char* CMission::GetName()
{
    return m_name;
}

int CMission::GetReqLevel()
{
    return m_req.m_level;
}

int CMission::GetReqGroup()
{
    return m_req.m_group;
}

int CMission::GetReqSupply()
{
    return m_req.m_supply;
}

int CMission::GetDuration()
{
    return m_req.m_duration;
}

char* CMission::GetReqTypeString()
{
    return CRequirement::ReqTypeToString(m_req.m_type);
}

CRequirement::Type CMission::EvalCounters(const CList<CExplorer *> &exps)
{
    int i;
    CRequirement::Type type, all = CRequirement::Type::NOTHING;
    for (i = 0; i < exps.GetSize(); i++)
        all |= exps.GetAt(i)->GetCounters();
    type = m_req.m_type & (~all);
    return type;
}

void CMission::Execute(const CList<CExplorer *> &explorers)
{
    m_avail = false;
    m_exps = new CList<CExplorer *>(explorers);
    int i;
    for (i = 0; i < m_exps->GetSize(); i++)
        m_exps->GetAt(i)->SetAvail(false);
}

bool CMission::Complete()
{
    CMissionEstimate* est = this->Check(*m_exps);
    int i, r = (g_rand[g_randIdx % 4096] & 0xFF) % 101;
    g_randIdx += 2;
    bool ret = false;
    if (est->GetSuccessRate() != 0 && r <= est->GetSuccessRate())
        ret = true;
    for (i = 0; i < m_exps->GetSize(); i++)
        m_exps->GetAt(i)->SetAvail(true);
    delete est;
    return ret;
}

CMissionEstimate* CMission::Check(const CList<CExplorer *> &explorers)
{
    CMissionEstimate *est = new CMissionEstimate();
    est->m_missing = EvalCounters(explorers);
    est->m_groupNeeded = m_req.m_group;
    est->m_groupSupplied = explorers.GetSize();
    est->m_successRate = 100;
    if (est->m_missing != CRequirement::Type::NOTHING)
    {
        int n = __builtin_popcount(static_cast<int>(est->m_missing));
        est->m_successRate -= n * 25;
    }
    int i;
    for (i = 0; i < explorers.GetSize(); i++)
    {
        int lvl = explorers.GetAt(i)->GetLevel();
        if (lvl < m_req.m_level)
            est->m_successRate -= ((m_req.m_level - lvl) * 5);
        est->m_successRate += 5;
    }
    if (est->m_successRate < 0 || est->m_groupSupplied < est->m_groupNeeded)
        est->m_successRate = 0;
    if (est->m_successRate > 100)
        est->m_successRate = 100;
    return est;
}

