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

from generator.actions import Actions, Variable
from random import choice, randint
from os.path import dirname, abspath, join
import sys

sys.path.append(join(dirname(dirname(dirname(abspath(__file__)))), "support"))
import support as sp
from common import DEBUG, CONFIG
from resort import Resort, Decider, Rider, Trail, Lift

class TemplatePoller(Actions):

    LOAD_DIGRAPH          =   '\xd0\xd1\xd2\xd3'
    LOAD_RIDER_GROUP      =   '\x40\x41\x42\x43'
    LOAD_RIDER_SINGLE     =   '\xe0\xe1\xe2\xe3'
    UNLOAD_RIDERS         =   '\xf0\xf1\xf2\xf3'
    START                 =   '\x10\x11\x12\x13'
    RESET                 =   '\x11\x22\x33\x11'
    LIFT_STATS            =   '\x11\x43\x34\x11'
    TRAIL_STATS           =   '\x77\x11\xee\x55'
    RIDER_STATS           =   '\x44\x11\x33\x55'

    OK      = ''
    ERR     = ''


    def _gen_status_msgs(self):
        ok = [0,0,0,0]
        err = [0,0,0,0]
        for idx in [c for c in range(len(self.magic_page)) if c % 2 == 0]:
            ok[idx % 4] ^= ord(self.magic_page[idx])
            err[(idx+1) % 4] ^= ord(self.magic_page[idx+1])
        self.OK  = ''.join([chr(c) for c in ok])
        self.ERR = ''.join([chr(c) for c in err])

    def _gen_random_rider(self):
        # r_id = randint(0, 100000)
        # while r_id in self.rider_ids:
        #     r_id = randint(0, 100000)
        self.rider_ids.add(self.rider_id_init)
        rider = Rider(self.rider_id_init, self.health_check_init)
        self.rider_id_init += 1
        self.health_check_init += 1
        rider.gen_stats(e_level=randint(5,10))
        return rider

    def start(self):
        if DEBUG:
            print "------- start -----------"
        self._gen_status_msgs()
        self.resort = Resort(flag_page=self.magic_page)
        self.rider_ids = set()
        self.rider_id_init = 0x41414141
        self.health_check_init = 0x1F1F1F1F

    def load_resort_digraph(self):
        '''
        Load a new resort digraph.
        '''
        if DEBUG:
            print "cmd: load resort digraph -----------"

        self.resort_size = 3
        self.resort_min_altitude = 5000
        self.resort_max_altitude = 15000

        # trash old digraph, but save and reset the riders
        self.resort.resort_reset()
        riders = self.resort.riders
        self.resort = Resort(self.resort_size, self.resort_min_altitude, self.resort_max_altitude, self.magic_page)
        self.resort.riders = riders

        self.resort.generate_random_layout(t_len=15, t_diffs=[3, 4, 4, 5], c_count=15)
        buf = self.LOAD_DIGRAPH + self.resort.generate_load_digraph_buffer()

        self.write(buf)
        self.read(length=len(self.OK))
        return 0

    def load_rider_group(self):
        '''
        Load a group of riders.
        '''
        if DEBUG:
            print "cmd: load rider group -----------"

        riders = []        
        # count = randint(50,200)
        r_id = 0x41414141
        count = 200
        rider_buf = self.LOAD_RIDER_GROUP + sp.pack_single_uint32(count)
        # self.write(rider_buf)

        for _ in range(count):
            r = self._gen_random_rider()
            r.id = r_id
            r_id += 1
            riders.append(r)
            rider_buf += r.generate_load_buffer()
            # self.write(r.generate_load_buffer())

        self.resort.riders += riders
        self.resort.rider_count += len(riders)

        if DEBUG:
            print "Adding {0} riders".format(len(riders))
            for r in riders:
                print " [r{0}] added".format(r.id)

        self.write(rider_buf)
        self.read(length=len(self.OK))

        return 0

    def load_rider_single(self):
        '''
        Load one rider.
        '''
        if DEBUG:
            print "cmd: load rider single -----------"

        riders = []        
        count = 1
        rider_buf = self.LOAD_RIDER_SINGLE + sp.pack_single_uint32(count)
        for _ in range(count):
            r = self._gen_random_rider()
            riders.append(r)
            rider_buf += r.generate_load_buffer()

        self.resort.riders += riders
        self.resort.rider_count += len(riders)

        if DEBUG:
            print " [r{0}] added".format(riders[0].id)

        self.write(rider_buf)
        self.read(length=len(self.OK))

        return 0

    def unload_riders(self):
        '''
        Reset simulation and delete all riders.
        '''
        if DEBUG:
            print "cmd: unload riders -----------"

        self.resort.resort_reset()
        self.resort.riders = []
        self.resort.rider_count = 0

        buf = self.UNLOAD_RIDERS
        self.write(buf)
        self.read(length=len(self.OK), expect=self.OK)

        return 0

    def start_simulation(self):
        '''
        Run the simulation for steps iterations.
        '''
        if DEBUG:
            print "cmd: start simulation -----------"

        # steps = randint(5000, 10000)
        steps = 10000
        self.resort.run_sim(steps)

        self.write(self.START + sp.pack_single_uint32(steps))

        if 0 == self.resort.rider_count:
            self.read(length=len(self.ERR), expect=self.ERR)
            return -1

        self.read(length=len(self.OK))
        return 0

    def reset_simulation(self):
        '''
        Reset simulation, but do not delete any riders.
        '''
        if DEBUG:
            print "cmd: reset simulation -----------"

        self.resort.resort_reset()

        self.write(self.RESET)
        self.read(length=len(self.OK))

        return 0

    def lift_stats(self):
        '''
        Get the stats from the lifts (ID, rider_total)
        '''
        if DEBUG:
            print "cmd: lift stats -----------"

        self.write(self.LIFT_STATS)
        ls_buf = self.resort.lift_stats_buffer()
        if '' == ls_buf:
            self.read(length=len(self.ERR), expect=self.ERR)
        else:
            self.read(length=len(ls_buf + self.OK), expect=ls_buf + self.OK)

        return 0

    def trail_stats(self):
        '''
        Get the stats from the trails (ID, rider_total)
        '''
        if DEBUG:
            print "cmd: trail stats -----------"

        self.write(self.TRAIL_STATS)
        s_buf = self.resort.trail_stats_buffer()
        if '' == s_buf:
            self.read(length=len(self.ERR), expect=self.ERR)
        else:
            self.read(length=len(s_buf + self.OK), expect=s_buf + self.OK)

        return 0

    def rider_stats(self):
        '''
        Get the stats from the riders (ID, energy_level)
        '''
        if DEBUG:
            print "cmd: rider stats -----------"

        self.write(self.RIDER_STATS)
        s_buf = self.resort.rider_stats_buffer()
        if '' == s_buf:
            self.read(length=len(self.ERR), expect=self.ERR)
        else:
            self.read(length=len(s_buf + self.OK), expect=s_buf + self.OK)

        return 0

    def full_set(self):
        self.load_resort_digraph()
        self.load_rider_group()
        self.start_simulation()
        fn = choice( [self.lift_stats, self.rider_stats, self.trail_stats] )
        fn()

        # self.resort.route()

        fn = choice( [self.reset_simulation, self.unload_riders] )
        fn()

        if 0 > self.start_simulation():
            return self.quit()

        fn = choice( [self.lift_stats, self.rider_stats, self.trail_stats] )
        fn()

        # self.resort.route()
        self.quit()

    def pov(self):
        self.load_resort_digraph()
        self.load_rider_group()
        self.start_simulation()

        self.reset_simulation()

        self.start_simulation()
        # self.resort.route()
        self.quit()

    def quit(self):
        '''
        Quit cleanly
        '''
        if DEBUG:
            print "cmd: quit -----------"

        return -1

    def broker(self):
        '''
        Branching node for all nodes
        '''
        return 0
