# Plan for testing
# - Decide to use weak team or strong team (i.e. always lose battles or always win battles)
# - Random walk with bias towards tiles that have not been visited, or have been visited least recently
# - Quit after N number of steps, where N is a random number between 100 and 500

import array
import random
import struct
from cStringIO import StringIO
from generator.actions import Actions, Variable

KINDS = [
    { 'type': 'earth', 'name': 'Pheapxalm', 'max_health': 100, 'attack':  90, 'defense': 100,
        'attacks': [('Scratch', 20), ('Cutting Leaf', 30)] },
    { 'type': 'wind', 'name': 'Eashtel', 'max_health': 110, 'attack':  90, 'defense':  90,
        'attacks': [('Scratch', 20), ('Tornado', 40)] },
    { 'type': 'fire', 'name': 'Tacalm', 'max_health': 120, 'attack': 100, 'defense':  60,
        'attacks': [('Scratch', 20), ('Bonfire', 50)] },
]
STATES = ['-KEABDCDCAADFDCPPABAAKBABPPADPOABPPALPOJEABPPBCPOIJABPPAGPOACPPAFPOABABANPOIJABPPAGPOABPPAGPOABPPAGPOAGPPABPOIKABPPACPOABPPABAGALPOAEPPAEPOABPPABACABPOIDABPPACPOAIPPAEPOABPPAGPOAGPPAGPOICABPPAGPOAGPPAGPOAKPPACPOABPPADPOICABPPABPOABCBACPOAHPPAIPOAIPPAIPOIBABPPAGPOAFPPAHPOACPPAEPOADPPABPOABADAEPOIDABPPABPOAEPPACPOAEPPACPOACPPADPOACPPAMPOIEABPPAGPOABCAABPOAHPPABAHBAPOIGABPPAGPOADPPADPOACPPBAPOAEPPAEPODKPPAIPOAFPPABCFACPOACPPAGPOABAEABAFAEPOACPPACPOAEPPACPOABPPAFPOACPPADPOCPPPAKPOAFPPABPOABPPACPOAGPPAHPOABPPAIPOAEPPADPOACPPADPOCPPPACPOACPPAFPOAGPPACPOABPPACPOAKPPABPOADPPBCPOABAJADPOCLPPADPOABPPAFPOAFPPADPOABPPADPOANPPAHPOABCHAMPOABAKADPOCIPPADPOABPPABPOABPPABPOABBPACPOAGPPACPOABPPAEPOAMPPBJPOABALCHPPACPOABPPAGPOAHPPACPOABPPACPOAHPPABPOABPPABPOABCKAMPOABCGAFPOABAIABPOABPPAIPOAKPPACPOABAMBFPPACPOABPPAEPOACPPAFPOAFPPADPOABPPBNPOABCJABCIABPOAEPPADPOAOPPAEPOBCPPAJPOADPPADPOABPPABPOAEPPABPOADPPBLPOABPPACPOAFPPAFPOAKPPAHPOBDPPAFPOACPPADPOACPPAEPOAEPPCAPOAFPPAHPOAJPPACPOABPPADPOABPPABPOBBPPAHPOABPPAEPOADPPAEPOAEPPAGPOABPPBHPOAGPPACPOABPPADPOAFPPACPOADPPABPOACPPACPOACPPABPOBAPPAIPOABPPALPOADPPAEPOADPPADPOABPPAFPOADPPAJPOAMPPABPOAGPPADPOADPPACPOACPPACPOABPPABPOBAPPAIPOACPPABPOABCCACPOABCDAFPOABPPAEPOAEPPAEPOABPPAFPOACPPAEPOACPPAEPOAKPPAMPOACPPAJPOBDPPAPPOABPPADPOABCEAFPPALPOABPPAFPOACPPACPOABCLAMPPBGPOBBPPAIPOADPPAGPOALPPAPPOADPPACPOAPPPBEPOBDPPADPOAJPPAEPOAHPPBBPOBHPPACPOABBDAJPOAFPPABPOBLPPAGPOAGPPANPOACPPAFPOBFPPAOPOAEPPACPOBJPPAHPOABPPACPOADPPAOPOAGPPACPOBDPPBFPOBJPPACPOACPPAKPOABCMAMPOAEPPABPOACPPABPOBDPPACPOABBCABPOABBEBAPOBIPPBNPOABPPAGPOBCPPBFPOABBBBDPPACPOACPPAJPOACPPAEPOACPPANPOACPPAFPOBCPPBGPOBCPPAEPOABCPACPOABPPAKPOABPPABPOABPPAFPOABPPADPOADPPABPOADPPAFPOBBPPBHPOBCPPABPOACPPACPOAFPPAGPOADPPAGPOABPPAFPOAGPPABPOBFPPANPOABBAAJPOBCPPAFPOAFPPAGPOACPPAFPOAEPPAFPOAEPPACPOABPPADPOAPPPADPOABPPACPOACPPAFPOABPPAIPOACPPABPOBBPPAGPOAGPPACPOABBOACPOAEPPABPOABCOAIPPADPOACPPAIPOAPPPABPOAHPPACPOACPPAEPOADPPACPOACPPABPOBBPPAEPOAKPPACPOAFPPBLPOALPPABPOAGPPACPOANPPACPOBBPPABPOAMPPAEPOAEPPBKPOABCNALPPABPOAGPPABPOAGPPAGPOACPPABPOBAPPACPOABDAALPPAFPOAEPPAJPOABBNABPOABBLAOPOAKPPADPOAGPPABPOAGPPAJPOAPPPADPOAHPPAJPOAEPPBDPOADPPABPOAOPPAFPOACPPADPOAHPPACPOACPPACPOABAOACPOBAPPAEPOABDBBLPOACPPACPOACPPABPOBDPPAFPOADPPAFPOABPPAEPOADPPAFPOBAPPACPOABPPAIPOABPPANPOAEPPADPOAGPPABPOANPPADPOABPPAMPOACPPABPOACPPACPOADPPAGPOBDPPAIPOABPPABBMALPOAHPPABPOAGPPADPOALPPBBPOABPPAOPOBDPPACPOABPPADPOABPPAJPOABPPAJPOABPPADPOADPPAFPOADPPABPOAHPPACPOAEPPANPOABAPALPOBJPPALPOABPPAPPOABPPAEPOACPPABPOABBIACPOACPPAIPOACPPADPOABBFAEPOABPPACPOAHPPAHPOBKPPBLPOABBKADPOAEPPAMPOACPPABPOABPPAMPOAEPPAFPOABPPABPOBMPPBEPOABPPADPOABDCAHPOABBJAKPOADPPAGPOABBGAEPOABPPABPOAFPPAJPOBKPPADPOABPPAFPOABPPAGPOAGPPABDDBAPOABBHACPOAJPPAGPOAIPPACPOABANACPPADPOABDEKFABPPAAACJEABAALEAHAFELGBHEGJGFAEAJFAGIGFGBHAHIGBGMGNAAABAAKMABKMABJLABKFABAJFAGIGFGBHAHIGBGMGNAAACAALEABLEABJMABKGABAHEFGBHDGIHEGFGMABACAALOABLOABJMABJMABAGFEGBGDGBGMGNACABAAIAACIAACKFABDNABCEKGADACJEABAAJABPAGEEHFHDHEGJGOADAHEFGBHDGIHEGFGMABBBAALGADLGADKLABKLABAHEFGBHDGIHEGFGMABBBAALGADLGADKLABKLABAHEFGBHDGIHEGFGMABBBAALGADLGADKLABKLABABCELGAEACJEABAAIABJAFECHCGFGOHEABAJFAGIGFGBHAHIGBGMGNAABBAAKMADKMADKLABLFABABCEIGABABCEIGABABCEICACABCEBOACJEABAALIEHAFECHCGFGOHEACAGFEGBGDGBGMGNACCMAAJIAHJIAHJAACKIABAHEFGBHDGIHEGFGMABCNAAJGAHJGAHIHACIHACACJEABAAKMEPAFEGGJGPGOGBACAJFAGIGFGBHAHIGBGMGNAADDAALMAHLMAHINACJHACAGFEGBGDGBGMGNACDAAALIAHLIAHJEACKMABACJEABAAIIGHAEFEGPGOHJAEAJFAGIGFGBHAHIGBGMGNAADMAAIEAJIEAJJGACKAACAJFAGIGFGBHAHIGBGMGNAADOAAJEAJJEAJJIACKCACAJFAGIGFGBHAHIGBGMGNAADMAAIEAJIEAJJGACKAACAHEFGBHDGIHEGFGMABDOAAJOAJJOAJJIACJIACACJEABAAKIIMABAFELGBHEGJGFAEAHEFGBHDGIHEGFGMABJHABAAKGAMKGAMLBACLBACAJFAGIGFGBHAHIGBGMGNAAJGABAAJEAMJEAMLAACLKACAGFEGBGDGBGMGNACJIABAALIAMLIAMLMACJEACAGFEGBGDGBGMGNACJIABAALIAMLIAMLMACJEACABCEIGAGABCEJKABACJEABAAKIHDAFEMGFHCGPHJACAGFEGBGDGBGMGNACIHABAALAAKLAAKKLACIDACAGFEGBGDGBGMGNACIJABAAIAALIAALKNACIFACABCEJOAFACJEABAALIGAAFEDGBHCGMHJADAHEFGBHDGIHEGFGMABDLAAIGAJIGAJJFACJFACAGFEGBGDGBGMGNACDKAAIIAJIIAJJOACLGABAJFAGIGFGBHAHIGBGMGNAADKAALEAILEAIJEACJOACACJEABAALAFNAFECHCGFGOHEACAJFAGIGFGBHAHIGBGMGNAADKAALEAILEAIJEACJOACAGFEGBGDGBGMGNACDKAAIIAJIIAJJOACLGABABCELOACACJEABAALMGOAFELGBHEGJGFACAHEFGBHDGIHEGFGMABIHABAAKGAKKGAKKBACKBACAJFAGIGFGBHAHIGBGMGNAAIEABAAIEAKIEAKJOACKIACABCEBOABCELCAFABCELKADABCELGAEABCEJKABACJEABAAKIEBAFEDGBHCGMHJAEAHEFGBHDGIHEGFGMABCGAAJOAGJOAGIAACIAACAHEFGBHDGIHEGFGMABCHAAKGAGKGAGIBACIBACAJFAGIGFGBHAHIGBGMGNAACEAAIEAGIEAGLOABIIACAGFEGBGDGBGMGNACCFAAKAAGKAAGIJACKBABABCEIGABACJEABAAIMEDAFELGBHEGJGFACAHEFGBHDGIHEGFGMABCLAAIGAHIGAHIFACIFACAGFEGBGDGBGMGNACCKAAIIAHIIAHIOACKGABACJEABAALMFFAGEEHFHDHEGJGOABAGFEGBGDGBGMGNACDIAALIAILIAIJMACLEABACJEABAAKMDGAEFEGPGOHJADAHEFGBHDGIHEGFGMABCBAALGAFLGAFLLABLLABAJFAGIGFGBHAHIGBGMGNAACDAALMAFLMAFLNABIHACAGFEGBGDGBGMGNACCDAAJAAGJAAGIHACJPABACJEABAAKACFAFELGBHEGJGFAEAHEFGBHDGIHEGFGMABBFAAJGAEJGAEKPABKPABAGFEGBGDGBGMGNACBGAAKIAEKIAELKABJCABAJFAGIGFGBHAHIGBGMGNAABEAAIEAEIEAEKOABLIABAJFAGIGFGBHAHIGBGMGNAABGAAJEAEJEAELAABLKABABCEJGACACJEABAAIAELAFECHCGFGOHEACAGFEGBGDGBGMGNACDAAALIAHLIAHJEACKMABAHEFGBHDGIHEGFGMABCOAAJOAHJOAHIIACIIACABCEKGADACJEABAAKADOAFELGBHEGJGFABAGFEGBGDGBGMGNACCEAAJIAGJIAGIIACKAABACJEABAALMCDAGEEHFHDHEGJGOABAHEFGBHDGIHEGFGMABBDAAIGAEIGAEKNABKNABABCELKADACJEABAAKMDGAFEMGFHCGPHJABAGFEGBGDGBGMGNACCBAAIAAGIAAGIFACJNABABCEICACABCEJOAFACJEABAALMCDAEFEGPGOHJACAGFEGBGDGBGMGNACBHAALAAELAAELLABJDABAHEFGBHDGIHEGFGMABBFAAJGAEJGAEKPABKPABABCELKADABCELOACACJEABAAIIEOAGFDHJGMHGGJGBABAGFEGBGDGBGMGNACDDAAJAAIJAAIJHACKPABACJEABAAIIEOAFECHCGFGOHEABAJFAGIGFGBHAHIGBGMGNAADAAAKEAHKEAHIKACJEACABCEIGABABCEIKAFACJEABAAIEHCAGEEHFHDHEGJGOAEAJFAGIGFGBHAHIGBGMGNAAIFABAAIMAKIMAKJPACKJACAJFAGIGFGBHAHIGBGMGNAAIGABAAJEAKJEAKKAACKKACAHEFGBHDGIHEGFGMABIDABAAIGAKIGAKJNACJNACAHEFGBHDGIHEGFGMABIGABAAJOAKJOAKKAACKAACACJEABAAIAELAGEEHFHDHEGJGOACAHEFGBHDGIHEGFGMABCNAAJGAHJGAHIHACIHACAJFAGIGFGBHAHIGBGMGNAACPAAJMAHJMAHIJACJDACABCEJGACADDCAACKAAABAHEFGBHDGIHEGFGMABADAAIGACIGACJNABJNABAAMNCC--']

def dearmor(s):
    s = s[1:-2]
    out = StringIO()
    for i in xrange(0, len(s), 2):
        b = (ord(s[i]) - ord('A')) & 0xf
        b = (b << 4) | ((ord(s[i+1]) - ord('A')) & 0xf)
        out.write(chr(b))
    return out.getvalue()[:-2] # exclude checksum

class Deserializer(object):
    def __init__(self, f):
        if isinstance(f, str):
            f = StringIO(f)
        self.f = f

    def u8(self):
        return struct.unpack('<B', self.f.read(1))[0]

    def u16(self):
        return struct.unpack('<H', self.f.read(2))[0]

    def u32(self):
        return struct.unpack('<I', self.f.read(4))[0]

    def number(self):
        b = self.u8()
        neg = b & 0x40
        val = b & 0x3F
        shift = 6

        while b & 0x80:
            b = self.u8()
            val |= (b & 0x7f) << shift

        if neg:
            val = -val
        return val

    def string(self):
        count = self.number()
        return self.f.read(count)

class Monster(object):
    def __init__(self, d):
        self.name = d.string()
        self.kind_id = d.number()
        self.kind = KINDS[self.kind_id]
        self.level = d.number()
        self.xp = d.number()
        self.health = d.number()
        self.max_health = d.number()
        self.attack = d.number()
        self.defense = d.number()

class GenMonster(object):
    def __init__(self, kind_id, level):
        self.level = level
        self.kind_id = kind_id
        self.kind = KINDS[kind_id]
        self.name = self.kind['name']
        self.max_health = self.kind['max_health'] + level * 8
        self.attack = self.kind['attack'] + level * 1
        self.defense = self.kind['defense'] + level * 1
        self.xp = 0
        self.health = self.max_health

class Vet(object):
    def __init__(self, d):
        self.icon = 'V'

class Trainer(object):
    def __init__(self, d):
        self.icon = chr(d.number())
        self.player_won = bool(d.number())
        self.reward = d.number()
        self.name = d.string()
        self.team = []
        for i in xrange(d.number()):
            self.team.append(Monster(d))

class Treasure(object):
    def __init__(self, d):
        self.icon = chr(d.number())
        self.avail = self.icon == '$'
        self.value = d.number()

class NameChanger(object):
    def __init__(self, d):
        self.icon = 'N'

class Empty(object):
    def __init__(self):
        self.icon = ' '

class Wall(object):
    def __init__(self):
        self.icon = '#'

class Player(object):
    def __init__(self, d):
        self.x = d.number()
        self.y = d.number()
        self.icon = chr(d.u8())
        self.money = d.number()

        self.team = []
        for i in xrange(d.number()):
            self.team.append(Monster(d))

        self.bank = []
        for i in xrange(d.number()):
            self.bank.append(Monster(d))

class Map(object):
    def __init__(self, d):
        self.width = d.number()
        self.height = d.number()
        self.start_x = d.number()
        self.start_y = d.number()
        self.next_id = d.number()

        self.tiles = array.array('B')
        i = 0
        while i < self.width * self.height:
            count = d.number()
            if count < 0:
                raise Exception('Bad RLE count')
            tile = d.u8()
            for j in xrange(count):
                self.tiles.append(tile)
            i += count
        if i != self.width * self.height:
            raise Exception('Bad RLE')

        self.objects = {}
        for i in xrange(self.next_id):
            self.objects[i] = self.decode_mapobject(d)
        self.objects[0xFE] = Empty()
        self.objects[0xFF] = Wall()

        self.player = Player(d)

    def decode_mapobject(self, d):
        type_ = d.number()
        if type_ == 0:
            return Vet(d)
        elif type_ == 1:
            return Treasure(d)
        elif type_ == 2:
            return Trainer(d)
        elif type_ == 3:
            return NameChanger(d)
        else:
            raise Exception('Bad map object type (%d)' % type_)

    def get_tile(self, x, y):
        return self.objects[self.tiles[x + y * self.width]]

    def display(self):
        out = StringIO()
        out.write('\x1B[2J')
        out.write('Money: %6d\n' % self.player.money)
        for y in xrange(self.height):
            for x in xrange(self.width):
                if (x, y) == (self.player.x, self.player.y):
                    out.write('*')
                else:
                    out.write(self.get_tile(x, y).icon)
            out.write('\n')
        return out.getvalue()

class Random(object):
    def __init__(self, state0, state1):
        self.state0 = 168642907
        self.state1 = 182064376

    def _update(self):
        if self.state0 & 1:
            self.state0 ^= 0x29D1E9EB << 1
        self.state0 >>= 1

        if self.state1 & 1:
            self.state1 ^= 0xF5CDE95 << 1
        self.state1 >>= 1

    def _rand(self):
        self._update()
        return (self.state0 ^ self.state1) & 0xFFFF

    def randint(self, upper):
        r = self._rand()
        while r > 0x10000 / upper * upper - 1:
            r = self._rand()
        return r % upper

class Game(object):
    def __init__(self, state_string, recv, send):
        self.MAX_STEPS = int(random.paretovariate(2) * 30)#random.randint(50, 200)
        self.recv = recv
        self.send = send
        self.map = Map(Deserializer(dearmor(state_string)))
        self.rand = Random(168642907, 182064376)

    def current(self):
        return (self.map.player.x, self.map.player.y)

    def calc_weight(self, p):
        x, y, d = p

        if (x, y) not in self.visited:
            # we have never visited this tile, give max weight
            return 5.0

        dt = min(self.time - self.visited[(x, y)], 40)
        return dt / 10.0

    def next_step(self):
        # all possible results
        OPTIONS = [(1, 0, 'd'), (-1, 0, 'a'), (0, 1, 's'), (0, -1, 'w')]

        self.visited[self.current()] = self.time
        self.time += 1

        # calculate real options
        options = map(lambda p: (p[0] + self.map.player.x, p[1] + self.map.player.y, p[2]), OPTIONS)
        # filter to get valid options
        options = filter(lambda p: 0 <= p[0] < self.map.width, options) 
        options = filter(lambda p: 0 <= p[1] < self.map.height, options) 
        options = filter(lambda p: not isinstance(self.map.get_tile(p[0], p[1]), Wall), options)
        # add weights
        options = map(lambda p: (p, self.calc_weight(p)), options)

        # from stack overflow... a weighted random choice
        total = sum(weight for p, weight in options)
        r = random.uniform(0, total)
        upto = 0
        for p, weight in options:
            if upto + weight > r:
                return p
            upto += weight

    def handle_vet(self):
        self.recv("Welcome to Vet Center! How can we help you?\n")

        while True:
            self.recv("Menu: (G)ood-bye, (H)eal, (S)tore a Monster, (W)ithdraw a Monster\n")
            self.send('g')
            break

    def handle_treasure(self, t):
        if t.avail:
            self.map.player.money += t.value
            t.avail = False
            t.icon = ' '

    def handle_trainer(self, t):
        if t.player_won:
            return

        self.recv("New challenger! Trainer %s prepares to battle!\n" % t.name)
        t.player_won = self.battle(t.team)
        if t.player_won:
            self.map.player.money += t.reward
            t.icon = ' '

    def handle_wild(self):
        level = self.get_level(*self.current())
        m = self.random_monster(level)
        self.recv("A wild %s attacks!\n" % m.name)
        self.battle([m], wild=True)

    def handle(self, tile):
        if isinstance(tile, Empty):
            return True
        elif isinstance(tile, Wall):
            return False
        elif isinstance(tile, Vet):
            self.handle_vet()
            return False
        elif isinstance(tile, Treasure):
            self.handle_treasure(tile)
            return True
        elif isinstance(tile, Trainer):
            self.handle_trainer(tile)
            return tile.player_won
        else:
            raise Exception('Bad tile type')

    def handle_death(self):
        alive = list(filter(lambda m: m.health > 0, self.map.player.team))
        if len(alive):
            return

        self.map.player.money /= 2
        self.map.player.x, self.map.player.y = self.map.start_x, self.map.start_y
        for m in self.map.player.team:
            m.health = m.max_health

    def random_walk(self):
        self.time = 1
        self.visited = {}
        steps = 0

        self.recv(self.map.display())
        while steps < self.MAX_STEPS:
            steps += 1
            x, y, direction = self.next_step()
            self.send(direction)

            new_tile = self.map.get_tile(x, y)
            if self.handle(new_tile):
                self.map.player.x = x
                self.map.player.y = y

                if self.rand.randint(10) == 0:
                    # wild battle!
                    self.handle_wild()

            self.handle_death()
            self.recv(self.map.display())

    def calc_dmg(self, attacker, defender, power):
        def multiplier(a, d):
            COMBOS = {
                ('earth', 'wind'): 200,
                ('wind', 'fire'): 200,
                ('fire', 'earth'): 200,
                ('wind', 'earth'): 50,
                ('fire', 'wind'): 50,
                ('earth', 'fire'): 50,
                ('earth', 'earth'): 100,
                ('wind', 'wind'): 100,
                ('fire', 'fire'): 100
            }
            return COMBOS[(a, d)]
        dmg = attacker.attack - defender.defense + power * multiplier(attacker.kind['type'], defender.kind['type']) / 100
        dmg = dmg * self.rand.randint(110) / 100
        if dmg > 0:
            defender.health = max(0, defender.health - dmg)

    def capture(self, m):
        if len(self.map.player.team) < 6:
            self.map.player.team.append(m)
        elif len(self.map.player.bank) < 99:
            self.map.player.bank.append(m)
        else:
            self.recv("No space on team or in bank. %s was abandoned.\n" % m.name)

    def gain_xp(self, pm, em):
        xp = em.level * 100
        pm.xp += xp
        to_level_up = 100 * pm.level * pm.level / 4
        if pm.xp > to_level_up:
            pm.xp -= to_level_up
            if pm.level < 99:
                pm.level += 1
                bonus = self.rand.randint(299)
                pm.max_health += (800 + bonus) / 100
                pm.attack += (100 + bonus) / 100
                pm.defense += (100 + bonus) / 100
                pm.health = pm.max_health

    def battle(self, enemy, wild=False):
        player = list(filter(lambda m: m.health > 0, self.map.player.team))
        enemy = list(enemy)
        for m in enemy:
            m.health = m.max_health
        
        while len(player) and len(enemy):
            pm, em = player[0], enemy[0]
            self.recv("%s (Lvl %d) versus %s (Lvl %d)\n" % (pm.name, pm.level, em.name, em.level))
            while True:
                defending = False
                self.recv("\nPlayer: %s\n        Health %d / %d\n" % (pm.name, pm.health, pm.max_health))
                self.recv("\nEnemy:  %s\n        Health %d / %d\n" % (em.name, em.health, em.max_health))
                self.recv("Menu: (A)ttack, (D)efend, (C)apture, (R)etreat\n")
                r = random.randint(0, 99)
                if r < 50: #attack
                    self.send("a")
                    for i in xrange(len(pm.kind['attacks'])):
                        name, power = pm.kind['attacks'][i]
                        self.recv("%d. %s (%d)\n" % (i+1, name, power))
                    self.recv("What attack to perform?\n")
                    i = random.randint(1, len(pm.kind['attacks']))
                    self.send(str(i))
                    name, power = pm.kind['attacks'][i-1]
                    self.calc_dmg(pm, em, power)
                    if em.health == 0:
                        self.gain_xp(pm, em)
                        del enemy[0]
                        break
                elif r < 70: #defend
                    self.send("d")
                    defending = True
                    self.recv("%s takes a defensive stance.\n" % pm.name)
                elif r < 90: #capture
                    self.send("c")
                    if wild and em.health * 10 < em.max_health and self.rand.randint(100) < 70:
                        self.recv("Successfully captured %s!\n" % em.name)
                        self.capture(em)
                        del enemy[0]
                        player = list(filter(lambda m: m.health > 0, self.map.player.team))
                        break
                    else:
                        self.recv("Unable to capture %s.\n" % em.name)
                else: #retreat
                    self.send("r")
                    if self.rand.randint(100) < 30:
                        self.recv("Successful retreat!\n")
                        return False
                    self.recv("Unable to retreat...\n")

                name, power = em.kind['attacks'][self.rand.randint(len(em.kind['attacks']))]
                self.calc_dmg(em, pm, power * (70 if defending else 100) / 100)
                if pm.health == 0:
                    del player[0]
                    break
        return len(enemy) == 0

    def get_level(self, x, y):
        max_dist = abs(self.map.width - self.map.start_x) + abs(self.map.height - self.map.start_y)
        dist = abs(x - self.map.start_x) + abs(y - self.map.start_y)
        return max(1, 99 * dist / max_dist)

    def random_monster(self, level):
        kind_id = self.rand.randint(len(KINDS))
        return GenMonster(kind_id, level)

class A(Actions):
    def start(self):
        self.state['state'] = 0

    def string_recv(self, s):
        # all strings are new-line delimited, so let's just split on that
        for l in s.splitlines(True):
            assert l[-1] == '\n'
            self.read(delim='\n', expect=l)
        #self.read(length=len(s), expect=s)

    def string_send(self, s):
        self.write(s)

    def doit(self):
        g = Game(STATES[self.state['state']], self.string_recv, self.string_send)
        g.random_walk()

