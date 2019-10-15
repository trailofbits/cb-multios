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
#include "cgc_data.h"
#include "cgc_fortress.h"

int cgc_g_randIdx = 0;
char *cgc_g_rand = NULL;
bool g_hidden = true;

CFortress cgc_g_fort;
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
    int r = (cgc_g_rand[cgc_g_randIdx % 4096] & 0xFF) % 4 + 1;
    cgc_g_randIdx += 2;
    int n = sizeof(g_missions) / sizeof(g_missions[0]);
    for (i = 0; i < r; i++)
    {
        int nn = sizeof(g_skills) / sizeof(g_skills[0]);
        int group = (cgc_g_rand[cgc_g_randIdx % 4096] & 0xFF) % 3 + 1;
        cgc_g_randIdx += 2;
        CRequirement::Type type = CRequirement::Type::NOTHING;
        for (j = 0; j < group; j++)
        {
            type |= g_skills[(cgc_g_rand[cgc_g_randIdx % 4096] & 0xFF) % nn].counter;
            cgc_g_randIdx += 2;
        }
        int supply = (cgc_g_rand[cgc_g_randIdx % 4096] & 0xFF) % 30 + 1;
        cgc_g_randIdx += 2;
        int duration = (cgc_g_rand[cgc_g_randIdx % 4096] & 0xFF) % 10 + 1;
        cgc_g_randIdx += 2;
        if (group != 1)
            group--;
        CRequirement req (type, cgc_g_fort.GetAvgLevel(), supply, duration, group);
        CReward reward (cgc_g_fort.GetAvgLevel() * group * 100, supply * (supply % 4));
        CMission *mission = new CMission(g_missions[(cgc_g_rand[cgc_g_randIdx % 4096] & 0xFF) % n].name, req, reward);
        cgc_g_randIdx += 2;
        cgc_g_fort.GetMissions().Append(mission);
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
        cgc_g_fort.GetSkills().Append(skill);
    }
}

void InitializeExplorers()
{
    int i;
    CSkill *no_skill = new CSkill("No Skill", CRequirement::Type::NOTHING, 0);
    for (i = 0; i < sizeof(g_explorers) / sizeof(g_explorers[0]); i++)
    {
        CExplorer *explorer = new CExplorer(g_explorers[i].name);
        CList<CSkill *>& skills = cgc_g_fort.GetSkills();
        int r = (cgc_g_rand[cgc_g_randIdx % 4096] & 0xFF) % (skills.GetSize());
        cgc_g_randIdx += 2;
        explorer->ReplaceSkill(skills.GetAt(r), 0);
        explorer->ReplaceSkill(no_skill, 1);
        cgc_g_fort.GetExplorers().Append(explorer);
    }
}

void PrintWelcomeBanner(char c)
{
    cgc_fprintf(cgc_stdout, banner, c);
}

void PrintMainMenu()
{
    int n, numMissions;
    cgc_fbuffered(cgc_stdout, 1);
    numMissions = cgc_g_fort.GetMissions().GetSize() - cgc_g_fort.GetNumAvailableMissions();
    n = cgc_fprintf(cgc_stdout, "\nDay-%03d => [%d mission] | [%d explorer] | [%d supply]\n", cgc_g_fort.GetDay(), numMissions, cgc_g_fort.GetNumHiredExplorers(), cgc_g_fort.GetSupply());
    for (; n > 1; n--)
        cgc_fprintf(cgc_stdout, "-");
    cgc_fprintf(cgc_stdout, "\n");
    cgc_fprintf(cgc_stdout, "0. Next day!\n");
    cgc_fprintf(cgc_stdout, "1. Missions\n");
    cgc_fprintf(cgc_stdout, "2. Explorers\n");
    cgc_fprintf(cgc_stdout, "3. Give up\n");
    cgc_fbuffered(cgc_stdout, 0);
}

void PrintMissionMenu()
{
    cgc_fbuffered(cgc_stdout, 1);
    cgc_fprintf(cgc_stdout, "\n]]] Missions [[[\n");
    cgc_fprintf(cgc_stdout, "1. Send mission (%d available)\n", cgc_g_fort.GetNumAvailableMissions());
    cgc_fprintf(cgc_stdout, "2. View current missions\n");
    cgc_fprintf(cgc_stdout, "3. Back\n");
    cgc_fbuffered(cgc_stdout, 0);
}

void PrintExplorerMenu()
{
    cgc_fbuffered(cgc_stdout, 1);
    cgc_fprintf(cgc_stdout, "\n]]] Explorers [[[\n");
    cgc_fprintf(cgc_stdout, "1. Hire explorer\n");
    cgc_fprintf(cgc_stdout, "2. View current explorers\n");
    cgc_fprintf(cgc_stdout, "3. Remove explorer\n");
    cgc_fprintf(cgc_stdout, "4. Learn skills\n");
    cgc_fprintf(cgc_stdout, "5. Back\n");
    if (!g_hidden)
        cgc_fprintf(cgc_stdout, "6. Change explorer name\n");
    cgc_fbuffered(cgc_stdout, 0);
}

void PrintMissions(CList<CMission *>& missions)
{
    int i;
    for (i = 0; i < missions.GetSize(); i++)
    {
        CMission *m = missions.GetAt(i);
        char *s = m->GetReqTypeString();
        cgc_fprintf(cgc_stdout, "%d. %s [LVL %d] [GRP %d] [DUR %d] [COST %d] <%s>\n", i, m->GetName(), m->GetReqLevel(), m->GetReqGroup(), m->GetDuration(), m->GetReqSupply(), s);
        cgc_fprintf(cgc_stdout, "   ==> +%d supply, +%d experience\n", m->GetRewardSupply(), m->GetRewardExp());
        cgc_free(s);
    }
}

void PrintExplorers(CList<CExplorer *>& explorers)
{
    int i;
    cgc_fbuffered(cgc_stdout, 1);
    for (i = 0; i < explorers.GetSize(); i++)
    {
        CExplorer *e = explorers.GetAt(i);
        int totalExp = e->GetExp() + e->GetNextExp();
        cgc_fprintf(cgc_stdout, "%d. %s [LVL %d] [EXP %d/%d] (%s)\n", i, e->GetName(), e->GetLevel(), e->GetExp(), totalExp, e->IsHired() ? "hired" : "not-hired");
        CSkill** skills = e->GetSkills();
        char *s = CRequirement::ReqTypeToString(skills[0]->GetCounter());
        cgc_fprintf(cgc_stdout, "   ==> Skill #1: %s <%s>\n", skills[0]->GetName(), cgc_strcmp(s, "") == 0 ? "None" : s);
        cgc_free(s);
        s = CRequirement::ReqTypeToString(skills[1]->GetCounter());
        cgc_fprintf(cgc_stdout, "   ==> Skill #2: %s <%s>\n", skills[1]->GetName(), cgc_strcmp(s, "") == 0 ? "None" : s);
        cgc_free(s);
    }
    cgc_fbuffered(cgc_stdout, 0);
}

void HandleSendMission()
{
    char buf[64];
    if (cgc_g_fort.GetNumAvailableMissions() == 0)
    {
        cgc_fprintf(cgc_stdout, "\nNo missions available. Check back later.\n");
        return;
    }
    int i;
    CList<CMission *>& missions = cgc_g_fort.GetMissions();
    CList<CMission *> availMissions;
    for (i = 0; i < missions.GetSize(); i++)
    {
        CMission *m = missions.GetAt(i);
        if (m->IsAvail())
            availMissions.Append(m);
    }
    cgc_fprintf(cgc_stdout, "\n... Available missions ...\n");
    PrintMissions(availMissions);
    if (cgc_g_fort.GetNumAvailableExplorers() == 0)
    {
        cgc_fprintf(cgc_stdout, "\nNo explorers available.\n");
        return;
    }
    cgc_fprintf(cgc_stdout, "\nselect> ");
    if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) < 0)
        cgc_exit(0);
    int idx = cgc_strtoul(buf, NULL, 10);
    if (idx >= availMissions.GetSize())
        cgc_fprintf(cgc_stdout, "Invalid mission.\n");
    else
    {
        int n;
        CMission *m = availMissions.GetAt(idx);
        if (m->GetReqSupply() > cgc_g_fort.GetSupply())
        {
            cgc_fprintf(cgc_stdout, "You don't have enough supply.\n");
            return;
        }
        CList<CExplorer *> selectedExps;
        CList<CExplorer *> availExps;
        CList<CExplorer *>& explorers = cgc_g_fort.GetExplorers();
        for (i = 0; i < explorers.GetSize(); i++)
        {
            CExplorer *e = explorers.GetAt(i);
            if (e->IsAvail() && e->IsHired())
                availExps.Append(e);
        }
        cgc_fprintf(cgc_stdout, "\n... Available explorers ...\n");
        PrintExplorers(availExps);
        cgc_fprintf(cgc_stdout, "\nselect> ");
        if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) < 0)
            cgc_exit(0);
        char *tmp = buf, *id = NULL;
        while ((id = cgc_strsep(&tmp, ",")))
        {
            if (cgc_strlen(id) == 0)
                continue;
            idx = cgc_strtoul(id, NULL, 10);
            if (idx >= availExps.GetSize())
                continue;
            CExplorer *e = availExps.GetAt(idx);
            if (!selectedExps.Has(e))
                selectedExps.Append(e);
        }
        if (selectedExps.GetSize() == 0)
        {
            cgc_fprintf(cgc_stdout, "No explorer is selected.\n");
            return;
        }

        char *s;
        cgc_fbuffered(cgc_stdout, 1);
        CMissionEstimate* est = m->Check(selectedExps);
        cgc_fprintf(cgc_stdout, "\n////////////////////////////\n");
        cgc_fprintf(cgc_stdout, "%s\n", m->GetName());
        cgc_fprintf(cgc_stdout, "////////////////////////////\n");
        cgc_fprintf(cgc_stdout, " - Success: %d%%\n", est->GetSuccessRate());
        s = CRequirement::ReqTypeToString(est->GetMissingTypes());
        cgc_fprintf(cgc_stdout, " - Missing: %s\n", cgc_strcmp(s, "") == 0 ? "None" : s);
        cgc_free(s);
        cgc_fprintf(cgc_stdout, " - Needed: %d\n", est->GetGroupNeeded());
        cgc_fprintf(cgc_stdout, " - Supplied: %d\n", est->GetGroupSupplied());
        cgc_fprintf(cgc_stdout, "////////////////////////////\n");
        cgc_fprintf(cgc_stdout, "confirm?> ");
        cgc_fbuffered(cgc_stdout, 0);
        if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) < 0)
            cgc_exit(0);
        if (cgc_strcmp(buf, "y") == 0 || cgc_strcmp(buf, "Y") == 0)
        {
            m->Execute(selectedExps);
            m->SetSuccessRate(est->GetSuccessRate());
            cgc_g_fort.SubSupply(m->GetReqSupply());
        }
        delete est;
    }
}

void HandleViewMissions()
{
    int i, n = 0;
    CList<CMission *>& missions = cgc_g_fort.GetMissions();
    cgc_fprintf(cgc_stdout, "\n... Current missions ...\n");
    for (i = 0; i < missions.GetSize(); i++)
    {
        CMission *m = missions.GetAt(i);
        if (!m->IsAvail())
        {
            cgc_fprintf(cgc_stdout, "%d. %s [%d%%] -- %d days left\n", n, m->GetName(), m->GetSuccessRate(), m->GetDuration());
            cgc_fprintf(cgc_stdout, "   ==> +%d supply, +%d experience\n", m->GetRewardSupply(), m->GetRewardExp());
            n++;
        }
    }
    if (n == 0)
        cgc_fprintf(cgc_stdout, "No missions :(\n");
}

void HandleHireExplorer()
{
    int i;
    char buf[32];
    CList<CExplorer *>& exps = cgc_g_fort.GetExplorers();
    cgc_fprintf(cgc_stdout, "\n... Available explorers ...\n");
    if (exps.GetSize() == 0 || cgc_g_fort.GetNumHiredExplorers() == exps.GetSize())
    {
        cgc_fprintf(cgc_stdout, "No explorers to hire :(\n");
        return;
    }
    if (cgc_g_fort.GetNumHiredExplorers() == cgc_g_fort.k_maxNumExplorers)
    {
        cgc_fprintf(cgc_stdout, "Can't hire more :(\n");
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
    cgc_fprintf(cgc_stdout, "\nselect> ");
    if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) < 0)
        cgc_exit(0);
    int idx = cgc_strtoul(buf, NULL, 10);
    if (idx >= unhiredExps.GetSize())
    {
        cgc_fprintf(cgc_stdout, "Invalid explorer.\n");
        return;
    }
    CExplorer *e = unhiredExps.GetAt(idx);
    e->SetHired(true);
}

void HandleViewExplorers()
{
    int i;
    CList<CExplorer *>& exps = cgc_g_fort.GetExplorers();
    CList<CExplorer *> hiredExps;
    for (i = 0; i < exps.GetSize(); i++)
    {
        CExplorer *e = exps.GetAt(i);
        if (e->IsHired())
            hiredExps.Append(e);
    }
    cgc_fprintf(cgc_stdout, "\n... Current explorers (%d/%d) ...\n", hiredExps.GetSize(), cgc_g_fort.k_maxNumExplorers);
    if (hiredExps.GetSize() == 0)
    {
        cgc_fprintf(cgc_stdout, "No explorers :(\n");
        return;
    }
    PrintExplorers(hiredExps);
}

void HandleRemoveExplorer()
{
    int i;
    char buf[8];
    CList<CExplorer *>& exps = cgc_g_fort.GetExplorers();
    CList<CExplorer *> hiredExps;
    for (i = 0; i < exps.GetSize(); i++)
    {
        CExplorer *e = exps.GetAt(i);
        if (e->IsHired() && e->IsAvail())
            hiredExps.Append(e);
    }
    cgc_fprintf(cgc_stdout, "\n... Removable explorers ...\n");
    if (hiredExps.GetSize() == 0)
    {
        cgc_fprintf(cgc_stdout, "No explorers :(\n");
        return;
    }
    PrintExplorers(hiredExps);
    cgc_fprintf(cgc_stdout, "\nselect> ");
    if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) < 0)
        cgc_exit(0);
    int idx = cgc_strtoul(buf, NULL, 10);
    if (idx >= hiredExps.GetSize())
    {
        cgc_fprintf(cgc_stdout, "Invalid explorer.\n");
        return;
    }
    CExplorer *e = hiredExps.GetAt(idx);
    e->SetHired(false);
}

void HandleLearnSkills()
{
    int i;
    char buf[8];
    CList<CExplorer *>& exps = cgc_g_fort.GetExplorers();
    CList<CExplorer *> availExps;
    for (i = 0; i < exps.GetSize(); i++)
    {
        CExplorer *e = exps.GetAt(i);
        if (e->IsHired() && e->IsAvail())
            availExps.Append(e);
    }
    cgc_fprintf(cgc_stdout, "\n... Available explorers ...\n");
    if (availExps.GetSize() == 0)
    {
        cgc_fprintf(cgc_stdout, "No explorers :(\n");
        return;
    }
    PrintExplorers(availExps);
    cgc_fprintf(cgc_stdout, "\nselect> ");
    if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) < 0)
        cgc_exit(0);
    int idx = cgc_strtoul(buf, NULL, 10);
    if (idx >= availExps.GetSize())
    {
        cgc_fprintf(cgc_stdout, "Invalid explorer.\n");
        return;
    }
    CExplorer *e = availExps.GetAt(idx);
    CList<CSkill *>& skills = cgc_g_fort.GetSkills();
    cgc_fprintf(cgc_stdout, "\n... Skills ...\n");
    for (i = 0; i < skills.GetSize(); i++)
    {
        CSkill *s = skills.GetAt(i);
        char *str = CRequirement::ReqTypeToString(s->GetCounter());
        cgc_fprintf(cgc_stdout, "%d. [%s] (counters <%s>) - %d supply\n", i, s->GetName(), str, s->GetPrice());
        cgc_free(str);
    }
    cgc_fprintf(cgc_stdout, "\nselect> ");
    if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) < 0)
        cgc_exit(0);
    idx = cgc_strtoul(buf, NULL, 10);
    if (idx >= skills.GetSize())
    {
        cgc_fprintf(cgc_stdout, "Invalid skill.\n");
        return;
    }
    CSkill *s = skills.GetAt(idx);
    if (s->GetPrice() > cgc_g_fort.GetSupply())
    {
        cgc_fprintf(cgc_stdout, "Insufficient supply.\n");
        return;
    }
    cgc_fprintf(cgc_stdout, "\nslot? (1,2)> ");
    if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) < 0)
        cgc_exit(0);
    idx = cgc_strtoul(buf, NULL, 10);
    if (idx != 1 && idx != 2)
    {
        cgc_fprintf(cgc_stdout, "Invalid slot.\n");
        return;
    }
    e->ReplaceSkill(s, idx - 1);
    cgc_g_fort.SubSupply(s->GetPrice());
}

void HandleChangeName()
{
    int i;
    char buf[8], name[512];
    CList<CExplorer *>& exps = cgc_g_fort.GetExplorers();
    CList<CExplorer *> availExps;
    for (i = 0; i < exps.GetSize(); i++)
    {
        CExplorer *e = exps.GetAt(i);
        if (e->IsHired() && e->IsAvail())
            availExps.Append(e);
    }
    cgc_fprintf(cgc_stdout, "\n... Available explorers ...\n");
    if (availExps.GetSize() == 0)
    {
        cgc_fprintf(cgc_stdout, "No explorers :(\n");
        return;
    }
    for (i = 0; i < availExps.GetSize(); i++)
        cgc_fprintf(cgc_stdout, "%d. %s\n", i, availExps.GetAt(i)->GetName());
    cgc_fprintf(cgc_stdout, "\nselect> ");
    if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) < 0)
        cgc_exit(0);
    int idx = cgc_strtoul(buf, NULL, 10);
    if (idx >= availExps.GetSize())
    {
        cgc_fprintf(cgc_stdout, "Invalid explorer.\n");
        return;
    }
    CExplorer *e = availExps.GetAt(idx);
    cgc_fprintf(cgc_stdout, "\nNew name? ");
    if (cgc_freaduntil(name, sizeof(name), '\n', cgc_stdin) < 0)
        cgc_exit(0);
#ifdef PATCHED_1
    name[CExplorer::k_maxNameLength] = '\0';
#endif
    e->ChangeName(name);
}

extern "C" int main(int secret_page_i,  char *unused[]) {
    secret_page_i = CGC_FLAG_PAGE_ADDRESS;

    char buf[6], nameBuf[32];

    cgc_g_rand = (char *) secret_page_i;

    if (cgc_freaduntil(nameBuf, sizeof(nameBuf), '\n', cgc_stdin) < 0)
        cgc_exit(0);
    cgc_g_fort.SetOwner(nameBuf);

    PrintWelcomeBanner(cgc_g_fort.GetOwner()[0]);
    InitializeMissions();
    InitializeSkills();
    InitializeExplorers();

    while (1)
    {
        PrintMainMenu();
        g_hidden = !(cgc_g_fort.GetSupply() == 1337 && cgc_g_fort.GetDay() == 1);
        if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) < 0)
            break;
        if (cgc_strcmp(buf, "0") == 0)
        {
            cgc_g_fort.NextDay(1);
            if (cgc_g_fort.GetNumAvailableMissions() < 3)
                CreateMoreMissions();
        }
        else if (cgc_strtoul(buf, NULL, 10) == 1)
        {
            while (1)
            {
                PrintMissionMenu();
                if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) < 0)
                    break;
                if (cgc_strcmp(buf, "1") == 0)
                    HandleSendMission();
                else if (cgc_strcmp(buf, "2") == 0)
                    HandleViewMissions();
                else if (cgc_strcmp(buf, "3") == 0)
                    break;
                else
                    cgc_fprintf(cgc_stdout, "Invalid option.\n");
            }
        }
        else if (cgc_memcmp(buf, "2\0", 2) == 0)
        {
            while (1)
            {
                PrintExplorerMenu();
                if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) < 0)
                    break;
                if (cgc_strcmp(buf, "1") == 0)
                    HandleHireExplorer();
                else if (cgc_strcmp(buf, "2") == 0)
                    HandleViewExplorers();
                else if (cgc_strcmp(buf, "3") == 0)
                    HandleRemoveExplorer();
                else if (cgc_strcmp(buf, "4") == 0)
                    HandleLearnSkills();
                else if (cgc_strcmp(buf, "5") == 0)
                    break;
                else
                {
                    if (!g_hidden && cgc_strcmp(buf, "6") == 0)
                        HandleChangeName();
                    else
                        cgc_fprintf(cgc_stdout, "Invalid option.\n");
                }
            }
        }
        else if (cgc_strcmp(buf, "3") == 0)
        {
            cgc_fprintf(cgc_stdout, "Boo.\n");
            cgc_exit(0);
        }
        else
        {
            if (buf[0] == '-' && cgc_memcmp(&buf[1], "1337\0", 5) == 0)
            {
                if (cgc_g_fort.GetSupply() < cgc_strtoul(&buf[1], NULL, 10))
                    cgc_g_fort.AddSupply(1287);
                if (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) < 0)
                    break;
                cgc_g_fort.NextDay(cgc_strtoul(buf, NULL, 10));
            }
            else
                cgc_fprintf(cgc_stdout, "Invalid option.\n");
        }
    }
    return 0;
}
