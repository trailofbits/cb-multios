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

#include <cstdlib.h>

#include "mission.h"
#include "explorer.h"
#include "list.h"

class CFortress
{
    public:
        CFortress();
        ~CFortress();
        int GetSupply();
        bool AddSupply(int n);
        bool SubSupply(int n);
        int GetDay();
        void NextDay(int n);
        CList<CMission *>& GetMissions();
        CList<CExplorer *>& GetExplorers();
        CList<CSkill *>& GetSkills();
        int GetNumAvailableMissions();
        int GetNumAvailableExplorers();
        int GetNumHiredExplorers();
        int GetAvgLevel();
        void SetOwner(char *owner);
        char* GetOwner() { return m_owner; }

        static const int k_maxNumExplorers = 15;
        static const int k_maxOwnerLen = 16;

    private:
        static const int k_maxSupply = 2000;

        char m_owner[k_maxOwnerLen + 1];
        int m_supply;
        int m_day;
        CList<CMission *> m_missions;
        CList<CExplorer *> m_explorers;
        CList<CSkill *> m_skills;
        int m_numSuccessfulMissions;
        int m_numTotalMissions;
        int m_totalSupplySpent;
        int m_totalSupplyEarned;
};
