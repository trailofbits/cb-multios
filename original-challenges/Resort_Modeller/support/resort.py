#!/usr/bin/env python
#
# Copyright (C) 2014 Narf Industries <info@narfindustries.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
from random import choice, randint

import support as sp
from common import DEBUG, CONFIG

class FlagPage(object):
    def __init__(self, flag_page):
        self.flag_page = flag_page
        self.cur_idx = 0

    def next_byte(self):
        b = self.flag_page[self.cur_idx]
        if DEBUG:
            print " fp[{0}] = 0x{1}".format(self.cur_idx, ord(b))
        self.cur_idx = (self.cur_idx + 1) % 4096
        return b

class Resort(object):
    def __init__(self, r_size=3, min_altitude=5000, max_altitude=15000, flag_page=''):
        self.size = r_size
        self.min_altitude = min_altitude
        self.max_altitude = max_altitude
        self.deciders = []
        self.rider_count = 0
        self.riders = []
        self.trails = []
        self.lifts = []
        self.flag_page = FlagPage(flag_page)

    def run_sim(self, steps):
        '''
        Run the simulation steps iterations.
        '''
        if DEBUG:
            self.route()

        min_decider = self.get_decider_min()
        min_decider.add_riders(self.riders)
        if DEBUG:
            print "start sim with {0} riders on D{1}".format(len(self.riders), min_decider.id)

        self.riders = []

        for count in range(steps):
            if DEBUG:
                print " step {0}".format(count)
            # deciders
            if DEBUG:
                print "{0} deciders".format(len(self.deciders))
            for d in self.deciders:
                d.step(self.flag_page, self.trails, self.lifts)

            # trails
            if DEBUG:
                print "{0} trails".format(len(self.trails))
            for t in self.trails:
                t.step(self.deciders)

            # lifts
            if DEBUG:
                print "{0} lifts".format(len(self.lifts))
            for l in self.lifts:
                l.step(self.deciders)

    def lift_stats_buffer(self):
        '''
        Examine all lifts and collect their stats into a buffer.

        For each lift, get id and rider_total
        '''
        buf = ''
        for l in self.lifts:
            if DEBUG:
                print "L{0} had {1} riders".format(l.id, l.rider_total)
            buf += sp.pack_single_uint32(l.id)
            buf += sp.pack_single_uint32(l.rider_total)
        return buf

    def trail_stats_buffer(self):
        '''
        Examine all trails and collect their stats into a buffer.

        For each trail, get id and rider_total
        '''
        buf = ''
        for t in self.trails:
            if DEBUG:
                print "T{0} had {1} riders".format(t.id, t.rider_total)
            buf += sp.pack_single_uint32(t.id)
            buf += sp.pack_single_uint32(t.rider_total)
        return buf

    def rider_stats_buffer(self):
        '''
        Examine all riders and collect their stats into a buffer.

        For each rider, get id and energy_level
        '''
        buf = ''

        for d in self.deciders:
            for r in d.rider_queue:
                buf += r.get_stats()
            for r in d.quitters:
                buf += r.get_stats()

        for l in self.lifts:
            for r in l.riders:
                buf += r.get_stats()
            for c in l.chairs:
                for r in c.riders:
                    buf += r.get_stats()

        for t in self.trails:
            for r in t.riders:
                buf += r.get_stats()

        for r in self.riders:
            buf += r.get_stats()

        return buf

    def resort_reset(self):
        '''
        Get all riders from lifts, trails, and deciders, and return them to self.riders.
        Reset deciders, riders, trails, lifts to initial state.
        '''
        for d in self.deciders:
            self.riders += d.decider_reset()
        for l in self.lifts:
            self.riders += l.lift_reset()
        for t in self.trails:
            self.riders += t.trail_reset()

        for r in self.riders:
            r.rider_reset()

    def generate_load_digraph_buffer(self):
        '''
        decider count, lift count, trail count
        decider tuples (ID, altitude)
        lift tuples (ID, start decider, end decider, chair_count, chair_capacity)
        trail tuples (ID, start decider, end decider, difficulty, length)
        '''
        lb = ''
        lb += sp.pack_single_uint32(len(self.deciders))
        lb += sp.pack_single_uint32(len(self.lifts))
        lb += sp.pack_single_uint32(len(self.trails))
        for d in self.deciders:
            lb += d.generate_load_buffer()
        for l in self.lifts:
            lb += l.generate_load_buffer()
        for t in self.trails:
            lb += t.generate_load_buffer()
        return lb

    def get_decider_min(self):
        return min(self.deciders, key=lambda d: d.altitude)

    def get_decider_by_id(self, d_id):
        for decider in self.deciders:
            if decider.id == d_id:
                return decider
        return None

    def generate_random_layout(self, t_len=randint(10, 50), t_diffs=[1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 5], c_count=randint(10, 50)):
        if DEBUG:
            print "generate_random_layout()"
        decider_altitudes = set()
        for d_id in range(self.size + 1):
            d = None
            if d_id == 0:
                d = Decider(d_id, self.min_altitude)
            else:
                d = Decider(d_id, randint(self.min_altitude, self.max_altitude))
                # no duplicate altitudes
                while d.altitude in decider_altitudes:
                    d = Decider(d_id, randint(self.min_altitude, self.max_altitude))

            decider_altitudes.add(d.altitude)
            self.deciders.append(d)
            if DEBUG:
                print " [d{0}] added".format(d.id)

        # all deciders sorted by altitude from low to high
        alt_sorted_deciders = sorted(self.deciders, key=lambda x: x.altitude)
        enum_alt_sorted_deciders = list(enumerate(alt_sorted_deciders))
        lift_start_decider_idxs = set()
        lift_end_decider_idxs = set()
        lift_end_decider_idxs_remaining = [i[0] for i in enum_alt_sorted_deciders[1:]]
        for l_id in range(self.size):
            l = Lift(l_id)
            l.chair_count = c_count
            # l.chair_count = 3
            l.chair_capacity = choice([2, 4])
            l.gen_chairs()

            start_decider_tuple = None
            if 0 == l_id:
                start_decider_tuple = enum_alt_sorted_deciders[0]
            else:
                start_decider_tuple = choice(enum_alt_sorted_deciders[:-1])

            remaining_usable_idxs = [i for i in lift_end_decider_idxs_remaining if i > start_decider_tuple[0]]
            if [] != remaining_usable_idxs:
                end_decider_tuple_idx = choice(remaining_usable_idxs)
                lift_end_decider_idxs_remaining.remove(end_decider_tuple_idx)
            else:
                end_decider_tuple_idx = choice([i[0] for i in enum_alt_sorted_deciders if i[0] > start_decider_tuple[0]])

            end_decider_tuple = enum_alt_sorted_deciders[end_decider_tuple_idx]    

            l.start_decider = start_decider_tuple[1].id
            l.end_decider = end_decider_tuple[1].id

            lift_start_decider_idxs.add(start_decider_tuple[0])
            lift_end_decider_idxs.add(end_decider_tuple[0])

            start_decider = self.get_decider_by_id(l.start_decider)
            start_decider.transport_options.append(l)

            self.lifts.append(l)
            if DEBUG:
                print " [l{0}] added".format(l.id)

        # lift end is used as the starting point of a trail
        # lift start is used as ending point of a trail
        trail_end_decider_idxs = sorted(list(lift_start_decider_idxs))
        trail_start_decider_idxs = sorted(list(lift_end_decider_idxs))

        # want to try to use up one of each of these before randomly selecting to help make closed graph
        trail_end_decider_idxs_remaining = list(trail_end_decider_idxs)
        for t_id in range(self.size * 2):
            t = Trail(t_id)
            t.difficulty = choice(t_diffs)
            t.length = t_len
            # t.length = 3

            start_decider_tuple = None
            if t_id < len(trail_start_decider_idxs):
                d_tuple_idx = trail_start_decider_idxs[t_id]
                start_decider_tuple = enum_alt_sorted_deciders[d_tuple_idx]
            else:
                start_decider_tuple = enum_alt_sorted_deciders[choice(trail_start_decider_idxs)]

            remaining_usable_idxs = [i for i in trail_end_decider_idxs_remaining if i < start_decider_tuple[0]]
            end_decider_tuple_idx = 0
            if [] != remaining_usable_idxs:
                end_decider_tuple_idx = choice(remaining_usable_idxs)
                trail_end_decider_idxs_remaining.remove(end_decider_tuple_idx)
            else:
                end_decider_tuple_idx = choice([i for i in trail_end_decider_idxs if i < start_decider_tuple[0]])

            end_decider_tuple = enum_alt_sorted_deciders[end_decider_tuple_idx]    

            t.start_decider = start_decider_tuple[1].id
            t.end_decider = end_decider_tuple[1].id

            start_decider = self.get_decider_by_id(t.start_decider)
            start_decider.transport_options.append(t)

            self.trails.append(t)
            if DEBUG:
                print " [t{0}] added".format(t.id)


    def route(self):
        for d in self.deciders:
            print d.route()

        for l in self.lifts:
            print l.route()

        for t in self.trails:
            print t.route()

    def __str__(self):
        return "Resort(size={0},min_altitude={1},max_altitude={2},\ndeciders={3},\nriders={4},\ntrails={5},\nlifts={6})".format(self.size, self.min_altitude, self.max_altitude, self.deciders, self.riders, self.trails, self.lifts)

    def __repr__(self):
        return self.__str__()



class Decider(object):
    def __init__(self, d_id=0, altitude=0):
        self.id = d_id
        self.altitude = altitude
        self.transport_options = []
        self.rider_queue = []
        self.quitters = []

    def add_riders(self, riders):
        for r in riders:
            self.rider_queue.append(r)
            if DEBUG:
                print "D{0} gained R{1}".format(self.id, r.id)

    def select_option(self, flag_page):
        idx = ord(flag_page.next_byte()) % len(self.transport_options)
        if DEBUG:
            print "D{0} selected option idx {1} = {2}".format(self.id, idx, self.transport_options[idx])
        return self.transport_options[idx]

    def step(self, flag_page, trails, lifts):
        if [] == self.transport_options:
            if DEBUG:
                print "D{0} has no transport options".format(self.id)
            return
        riders = len(self.rider_queue)
        if DEBUG:
            print "D{0} rider's in queue {1} quitters {2}".format(self.id, len(self.rider_queue), len(self.quitters))

        for _ in range(riders):
            op = self.select_option(flag_page)
            r = self.rider_queue.pop(0)
            if isinstance(op, Trail) and r.energy_level < op.difficulty:
                    self.quitters.append(r)
                    if DEBUG:
                        print "D{0} rider {1} quit".format(self.id, r.id)
                    continue
            if isinstance(op, Lift) and r.energy_level == 0:
                    self.quitters.append(r)
                    if DEBUG:
                        print "D{0} rider {1} quit".format(self.id, r.id)
                    continue
            op.add_riders([r])
            # if DEBUG:
            #     print "D{0} op: {1}, r: {2}".format(self.id, op, r)
            if DEBUG:
                print "D{0}: moved R{1} to {2}{3}".format(self.id, r.id, type(op), op.id)

    def decider_reset(self):
        riders = self.rider_queue
        riders += self.quitters
        self.rider_queue = []
        self.quitters = []
        return riders

    def generate_load_buffer(self):
        '''
        decider tuple (ID, altitude)
        '''
        return sp.pack_single_uint32(self.id) + sp.pack_single_uint32(self.altitude)

    def route(self):
        return "Decider(id={0},altitude={1},transport_options={2})".format(self.id, self.altitude, ["{0}{1}".format(type(o), o.id) for o in self.transport_options])

    def __eq__(self, other):
        return self.id == other.id

    def __hash__(self):
        return hash( ("id", self.id, "altitude", self.altitude))

    def __str__(self):
        return "Decider(id={0},altitude={1},transport_options={2},rider_queue={3},quitters={4})".format(self.id, self.altitude, self.transport_options, self.rider_queue, self.quitters)

    def __repr__(self):
        return self.__str__()


class Rider(object):

    SKIER = 0
    BOARDER = 1

    def __init__(self, r_id=0, health_code=0xFFFFFFFF):
        self.id = r_id
        self.type = 0
        self.energy_level = 0
        self.initial_energy_level = 0
        self.trail_count = 0
        self.trail_distance = 0
        self.health_code = health_code

    def get_stats(self):
        if DEBUG:
            print self.__str__()

        return sp.pack_single_uint32(self.id) + sp.pack_single_uint32(self.energy_level)

    def rider_reset(self):
        self.energy_level = self.initial_energy_level
        self.trail_count = 0
        self.trail_distance = 0
        if DEBUG:
            print "R{0} reset".format(self.id)

    def generate_load_buffer(self):
        '''
        rider tuple (ID, type, energy_level, health_code)
        '''
        return sp.pack_single_uint32(self.id) + sp.pack_single_uint32(self.type) + \
                sp.pack_single_uint32(self.energy_level) + sp.pack_single_uint32(self.health_code)

    def gen_stats(self, e_level=randint(50, 100)):
        self.type = choice([self.SKIER, self.BOARDER])
        self.energy_level = e_level
        self.initial_energy_level = self.energy_level

    def __str__(self):
        return "Rider(id={0},type={1},energy_level={2},trail_count={3})".format(self.id, self.type, self.energy_level, self.trail_count)

    def __repr__(self):
        return self.__str__()


class Trail(object):
    def __init__(self, t_id=0):
        self.id = t_id
        self.difficulty = 0
        self.length = 0
        self.rider_total = 0
        self.riders = []
        self.start_decider = None
        self.end_decider = None

    def add_riders(self, riders):
        self.rider_total += 1
        self.riders += riders
        if DEBUG:
            for r in riders:
                print "T{0} gained R{1}".format(self.id, r.id)

    def step(self, deciders):
        end_decider = deciders[self.end_decider]

        # move completed riders to end decider
        if [] == self.riders:
            return

        done = [r for r in self.riders if self.length == r.trail_distance]
        self.riders = [r for r in self.riders if self.length != r.trail_distance]

        done_cnt = len(done)
        for r in done:
            r.trail_distance = 0
            r.trail_count += 1
            r.energy_level -= self.difficulty
            end_decider.add_riders([r])

        if DEBUG:
            if 0 != done_cnt:
                print "T{0} moved {1} riders to D{2}".format(self.id, done_cnt, end_decider.id)

        # increment trail_distance on rest of riders
        for r in self.riders:
            r.trail_distance += 1

        if DEBUG:
            if 0 != len(self.riders):
                print "T{0} update {1} riders' distance".format(self.id, len(self.riders))


    def trail_reset(self):
        riders = self.riders
        self.riders = []
        self.rider_total = 0
        return riders

    def generate_load_buffer(self):
        '''
        trail tuple (ID, start decider, end decider, difficulty, length)
        '''
        return sp.pack_single_uint32(self.id) + sp.pack_single_uint32(self.start_decider) + \
                sp.pack_single_uint32(self.end_decider) + sp.pack_single_uint32(self.difficulty) + \
                sp.pack_single_uint32(self.length)

    def route(self):
        return "Trail(id={0},D{1}->D{2})".format(self.id, self.start_decider, self.end_decider)

    def __str__(self):
        return "Trail(id={0},difficulty={1},rider_total={2},riders={3},start_decider={4},end_decider={5})".format(self.id, self.difficulty, self.rider_total, self.riders, self.start_decider, self.end_decider)

    def __repr__(self):
        return self.__str__()

class Chair(object):
    def __init__(self, c_id, capacity=2):
        self.id = c_id
        self.capacity = capacity
        self.riders = []

    def unload(self):
        riders = self.riders
        if DEBUG:
            for r in self.riders:
                print " C{0} unloaded R{1}".format(self.id, r.id)
        self.riders = []
        return riders

    def load(self, r):
        self.riders.append(r)
        if DEBUG:
            print " C{0} loaded R{1}".format(self.id, r.id)


class Lift(object):
    def __init__(self, l_id=0):
        self.id = l_id
        self.chair_count = 0
        self.chair_capacity = 0
        self.rider_total = 0
        self.riders = []
        self.chairs = []
        self.start_decider = None
        self.end_decider = None
        self.c_embark = 0
        self.c_disembark = 0

    def add_riders(self, riders):
        self.riders += riders
        if DEBUG:
            for r in riders:
                print "L{0} gained R{1}".format(self.id, r.id)

    def gen_chairs(self):
        for c_id in range(self.chair_count):
            self.chairs.append(Chair(c_id, self.chair_capacity))
        self.c_embark = 0
        self.c_disembark = len(self.chairs)/2

    def step(self, deciders):
        if [] == self.chairs:
            return

        if DEBUG:
            print "L{0} c_disembark {1} c_embark {2}".format(self.id, self.c_disembark, self.c_embark)

        ''' move riders from c_disembark chair to end_decider's rider_queue '''
        end_decider = deciders[self.end_decider]

        # move riders from c_disembark to end decider
        d_riders = self.chairs[self.c_disembark].unload()
        if 0 != len(d_riders):
            end_decider.add_riders(d_riders)
            if DEBUG:
                print "L{0} unloaded {1} riders to D{2}".format(self.id, len(d_riders), end_decider.id)

        # increment c_disembark
        self.c_disembark = (self.c_disembark + 1) % len(self.chairs)

        ''' move riders from riders to c_embark chair '''
        loaded = 0
        for _ in range(self.chair_capacity):
            if [] == self.riders:
                break;

            r = self.riders.pop(0)
            self.chairs[self.c_embark].load(r)
            self.rider_total += 1
            loaded += 1

        if DEBUG:
            if 0 != loaded:
                print "L{0} loaded {1} riders onto chair {2}".format(self.id, len(self.chairs[self.c_embark].riders), self.chairs[self.c_embark].id)

        # increment c_embark
        self.c_embark = (self.c_embark + 1) % len(self.chairs)


    def lift_reset(self):
        all_riders = []
        for c in self.chairs:
            all_riders += c.unload()

        all_riders += self.riders
        self.riders = []

        self.rider_total = 0
        self.c_embark = 0
        self.c_disembark = len(self.chairs)/2
        return all_riders

    def generate_load_buffer(self):
        '''
        lift tuple (ID, start decider, end decider, chair_count, chair_capacity)
        '''
        return sp.pack_single_uint32(self.id) + sp.pack_single_uint32(self.start_decider) + \
                sp.pack_single_uint32(self.end_decider) + sp.pack_single_uint32(self.chair_count) + \
                sp.pack_single_uint32(self.chair_capacity)

    def route(self):
        return "Lift(id={0},D{1}->D{2})".format(self.id, self.start_decider, self.end_decider)

    def __str__(self):
        return "Lift(id={0},chair_count={1},chair_capacity={2},rider_total={3},riders={4},start_decider={5},end_decider={6})".format(self.id, self.chair_count, self.chair_capacity, self.rider_total, self.riders, self.start_decider, self.end_decider)

    def __repr__(self):
        return self.__str__()



if __name__ == '__main__':

    r = Resort()
    r.generate_random_layout()

    r.route()
