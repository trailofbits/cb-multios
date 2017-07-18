#!/usr/bin/env python
#
# Copyright (C) 2014, 2015
#   Brian Caswell <bmc@lungetech.com>
#   Narf Industries <info@narfindustries.com>
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
from random import randint, choice, sample
import struct
import copy

# Almost random.  We need to avoid delim chars (' ' and '\n' and NULL)
def random_bytes(min, max, mod=255):
    return (''.join(chr(choice(range(mod))) for _ in range(randint(min,max)))).replace(' ', '').replace('\n', '').replace('\x00', '')


class Insulatr(Actions):

    GLOBAL_DEBUG = False
    GLOBAL_POV = False

    # rx_buf is 65535 bytes; lines are capped at MAX_SZ_LINE = 256.
    # 65535 / 256 = 255.
    # Let's cap at 250 to be safe.
    MAX_PENDING_INSN = 250

    MSG_DESERIALIZE = 1
    MSG_SERIALIZE = 2
    MSG_EXIT = 3

    NUM_OBJS = 256
    MAX_SZ_LINE = 256
    MAX_SZ_STRING = MAX_SZ_LINE - len('255 STRING \n') - 50

    def exit(self):
        """
        Tell CB to immediately exit.
        """
        self.write(struct.pack("<B", self.MSG_EXIT))
        return -1

    def deserialize(self):
        """
        Flush pending INSNs to the CB.
        """
        DEBUG = self.GLOBAL_DEBUG and True
        if DEBUG: print "\n[D] deserialize | pending:\n %s" % self.state['pending_insns']

        # Prepend initial newline.
        self.state['pending_insns'] = '\n' + self.state['pending_insns']

        # Write & flush the INSNs.
        self.write(struct.pack("<BH", self.MSG_DESERIALIZE, len(self.state['pending_insns'])) + self.state['pending_insns'])
        self.state['pending_insns'] = ""
        self.state['pending_count'] = 0

        # Actualize the state.
        self.state['obj_real'] = copy.deepcopy(self.state['obj_pend'])

    def serialize(self):
        """
        Request state from the CB.
        """
        DEBUG = self.GLOBAL_DEBUG and True
        if DEBUG: print "\n[D] serialize"

        self.write(struct.pack("<B", self.MSG_SERIALIZE))
        for obj_id in range(self.NUM_OBJS):
            try:
                expected = "%d %s %s" % (obj_id, self.state['obj_real'][obj_id]['type'], str(self.state['obj_real'][obj_id]['val']))
                self.read(delim='\n', expect=expected)
            except KeyError: continue
            

    def obj_new(self):
        """
        We (may) create an object.  

        INSN appended to outgoing buffer.
        """
        DEBUG = self.GLOBAL_DEBUG and True
        if DEBUG: print "\n[D] obj_new"

        # Check whether we've hit our INSN limit.
        if (self.state['pending_count'] > self.MAX_PENDING_INSN):
            if DEBUG: print "obj_new | exceeded MAX_PENDING_INSN"
            return

        obj_id = randint(0, self.NUM_OBJS-1)
        obj_type = ["NUMBER", "STRING"][randint(0, 1)]
        if "NUMBER" == obj_type:
            if randint(0, 1):
                obj_val = randint(0, 0xFFFFFFFFFFFFFFFF)
            else:
                obj_val = randint(0, 0xFFFFFFFF)
        else:
            obj_val = random_bytes(0, self.MAX_SZ_STRING)
            if DEBUG: print "OBJ_VAL: %s" % obj_val

        cmd = "NEW %d %s %s \n" % (obj_id, obj_type, str(obj_val))
        self.state['pending_insns'] += cmd
        self.state['pending_count'] += 1
        if DEBUG: print "[D] obj_new | generated INSN:\n%s" % cmd[:-1]

        # If we attempt to create a NEW object for an ID that already exists, 
        # the new object is ignored.
        try:
            tmp = self.state['obj_pend'][obj_id]
            if DEBUG:
                print "[D] obj_new | ID %03d already exists, not adding to state" % obj_id
            return    
        except KeyError: pass       

        # Append to pending state, promote if necessary.
        if 0xFFFFFFFF < obj_val: obj_type = "STRING"
        self.state['obj_pend'][obj_id] = {"type" : obj_type, "val" : obj_val}

    def obj_set(self):
        """
        We (may) modify an object.

        INSN appended to outgoing buffer.
        """
        DEBUG = self.GLOBAL_DEBUG and True
        if DEBUG: print "\n[D] obj_set"

        if (self.state['pending_count'] > self.MAX_PENDING_INSN):
            if self.DEBUG:
                print "obj_set | exceeded MAX_PENDING_INSN"
            return

        # 50/50 chance we pick an object that actually exists (if any exist).
        if randint(0, 1): 

            if (0 != len(self.state['obj_pend'].keys())):
                id_exists = True
                obj_id = choice(self.state['obj_pend'].keys())
                obj_type = self.state['obj_pend'][obj_id]['type']

            else:
                id_exists = False
                obj_id = randint(0, self.NUM_OBJS-1)  
                obj_type = ["NUMBER", "STRING"][randint(0, 1)]       

        # Otherwise we (try) to pick a non-existant obj_id (they may all exist).
        else:

            existing = set(self.state['obj_pend'].keys())
            #existing.update(self.state['obj_pend'].keys())

            # Every object exists, pick an existing one.
            if (len(existing) == self.NUM_OBJS):
                id_exists = True
                obj_id = sample(existing, 1)[0]
                obj_type = self.state['obj_pend'][obj_id]['type']
                     
            # Some objects don't exist.  Pick an obj_id that doesn't exist.
            else:
                id_exists = False
                obj_id = sample(set([i for i in xrange(self.NUM_OBJS)]).difference(existing), 1)[0]
                obj_type = ["NUMBER", "STRING"][randint(0, 1)]

        if "NUMBER" == obj_type:
            # We do not cause PROMOTION via the SET command so as to avoid the 
            # vulnerable code path.
            obj_val = randint(0, 0xFFFFFFFF)
        else:
            obj_val = random_bytes(0, self.MAX_SZ_STRING)

        cmd = "SET %d %s \n" % (obj_id, str(obj_val))
        self.state['pending_insns'] += cmd
        self.state['pending_count'] += 1
        if DEBUG: print "[D] obj_set | generated INSN:\n%s" % cmd[:-1]

        # If we attempt to SET an object that doesn't exist, no state change.
        if False == id_exists:
            if DEBUG:
                print "[D] obj_set | %03d does not exist; not modifying state" % obj_id
            return

        # Otherwise, update state.
        if DEBUG: 
            print "id_exists: %s" % id_exists
            print "SET | obj_id = %d; before: %s" % (obj_id, self.state['obj_pend'])
        self.state['obj_pend'][obj_id] = {"type" : obj_type, "val" : obj_val}
        if DEBUG: print "SET | obj_id = %d; after: %s" % (obj_id, self.state['obj_pend'])

    def obj_del(self):
        """
        We (may) delete an object.

        INSN appended to outgoing buffer.
        """
        DEBUG = self.GLOBAL_DEBUG and True
        if DEBUG: print "\n[D] obj_del"

        if (self.state['pending_count'] > self.MAX_PENDING_INSN):
            if self.DEBUG:
                print "obj_del | exceeded MAX_PENDING_INSN"
            return

        existing = set(self.state['obj_pend'].keys())

        # 50/50 chance we pick an object that actually exists (if any exist).
        if randint(0, 1): 

            if (0 != len(existing)):
                id_exists = True
                obj_id = sample(existing, 1)[0]
            else:
                id_exists = False
                obj_id = randint(0, self.NUM_OBJS-1)

        else:
            obj_id = sample(set([i for i in xrange(self.NUM_OBJS)]).difference(existing), 1)[0]

        cmd = "DEL %d \n" % obj_id
        self.state['pending_insns'] += cmd
        self.state['pending_count'] += 1
        if DEBUG: print "[D] obj_del | generated INSN:\n%s" % cmd[:-1]

        # If we attempt to DEL an object that doesn't exist, no state change.
        try:
            del self.state['obj_pend'][obj_id]
        except KeyError: pass
        
    def start(self):
        """
        Initialize state.
        """
        DEBUG = self.GLOBAL_DEBUG and True
        if DEBUG: 
            print "**** NEW RUN ****"
            print "[D] start"

        self.state['obj_real'] = {}
        self.state['obj_pend'] = {}
        self.state['pending_insns'] = ""
        self.state['pending_count'] = 0

    def dispatch(self):
        """
        No-op.  Easier than linking all nodes directly together.
        """
        pass


