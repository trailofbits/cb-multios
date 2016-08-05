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

#include "req.h"
#include "data.h"
#include "fortress.h"

int g_randIdx = 0;
char *g_rand = NULL;
bool g_hidden = true;

CFortress g_fort;
const char *banner = "\
\n\
 _______  _______  _______ _________ _______  _______  _______  _______\n\
(  ____ \\(  ___  )(  ____ )\\__   __/(  ____ )(  ____ \\(  ____ \\(  ____ \\\n\
| (    \\/| (   ) || (    )|   ) (   | (    )|| (    \\/| (    \\/| (    \\/\n\
| (__    | |   | || (____)|   | |   | (____)|| (__    | (_____ | (_____\n\
|  __)   | |   | ||     __)   | |   |     __)|  __)   (_____  )(_____  )\n\
| (      | |   | || (\\ (      | |   | (\\ (   | (            ) |      ) |\n\
| )      | (___) || ) \\ \\__   | |   | ) \\ \\__| (____/\\/\\____) |/\\____) |\n\
|/       (_______)|/   \\__/   )_(   |/   \\__/(_______/\\_______)\\_______)\n\
                                                                  v0.1 %c\n\
\n\
";

void CreateMoreMissions()
{
    int i, j;
    int r = (g_rand[g_randIdx % 4096] & 0xFF) % 4 + 1;
    g_randIdx += 2;
    int n = sizeof(g_missions) / sizeof(g_missions[0]);
    for (i = 0; i < r; i++)
    {
        int nn = sizeof(g_skills) / sizeof(g_skills[0]);
        int group = (g_rand[g_randIdx % 4096] & 0xFF) % 3 + 1;
        g_randIdx += 2;
        CRequirement::Type type = CRequirement::Type::NOTHING;
        for (j = 0; j < group; j++)
        {
            type |= g_skills[(g_rand[g_randIdx % 4096] & 0xFF) % nn].counter;
            g_randIdx += 2;
        }
        int supply = (g_rand[g_randIdx % 4096] & 0xFF) % 30 + 1;
        g_randIdx += 2;
        int duration = (g_rand[g_randIdx % 4096] & 0xFF) % 10 + 1;
        g_randIdx += 2;
        if (group != 1)
            group--;
        CRequirement req (type, g_fort.GetAvgLevel(), supply, duration, group);
        CReward reward (g_fort.GetAvgLevel() * group * 100, supply * (supply % 4));
        CMission *mission = new CMission(g_missions[(g_rand[g_randIdx % 4096] & 0xFF) % n].name, req, reward);
        g_randIdx += 2;
        g_fort.GetMissions().Append(mission);
    }
}

void InitializeMissions()
{
    CreateMoreMissions();
}

void InitializeSkills()
{
    int i;
    for (i = 0; i < sizeof(g_skills) / sizeof(g_skills[0]); i++)
    {
        CSkill *skill = new CSkill(g_skills[i].name, g_skills[i].counter, g_skills[i].price);
        g_fort.GetSkills().Append(skill);
    }
}

void InitializeExplorers()
{
    int i;
    CSkill *no_skill = new CSkill("No Skill", CRequirement::Type::NOTHING, 0);
    for (i = 0; i < sizeof(g_explorers) / sizeof(g_explorers[0]); i++)
    {
        CExplorer *explorer = new CExplorer(g_explorers[i].name);
        CList<CSkill *>& skills = g_fort.GetSkills();
        int r = (g_rand[g_randIdx % 4096] & 0xFF) % (skills.GetSize());
        g_randIdx += 2;
        explorer->ReplaceSkill(skills.GetAt(r), 0);
        explorer->ReplaceSkill(no_skill, 1);
        g_fort.GetExplorers().Append(explorer);
    }
}

void PrintWelcomeBanner(char c)
{
    fprintf(stdout, banner, c);
}

void PrintMainMenu()
{
    int n, numMissions;
    fbuffered(stdout, 1);
    numMissions = g_fort.GetMissions().GetSize() - g_fort.GetNumAvailableMissions();
    n = fprintf(stdout, "\nDay-%03d => [%d mission] | [%d explorer] | [%d supply]\n", g_fort.GetDay(), numMissions, g_fort.GetNumHiredExplorers(), g_fort.GetSupply());
    for (; n > 1; n--)
        fprintf(stdout, "-");
    fprintf(stdout, "\n");
    fprintf(stdout, "0. Next day!\n");
    fprintf(stdout, "1. Missions\n");
    fprintf(stdout, "2. Explorers\n");
    fprintf(stdout, "3. Give up\n");
    fbuffered(stdout, 0);
}

void PrintMissionMenu()
{
    fbuffered(stdout, 1);
    fprintf(stdout, "\n]]] Missions [[[\n");
    fprintf(stdout, "1. Send mission (%d available)\n", g_fort.GetNumAvailableMissions());
    fprintf(stdout, "2. View current missions\n");
    fprintf(stdout, "3. Back\n");
    fbuffered(stdout, 0);
}

void PrintExplorerMenu()
{
    fbuffered(stdout, 1);
    fprintf(stdout, "\n]]] Explorers [[[\n");
    fprintf(stdout, "1. Hire explorer\n");
    fprintf(stdout, "2. View current explorers\n");
    fprintf(stdout, "3. Remove explorer\n");
    fprintf(stdout, "4. Learn skills\n");
    fprintf(stdout, "5. Back\n");
    if (!g_hidden)
        fprintf(stdout, "6. Change explorer name\n");
    fbuffered(stdout, 0);
}

void PrintMissions(CList<CMission *>& missions)
{
    int i;
    for (i = 0; i < missions.GetSize(); i++)
    {
        CMission *m = missions.GetAt(i);
        char *s = m->GetReqTypeString();
        fprintf(stdout, "%d. %s [LVL %d] [GRP %d] [DUR %d] [COST %d] <%s>\n", i, m->GetName(), m->GetReqLevel(), m->GetReqGroup(), m->GetDuration(), m->GetReqSupply(), s);
        fprintf(stdout, "   ==> +%d supply, +%d experience\n", m->GetRewardSupply(), m->GetRewardExp());
        free(s);
    }
}

void PrintExplorers(CList<CExplorer *>& explorers)
{
    int i;
    fbuffered(stdout, 1);
    for (i = 0; i < explorers.GetSize(); i++)
    {
        CExplorer *e = explorers.GetAt(i);
        int totalExp = e->GetExp() + e->GetNextExp();
        fprintf(stdout, "%d. %s [LVL %d] [EXP %d/%d] (%s)\n", i, e->GetName(), e->GetLevel(), e->GetExp(), totalExp, e->IsHired() ? "hired" : "not-hired");
        CSkill** skills = e->GetSkills();
        char *s = CRequirement::ReqTypeToString(skills[0]->GetCounter());
        fprintf(stdout, "   ==> Skill #1: %s <%s>\n", skills[0]->GetName(), strcmp(s, "") == 0 ? "None" : s);
        free(s);
        s = CRequirement::ReqTypeToString(skills[1]->GetCounter());
        fprintf(stdout, "   ==> Skill #2: %s <%s>\n", skills[1]->GetName(), strcmp(s, "") == 0 ? "None" : s);
        free(s);
    }
    fbuffered(stdout, 0);
}

void HandleSendMission()
{
    char buf[64];
    if (g_fort.GetNumAvailableMissions() == 0)
    {
        fprintf(stdout, "\nNo missions available. Check back later.\n");
        return;
    }
    int i;
    CList<CMission *>& missions = g_fort.GetMissions();
    CList<CMission *> availMissions;
    for (i = 0; i < missions.GetSize(); i++)
    {
        CMission *m = missions.GetAt(i);
        if (m->IsAvail())
            availMissions.Append(m);
    }
    fprintf(stdout, "\n... Available missions ...\n");
    PrintMissions(availMissions);
    if (g_fort.GetNumAvailableExplorers() == 0)
    {
        fprintf(stdout, "\nNo explorers available.\n");
        return;
    }
    fprintf(stdout, "\nselect> ");
    if (freaduntil(buf, sizeof(buf), '\n', stdin) < 0)
        exit(0);
    int idx = strtoul(buf, NULL, 10);
    if (idx >= availMissions.GetSize())
        fprintf(stdout, "Invalid mission.\n");
    else
    {
        int n;
        CMission *m = availMissions.GetAt(idx);
        if (m->GetReqSupply() > g_fort.GetSupply())
        {
            fprintf(stdout, "You don't have enough supply.\n");
            return;
        }
        CList<CExplorer *> selectedExps;
        CList<CExplorer *> availExps;
        CList<CExplorer *>& explorers = g_fort.GetExplorers();
        for (i = 0; i < explorers.GetSize(); i++)
        {
            CExplorer *e = explorers.GetAt(i);
            if (e->IsAvail() && e->IsHired())
                availExps.Append(e);
        }
        fprintf(stdout, "\n... Available explorers ...\n");
        PrintExplorers(availExps);
        fprintf(stdout, "\nselect> ");
        if (freaduntil(buf, sizeof(buf), '\n', stdin) < 0)
            exit(0);
        char *tmp = buf, *id = NULL;
        while ((id = strsep(&tmp, ",")))
        {
            if (strlen(id) == 0)
                continue;
            idx = strtoul(id, NULL, 10);
            if (idx >= availExps.GetSize())
                continue;
            CExplorer *e = availExps.GetAt(idx);
            if (!selectedExps.Has(e))
                selectedExps.Append(e);
        }
        if (selectedExps.GetSize() == 0)
        {
            fprintf(stdout, "No explorer is selected.\n");
            return;
        }

        char *s;
        fbuffered(stdout, 1);
        CMissionEstimate* est = m->Check(selectedExps);
        fprintf(stdout, "\n////////////////////////////\n");
        fprintf(stdout, "%s\n", m->GetName());
        fprintf(stdout, "////////////////////////////\n");
        fprintf(stdout, " - Success: %d%%\n", est->GetSuccessRate());
        s = CRequirement::ReqTypeToString(est->GetMissingTypes());
        fprintf(stdout, " - Missing: %s\n", strcmp(s, "") == 0 ? "None" : s);
        free(s);
        fprintf(stdout, " - Needed: %d\n", est->GetGroupNeeded());
        fprintf(stdout, " - Supplied: %d\n", est->GetGroupSupplied());
        fprintf(stdout, "////////////////////////////\n");
        fprintf(stdout, "confirm?> ");
        fbuffered(stdout, 0);
        if (freaduntil(buf, sizeof(buf), '\n', stdin) < 0)
            exit(0);
        if (strcmp(buf, "y") == 0 || strcmp(buf, "Y") == 0)
        {
            m->Execute(selectedExps);
            m->SetSuccessRate(est->GetSuccessRate());
            g_fort.SubSupply(m->GetReqSupply());
        }
        delete est;
    }
}

void HandleViewMissions()
{
    int i, n = 0;
    CList<CMission *>& missions = g_fort.GetMissions();
    fprintf(stdout, "\n... Current missions ...\n");
    for (i = 0; i < missions.GetSize(); i++)
    {
        CMission *m = missions.GetAt(i);
        if (!m->IsAvail())
        {
            fprintf(stdout, "%d. %s [%d%%] -- %d days left\n", n, m->GetName(), m->GetSuccessRate(), m->GetDuration());
            fprintf(stdout, "   ==> +%d supply, +%d experience\n", m->GetRewardSupply(), m->GetRewardExp());
            n++;
        }
    }
    if (n == 0)
        fprintf(stdout, "No missions :(\n");
}

void HandleHireExplorer()
{
    int i;
    char buf[32];
    CList<CExplorer *>& exps = g_fort.GetExplorers();
    fprintf(stdout, "\n... Available explorers ...\n");
    if (exps.GetSize() == 0 || g_fort.GetNumHiredExplorers() == exps.GetSize())
    {
        fprintf(stdout, "No explorers to hire :(\n");
        return;
    }
    if (g_fort.GetNumHiredExplorers() == g_fort.k_maxNumExplorers)
    {
        fprintf(stdout, "Can't hire more :(\n");
        return;
    }
    CList<CExplorer *> unhiredExps;
    for (i = 0; i < exps.GetSize(); i++)
    {
        CExplorer *e = exps.GetAt(i);
        if (!e->IsHired())
            unhiredExps.Append(e);
    }
    PrintExplorers(unhiredExps);
    fprintf(stdout, "\nselect> ");
    if (freaduntil(buf, sizeof(buf), '\n', stdin) < 0)
        exit(0);
    int idx = strtoul(buf, NULL, 10);
    if (idx >= unhiredExps.GetSize())
    {
        fprintf(stdout, "Invalid explorer.\n");
        return;
    }
    CExplorer *e = unhiredExps.GetAt(idx);
    e->SetHired(true);
}

void HandleViewExplorers()
{
    int i;
    CList<CExplorer *>& exps = g_fort.GetExplorers();
    CList<CExplorer *> hiredExps;
    for (i = 0; i < exps.GetSize(); i++)
    {
        CExplorer *e = exps.GetAt(i);
        if (e->IsHired())
            hiredExps.Append(e);
    }
    fprintf(stdout, "\n... Current explorers (%d/%d) ...\n", hiredExps.GetSize(), g_fort.k_maxNumExplorers);
    if (hiredExps.GetSize() == 0)
    {
        fprintf(stdout, "No explorers :(\n");
        return;
    }
    PrintExplorers(hiredExps);
}

void HandleRemoveExplorer()
{
    int i;
    char buf[8];
    CList<CExplorer *>& exps = g_fort.GetExplorers();
    CList<CExplorer *> hiredExps;
    for (i = 0; i < exps.GetSize(); i++)
    {
        CExplorer *e = exps.GetAt(i);
        if (e->IsHired() && e->IsAvail())
            hiredExps.Append(e);
    }
    fprintf(stdout, "\n... Removable explorers ...\n");
    if (hiredExps.GetSize() == 0)
    {
        fprintf(stdout, "No explorers :(\n");
        return;
    }
    PrintExplorers(hiredExps);
    fprintf(stdout, "\nselect> ");
    if (freaduntil(buf, sizeof(buf), '\n', stdin) < 0)
        exit(0);
    int idx = strtoul(buf, NULL, 10);
    if (idx >= hiredExps.GetSize())
    {
        fprintf(stdout, "Invalid explorer.\n");
        return;
    }
    CExplorer *e = hiredExps.GetAt(idx);
    e->SetHired(false);
}

void HandleLearnSkills()
{
    int i;
    char buf[8];
    CList<CExplorer *>& exps = g_fort.GetExplorers();
    CList<CExplorer *> availExps;
    for (i = 0; i < exps.GetSize(); i++)
    {
        CExplorer *e = exps.GetAt(i);
        if (e->IsHired() && e->IsAvail())
            availExps.Append(e);
    }
    fprintf(stdout, "\n... Available explorers ...\n");
    if (availExps.GetSize() == 0)
    {
        fprintf(stdout, "No explorers :(\n");
        return;
    }
    PrintExplorers(availExps);
    fprintf(stdout, "\nselect> ");
    if (freaduntil(buf, sizeof(buf), '\n', stdin) < 0)
        exit(0);
    int idx = strtoul(buf, NULL, 10);
    if (idx >= availExps.GetSize())
    {
        fprintf(stdout, "Invalid explorer.\n");
        return;
    }
    CExplorer *e = availExps.GetAt(idx);
    CList<CSkill *>& skills = g_fort.GetSkills();
    fprintf(stdout, "\n... Skills ...\n");
    for (i = 0; i < skills.GetSize(); i++)
    {
        CSkill *s = skills.GetAt(i);
        char *str = CRequirement::ReqTypeToString(s->GetCounter());
        fprintf(stdout, "%d. [%s] (counters <%s>) - %d supply\n", i, s->GetName(), str, s->GetPrice());
        free(str);
    }
    fprintf(stdout, "\nselect> ");
    if (freaduntil(buf, sizeof(buf), '\n', stdin) < 0)
        exit(0);
    idx = strtoul(buf, NULL, 10);
    if (idx >= skills.GetSize())
    {
        fprintf(stdout, "Invalid skill.\n");
        return;
    }
    CSkill *s = skills.GetAt(idx);
    if (s->GetPrice() > g_fort.GetSupply())
    {
        fprintf(stdout, "Insufficient supply.\n");
        return;
    }
    fprintf(stdout, "\nslot? (1,2)> ");
    if (freaduntil(buf, sizeof(buf), '\n', stdin) < 0)
        exit(0);
    idx = strtoul(buf, NULL, 10);
    if (idx != 1 && idx != 2)
    {
        fprintf(stdout, "Invalid slot.\n");
        return;
    }
    e->ReplaceSkill(s, idx - 1);
    g_fort.SubSupply(s->GetPrice());
}

void HandleChangeName()
{
    int i;
    char buf[8], name[512];
    CList<CExplorer *>& exps = g_fort.GetExplorers();
    CList<CExplorer *> availExps;
    for (i = 0; i < exps.GetSize(); i++)
    {
        CExplorer *e = exps.GetAt(i);
        if (e->IsHired() && e->IsAvail())
            availExps.Append(e);
    }
    fprintf(stdout, "\n... Available explorers ...\n");
    if (availExps.GetSize() == 0)
    {
        fprintf(stdout, "No explorers :(\n");
        return;
    }
    for (i = 0; i < availExps.GetSize(); i++)
        fprintf(stdout, "%d. %s\n", i, availExps.GetAt(i)->GetName());
    fprintf(stdout, "\nselect> ");
    if (freaduntil(buf, sizeof(buf), '\n', stdin) < 0)
        exit(0);
    int idx = strtoul(buf, NULL, 10);
    if (idx >= availExps.GetSize())
    {
        fprintf(stdout, "Invalid explorer.\n");
        return;
    }
    CExplorer *e = availExps.GetAt(idx);
    fprintf(stdout, "\nNew name? ");
    if (freaduntil(name, sizeof(name), '\n', stdin) < 0)
        exit(0);
#ifdef PATCHED_1
    name[CExplorer::k_maxNameLength] = '\0';
#endif
    e->ChangeName(name);
}

extern "C" int __attribute__((fastcall)) main(int secret_page_i, char *unused[])
{
    char buf[6], nameBuf[32];

    g_rand = (char *) secret_page_i;

    if (freaduntil(nameBuf, sizeof(nameBuf), '\n', stdin) < 0)
        exit(0);
    g_fort.SetOwner(nameBuf);

    PrintWelcomeBanner(g_fort.GetOwner()[0]);
    InitializeMissions();
    InitializeSkills();
    InitializeExplorers();

    while (1)
    {
        PrintMainMenu();
        g_hidden = !(g_fort.GetSupply() == 1337 && g_fort.GetDay() == 1);
        if (freaduntil(buf, sizeof(buf), '\n', stdin) < 0)
            break;
        if (strcmp(buf, "0") == 0)
        {
            g_fort.NextDay(1);
            if (g_fort.GetNumAvailableMissions() < 3)
                CreateMoreMissions();
        }
        else if (strtoul(buf, NULL, 10) == 1)
        {
            while (1)
            {
                PrintMissionMenu();
                if (freaduntil(buf, sizeof(buf), '\n', stdin) < 0)
                    break;
                if (strcmp(buf, "1") == 0)
                    HandleSendMission();
                else if (strcmp(buf, "2") == 0)
                    HandleViewMissions();
                else if (strcmp(buf, "3") == 0)
                    break;
                else
                    fprintf(stdout, "Invalid option.\n");
            }
        }
        else if (memcmp(buf, "2\0", 2) == 0)
        {
            while (1)
            {
                PrintExplorerMenu();
                if (freaduntil(buf, sizeof(buf), '\n', stdin) < 0)
                    break;
                if (strcmp(buf, "1") == 0)
                    HandleHireExplorer();
                else if (strcmp(buf, "2") == 0)
                    HandleViewExplorers();
                else if (strcmp(buf, "3") == 0)
                    HandleRemoveExplorer();
                else if (strcmp(buf, "4") == 0)
                    HandleLearnSkills();
                else if (strcmp(buf, "5") == 0)
                    break;
                else
                {
                    if (!g_hidden && strcmp(buf, "6") == 0)
                        HandleChangeName();
                    else
                        fprintf(stdout, "Invalid option.\n");
                }
            }
        }
        else if (strcmp(buf, "3") == 0)
        {
            fprintf(stdout, "Boo.\n");
            exit(0);
        }
        else
        {
            if (buf[0] == '-' && memcmp(&buf[1], "1337\0", 5) == 0)
            {
                if (g_fort.GetSupply() < strtoul(&buf[1], NULL, 10))
                    g_fort.AddSupply(1287);
                if (freaduntil(buf, sizeof(buf), '\n', stdin) < 0)
                    break;
                g_fort.NextDay(strtoul(buf, NULL, 10));
            }
            else
                fprintf(stdout, "Invalid option.\n");
        }
    }
    return 0;
}
