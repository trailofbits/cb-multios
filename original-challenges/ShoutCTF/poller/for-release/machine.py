#!/usr/bin/env python

from generator.actions import Actions
import random, string, struct

def random_string(size=20):
    return ''.join([random.choice(string.ascii_letters + string.digits) for x in xrange(random.randint(8,size))])
def random_string_s(size=20):
    return ''.join([random.choice(string.ascii_letters + ' ') for x in xrange(random.randint(1,size))])
def random_bytes(size=20):
    return ''.join([chr(random.randint(1,255)) for x in xrange(random.randint(1,size))])
def random_bytes_n(size=20):
    return ''.join([chr(random.randint(0,255)) for x in xrange(size)])

def kaprica_mixin(self):
    if hasattr(self, 'xlat_seed'):
        return

    def xlat_seed(seed):
        def hash_string(seed):
            H = 0x314abc86
            for c in seed:
                H = (H * 37) & 0xffffffff
                H ^= ord(c)
                H = ((H << 13) ^ (H >> 19)) & 0xffffffff
            return H
        def hash_iterate(H):
            H = (H * 3) & 0xffffffff
            H = ((H << 13) ^ (H >> 19) ^ (H >> 21)) & 0xffffffff
            return H
        xmap = list(xrange(256))
        xmap_inv = list(xrange(256))
        state = hash_string(seed)
        for i in xrange(255, 0, -1):
            j = state % i
            state = hash_iterate(state)
            xmap[i], xmap[j] = xmap[j], xmap[i]
        for i in xrange(256):
            xmap_inv[xmap[i]] = i
        self.xlat_map = xmap
        self.xlat_map_inv = xmap_inv
    self.xlat_seed = xlat_seed
    self.xlat_map = None
    self.xlat_map_inv = None

    def xlat_string(s, inverse=False):
        if inverse:
            return ''.join([chr(self.xlat_map_inv[ord(c)]) for c in s])
        return ''.join([chr(self.xlat_map[ord(c)]) for c in s])
    self.xlat_string = xlat_string

    def read(delim=None, length=None, expect=None):
        if self.xlat_map:
            if delim:
                delim = self.xlat_string(delim)
            if expect:
                expect = self.xlat_string(expect)
        return self._original_read(delim=delim, length=length, expect=expect)
    self._original_read = self.read
    self.read = read

    def write(s):
        if self.xlat_map:
            if s:
                s = self.xlat_string(s)
        return self._original_write(s)
    self._original_write = self.write
    self.write = write


class Challenge(object):
    CAT_CRYPTO = 0
    CAT_PWNABLE = 1
    CAT_FORENSICS = 2
    CAT_WEB = 3
    CAT_NETWORK = 4
    CAT_REVERSING = 5
    CAT_MISC = 6

    CSTAT_LOCKED = 0
    CSTAT_SOLVED = 1
    CSTAT_SOLVED_U = 2
    CSTAT_OPEN = 3

    def __init__(self):
        self.name = ''
        self.desc = ''
        self.points = 0
        self.status = self.CSTAT_LOCKED
        self.cat = self.CAT_MISC
        self.flag = ''

    @staticmethod
    def cat_to_string(cat):
        if cat == Challenge.CAT_CRYPTO:
            return 'Crypto'
        elif cat == Challenge.CAT_PWNABLE:
            return 'Pwnable'
        elif cat == Challenge.CAT_FORENSICS:
            return 'Forensics'
        elif cat == Challenge.CAT_WEB:
            return 'Web'
        elif cat == Challenge.CAT_NETWORK:
            return 'Network'
        elif cat == Challenge.CAT_REVERSING:
            return 'Reversing'
        elif cat == Challenge.CAT_MISC:
            return 'Misc.'
        else:
            return 'Unknown'

    @staticmethod
    def status_to_string(stat):
        if stat == Challenge.CSTAT_LOCKED:
            return 'Locked'
        elif stat == Challenge.CSTAT_SOLVED:
            return 'Solved'
        elif stat == Challenge.CSTAT_SOLVED_U:
            return 'Cleared'
        elif stat == Challenge.CSTAT_OPEN:
            return 'Open'
        else:
            return 'Unknown'

class Error(object):
    ERR_OK = 0
    ERR_INTERNAL = 1
    ERR_NICK_LONG = 2
    ERR_PASS_LONG = 3
    ERR_NAME_LONG = 4
    ERR_NO_SUCH_USER = 5
    ERR_NO_SUCH_CHAL = 6
    ERR_NO_SUCH_TEAM = 7
    ERR_CHAL_ALREADY_OPEN = 8
    ERR_DUPLICATE_FLAG = 9
    ERR_INVALID_FLAG = 10
    ERR_USER_EXISTS = 11
    ERR_TEAM_EXISTS = 12
    ERR_CHAL_EXISTS = 13
    ERR_WRONG_PASS = 14
    ERR_INVALID_VALUE = 15

    msg = ["",
            "Internal error.",
            "Nickname is too long.",
            "Password is too long.",
            "Team Name is too long.",
            "No such user found.",
            "No such challenge found.",
            "No such team found.",
            "The challenge is already open.",
            "Duplicate flag.",
            "Invalid flag.",
            "User already exists.",
            "Team already exists.",
            "Challenge already exists.",
            "Wrong password.",
            "Invalid value."]

    @staticmethod
    def error_to_string(err):
        if 0 <= err <= 15:
            return Error.msg[err]
        else:
            return 'Unknown error.'

class User(object):
    def __init__(self, nick, pw, team):
        self.nick = nick
        self.pw = pw
        self.team = team

    def set_nick(self, nick):
        if len(nick) >= 16:
            return Error.ERR_NICK_LONG
        self.nick = nick
        return Error.ERR_OK

    def set_pw(self, pw):
        if len(nick) >= 32:
            return Error.ERR_PASS_LONG
        self.pw = pw
        return Error.ERR_OK

    def set_team(self, team):
        self.team = team
        return Error.ERR_OK

class Team(object):
    def __init__(self, name, leader, shout):
        self.code = None
        self.name = name
        self.members = []
        self.leader = None
        self.shout = shout
        self.score = 0

    def add_member(self, user):
        if len(self.members) == 0:
            self.leader = user
        self.members.append(user)

    def remove_member(self, nick):
        pass

    def change_name(self, name):
        pass

    def set_shoutout(self, shout):
        self.shout = shout
        return Error.ERR_OK

class Flag(object):
    def __init__(self, team, chal, flag, valid, idx, shout):
        self.team = team
        self.chal = chal
        self.flag = flag
        self.valid = valid
        self.idx = idx
        self.shout = shout

class FlgMgr(object):
    def __init__(self, ctf):
        self.submits = []
        self.ctf = ctf

    def is_duplicate(self, team, flag):
        for f in self.submits:
            if f.team == team and f.flag == flag:
                return True
        return False

    def add_submit(self, team, flag):
        if self.is_duplicate(team, flag):
            return Error.ERR_DUPLICATE_FLAG
        err, chal = self.find_chal(flag)
        if err != Error.ERR_OK:
            err = Error.ERR_INVALID_FLAG
        f = Flag(team, chal, flag, (chal is not None), len(self.submits), None)
        if f.chal and f.chal.status == Challenge.CSTAT_OPEN:
            f.chal.status = Challenge.CSTAT_SOLVED
        self.submits.append(f)
        return err

    def get_solves(self, chal, n):
        global g
        flags = []
        n = min(n, len(self.submits))
        if chal:
            for s in self.submits:
                if len(flags) == n:
                    break
                if s.chal == chal and s.valid:
                    flags.append(s)
        else:
            for i in xrange(len(self.submits)):
                if len(flags) == n:
                    break
                if self.submits[len(self.submits) - i - 1].valid:
                    flags.append(self.submits[len(self.submits) - i - 1])
        return Error.ERR_OK, flags

    def find_chal(self, flag):
        for c in self.ctf.chals:
            if c.flag == flag:
                return Error.ERR_OK, c
        return Error.ERR_NO_SUCH_CHAL, None

    def team_did_solve(self, team, chal):
        for f in self.submits:
            if f.valid and f.team == team and f.chal == chal:
                return True
        return False

class CTF(object):
    CTF_STAT_DOWN = 0
    CTF_STAT_LIVE = 1

    def __init__(self):
        self.status = self.CTF_STAT_DOWN
        self.chals = []
        self.teams = []
        self.users = []
        self.flg = FlgMgr(self)
        self.logged_in = None

    def submit_flag(self, team, flag):
        err = self.flg.add_submit(team, flag)
        return err

    def add_user(self, user):
        for u in self.users:
            if u.nick == user.nick:
                return Error.ERR_USER_EXISTS
        self.users.append(user)
        return Error.ERR_OK

    def auth_user(self, nick, pw):
        for u in self.users:
            if u.nick == nick:
                if u.pw == pw:
                    return Error.ERR_OK, u
                return Error.ERR_WRONG_PASS, None
        return Error.ERR_NO_SUCH_USER, None

    def add_team(self, team):
        for t in self.teams:
            if t.name == team.name:
                return Error.ERR_TEAM_EXISTS
        self.teams.append(team)
        return Error.ERR_OK

    def add_chal(self, chal):
        for c in self.chals:
            if c.name == chal.name or c.flag == chal.flag:
                return Error.ERR_CHAL_EXISTS
        self.chals.append(chal)
        return Error.ERR_OK

    def open_chal(self, cid):
        if cid >= len(self.chals):
            return Error.ERR_NO_SUCH_CHAL
        chal = self.chals[cid]
        if chal.status != Challenge.CSTAT_LOCKED:
            return Error.ERR_CHAL_ALREADY_OPEN
        chal.status = Challenge.CSTAT_OPEN
        return Error.ERR_OK

    def get_solves(self, n):
        return self.flg.get_solves(None, n)

    def select_nth(self, arr, length, n):
        i = 0
        j = 0
        tmp = None
        while True:
            if i >= length - 1:
                break
            if arr[i].score < arr[length-1].score:
                i += 1
                continue
            tmp = arr[i]
            arr[i] = arr[j]
            arr[j] = tmp
            j += 1
            i += 1
        tmp = arr[length-1]
        arr[length-1] = arr[j]
        arr[j] = tmp
        if n == j:
            return arr[j]
        if j > n:
            return self.select_nth(arr, j, n)
        return self.select_nth(arr[j:], length - j, n - j)

    def get_ranks(self, page):
        for t in self.teams:
            t.score = 0
        for c in self.chals:
            if c.status != Challenge.CSTAT_LOCKED:
                for t in self.teams:
                    if self.flg.team_did_solve(t, c):
                        t.score += c.points
        n = min(5, len(self.teams))
        p = page
        if n == 0:
            return Error.ERR_OK, None
        if ((p - 1) * 5 >= len(self.teams)):
            p = 0
        else:
            p = (p - 1) * 5
        ranks = []
        i = p
        j = 0
        tmp = list(self.teams)
        while True:
            if not (i < len(self.teams) and j < n):
                break
            ranks.append(self.select_nth(tmp, len(self.teams), i))
            i += 1
            j += 1
        return Error.ERR_OK, ranks, p

    def get_team(self, tid):
        if tid >= len(self.teams):
            return Error.ERR_NO_SUCH_TEAM, None
        return Error.ERR_OK, self.teams[tid]

    def get_chal(self, cid):
        if cid >= len(self.chals):
            return Error.ERR_NO_SUCH_CHAL, None
        return Error.ERR_OK, self.chals[cid]

class ASHOUT(Actions):

    def prng(self):
        r = self.state['r']
        r = ((((r >> 31) ^ (r >> 30) ^ (r >> 10) ^ (r >> 0)) & 1) << 31) | (r >> 1)
        self.state['r'] = r
        return r

    def random_string(self, l):
        s = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'
        buf = []
        for i in xrange(l):
            r = self.prng()
            buf.append(s[r % len(s)])
        return ''.join(buf)

    def start(self):
        #self.delay(100)
        kaprica_mixin(self)
        self.xlat_seed('7943')

        #print '\nstart'
        r1 = struct.unpack('<I', self.magic_page[:4])[0]
        r2 = struct.unpack('<I', self.magic_page[20:24])[0]
        self.state['r'] = r1 ^ r2
        self.state['ctf'] = CTF()
        self.state['action'] = True

        s = 'Shout CTF CLI v0.1\n'
        s += '=================\n'
        self.read(length=len(s), expect=s)

    def ready(self):
        #print 'ready %s' % self.state['ctf'].logged_in
        pass

    def main_menu(self):
        #print 'main_menu %s' % self.state['ctf'].logged_in
        if self.state['ctf'].logged_in:
            return
        if not self.state['action']:
            return
        self.do_random_action()

        s = "\n=== Menu ===================\n"
        s += "1. Register User\n"
        s += "2. Login User\n"
        s += "3. Quit\n"
        s += "> "
        self.read(length=len(s), expect=s)
        self.state['action'] = False

    def ctf_ticker(self):
        ctf = self.state['ctf']
        t = ctf.logged_in.team
        ctf.get_ranks(1)
        s = '\n================================\n'
        s += '| [%s] - %d\n' % (t.name, t.score)
        s += '================================\n'
        self.read(length=len(s), expect=s)
        err, solves = ctf.get_solves(5)
        if len(solves) == 0:
            s = 'No solves yet.\n'
            self.read(length=len(s), expect=s)
        s = ''
        for i in xrange(len(solves)):
            s += '| %s solved %s (%d pts)\n' % (solves[i].team.name, solves[i].chal.name, solves[i].chal.points)
        s += '================================\n'
        self.read(length=len(s), expect=s)

    def ctf_menu(self):
        #print 'ctf_menu %s' % self.state['ctf'].logged_in
        if not self.state['ctf'].logged_in:
            return
        if not self.state['action']:
            return
        self.do_random_action()

        self.ctf_ticker()
        s = "\n=== CTF Menu ===================\n"
        s += "1. View challenge list\n"
        s += "2. View challenge detail\n"
        s += "3. View ranking\n"
        s += "4. View team profile\n"
        s += "5. Submit flag\n"
        s += "6. Logout\n"
        s += "> "
        self.read(length=len(s), expect=s)
        self.state['action'] = False

    def do_random_action(self):
        ctf = self.state['ctf']
        ctf.status = CTF.CTF_STAT_LIVE
        r = self.prng() % 10
        if 0 <= r <= 3:
            chal = Challenge()
            chal.name = self.random_string(32)
            chal.desc = self.random_string(64)
            chal.points = self.prng() % 600
            if chal.points == 0:
                chal.points = 1
            chal.status = Challenge.CSTAT_LOCKED
            chal.cat = self.prng() % 7
            chal.flag = self.random_string(32)
            ctf.add_chal(chal)
        elif 4 <= r <= 7:
            for i in xrange(len(ctf.chals)):
                c = ctf.chals[i]
                if c.status == Challenge.CSTAT_LOCKED:
                    if self.prng() % 100 < 50:
                        ctf.open_chal(i)
                        break
        elif r == 8:
            ctf.status = CTF.CTF_STAT_DOWN

    def register_user(self):
        #print 'register_user %s' % self.state['ctf'].logged_in
        if self.state['ctf'].logged_in:
            return
        self.state['action'] = True
        self.write('1\n')
        ctf = self.state['ctf']
        if ctf.status == CTF.CTF_STAT_DOWN:
            s = 'CTF server is down! Try again later :(\n'
            self.read(length=len(s), expect=s)
            return
        nick = random_string(15)
        pw = random_string(31)
        s = '\n=== User Creation ===================\n'
        s += 'Nickname: '
        self.read(length=len(s), expect=s)
        self.write(nick + '\n')
        s = 'Password: '
        self.read(length=len(s), expect=s)
        self.write(pw + '\n')
        s = 'Team token: '
        self.read(length=len(s), expect=s)
        user = User(nick, pw, None)
        new_team = False
        if len(ctf.teams) > 0 and random.randint(1,100) <= 50:
            team = random.choice(ctf.teams)
            self.write(team.code + '\n')
        else:
            self.write('\n')
            s = '\n=== Team Creation ===================\n'
            s += 'Team name: '
            self.read(length=len(s), expect=s)
            team_name = random_string(31)
            self.write(team_name + '\n')
            s = 'Shoutout: '
            self.read(length=len(s), expect=s)
            shout = random_string(64)
            self.write(shout + '\n')
            team = Team(team_name, user, shout)
            team.code = self.random_string(32)
            new_team = True
        ctf.add_user(user)
        if new_team:
            ctf.add_team(team)
        team.add_member(user)
        user.set_team(team)
        s = '[INFO] Successfully registered.\n'
        if new_team:
            s += '[INFO] Team code: %s\n' % team.code
        self.read(length=len(s), expect=s)

    def login_user(self):
        #print 'login_user %s' % self.state['ctf'].logged_in
        if self.state['ctf'].logged_in:
            return
        self.state['action'] = True
        ctf = self.state['ctf']
        self.write('2\n')
        if ctf.status == CTF.CTF_STAT_DOWN:
            s = 'CTF server is down! Try again later :(\n'
            self.read(length=len(s), expect=s)
            return
        s = '\n=== Login ===================\n'
        s += 'Nick: '
        self.read(length=len(s), expect=s)
        if len(ctf.users) == 0 or random.randint(1,100) <= 20:
            nick = random_string().ljust(40, random_string()[0])
            pw = random_string()
        else:
            user = random.choice(ctf.users)
            nick = user.nick
            if random.randint(1,100) <= 10:
                pw = random_string().ljust(40, random_string()[0])
            else:
                pw = user.pw
        self.write(nick + '\n')
        s = 'Password: '
        self.read(length=len(s), expect=s)
        self.write(pw + '\n')
        err, user = ctf.auth_user(nick, pw)
        if err != Error.ERR_OK:
            s = '[ERROR] %s\n' % Error.error_to_string(err)
            self.read(length=len(s), expect=s)
            return
        ctf.logged_in = user
        s = '[INFO] Successfully logged in as %s.\n' % nick
        self.read(length=len(s), expect=s)

    def quit(self):
        if self.state['ctf'].logged_in:
            return
        self.write('3\n')
        ctf = self.state['ctf']
        if ctf.status == CTF.CTF_STAT_DOWN:
            s = 'CTF server is down! Try again later :(\n'
            self.read(length=len(s), expect=s)
            return
        s = 'Bye.\n'
        self.read(length=len(s), expect=s)

    def print_challenge(self, chal, detail):
        ctf = self.state['ctf']
        cat = Challenge.cat_to_string(chal.cat)
        stat = chal.status
        if ctf.flg.team_did_solve(ctf.logged_in.team, chal):
            stat = Challenge.CSTAT_SOLVED_U
        status = Challenge.status_to_string(stat)
        if not detail:
            return '[%s] [%d pts] %s - %s\n' % (cat, chal.points, chal.name, status)
        else:
            s = '[%s] [%d pts] %s - %s\n' % (cat, chal.points, chal.name, status)
            if chal.status == Challenge.CSTAT_LOCKED:
                s += 'Hidden.\n'
            else:
                s += '%s\n' % chal.desc
            # s += 'flag: %s\n' % (chal.flag)
            err, f = ctf.flg.get_solves(chal, 3)
            if len(f) > 0:
                s += '\nTop Solvers\n'
                s += '===========\n'
                for i in xrange(len(f)):
                    s += '%d. %s\n' % (i+1, f[i].team.name)
            return s

    def view_challenge_list(self):
        ctf = self.state['ctf']
        if not ctf.logged_in:
            return
        self.state['action'] = True
        self.write('1\n')
        if ctf.status == CTF.CTF_STAT_DOWN:
            s = 'CTF server is down! Try again later :(\n'
            self.read(length=len(s), expect=s)
            return
        if len(ctf.chals) == 0:
            s = '[INFO] No challenges are available.\n'
            self.read(length=len(s), expect=s)
            return
        s = '\n=== Challenge list ===================\n'
        self.read(length=len(s), expect=s)
        s = ''
        for i in xrange(len(ctf.chals)):
            s += '%d. ' % i
            s += self.print_challenge(ctf.chals[i], False)
        self.read(length=len(s), expect=s)

    def view_challenge_detail(self):
        ctf = self.state['ctf']
        if not ctf.logged_in:
            return
        self.state['action'] = True
        self.write('2\n')
        if ctf.status == CTF.CTF_STAT_DOWN:
            s = 'CTF server is down! Try again later :(\n'
            self.read(length=len(s), expect=s)
            return
        if len(ctf.chals) == 0:
            s = '[INFO] No challenges are available.\n'
            self.read(length=len(s), expect=s)
            return
        s = '\n=== Challenge list ===================\n'
        self.read(length=len(s), expect=s)
        s = ''
        for i in xrange(len(ctf.chals)):
            s += '%d. ' % i
            s += self.print_challenge(ctf.chals[i], False)
        self.read(length=len(s), expect=s)
        if len(ctf.chals) == 0:
            return
        s = '\nChoose idx: '
        self.read(length=len(s), expect=s)
        idx = ctf.chals.index(random.choice(ctf.chals))
        self.write('%d\n' % idx)
        err, chal = ctf.get_chal(idx)
        s = '\n=== Challenge detail ===================\n'
        s += self.print_challenge(chal, True)
        self.read(length=len(s), expect=s)

    def view_ranking_page(self, page):
        ctf = self.state['ctf']
        n = min(5, len(ctf.teams) - (page - 1) * 5)
        err, ranks, page = ctf.get_ranks(page)
        s = ''
        for i in xrange(n):
            rank = i + page * 5 + 1
            s += '%d. %s (%d pts)\n' % (rank, ranks[i].name, ranks[i].score)
        self.read(length=len(s), expect=s)

    def view_ranking(self):
        ctf = self.state['ctf']
        if not ctf.logged_in:
            return
        self.state['action'] = True
        self.write('3\n')
        if ctf.status == CTF.CTF_STAT_DOWN:
            s = 'CTF server is down! Try again later :(\n'
            self.read(length=len(s), expect=s)
            return
        s = '\n=== Ranking ===================\n'
        self.read(length=len(s), expect=s)
        num_pages = (len(ctf.teams) / 5) + (0 if len(ctf.teams) % 5 == 0 else 1)
        self.view_ranking_page(1)
        s = '\n=== 1 / %d ===================\n' % num_pages
        self.read(length=len(s), expect=s)
        while True:
            s = '\nPage: '
            self.read(length=len(s), expect=s)
            pg = random.choice(range(1, num_pages + 3) + ['q'] * 5)
            self.write(str(pg) + '\n')
            if pg == 'q':
                return
            if pg > num_pages:
                s = '[ERROR] %s\n' % Error.error_to_string(Error.ERR_INVALID_VALUE)
                self.read(length=len(s), expect=s)
                return
            self.view_ranking_page(pg)
            s = '\n=== %d / %d ===================\n' % (pg, num_pages)
            self.read(length=len(s), expect=s)

    def view_team_profile(self):
        ctf = self.state['ctf']
        if not ctf.logged_in:
            return
        self.state['action'] = True
        self.write('4\n')
        if ctf.status == CTF.CTF_STAT_DOWN:
            s = 'CTF server is down! Try again later :(\n'
            self.read(length=len(s), expect=s)
            return
        s = '\nTeam name: '
        self.read(length=len(s), expect=s)
        t = random.choice(ctf.teams)
        self.write(t.name + '\n')
        s = '\n=== Team profile ===================\n'
        s += '%s\n' % t.name
        s += 'Leader: %s\n' % t.leader.nick
        s += 'Members (%d)\n - ' % len(t.members)
        for m in t.members:
            s += '%s, ' % m.nick
        s = s[:-2]
        s += '\nShoutout: %s\n' % t.shout
        self.read(length=len(s), expect=s)

    def submit_flag(self):
        ctf = self.state['ctf']
        if not ctf.logged_in:
            return
        self.state['action'] = True
        self.write('5\n')
        if ctf.status == CTF.CTF_STAT_DOWN:
            s = 'CTF server is down! Try again later :(\n'
            self.read(length=len(s), expect=s)
            return
        s = '\n=== Submit flag ===================\n'
        s += 'Flag: '
        self.read(length=len(s), expect=s)
        avail_chals = filter(lambda c: c.status != Challenge.CSTAT_LOCKED, ctf.chals)
        if len(avail_chals) > 0 and random.randint(1, 100) <= 80:
            chal = random.choice(avail_chals)
            flag = chal.flag
        else:
            chal = None
            flag = random_string(40)
        err = ctf.submit_flag(ctf.logged_in.team, flag)
        self.write(flag + '\n')
        if chal and err == Error.ERR_OK:
            s = '[INFO] Congrats! You scored %d points!\n' % chal.points
            self.read(length=len(s), expect=s)
        if err != Error.ERR_OK:
            s = '[ERROR] %s\n' % Error.error_to_string(err)
            self.read(length=len(s), expect=s)

    def logout_user(self):
        ctf = self.state['ctf']
        if not ctf.logged_in:
            return
        self.state['action'] = True
        self.write('6\n')
        if ctf.status == CTF.CTF_STAT_DOWN:
            s = 'CTF server is down! Try again later :(\n'
            self.read(length=len(s), expect=s)
            return
        s = '[INFO] Successfully logged out.\n'
        self.read(length=len(s), expect=s)
        self.state['ctf'].logged_in = None

