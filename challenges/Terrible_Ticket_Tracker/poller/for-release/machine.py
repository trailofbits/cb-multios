#!/usr/bin/env python

from collections import deque
from generator.actions import Actions
import random
import struct
import string

EOL = '\n'
COMMAND_DELIM = '|'
MAX_WORKERS = 128


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

OPEN = 1
IN_PROGRESS = 2
REJECTED = 3
RESOLVED = 4

LOW = 1
MEDIUM = 2
HIGH = 3
SEVERE = 4
CRITICAL = 5

priorities = [
    LOW,
    MEDIUM,
    HIGH,
    SEVERE,
    CRITICAL
]

statuses = [
    OPEN,
    IN_PROGRESS,
    REJECTED,
    RESOLVED,
]


class Time(object):
    def __init__(self):
        self.tick = 0

    def time(self):
        self.tick += 1
        return self.tick

    def tick(self):
        self.tick += 1

    def reset(self):
        self.tick = 0

clock = Time()
tid = 1
sid = 1


class Ticket(object):
    def __init__(self, email, desc, entry, duration, priority):
        global tid
        self.id = tid
        tid += 1

        self.email = email
        self.desc = desc
        self.entry = entry
        self.duration = duration
        self.priority = priority
        self.status = OPEN
        self.prev = None

    def workon(self):
        if self.duration > 0:
            self.duration -= 1

    def done(self):
        return self.duration == 0

    def display(self):
        s = ''
        s += '%d' % self.id
        s += EOL
        s += '%s' % self.email
        s += EOL
        s += '%s' % self.desc
        s += EOL
        s += '%d' % self.status
        s += EOL
        s += '%d' % self.priority
        s += EOL
        s += '%d' % self.entry
        s += EOL
        s += '%d' % self.duration
        s += EOL

        return s


class Support(object):
    def __init__(self, contact, prio):
        global sid
        self.id = sid
        sid += 1

        self.contact = contact
        self.priority = prio
        self.ticket = None

    def assign_ticket(self, ticket):
        self.ticket = ticket

    def update_ticket(self, status):
        if self.ticket:
            self.ticket.status = status

    def display(self):
        s = ''
        s += '%d' % self.id
        s += EOL
        if self.ticket:
            s += '%d' % self.ticket.id
        else:
            s += 'None'
        s += EOL
        s += '%d' % self.contact
        s += EOL
        s += '%d' % self.priority
        s += EOL

        return s


class Scheduler(object):
    def __init__(self, dispatcher, workers):
        self.dispatcher = dispatcher
        self.workers = workers

    def run(self):
        for w in self.workers:
            if w.ticket is None:
                t = self.dispatcher.get_ticket(w.priority)
                if t and t.prev != w:
                    w.assign_ticket(t)
                    w.update_ticket(IN_PROGRESS)
                else:
                    self.dispatcher.add_ticket(t)
            else:
                w.ticket.workon()
                if w.ticket.done():
                    w.ticket.status = RESOLVED
                    self.dispatcher.record_finished(w)
                    w.ticket = None
                elif self.dispatcher.random_tick(10) < 2:
                    if w.ticket.priority > HIGH:
                        continue
                    w.ticket.status = REJECTED
                    w.ticket = None
                elif self.dispatcher.random_tick(10) < 3:
                    self.dispatcher.add_ticket(w.ticket)
                    w.ticket.status = OPEN
                    w.ticket.prev = w
                    w.ticket = None


class Dispatcher(object):
    def __init__(self, workers, magic, r):
        self.workers = workers
        self.magic = magic
        self.midx = 0
        self.r = r

        self.tickets = []
        for _ in xrange(CRITICAL):
            self.tickets.append(deque())

    def add_ticket(self, ticket):
        if not ticket:
            return

        if ticket.status == OPEN:
            self.tickets[ticket.priority - 1].append(ticket)
        else:
            self.tickets[ticket.priority - 1].appendleft(ticket)

    def record_finished(self, worker):
        s1 = 'Ticket Finished' + EOL
        self.r(expect=s1, length=len(s1))
        self.r(expect=str(worker.id) + EOL, length=len(str(worker.id) + EOL))
        self.r(expect=worker.ticket.desc, length=len(worker.ticket.desc))
        worker.ticket = None

    def cancel_ticket(self, tid):
        for q in self.tickets:
            for ticket in list(q):
                if ticket.id == tid:
                    q.remove(ticket)
                    return

        for worker in self.workers:
            if worker.ticket and worker.ticket.id == tid:
                worker.ticket = None

    def view_ticket(self, iid):
        for q in self.tickets:
            for ticket in q:
                if ticket.id == iid:
                    return ticket.display()

        for w in self.workers:
            if w.ticket and w.ticket.id == iid:
                    return w.ticket.display()

    def view_tickets(self, status):
        s = ''
        for q in self.tickets:
            for ticket in q:
                if ticket.status == status:
                    s += ticket.display()

        for w in self.workers:
            if w.ticket and w.ticket.status == status:
                s += w.ticket.display()

        return s

    def get_ticket(self, prio):
        for p in xrange(prio, 0, -1):
            if len(self.tickets[p - 1]):
                return self.tickets[p - 1].popleft()

    def random_tick(self, mmax):
        v = struct.unpack('<I', self.magic[self.midx: self.midx + 4])[0]
        self.midx = (self.midx + 4) % 0x1000
        return v % mmax


def rs():
    n = random.randint(2, 16)
    return ''.join([random.choice(string.letters) for _ in xrange(n)])


class TemplateGenerator(Actions):
    def start(self):
        #self.delay(100)
        kaprica_mixin(self)
        self.xlat_seed('EREH_EULAV_MODNAR')

        global tid
        global sid
        tid = 1
        sid = 1
        clock.reset()

        self.workers = [
            Support(0, HIGH),
            Support(0, CRITICAL),
        ]
        self.dispatcher = Dispatcher(self.workers, self.magic_page, self.read)
        self.scheduler = Scheduler(self.dispatcher, self.workers)

        self.read_delim_s("Welcome to the terrible ticket tracker")

    def read_delim_s(self, s):
        self.read(delim=EOL, expect=s)

    def read_prompt(self):
        self.read(length=2, expect="$ ")

    def write_command(self, *args):
        s = COMMAND_DELIM.join(map(str, args)) + COMMAND_DELIM + COMMAND_DELIM
        self.comment(s)
        self.write(s)

    def pick_command(self):
        clock.time()
        self.scheduler.run()

    def add_ticket(self):
        self.read_prompt()

        email = rs()
        desc = rs()
        p = random.choice(priorities)

        t = Ticket(email, desc, clock.time(), self.dispatcher.random_tick(100), p)
        self.dispatcher.add_ticket(t)

        self.write_command("ADD_TICKET", email, desc, '%02d' % p)
        self.read_delim_s('OK')

    def view_tickets(self):
        self.read_prompt()

        if self.chance(0.5):
            st = random.choice(statuses)
            self.write_command("VIEW", '%02d' % st)
            s = self.dispatcher.view_tickets(st)
            if s:
                self.read(length=len(s), expect=s)
        else:
            self.write_command("VIEW")
            s = ''

            for status in statuses:
                s += self.dispatcher.view_tickets(status)

            if s:
                self.read(length=len(s), expect=s)

        self.read_delim_s('OK')

    def view_ticket(self):
        self.read_prompt()

        if self.chance(0.3):
            t = random.choice(xrange(tid))
        else:
            t = tid * 2

        self.write_command("VSTATUS", '%02d' % t)
        s = self.dispatcher.view_ticket(t)
        if s:
            self.read(length=len(s), expect=s)
        self.read_delim_s('OK')

    def cancel_ticket(self):
        self.read_prompt()

        if self.chance(0.3):
            t = random.choice(xrange(tid))
        else:
            t = tid * 2

        self.write_command("CANCEL_TICKET", '%02d' % t)
        self.dispatcher.cancel_ticket(t)
        self.read_delim_s('OK')

    def list_free_support(self):
        s = ''
        for w in self.workers:
            if w.ticket is None:
                s += w.display()

        self.read_prompt()
        self.write_command("LIST_FREE_SUPPORT")
        if len(s):
            self.read(length=len(s), expect=s)
        self.read_delim_s('OK')

    def list_support(self):
        s = ''
        for w in self.workers:
            s += w.display()

        self.read_prompt()
        self.write_command("LIST_SUPPORT")
        if s:
            self.read(length=len(s), expect=s)
        self.read_delim_s('OK')

    def hire(self):
        p = random.choice(xrange(SEVERE + 2))

        if LOW <= p <= CRITICAL and len(self.workers) < MAX_WORKERS:
            self.workers.append(Support(0, p))

        self.read_prompt()
        self.write_command("HIRE", '%02d' % p)
        self.read_delim_s('OK')

    def fire(self):
        p = random.choice(xrange(SEVERE + 2))

        if LOW <= p <= CRITICAL and len(self.workers) > 0:
            try:
                to_fire = filter(lambda x: x.priority == p, self.workers)[0]
            except IndexError:
                to_fire = None

            if to_fire:
                self.workers.remove(to_fire)
                if to_fire.ticket:
                    self.dispatcher.add_ticket(to_fire.ticket)

        self.read_prompt()
        self.write_command("FIRE", '%02d' % p)
        self.read_delim_s('OK')

    def fin(self):
        self.read_prompt()
        self.write_command('QUIT')
        self.read_delim_s('TERMINATING TERRIBLE TICKET TRACKER')
