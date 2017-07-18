#!/usr/bin/env python

"""
CB POV / Poll communication verification tool

Copyright (C) 2014 - Brian Caswell <bmc@lungetech.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

This tool allows for deterministic communication to a CGC Challenge Binary
using a Challenge Binary as input.

1 - http://testanything.org/
"""

import subprocess as sp
import multiprocessing as mp
import random
import argparse
import os
import signal
import struct
import threading

from common import IS_WINDOWS, Timeout, TimeoutError
import challenge_runner


def get_fd(fileobj):
    """ Gets the file descriptor for a given fileobject

    On Unix systems this returns the result of fileno()

    On Windows systems, fileno() returns a HANDLE. This will open
    that HANDLE and return a CRT file descriptor
    """
    if IS_WINDOWS:
        import msvcrt
        return msvcrt.open_osfhandle(fileobj.fileno(), os.O_TEXT)
    return fileobj.fileno()


class TestFailure(Exception):
    """ Exception to be used by Throw(), to allow catching of test failures """
    pass


class Throw(object):
    """Throw - Perform the interactions with a CB

    This class implements the basic methods to interact with a CB, verifying
    the interaction works as expected.

    Usage:
        a = Throw((source_ip, source_port), (target_ip, target_port), POV,
                  timeout, should_debug)
        a.run()

    Attributes:
        cb_paths: List of paths to all cb executables

        count: Number of actions performed

        debug: Is debugging enabled

        failed: Number of actions that did not work as expected

        passed: Number of actions that did worked as expected

        pov: POV, as defined by POV()

        timeout: connection timeout
    """
    def __init__(self, cb_paths, pov, timeout, debug, pov_seed):
        self.cb_paths = cb_paths
        self.pov = pov
        self.debug = debug
        self.timeout = timeout
        self.pov_seed = pov_seed

    def log(self, data):
        print "# %s" % data

    def count_bits_set(self, value):
        count = 0
        while value:
            value &= value - 1
            count += 1
        return count

    def read_all(self, fd, data_len):
        data = ''
        while len(data) < data_len:
            read = os.read(fd, data_len - len(data))
            assert len(read)
            data += read
        return data

    def pov_negotiate(self, pipefd):
        MIN_BITS = 0

        if self.debug:
            self.log("negotiating")

        data = self.read_all(pipefd, 4)
        pov_type = struct.unpack('<L', data)[0]
        assert pov_type in [1, 2], 'invalid pov type'

        self.log("negotiation type: %d" % pov_type)

        if pov_type == 1:
            data = self.read_all(pipefd, 12)
            ipmask, regmask, regnum = struct.unpack('<LLL', data)
            accept = True

            if self.count_bits_set(ipmask) < MIN_BITS:
                self.log('not enough bits in IP mask')
                accept = False

            if self.count_bits_set(regmask) < MIN_BITS:
                self.log('not enough bits in REG mask')
                accept = False

            if regnum > 7:
                self.log('invalid GPR')
                accept = False

            if accept:
                ip = random.randint(0, 0xFFFFFFFF) & ipmask
                reg = random.randint(0, 0xFFFFFFFF) & regmask

                self.log('type 1 masks: %08x %08x' % (ipmask, regmask))
                self.log('type 1 pov: %08x %08x %d' % (ip, reg, regnum))

                pov_values = struct.pack('<LL', ip, reg)
                os.write(pipefd, pov_values)

        if pov_type == 2:
            PAGE_ADDR = 0x4347C000
            PAGE_LENGTH = 0x1000
            PAGE_BYTES = 4

            self.log("sending page location: %d, %d, %d" % (PAGE_ADDR, PAGE_LENGTH, PAGE_BYTES))
            pov_location = struct.pack('<LLL', PAGE_ADDR, PAGE_LENGTH, PAGE_BYTES)
            os.write(pipefd, pov_location)

            if self.debug:
                self.log("getting secret")
            data = self.read_all(pipefd, 4)
            self.log("secret value: %s" % data.encode('hex'))

        if self.debug:
            self.log('done')

    def _launch_pov_unix(self, mainproc, pipe):
        # NOTE: This is running a forked process, free to clobber fds
        # This is mostly unchanged from the original source
        if self.timeout > 0:
            signal.alarm(self.timeout)

        # Setup fds for communication
        os.dup2(mainproc.stdout.fileno(), 0)
        os.dup2(mainproc.stdin.fileno(), 1)
        os.dup2(pipe.fileno(), 3)

        if not self.debug:
            null = os.open('/dev/null', 0)
            os.dup2(null, 2)
            os.close(null)

        args = [self.pov]
        if self.pov_seed:
            args.append('seed=%s' % self.pov_seed)

        # Launch the POV
        os.execv(self.pov, args)
        exit(-1)

    def _launch_pov_win(self, mainproc, pipe):
        import _subprocess as _sp

        cmd = [self.pov]
        if self.pov_seed:
            cmd.append('seed=%s' % self.pov_seed)

        # The pipe HANDLE isn't inheritable, make a duplicate that is
        cur_proc = _sp.GetCurrentProcess()
        inh_pipe = _sp.DuplicateHandle(cur_proc,       # Source process
                                       pipe.fileno(),  # HANDLE
                                       cur_proc,       # Target process
                                       0,              # Desired access
                                       1,              # Inheritable
                                       _sp.DUPLICATE_SAME_ACCESS)  # Options

        # Run the POV
        pov_proc = sp.Popen(cmd,
                            # Passing the HANDLE value here through an environment variable
                            # libpov will grab this and open it in fd 3
                            # see: include/libpov/pov.c - DLLMain
                            env={'POV_FD': str(int(inh_pipe))},

                            # stdin/out connect to the cb directly
                            stdin=mainproc.stdout,
                            stdout=mainproc.stdin)
        pov_proc.wait()

    def launch_pov(self, mainproc, pipe):
        if IS_WINDOWS:
            # Can't pass process/pipe handles to another process here, using a thread
            pov_runner = threading.Thread(target=self._launch_pov_win, args=(mainproc, pipe))
            pov_runner.setDaemon(True)
        else:
            # Fork on unix systems so we can dup fds where we want them
            pov_runner = mp.Process(target=self._launch_pov_unix, args=(mainproc, pipe))

        pov_runner.start()
        return pov_runner

    def gen_seed(self):
        """ Prepare the seed that will be used in the replay """
        seed = os.urandom(48)
        self.log("using seed: %s" % seed.encode('hex'))
        return seed.encode('hex')

    def run(self):
        """ Iteratively execute each of the actions within the POV

        Args:
            None

        Returns:
            None

        Raises:
            AssertionError: if a POV action is not in the pre-defined methods
        """
        self.log('%s' % (self.pov))

        # Get the seed for the tests
        seed = self.gen_seed()

        # Launch the challenges
        self.procs, watcher = challenge_runner.run(self.cb_paths, self.timeout, seed, self.log)

        # Setup and run the POV
        pov_pipes = mp.Pipe(duplex=True)
        pov_runner = self.launch_pov(self.procs[0], pov_pipes[1])

        if self.timeout > 0:
            try:
                with Timeout(self.timeout + 5):
                    self.pov_negotiate(get_fd(pov_pipes[0]))
            except TimeoutError:
                self.log('pov negotiation timed out')
        else:
            self.pov_negotiate()

        if self.debug:
            self.log('waiting')

        # Wait for the POV to finish and results to get logged
        pov_runner.join()
        watcher.join()

        self.log('END REPLAY')
        return self.procs[0].returncode


def run_pov(cbs, pov, timeout, debug, pov_seed):
    """
    Parse and Throw a POV/Poll

    Arguments:
        cbs: List of paths to all cb executables
        pov: filename of the POV
        timeout: How long the POV communication is allowed to take
        debug: Flag to enable debug logs
        negotate: Should PRNG be negotiated with the CB
        pov_seed: the POV seed to use

    Returns:
        The number of passed tests
        The number of failed tests
        A list containing the logs

    Raises:
        Exception if parsing the POV times out
    """

    thrower = Throw(cbs, pov, timeout, debug, pov_seed)
    return thrower.run()


def main():
    """ Parse and Throw the POVs """
    parser = argparse.ArgumentParser(description='Send CB based CGC Polls and POVs')
    required = parser.add_argument_group(title='required arguments')
    required.add_argument('--cbs', nargs='+', required=True,
                          help='List of challenge binaries to run on the server')
    required.add_argument('files', metavar='pov', type=str, nargs='+',
                          help='pov file')
    parser.add_argument('--timeout', required=False, type=int, default=15,
                        help='Connect timeout')
    parser.add_argument('--debug', required=False, action='store_true',
                        default=False, help='Enable debugging output')
    parser.add_argument('--negotiate', required=False, action='store_true',
                        default=False, help='The CB seed should be negotiated')
    parser.add_argument('--pov_seed', required=False, type=str,
                        help='Specify the POV Seed')

    args = parser.parse_args()

    assert len(args.files)
    for filename in args.files:
        assert os.path.isfile(filename), "pov must be a file: %s" % repr(filename)

    for pov in args.files:
        status = run_pov(args.cbs, pov, args.timeout,
                         args.debug, args.pov_seed)
    return status != 0


if __name__ == "__main__":
    exit(main())
