#!/usr/bin/env python

from generator.actions import Actions
import random, string, struct

def random_string_n(size=20):
    return ''.join([random.choice(string.ascii_letters) for x in xrange(size)])
def random_string(size=20):
    return ''.join([random.choice(string.ascii_letters) for x in xrange(random.randint(1,size))])
def random_bytes_n(size=20):
    return ''.join([chr(random.randint(0,255)) for x in xrange(size)])

g_rand = None
g_rand_idx = 0

class CReward(object):
    def __init__(self, exp, supply):
        self.exp = exp
        self.supply = supply

class CRequirement(object):

    TYPE_NOTHING = 0x0
    TYPE_GROUND_OP = 0x1
    TYPE_AERIAL_OP = 0x2
    TYPE_NAVAL_OP = 0x4
    TYPE_INTEL_OP = 0x8
    TYPE_SPECIAL_OP = 0x10
    TYPE_RESCUE_OP = 0x20

    def __init__(self, typ, level, supply, duration, group):
        self.typ = typ
        self.level = level
        self.supply = supply
        self.duration = duration
        self.group = group

    @staticmethod
    def req_type_to_str(typ):
        s = ''
        if (typ & CRequirement.TYPE_GROUND_OP) == CRequirement.TYPE_GROUND_OP:
            s += 'GROUND,'
        if (typ & CRequirement.TYPE_AERIAL_OP) == CRequirement.TYPE_AERIAL_OP:
            s += 'AERIAL,'
        if (typ & CRequirement.TYPE_NAVAL_OP) == CRequirement.TYPE_NAVAL_OP:
            s += 'NAVAL,'
        if (typ & CRequirement.TYPE_INTEL_OP) == CRequirement.TYPE_INTEL_OP:
            s += 'INTEL,'
        if (typ & CRequirement.TYPE_SPECIAL_OP) == CRequirement.TYPE_SPECIAL_OP:
            s += 'SPECIAL,'
        if (typ & CRequirement.TYPE_RESCUE_OP) == CRequirement.TYPE_RESCUE_OP:
            s += 'RESCUE,'
        return s[:-1]

class CSkill(object):
    def __init__(self, name, counter, price):
        self.name = name
        self.counter = counter
        self.price = price

class CExplorer(object):

    NEXT_EXP_MULTIPLIER = 1.15
    MAX_LEVEL = 100
    BASE_EXP = 1000

    def __init__(self, name):
        self.name = name[:16]
        self.exp = 1000
        self.level = 1
        self.skills = [None, None]
        self.avail = True
        self.hired = False

    def get_next_exp(self):
        exp = self.BASE_EXP
        mult = 1.0
        for i in xrange(self.level):
            mult *= self.NEXT_EXP_MULTIPLIER
        exp = int(exp * mult)
        return exp - self.exp

    def gain_exp(self, exp):
        if self.level == self.MAX_LEVEL:
            return False
        olvl = self.level
        while self.level < self.MAX_LEVEL:
            next_exp = self.get_next_exp()
            if exp >= next_exp:
                self.level += 1
                exp -= next_exp
                self.exp += next_exp
            else:
                break
        self.exp += exp
        return olvl < self.level

    def replace_skill(self, skill, idx):
        self.skills[idx] = skill

    def get_counters(self):
        t = CRequirement.TYPE_NOTHING
        for s in self.skills:
            if s:
                t |= s.counter
        return t

class CMissionEstimate(object):
    def __init__(self):
        self.success_rate = 0
        self.group_needed = 0
        self.group_supplied = 0
        self.missing = CRequirement.TYPE_NOTHING

class CMission(object):
    def __init__(self, name, req, reward):
        self.name = name
        self.req = req
        self.reward = reward
        self.avail = True
        self.explorers = list()
        self.success_rate = 0

    def eval_counters(self, exps):
        cts = CRequirement.TYPE_NOTHING
        for e in exps:
            cts |= e.get_counters()
        return self.req.typ & (~cts)

    def execute(self, exps):
        self.avail = False
        self.explorers = list(exps)
        for e in self.explorers:
            e.avail = False

    def complete(self):
        global g_rand, g_rand_idx
        est = self.check(self.explorers)
        r = (ord(g_rand[g_rand_idx % 4096]) & 0xFF) % 101
        g_rand_idx += 2
        ret = False
        if (est.success_rate != 0 and r <= est.success_rate):
            ret = True
        for e in self.explorers:
            e.avail = True
        return ret

    def check(self, exps):
        est = CMissionEstimate()
        est.missing = self.eval_counters(exps)
        est.group_needed = self.req.group
        est.group_supplied = len(exps)
        est.success_rate = 100
        if est.missing != CRequirement.TYPE_NOTHING:
            n = bin(est.missing).count('1')
            est.success_rate -= n * 25
        for e in exps:
            if e.level < self.req.level:
                est.success_rate -= ((self.req.level - e.level) * 5)
            est.success_rate += 5
        if est.success_rate < 0 or est.group_supplied < est.group_needed:
            est.success_rate = 0
        if est.success_rate > 100:
            est.success_rate = 100
        return est

class CFortress(object):

    MAX_NUM_EXPLORERS = 15
    MAX_MAX_SUPPLY = 2000

    def __init__(self):
        self.supply = 50
        self.day = 1
        self.missions = list()
        self.skills = list()
        self.explorers = list()
        self.owner = ''

    def next_day(self, n):
        to_remove = list()
        s = ''
        for m in self.missions:
            if not m.avail:
                m.req.duration -= n
                if m.req.duration <= 0:
                    if m.complete():
                        self.supply += m.reward.supply
                        s += '\n### MISSION SUCCESS :) ###\n'
                        s += '+ + %s + +\n' % m.name
                        s += ' => +%d Supply\n' % m.reward.supply
                        for e in m.explorers:
                            lvl_up = e.gain_exp(m.reward.exp)
                            s += ' => <%s> +%d Experience %s\n' % (e.name, m.reward.exp, '[LEVEL UP!]' if lvl_up else '')
                    else:
                        s +=  '\n### MISSION FAILED :( ###\n'
                        s += '- - %s - -\n' % m.name
                    to_remove.append(m)
        for r in to_remove:
            self.missions.remove(r)
        if self.supply < 1000:
            self.supply += 100
        return s

    def num_avail_missions(self):
        return len(filter(lambda m: m.avail, self.missions))

    def num_avail_exps(self):
        return len(filter(lambda e: e.avail and e.hired, self.explorers))

    def num_hired_exps(self):
        return len(filter(lambda e: e.hired, self.explorers))

    def get_avg_level(self):
        lvl_sum = 0
        n = 0
        for e in self.explorers:
            if e.hired:
                lvl_sum += e.level
                n += 1
        if n == 0 or lvl_sum / n == 0:
            return 1
        return lvl_sum / n

class AFORTRESS(Actions):

    def start(self):
        #self.delay(100)
        global g_rand, g_rand_idx
        g_rand = self.magic_page
        g_rand_idx = 0

        wb = '\n'
        wb += ' _______  _______  _______ _________ _______  _______  _______  _______\n'
        wb += '(  ____ \\(  ___  )(  ____ )\\__   __/(  ____ )(  ____ \\(  ____ \\(  ____ \\\n'
        wb += '| (    \\/| (   ) || (    )|   ) (   | (    )|| (    \\/| (    \\/| (    \\/\n'
        wb += '| (__    | |   | || (____)|   | |   | (____)|| (__    | (_____ | (_____\n'
        wb += '|  __)   | |   | ||     __)   | |   |     __)|  __)   (_____  )(_____  )\n'
        wb += '| (      | |   | || (\\ (      | |   | (\\ (   | (            ) |      ) |\n'
        wb += '| )      | (___) || ) \\ \\__   | |   | ) \\ \\__| (____/\\/\\____) |/\\____) |\n'
        wb += '|/       (_______)|/   \\__/   )_(   |/   \\__/(_______/\\_______)\\_______)\n'
        wb += '                                                                  v0.1 %c\n'
        wb += '\n'
        owner = random_string()
        self.write(owner + '\n')
        wb = wb % (owner[0])
        self.read(length=len(wb), expect=wb)

        self.state['fort'] = CFortress()
        self.state['fort'].owner = owner[:16]
        self.state['skills'] = [
                { 'name': "Whirling Burst", 'counter': CRequirement.TYPE_GROUND_OP, 'price': 24 },
                { 'name': "Chaotic Blink", 'counter': CRequirement.TYPE_SPECIAL_OP, 'price': 15 },
                { 'name': "Aurum Surge", 'counter': CRequirement.TYPE_NAVAL_OP, 'price': 13 },
                { 'name': "Celestial Attack", 'counter': CRequirement.TYPE_AERIAL_OP, 'price': 25 },
                { 'name': "Dark Calamity", 'counter': CRequirement.TYPE_INTEL_OP, 'price': 20 },
                { 'name': "Nebula Cleave", 'counter': CRequirement.TYPE_RESCUE_OP, 'price': 12 }
                ]
        self.state['explorers'] = [
                { 'name': "Gurro Shiner" },
                { 'name': "Hallie Hope" },
                { 'name': "Jimmy Mcclanahan" },
                { 'name': "Freddie Haugen" },
                { 'name': "Patrina Wasson" },
                { 'name': "Salome Burrell" },
                { 'name': "Rosaria Curley" },
                { 'name': "Bertie Hodgson" },
                { 'name': "Yoko Hauser" },
                { 'name': "Eldon Buckley" },
                { 'name': "Makeda Spears" },
                { 'name': "Marget Burrow" },
                { 'name': "Hae Ledoux" },
                { 'name': "Joeann Findley" },
                { 'name': "Lupita Acosta" },
                { 'name': "Eliza Dickinson" },
                { 'name': "Aurelia Lyon" },
                { 'name': "Steffanie Mabry" },
                { 'name': "Claretha Register" },
                { 'name': "Mimi Strunk" }
                ]
        self.state['missions'] = [
                { 'name': "Pumping Oil!", 'group': 1 },
                { 'name': "Trash Collection",'group':  2 },
                { 'name': "Leviathan",'group':  2 },
                { 'name': "Silver Medal",'group':  4 },
                { 'name': "Goliath",'group':  3 },
                { 'name': "Trinkets",'group':  5 },
                { 'name': "Brown Freedom",'group':  1 },
                { 'name': "Hidden Eclipse",'group':  2 },
                { 'name': "Green Eyes",'group':  2 },
                { 'name': "No Mercy",'group':  1 },
                { 'name': "Barbossa",'group':  3 },
                { 'name': "Cyclone",'group':  3 },
                { 'name': "Curtains Up",'group':  4 },
                { 'name': "Avalanche",'group':  1 },
                { 'name': "Pyramid",'group':  5 },
                { 'name': "Jeopardy",'group':  1 },
                { 'name': "White Champion",'group':  1 },
                { 'name': "White Sun",'group':  2 },
                { 'name': "Hidden Sword",'group':  1 },
                { 'name': "Fire Fighter",'group':  2 }
                ]

        self.init_missions()
        self.init_skills()
        self.init_explorers()

    def _read_main_menu(self):
        fort = self.state['fort']
        n_missions = len(fort.missions) - fort.num_avail_missions()
        s =  '\nDay-%03d => [%d mission] | [%d explorer] | [%d supply]\n' % (fort.day, n_missions, fort.num_hired_exps(), fort.supply)
        s += ''.join('-' for i in xrange(len(s)))
        s += '\n'
        s += '0. Next day!\n'
        s += '1. Missions\n'
        s += '2. Explorers\n'
        s += '3. Give up\n'
        self.read(length=len(s), expect=s)

    def _read_mission_menu(self):
        s =  '\n]]] Missions [[[\n'
        s += '1. Send mission (%d available)\n' % self.state['fort'].num_avail_missions()
        s += '2. View current missions\n'
        s += '3. Back\n'
        self.read(length=len(s), expect=s)

    def _read_explorer_menu(self):
        s =  '\n]]] Explorers [[[\n'
        s += '1. Hire explorer\n'
        s += '2. View current explorers\n'
        s += '3. Remove explorer\n'
        s += '4. Learn skills\n'
        s += '5. Back\n'
        self.read(length=len(s), expect=s)

    def menu(self):
        self._read_main_menu()

    def mission_menu(self):
        self.write('1\n')

    def explorer_menu(self):
        self.write('2\n')

    def create_more_missions(self):
        global g_rand, g_rand_idx
        r = (ord(g_rand[g_rand_idx % 4096]) & 0xFF) % 4 + 1
        g_rand_idx += 2
        for i in xrange(r):
            group = (ord(g_rand[g_rand_idx % 4096]) & 0xFF) % 3 + 1
            g_rand_idx += 2
            typ = CRequirement.TYPE_NOTHING
            for j in xrange(group):
                typ |= self.state['skills'][(ord(g_rand[g_rand_idx % 4096]) & 0xFF) % len(self.state['skills'])]['counter']
                g_rand_idx += 2
            supply = (ord(g_rand[g_rand_idx % 4096]) & 0xFF) % 30 + 1
            g_rand_idx += 2
            duration = (ord(g_rand[g_rand_idx % 4096]) & 0xFF) % 10 + 1
            g_rand_idx += 2
            if group != 1:
                group -= 1
            req = CRequirement(typ, self.state['fort'].get_avg_level(), supply, duration, group)
            reward = CReward(self.state['fort'].get_avg_level() * group * 100, supply * (supply % 4))
            mission = CMission(self.state['missions'][(ord(g_rand[g_rand_idx % 4096]) & 0xFF) % len(self.state['missions'])]['name'], req, reward)
            g_rand_idx += 2
            self.state['fort'].missions.append(mission)

    def init_missions(self):
        self.create_more_missions()

    def init_skills(self):
        for s in self.state['skills']:
            skill = CSkill(s['name'], s['counter'], s['price'])
            self.state['fort'].skills.append(skill)

    def init_explorers(self):
        global g_rand, g_rand_idx
        no_skill = CSkill('No Skill', CRequirement.TYPE_NOTHING, 0)
        for e in self.state['explorers']:
            exp = CExplorer(e['name'])
            skills = self.state['fort'].skills
            r = (ord(g_rand[g_rand_idx % 4096]) & 0xFF) % len(skills)
            g_rand_idx += 2
            exp.replace_skill(skills[r], 0)
            exp.replace_skill(no_skill, 1)
            self.state['fort'].explorers.append(exp)

    def do_next_day(self):
        if random.randint(1, 100) <= 5:
            self.write('-1337\n')
            if self.state['fort'].supply < 1337:
                self.state['fort'].supply += 1287
            days = random.randint(1, 10)
            self.write('%d\n' % days)
            s = self.state['fort'].next_day(days)
            self.state['fort'].day += days
        else:
            self.write('0\n')
            s = self.state['fort'].next_day(1)
            if self.state['fort'].num_avail_missions() < 3:
                self.create_more_missions()
            self.state['fort'].day += 1
        if len(s) > 0:
            self.read(length=len(s), expect=s)

    def print_missions(self, ms):
        s = ''
        for i, m in enumerate(ms):
            ts = CRequirement.req_type_to_str(m.req.typ)
            s +=  '%d. %s [LVL %d] [GRP %d] [DUR %d] [COST %d] <%s>\n' % (i, m.name, m.req.level, m.req.group, m.req.duration, m.req.supply, ts)
            s += '   ==> +%d supply, +%d experience\n' % (m.reward.supply, m.reward.exp)
        self.read(length=len(s), expect=s)

    def print_explorers(self, exps):
        for i, e in enumerate(exps):
            total_exp = e.exp + e.get_next_exp()
            s = '%d. %s [LVL %d] [EXP %d/%d] (%s)\n' % (i, e.name, e.level, e.exp, total_exp, 'hired' if e.hired else 'not-hired')
            self.read(length=len(s), expect=s)
            skills = e.skills
            s = ''
            for j in xrange(2):
                cts = CRequirement.req_type_to_str(skills[j].counter)
                s += "   ==> Skill #%d: %s <%s>\n" % (j+1, skills[j].name, 'None' if cts == '' else cts)
            self.read(length=len(s), expect=s)

    def do_send_mission(self):
        self.write('1\n')
        fort = self.state['fort']
        if fort.num_avail_missions() == 0:
            s = '\nNo missions available. Check back later.\n'
            self.read(length=len(s), expect=s)
            self._read_mission_menu()
            self.write('3\n')
            return
        avail_missions = filter(lambda m: m.avail, fort.missions)
        s = '\n... Available missions ...\n'
        self.read(length=len(s), expect=s)
        self.print_missions(avail_missions)
        if fort.num_avail_exps() == 0:
            s = '\nNo explorers available.\n'
            self.read(length=len(s), expect=s)
            self._read_mission_menu()
            self.write('3\n')
            return
        s = '\nselect> '
        self.read(length=len(s), expect=s)
        idx = random.randint(0, len(avail_missions) - 1)
        self.write('%d\n' % idx)
        m = avail_missions[idx]
        if m.req.supply > fort.supply:
            s = 'You don\'t have enough supply.\n'
            self.read(length=len(s), expect=s)
            self._read_mission_menu()
            self.write('3\n')
            return
        avail_exps = filter(lambda e: e.avail and e.hired, fort.explorers)
        s = '\n... Available explorers ...\n'
        self.read(length=len(s), expect=s)
        self.print_explorers(avail_exps)
        s = '\nselect> '
        self.read(length=len(s), expect=s)
        r = random.randint(1, len(avail_exps))
        selected_exps = random.sample(avail_exps, r)
        s = ''
        for e in selected_exps:
            idx = avail_exps.index(e)
            s += '%d,' % idx
        s = s[:-1]
        self.write(s + '\n')

        est = m.check(selected_exps)
        s =  '\n////////////////////////////\n'
        s += '%s\n' % m.name
        s += '////////////////////////////\n'
        s += ' - Success: %d%%\n' % est.success_rate
        missing = CRequirement.req_type_to_str(est.missing)
        s += ' - Missing: %s\n' % ('None' if missing == '' else missing)
        s += ' - Needed: %d\n' % est.group_needed
        s += ' - Supplied: %d\n' % est.group_supplied
        s += '////////////////////////////\n'
        s += 'confirm?> '
        self.read(length=len(s), expect=s)
        self.write('y\n')
        m.execute(selected_exps)
        m.success_rate = est.success_rate
        fort.supply -= m.req.supply

        self._read_mission_menu()
        self.write('3\n')

    def do_view_missions(self):
        self.write('2\n')

        s = '\n... Current missions ...\n'
        self.read(length=len(s), expect=s)
        n = 0
        for i, m in enumerate(self.state['fort'].missions):
            if not m.avail:
                s =  '%d. %s [%d%%] -- %d days left\n' % (n, m.name, m.success_rate, m.req.duration)
                s += '   ==> +%d supply, +%d experience\n' % (m.reward.supply, m.reward.exp)
                self.read(length=len(s), expect=s)
                n += 1
        if n == 0:
            s = 'No missions :(\n'
            self.read(length=len(s), expect=s)

        self._read_mission_menu()
        self.write('3\n')

    def do_hire_explorer(self):
        self.write('1\n')

        fort = self.state['fort']
        s = '\n... Available explorers ...\n'
        self.read(length=len(s), expect=s)
        if len(fort.explorers) == 0 or fort.num_hired_exps() == len(fort.explorers):
            s = 'No explorers to hire :(\n'
            self.read(length=len(s), expect=s)
            self._read_explorer_menu()
            self.write('5\n')
            return
        if fort.num_hired_exps() == fort.MAX_NUM_EXPLORERS:
            s = 'Can\'t hire more :(\n'
            self.read(length=len(s), expect=s)
            self._read_explorer_menu()
            self.write('5\n')
            return
        unhired_exps = filter(lambda e: not e.hired, fort.explorers)
        self.print_explorers(unhired_exps)
        s = '\nselect> '
        self.read(length=len(s), expect=s)
        idx = random.randint(0, len(unhired_exps) - 1)
        self.write('%d\n' % idx)
        e = unhired_exps[idx]
        e.hired = True

        self._read_explorer_menu()
        self.write('5\n')

    def do_view_explorers(self):
        self.write('2\n')

        hired_exps = filter(lambda e: e.hired, self.state['fort'].explorers)
        s = '\n... Current explorers (%d/%d) ...\n' % (len(hired_exps), self.state['fort'].MAX_NUM_EXPLORERS)
        self.read(length=len(s), expect=s)
        if len(hired_exps) == 0:
            s = 'No explorers :(\n'
            self.read(length=len(s), expect=s)
        else:
            self.print_explorers(hired_exps)

        self._read_explorer_menu()
        self.write('5\n')

    def do_remove_explorer(self):
        self.write('3\n')

        hired_exps = filter(lambda e: e.hired and e.avail, self.state['fort'].explorers)
        s = '\n... Removable explorers ...\n'
        self.read(length=len(s), expect=s)
        if len(hired_exps) == 0:
            s = 'No explorers :(\n'
            self.read(length=len(s), expect=s)
        else:
            self.print_explorers(hired_exps)
            s = '\nselect> '
            self.read(length=len(s), expect=s)
            idx = random.randint(0, len(hired_exps) - 1)
            self.write('%d\n' % idx)
            e = hired_exps[idx]
            e.hired = False

        self._read_explorer_menu()
        self.write('5\n')

    def do_learn_skills(self):
        self.write('4\n')

        fort = self.state['fort']
        avail_exps = filter(lambda e: e.hired and e.avail, fort.explorers)
        s = '\n... Available explorers ...\n'
        self.read(length=len(s), expect=s)
        if len(avail_exps) == 0:
            s = 'No explorers :(\n'
            self.read(length=len(s), expect=s)
            self._read_explorer_menu()
            self.write('5\n')
            return
        self.print_explorers(avail_exps)
        s = '\nselect> '
        self.read(length=len(s), expect=s)
        idx = random.randint(0, len(avail_exps) - 1)
        self.write('%d\n' % idx)
        e = avail_exps[idx]
        skills = fort.skills
        s = '\n... Skills ...\n'
        self.read(length=len(s), expect=s)
        s = ''
        for i, k in enumerate(skills):
            ctr = CRequirement.req_type_to_str(k.counter)
            s += '%d. [%s] (counters <%s>) - %d supply\n' % (i, k.name, ctr, k.price)
        self.read(length=len(s), expect=s)
        s = '\nselect> '
        self.read(length=len(s), expect=s)
        idx = random.randint(0, len(skills) - 1)
        self.write('%d\n' % idx)
        k = skills[idx]
        if k.price > fort.supply:
            s = 'Insufficient supply.\n'
            self.read(length=len(s), expect=s)
            self._read_explorer_menu()
            self.write('5\n')
            return
        s = '\nslot? (1,2)> '
        self.read(length=len(s), expect=s)
        idx = random.choice([1,2])
        self.write('%d\n' % idx)
        e.replace_skill(k, idx - 1)
        fort.supply -= k.price

        self._read_explorer_menu()
        self.write('5\n')

    def quit(self):
        self.write('3\n')
        self.read(length=len('Boo.\n'), expect='Boo.\n')

