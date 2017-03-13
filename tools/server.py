#!/usr/bin/env python2

import argparse
import os
import subprocess
import sys
from threading import Thread
from SocketServer import StreamRequestHandler, ThreadingTCPServer

from common import *


class ChallengeHandler(StreamRequestHandler):
    challenges = []
    chal_timeout = 2
    use_signals = False
    dup_out = 1

    def handle(self):
        # Prepare the challenge runner
        runner_cmd = [sys.executable, RUNNER, '-t', str(self.chal_timeout), str(self.dup_out)] + self.challenges
        if self.use_signals:
            runner_cmd.append('--use-signals')

        # Start the challenge runner
        sock = self.connection
        subprocess.Popen(runner_cmd, stdin=sock, stdout=sock, stderr=sock).wait()


class LimitedConnectionServer(ThreadingTCPServer):
    def __init__(self, server_address, handler, max_connections):
        self.max_connections = max_connections
        ThreadingTCPServer.__init__(self, server_address, handler)

    def process_request(self, request, client_address):
        # Only the parent (server) will return from this
        ThreadingTCPServer.process_request(self, request, client_address)

        # Check if we need to shutdown now
        self.max_connections -= 1
        stdout_flush('Client connected! {} remaining\n'.format(self.max_connections))
        if self.max_connections <= 0:
            stdout_flush('No more connections allowed, shutting down!\n')
            Thread(target=self.shutdown).start()


def launch_ajl(args):
    ajl_cmd = [
        AJL,
        '/port:{}'.format(args.port),
        '/nojail', '/timeout:20',
        '"{}"'.format(' '.join([
            sys.executable,
            RUNNER,
            '-t', str(ChallengeHandler.chal_timeout),
            str(ChallengeHandler.dup_out)
        ] + ChallengeHandler.challenges))
    ]
    subprocess.Popen(' '.join(ajl_cmd)).wait()  # TODO: let's not wait there...


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

    # Duplicate stdout for children to report back to
    ChallengeHandler.dup_out = os.dup(1)
    if IS_WINDOWS:
        # Get the HANDLE of the new stdout
        ChallengeHandler.dup_out = win32file._get_osfhandle(ChallengeHandler.dup_out)

    # Start the challenge server
    if IS_WINDOWS:
        launch_ajl(args)
    else:
        ThreadingTCPServer.allow_reuse_address = True
        if args.max_connections > 0:
            srv = LimitedConnectionServer(('localhost', args.port), ChallengeHandler, args.max_connections)
        else:
            srv = ThreadingTCPServer(('localhost', args.port), ChallengeHandler)
        try:
            stdout_flush('Starting server at localhost:{}\n'.format(args.port))
            srv.serve_forever()
        except KeyboardInterrupt:
            pass
        finally:
            srv.server_close()


if __name__ == '__main__':
    exit(main())
