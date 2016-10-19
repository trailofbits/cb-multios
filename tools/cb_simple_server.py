#!/usr/bin/env python

import argparse
import os
import re
import socket
import subprocess
import sys
import time
import thread
from SocketServer import ForkingTCPServer, StreamRequestHandler
import signal

# For OS specific tasks
IS_DARWIN = sys.platform == 'darwin'
IS_LINUX = 'linux' in sys.platform


class TimeoutError(Exception):
    pass


def alarm_handler(signum, frame):
    raise TimeoutError()


def stdout_flush(s):
    sys.stdout.write(s)
    sys.stdout.flush()


def try_delete(path):
    try:
        os.remove(path)
    except OSError:
        pass


class ChallengeHandler(StreamRequestHandler):
    challenges = []
    chal_timeout = 2
    use_signals = False

    def handle(self):
        # Setup fds for all challenges according to:
        # https://github.com/CyberGrandChallenge/cgc-release-documentation/blob/master/newsletter/ipc.md

        # Get the test path for logging purposes
        testpath = self.rfile.readline()

        # Get the seed from cb-replay
        # Encoded seed sent as:
        # [record count (1)] [record type (1)] [record size (48)] [seed]
        seed = self.rfile.read(60)[12:].encode('hex')

        # Get the pid of cb-replay
        # This will be used to send a signal when challenges are ready
        if self.use_signals:
            replay_pid = self.rfile.readline()
            try:
                replay_pid = int(replay_pid)
            except ValueError:
                sys.stderr.write("Invalid cb-replay pid: {}".format(replay_pid))
                return

        # This is the first fd after all of the challenges
        last_fd = 2 * len(self.challenges) + 3

        # Make sure the socket fds are out of the way
        req_socks = [last_fd + 2, last_fd + 3]
        os.dup2(self.wfile.fileno(), req_socks[0])
        os.dup2(self.rfile.fileno(), req_socks[1])

        # Duplicate stdin/out to fds after the challenge fds so we can restore them later
        saved = [last_fd, last_fd + 1]
        os.dup2(0, saved[0])
        os.dup2(1, saved[1])

        # Redirect stdin/out to the socket
        os.dup2(req_socks[0], 0)
        os.dup2(req_socks[1], 1)

        # Create all challenge fds
        socks = []
        if len(self.challenges) > 1:
            # Close fds where the sockets will be placed
            os.closerange(3, last_fd)

            new_fd = 3  # stderr + 1
            for i in xrange(len(self.challenges)):
                # Create a socketpair for every running binary
                socks += socket.socketpair(socket.AF_UNIX, socket.SOCK_STREAM, socket.AF_UNSPEC)
                sock_fds = [sock.fileno() for sock in socks[-2:]]

                # Duplicate the sockets to the correct fds if needed
                for fd in sock_fds:
                    if fd != new_fd:
                        os.dup2(fd, new_fd)
                    new_fd += 1

        # Start all challenges
        cb_env = {'seed': seed}
        procs = [subprocess.Popen(c, env=cb_env) for c in self.challenges]

        # Send a signal to cb-replay to tell it the challenges are ready
        # NOTE: cb-replay has been modified to wait for this
        # This forces cb-replay to wait until all binaries are running,
        # avoiding the race condition where the replay starts too early
        # Using SIGILL here because SIGUSR1 is invalid on Windows
        if self.use_signals:
            os.kill(replay_pid, signal.SIGILL)

        # Continue until any of the processes die
        # TODO: SIGALRM is invalid on Windows
        signal.signal(signal.SIGALRM, alarm_handler)
        signal.alarm(self.chal_timeout)
        try:
            while all([proc.poll() is None for proc in procs]):
                time.sleep(0.1)
        except TimeoutError:
            pass

        # Kill the rest
        for proc in procs:
            if proc.poll() is None:
                proc.terminate()

        # Close all sockpairs
        map(lambda s: s.close(), socks)

        # Try to close any remaining duplicated sock fds
        os.closerange(3, last_fd)

        # Restore stdin/out
        os.dup2(saved[0], 0)
        os.dup2(saved[1], 1)

        # If any of the processes crashed, print out crash info
        for proc in procs:
            if proc.returncode not in [None, 0, signal.SIGTERM]:
                # Print the return code
                pid, sig = proc.pid, abs(proc.returncode)
                stdout_flush('Process generated signal (pid: {}, signal: {}) - {}\n'.format(pid, sig, testpath))

                # Print register values
                regs = self.get_core_dump_regs(pid)
                if regs is not None:
                    reg_str = ' '.join(['{}:{}'.format(reg, val) for reg, val in regs.iteritems()])
                    stdout_flush('register states - {}\n'.format(reg_str))

        # Final cleanup
        self.clean_cores(procs)

    def get_core_dump_regs(self, pid):
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

        # Read the registers
        dbg_out = '\n'.join(subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE).communicate())
        if 'No such file or directory' in dbg_out or "doesn't exist" in dbg_out:
            stdout_flush('Core dump not found, are they enabled on your system?\n')
            return

        # Parse out registers/values
        regs = {}
        for line in dbg_out.split('\n'):
            # Try to match a register value
            match = re.search(r'([a-z]+)[=\ ]+0x([a-fA-F0-9]+)', line)
            if match is not None:
                regs[match.group(1)] = match.group(2)

        return regs

    def clean_cores(self, procs):
        """ Delete all generated core dumps

        Args:
            procs (list): List of all processes that may have generated core dumps
        """
        if IS_DARWIN:
            map(try_delete, ['/cores/core.{}'.format(p.pid) for p in procs])
        elif IS_LINUX:
            try_delete('core')


class LimitedForkServer(ForkingTCPServer):
    def __init__(self, server_address, handler, max_connections):
        self.max_connections = max_connections
        ForkingTCPServer.__init__(self, server_address, handler)

    def process_request(self, request, client_address):
        # Only the parent (server) will return from this
        ForkingTCPServer.process_request(self, request, client_address)

        # Check if we need to shutdown now
        self.max_connections -= 1
        stdout_flush('Client connected! {} remaining\n'.format(self.max_connections))
        if self.max_connections <= 0:
            stdout_flush('No more connections allowed, shutting down!\n')
            thread.start_new_thread(self.shutdown, ())


def main():
    parser = argparse.ArgumentParser()

    parser.add_argument('-p', '--port', required=True, type=int,
                        help='TCP port used for incoming connections')
    parser.add_argument('-d', '--directory', required=True,
                        help='Directory containing the challenge binaries')
    parser.add_argument('-m', '--max-connections', required=False,
                        type=int, default=0,
                        help='The number of connections this server will handle before shutting down')
    parser.add_argument('-t', '--timeout', type=int,
                        help='The time in seconds that challenges are allowed to run before quitting'
                        ' (default is {} seconds)'.format(ChallengeHandler.chal_timeout))
    parser.add_argument('--use-signals', action='store_true',
                        help='Use signals to coordinate starting the challenges with another process')
    parser.add_argument('challenge_binaries', nargs='+',
                        help='List of challenge binaries to run on the server')

    args = parser.parse_args(sys.argv[1:])

    # Generate the full paths to all binaries in the request handler
    cdir = os.path.abspath(args.directory)
    for chal in args.challenge_binaries:
        ChallengeHandler.challenges.append(os.path.join(cdir, chal))

    # Set challenge timeout
    if args.timeout and args.timeout > 0:
        ChallengeHandler.chal_timeout = args.timeout

    # Set how the handler will start challenges
    ChallengeHandler.use_signals = args.use_signals

    # Start the challenge server
    ForkingTCPServer.allow_reuse_address = True
    if args.max_connections > 0:
        srv = LimitedForkServer(('localhost', args.port), ChallengeHandler, args.max_connections)
    else:
        srv = ForkingTCPServer(('localhost', args.port), ChallengeHandler)

    try:
        stdout_flush('Starting server at localhost:{}\n'.format(args.port))
        srv.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        srv.server_close()


if __name__ == '__main__':
    exit(main())
