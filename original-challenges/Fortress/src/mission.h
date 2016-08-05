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

#include <cstdint.h>

#include "req.h"
#include "reward.h"
#include "explorer.h"
#include "list.h"

class CMissionEstimate
{
    friend class CMission;

    public:
        CMissionEstimate() {};
        ~CMissionEstimate() {};

        int GetSuccessRate() { return m_successRate; }
        int GetGroupNeeded() { return m_groupNeeded; }
        int GetGroupSupplied() { return m_groupSupplied; }
        CRequirement::Type GetMissingTypes() { return m_missing; }

    private:
        int m_successRate;
        CRequirement::Type m_missing;
        int m_groupNeeded;
        int m_groupSupplied;
};

class CMission
{
    public:
        CMission(const char *name, const CRequirement &req, const CReward &reward);
        ~CMission();

        void SetRequirement(const CRequirement &req);
        CRequirement& GetRequirement();
        void SetReward(const CReward &reward);
        CReward& GetReward();
        CList<CExplorer *>* GetExplorers() { return m_exps; }
        bool IsAvail();
        int GetSuccessRate() { return m_successRate; }
        void SetSuccessRate(int sr) { m_successRate = sr; }

        const char* GetName();
        int GetReqLevel();
        int GetReqGroup();
        int GetReqSupply();
        int GetDuration();
        void SubDuration(int n) { m_req.m_duration -= n; }
        char* GetReqTypeString();

        int GetRewardExp() { return m_reward.m_exp; }
        int GetRewardSupply() { return m_reward.m_supply; }

        void Execute(const CList<CExplorer *> &explorers);
        CMissionEstimate* Check(const CList<CExplorer *> &explorers);
        bool Complete();

    private:
        CRequirement::Type EvalCounters(const CList<CExplorer *> &exps);

        static const int k_maxNameLength = 32;

        char *m_name;
        CRequirement m_req;
        CReward m_reward;
        bool m_avail;
        int m_successRate;
        CList<CExplorer *> *m_exps;
};
