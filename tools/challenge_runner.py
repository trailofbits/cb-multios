#!/usr/bin/env python2

import os
import re
import signal
import subprocess as sp
from time import time, sleep
import threading

from common import IS_DARWIN, IS_LINUX, IS_WINDOWS, try_delete

# Path to crash dumps in windows
if IS_WINDOWS:
    # NOTE: These may need to be changed depending on your setup
    DUMP_DIR = os.path.join(os.path.expandvars('%LOCALAPPDATA%'), 'CrashDumps')
    CDB_PATH = 'C:/Program Files (x86)/Windows Kits/10/Debuggers/x64/cdb.exe'


def run(challenges, timeout, seed, logfunc):
    """ Challenge launcher for replay services

    This will setup fds for all challenges according to:
    https://github.com/CyberGrandChallenge/cgc-release-documentation/blob/master/newsletter/ipc.md

    Args:
        challenges (list): List of absolute paths to all challenges to launch
        timeout (int): Maximum time in seconds a challenge is allowed to run for
        seed (str): Hex encoded seed for libcgc random
        logfunc ((str) -> None): Replayer log function used for reporting results

    Returns:
        (list): all processes that were started
    """
    cb_env = {'seed': seed}  # Environment variables for all challenges

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

        # None of the above file descriptors will actually be inherited on Windows
        # Prepare the environment so libcgc can regenerate this setup
        # with the inherited HANDLEs
        if IS_WINDOWS:
            import msvcrt

            # Store the number of pipes that need to be set up
            numpipes = len(challenges) * 2  # Pipe pair for each
            cb_env['PIPE_COUNT'] = str(numpipes)

            # Store the HANDLE for each of the pipes
            for i in xrange(len(challenges) * 2):
                cb_env['PIPE_{}'.format(i)] = str(msvcrt.get_osfhandle(3 + i))  # First pipe is at 3

    # Start all challenges
    # Launch the main binary first
    mainchal, otherchals = challenges[0], challenges[1:]
    procs = [sp.Popen(mainchal, env=cb_env, stdin=sp.PIPE,
                      stdout=sp.PIPE, stderr=sp.PIPE)]

    # Any others should be launched with the same std i/o pipes
    # as the main binary
    if len(otherchals) > 0:
        main = procs[0]
        procs += [sp.Popen(c, env=cb_env, stdin=main.stdin,
                           stdout=main.stdout, stderr=main.stderr) for c in otherchals]

    # Start a watcher to report results when the challenges exit
    watcher = threading.Thread(target=chal_watcher, args=(challenges, procs, timeout, logfunc))
    watcher.setDaemon(True)
    watcher.start()

    return procs, watcher


def chal_watcher(paths, procs, timeout, log):
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
    for path, proc in zip(paths, procs):
        pid, sig = proc.pid, abs(proc.returncode)
        if sig not in [None, 0, signal.SIGTERM]:
            log('[DEBUG] pid: {}, sig: {}'.format(pid, sig))

            # Attempt to get register values
            regs = get_core_dump_regs(path, pid, log)
            if regs is not None:
                # If a core dump was generated, report this as a crash
                # log('Process generated signal (pid: {}, signal: {}) - {}\n'.format(pid, sig, testpath))
                log('Process generated signal (pid: {}, signal: {})'.format(pid, sig))

                # Report the register states
                reg_str = ' '.join(['{}:{}'.format(reg, val) for reg, val in regs.iteritems()])
                log('register states - {}'.format(reg_str))

    # Final cleanup
    clean_cores(paths, procs)


def get_core_dump_regs(path, pid, log):
    """ Read all register values from a core dump
    MacOS:   all core dumps are stored as /cores/core.[pid]
    Linux:   the core dump is stored as a 'core' file in the cwd
    Windows: If the given registry file was used, core dumps are stored in %LOCALAPPDATA%\CrashDumps

    Args:
        path (str): path to the executable that generated the dump
        pid (int): pid of the process that generated the core dump
        log ((str) -> None): logging function used to report information
    Returns:
        (dict): Registers and their values
    """
    # Create a gdb/lldb/cdb command to get regs
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
    elif IS_WINDOWS:
        # Dumps are named "[filename.exe].[pid].dmp"
        dmp_name = '{}.{}.dmp'.format(os.path.basename(path), pid)
        cmd = [
            CDB_PATH,
            '-z', os.path.join(DUMP_DIR, dmp_name),
            '-c', 'q'  # Registers already get printed when the dump is loaded
                       # quit immediately
        ]

    # Read the registers
    dbg_out = '\n'.join(sp.Popen(cmd, stdout=sp.PIPE, stderr=sp.PIPE).communicate())

    # Batch commands return successful even if there was an error loading a file
    # Check for these strings in the output instead
    errs = [
        'No such file or directory',
        "doesn't exist",
        'cannot find the file specified'
    ]

    if any(err in dbg_out for err in errs):
        log('Core dump not found, are they enabled on your system?')
        return

    # Parse out registers/values
    regs = {}
    if IS_WINDOWS:
        for match in re.finditer(r'([a-z]+)=([a-fA-F0-9]+)', dbg_out):
            regs[match.group(1)] = match.group(2)
    else:
        for line in dbg_out.split('\n'):
            # Try to match a register value
            match = re.search(r'([a-z]+)[=\ ]+0x([a-fA-F0-9]+)', line)
            if match is not None:
                regs[match.group(1)] = match.group(2)

    return regs


def clean_cores(paths, procs):
    """ Delete all generated core dumps

    Args:
        paths (list): paths to all challenges that were launched
        procs (list): List of all processes that may have generated core dumps
    """
    if IS_DARWIN:
        map(try_delete, ['/cores/core.{}'.format(p.pid) for p in procs])
    elif IS_LINUX:
        try_delete('core')
    elif IS_WINDOWS:
        for path, proc in zip(paths, procs):
            dmp_name = '{}.{}.dmp'.format(os.path.basename(path), proc.pid)
            try_delete(os.path.join(DUMP_DIR, dmp_name))
