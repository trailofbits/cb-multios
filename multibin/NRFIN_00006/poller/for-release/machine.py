#!/usr/bin/env python
#
# Copyright (C) 2014 
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

# TODO: test error states, e.g. invalid syscalls, invalid arguments, invalid tids

from generator.actions import Actions
from random import choice, randint
import imp
import os
import string
import struct

conf = imp.load_source(
        'conf', 
        os.path.join(
            os.path.dirname(os.path.realpath(__file__)), 
            '..',
            '..',
            'support',
            'config.py')).conf


def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))


def random_hex(a, b):
    return ''.join(choice(string.hexdigits) for _ in range(randint(a, b))) 


def le(msg):
    """
    Puts a length byte at the beginning of the message... in a very inefficient 
    manner.
    """
    return "" + struct.pack('B', len(msg)) + msg


class RedPill(Actions):

    DEBUG = 0
    SZ_PTR = 4

    def queue_append(self, tid):
        try: 
            self.state["queue"].index(tid)
            return False
        except ValueError:
            self.state["queue"].append(tid)
            if self.DEBUG:
                print "[machine.py]: added %d to queue: %s" % (tid, self.state["queue"])
            return True

    def queue_remove(self, tid):
        try:
            self.state["queue"].remove(tid)
            if self.DEBUG:
                print "[machine.py]: removed %d from the queue: %s" % (tid, self.state["queue"])
            return True
        except ValueError:
            return False

    def start(self):
        """
        Intialize state.
        """
        # There are two internal state objects accessible via /proc interface:
        # 1) PROC_LIST_DUMP: the queue - a doubly-linked list
        # 2) PROC_THREAD_STATE: the kernel's record of thread state

        # We don't implement a proper linked list structure because we can't 
        # reason about addresses leaked from the CB.  
        # See discussion in README.md.
        self.state["queue"] = []

        # The kernel is "thread 0", which we shouldn't ever see in a dump
        self.state["threads"] = [ conf["MAJOR_UNKNOWN"] ] * (conf["NUM_THREADS"]+1)

    def proc(self):
        """
        Our main loop.  This function requests a state dump from REDPILL and 
        compares kernel state to expected state.
        """
        # Request queue dump & thread state (in that order)
        syscall = le(struct.pack("BB", 
            conf["MAJOR_PROC"] | conf["MINOR_PROC_LIST_DUMP"],
            conf["MAJOR_PROC"] | conf["MINOR_PROC_THREAD_STATE"]))
        self.write(syscall)

        # Verify queue state
        # The CB first leaks the list struct which consists of 2 pointers.
        # struct list {
        #     struct node *head;
        #     struct node *tail;
        # };
        self.read(length=self.SZ_PTR*2)

        # Next, the CB walks the list and leaks each of the nodes.
        # NOTE: clang uses 4B for the value member.
        # struct node {
        #     unsigned char value;
        #     struct node *next;
        #     struct node *prev;
        # };
        for tid in self.state["queue"]:
            self.read(length=self.SZ_PTR, expect=struct.pack("<L", tid)) # match on the tid
            self.read(length=self.SZ_PTR*2) # bury the next and prev ptrs

        # Verify thread state
        self.read(
            length=conf["NUM_THREADS"] * 4,
            expect=struct.pack(
                "<" + "I" * conf["NUM_THREADS"], 
                *self.state["threads"][1:]
            )
        )

    #### ERROR STATES

    def invalid_syscall_major(self):
        """
        This node issues UNUSED and UNKNOWN syscalls.
        
        These should not permute kernel state and should not consume any futher 
        bytes.

        Processing should be rejected at syscall_dispatch().
        """
        self.write(le(struct.pack("B", 0xA0 + randint(0, 0x3F)))) #  UNUSED: 0xA0 - 0xDF
        self.write(le(struct.pack("B", 0xE0 + randint(0, 0x1F)))) # UNKNOWN: 0xE0 - 0xFF

    def invalid_futex_minor(self):
        """
        This node issues futex() syscalls with invalid MINORs.
        
        These should not permute kernel state and should not consume any further
        bytes.

        Processing should be rejected at the beginning of syscall_futex().
        """
        self.write(le(struct.pack("B",
            conf["MAJOR_FUTEX"] | (randint(5, 7) << conf["IDX_MINOR"]))))

    def invalid_futex_tid(self):
        """
        This node issues valid futex() syscalls with invalid TID arguments.
        
        These call consumes an additional byte for the TID.

        Processing should be rejected in syscall_futex() following MINOR 
        validation.
        """
        self.write(le(struct.pack("BB",
            conf["MAJOR_FUTEX"] | (randint(0, 4) << conf["IDX_MINOR"]), 
            randint(conf["NUM_THREADS"]+1, 255))))

    def invalid_proc_minor(self):
        """
        This node issues proc() syscalls with invalid MINORs.
        
        These should not permute kernel state and should not consume any further
        bytes.

        Processing should be rejected at the beginning of syscall_proc().

        Valid values: 0, 4
        """
        self.write(le(struct.pack("B",
            conf["MAJOR_PROC"] | (randint(2, 7) << conf["IDX_MINOR"]))))

    def invalid_tgkill_minor(self):
        """
        This node issues tgkill() syscalls with invalid MINORs.
        
        These should not permute kernel state and should not consume any further
        bytes.

        Processing should be rejected at the beginning of syscall_tgkill().
        """
        self.write(le(struct.pack("B",
            conf["MAJOR_TGKILL"] | (randint(1, 7) << conf["IDX_MINOR"]))))

    def invalid_tgkill_tid(self):
        """
        This node issues valid tgkill() syscalls with invalid TID arguments.
        
        These call consumes an additional byte for the TID.

        Processing should be rejected in syscall_tgkill() following MINOR 
        validation.

        Attempting to tgkill() and already dead process is done in tgkill node.
        """
        self.write(le(struct.pack("BB",
            conf["MAJOR_TGKILL"], 
            randint(conf["NUM_THREADS"]+1, 255))))

    #### NON-ERROR SYSCALLS

    def futex_wait(self):
        """
        Pick a thread and put it to sleep.
        This should not change states for threads that are already sleeping or 
        are killed.
        """
        tid = randint(1, conf["NUM_THREADS"])

        syscall = le(struct.pack("BB", 
            conf["MAJOR_FUTEX"] | conf["MINOR_FUTEX_WAIT"], tid))
        self.write(syscall)

        # If the thread isn't killed, then it should be added to the queue and 
        # its status updated.
        if conf["MAJOR_TGKILL"] != self.state["threads"][tid]:
            self.queue_append(tid)
            self.state["threads"][tid] = (conf["MAJOR_FUTEX"] | conf["MINOR_FUTEX_WAIT"])

    def futex_wake(self):
        """
        Pick a thread and wake it up.
        This should not change states for threads that are already awake or 
        are killed.
        """
        tid = randint(1, conf["NUM_THREADS"])

        syscall = le(struct.pack("BB", 
            conf["MAJOR_FUTEX"] | conf["MINOR_FUTEX_WAKE"], tid))
        self.write(syscall)

        # If the thread isn't killed, then it should be removed from the queue 
        # and its status updated.
        if conf["MAJOR_TGKILL"] != self.state["threads"][tid]:
            self.queue_remove(tid)
            self.state["threads"][tid] = (conf["MAJOR_FUTEX"] | conf["MINOR_FUTEX_WAKE"])

    def futex_fd(self):
        """
        Like real-world FUTEX_FD, this call does not permute state.
        """
        tid = randint(1, conf["NUM_THREADS"])

        syscall = le(struct.pack("BB", 
            conf["MAJOR_FUTEX"] | conf["MINOR_FUTEX_FD"], tid))
        self.write(syscall)

    def futex_requeue_pi(self):
        """
        Pick a thread and "requeue" it.
        Due to simplification, this doesn't actually move a thread from one 
        queue to another; it just changes the thread's state.
        This does not affect killed threads.
        """
        tid = randint(1, conf["NUM_THREADS"])

        syscall = le(struct.pack("BB", 
            conf["MAJOR_FUTEX"] | conf["MINOR_FUTEX_REQUEUE_PI"], tid))
        self.write(syscall)

        # REQUEUE operations are list-atomic from machine.py's perspective.  
        # They will push() and pop()* before responding to further CRS syscalls.
        # 
        # However, if the TID was already on the list (transition from 
        # FUTEX_WAIT to a REQUEUE state), then that atomic push will fail and 
        # the pop will succeed.  In other words, we also need to do a queue pop 
        # *in the case that the item was already on the queue*.  In other, other 
        # words, we just need to do a queue_remove() - and we don't care if it 
        # succeeds.
        #
        # *Except in the case of triggering the vuln, but we won't be 
        # triggering the vuln in the pollers.
        self.queue_remove(tid)

        if conf["MAJOR_TGKILL"] != self.state["threads"][tid]:
            self.state["threads"][tid] = (conf["MAJOR_FUTEX"] | conf["MINOR_FUTEX_REQUEUE_PI"])

    def futex_cmp_requeue_pi(self):
        """
        Pick a thread and conditionally "requeue" it based on 'cmp' parameter.
        This does not affect killed threads.

        The vulnerability lies in this interface and the 'cmp' logic is 
        considered (somewhat) secret.  This function is present in the 
        for-release directory, so competitors may infer the bitwise NOT 
        relationship between op and the tid, but there's a lot more they'll 
        need to do.
        """
        tid = randint(1, conf["NUM_THREADS"])

        # Pick an op that is _not_ the bitwise NOT of tid (so that we do not 
        # trigger the vulnerable condition)
        tmp = []
        for i in range(0, 256):
            tmp.append(i)
        tmp.remove(~tid & 0xFF)
        op = tmp[randint(0, 254)]

        syscall = le(struct.pack("BBB", 
            conf["MAJOR_FUTEX"] | conf["MINOR_FUTEX_CMP_REQUEUE_PI"], tid, op))
        self.write(syscall)

        self.queue_remove(tid)

        if conf["MAJOR_TGKILL"] != self.state["threads"][tid]:
            self.state["threads"][tid] = (conf["MAJOR_FUTEX"] | conf["MINOR_FUTEX_CMP_REQUEUE_PI"])

    def sendmsg(self):
        """
        Cause the kernel to recurse a chosen number of times.  Intended to 
        emulate the use of sendmsg(), sendmmsg(), recvmsg() and recvmmsg() to 
        consume kernel stack by Towelroot.

        Pollers should not cause the CB to crash, so we will never put the CB 
        in a state with a dangling pointer.  Therefore, this function should be
        safe, irrespective of the number of recursions.
        """
        syscall = le(struct.pack("BBB", 
            conf["MAJOR_SENDMSG"], randint(0, 255), randint(0, 255)))
        self.write(syscall)

    def tgkill(self):
        """
        Pick a thread and kill it.

        Killed threads should cause the CB to _terminate(), thereby failing to 
        respond to future ACK expecations, meaning their state should not 
        permute further... but we can still try to kill them more times.

        The TGKILL interface provides a means to cause an exit code in [0, 7].
        Unsure whether CBs that _terminate() with nonzero exit statuses are 
        considered failures by the framework; we'll just specify 0 here.
        """
        tid = randint(1, conf["NUM_THREADS"])

        syscall = le(struct.pack("BB", conf["MAJOR_TGKILL"], tid))
        self.write(syscall)

        # If the thread was on the queue, it's not anymore (we don't care about 
        # return value).
        self.queue_remove(tid)

        self.state["threads"][tid] = conf["MAJOR_TGKILL"]

        # If we're killing the last thread, the kernel will shut down and so 
        # should we.
        all_dead = True
        for tid in range(1, conf["NUM_THREADS"]):
            if conf["MAJOR_TGKILL"] != self.state["threads"][tid]:
                all_dead = False
        if all_dead:
            return -1

    def finish(self):
        """
        Kill all living threads and then shut down the kernel.

        Technically we can kill all threads, irrespective of whether they're 
        already dead, but that would be overkill.
        """
        if self.DEBUG:
            print "im doing a shutdown"
        for tid in range(1, conf["NUM_THREADS"]+1):
            if conf["MAJOR_TGKILL"] != self.state["threads"][tid]:
                syscall = le(struct.pack("BB", conf["MAJOR_TGKILL"], tid))
                self.write(syscall)

        # All threads should be dead, now we "shutdown" the kernel.
        self.write(struct.pack("B", 0))

        # We return -1 because we expect the connection to terminate.
        return -1

