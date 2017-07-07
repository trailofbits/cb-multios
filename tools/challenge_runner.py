#!/usr/bin/env python2

import os
import re
import signal
import subprocess as sp
from time import time, sleep
import threading

from common import *


def run(challenges, timeout, seed, logfunc):
    """ Challenge launcher for replay services

    This will setup fds for all challenges according to:
    https://github.com/CyberGrandChallenge/cgc-release-documentation/blob/master/newsletter/ipc.md

    Args:
        challenges (list): List of absolute paths to all challenges to launcher
        timeout (int): Maximum time in seconds a challenge is allowed to run for

    Returns:
        (list): all processes that were started
    """
    # This is the first fd after all of the challenges
    last_fd = 2 * len(challenges) + 3

    # Create all challenge fds
    if len(challenges) > 1:
        # Close fds where the pipes will be placed
        os.closerange(3, last_fd)

        new_fd = 3  # stderr + 1
        for i in xrange(len(challenges)):
            # Create a pipe for every running binary
            rpipe, wpipe = os.pipe()

            # The write end of the pipe needs to be at the lower fd, so it *may* get dup'd over the read end
            # Preemptively dup the read fd here to avoid the issue
            rpipe_tmp = os.dup(rpipe)
            pipe_fds = [wpipe, rpipe_tmp]

            # Duplicate the pipe ends to the correct fds if needed
            for fd in pipe_fds:
                if fd != new_fd:
                    os.dup2(fd, new_fd)
                new_fd += 1

            # Done with the temporary dup
            os.close(rpipe_tmp)

    # Start all challenges
    logfunc(repr(challenges))
    cb_env = {'seed': seed}
    procs = [sp.Popen(c, env=cb_env, stdin=sp.PIPE,
                      stdout=sp.PIPE, stderr=sp.PIPE) for c in challenges]

    # Start a watcher to report results when the challenges exit
    watcher = threading.Thread(target=chal_watcher, args=(procs, timeout, logfunc))
    watcher.setDaemon(True)
    watcher.start()

    return procs, watcher


def chal_watcher(procs, timeout, log):
    # Continue until any of the processes die

    # Wait until any process exits
    start = time()
    while time() - start < timeout \
            and all(proc.poll() is None for proc in procs):
        sleep(0.1)

    # Give the others a chance to exit
    while time() - start < timeout \
            and any(proc.poll() is None for proc in procs):
        sleep(0.1)

    # Kill any remaining processes
    for proc in procs:
        if proc.poll() is None:
            proc.terminate()
            proc.wait()

    # Close all of the ipc pipes
    if len(procs) > 1:
        last_fd = 2 * len(procs) + 3
        os.closerange(3, last_fd)

    # If any of the processes crashed, print out crash info
    for proc in procs:
        pid, sig = proc.pid, abs(proc.returncode)
        if sig not in [None, 0, signal.SIGTERM]:
            log('[DEBUG] pid: {}, sig: {}\n'.format(pid, sig))

            # Attempt to get register values
            regs = get_core_dump_regs(pid, log)
            if regs is not None:
                # If a core dump was generated, report this as a crash
                # log('Process generated signal (pid: {}, signal: {}) - {}\n'.format(pid, sig, testpath))
                log('Process generated signal (pid: {}, signal: {})\n'.format(pid, sig))

                # Report the register states
                reg_str = ' '.join(['{}:{}'.format(reg, val) for reg, val in regs.iteritems()])
                log('register states - {}\n'.format(reg_str))

    # Final cleanup
    clean_cores(procs)


def get_core_dump_regs(pid, log):
    """ Read all register values from a core dump
    On OS X, all core dumps are stored as /cores/core.[pid]
    On Linux, the core dump is stored as a 'core' file in the cwd

    Args:
        pid (int): pid of the process that generated the core dump
    Returns:
        (dict): Registers and their values
    """
    # Create a gdb/lldb command to get regs
    if IS_DARWIN:
        cmd = [
            'lldb',
            '--core', '/cores/core.{}'.format(pid),
            '--batch', '--one-line', 'register read'
        ]
    elif IS_LINUX:
        cmd = [
            'gdb',
            '--core', 'core',
            '--batch', '-ex', 'info registers'
        ]
    else:  # TODO: Windows registers
        return

    # Read the registers
    dbg_out = '\n'.join(sp.Popen(cmd, stdout=sp.PIPE, stderr=sp.PIPE).communicate())
    if 'No such file or directory' in dbg_out or "doesn't exist" in dbg_out:
        log('Core dump not found, are they enabled on your system?\n')
        return

    # Parse out registers/values
    regs = {}
    for line in dbg_out.split('\n'):
        # Try to match a register value
        match = re.search(r'([a-z]+)[=\ ]+0x([a-fA-F0-9]+)', line)
        if match is not None:
            regs[match.group(1)] = match.group(2)

    return regs


def clean_cores(procs):
    """ Delete all generated core dumps

    Args:
        procs (list): List of all processes that may have generated core dumps
    """
    if IS_DARWIN:
        map(try_delete, ['/cores/core.{}'.format(p.pid) for p in procs])
    elif IS_LINUX:
        try_delete('core')
    elif IS_WINDOWS:
        # TODO: any cleanup needed
        pass
