#!/usr/bin/env python

import argparse
import os
import subprocess
import sys
import time
from SocketServer import ForkingTCPServer, StreamRequestHandler
import signal

class TimeoutError(Exception):
    pass

def alarm_handler(signum, frame):
    raise TimeoutError()


class ChallengeHandler(StreamRequestHandler):
    challenges = []

    def handle(self):
        # Setup fds for all challenges according to:
        # https://github.com/CyberGrandChallenge/cgc-release-documentation/blob/master/newsletter/ipc.md

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
        if len(self.challenges) > 1:
            new_fd = 3  # stderr + 1
            for i in xrange(len(self.challenges)):
                # Create a new pipe for a challenge
                socks = os.pipe()[::-1]  # (write_fd, read_fd)

                # Duplicate the ends of the pipe to the correct fds
                for s in socks:
                    if s != new_fd:
                        os.dup2(s, new_fd)
                    new_fd += 1

        # Start all challenges
        procs = map(subprocess.Popen, self.challenges)

        # Continue until any of the processes die
	signal.signal(signal.SIGALRM, alarm_handler)
	signal.alarm(2)
	try:
            while all([proc.poll() is None for proc in procs]):
                time.sleep(0.1)
        except TimeoutError:
            pass

        # Kill the rest
        for proc in procs:
            if proc.poll() is None:
                proc.terminate()

        # Restore stdin/out
        os.dup2(saved[0], 0)
        os.dup2(saved[1], 1)


def main():
    parser = argparse.ArgumentParser()

    parser.add_argument('-p', '--port', required=True, type=int,
                        help='TCP port used for incoming connections')
    parser.add_argument('-d', '--directory', required=True,
                        help='Directory containing the challenge binaries')
    parser.add_argument('challenge_binaries', nargs='+',
                        help='List of challenge binaries to run on the server')

    args = parser.parse_args(sys.argv[1:])

    # Generate the full paths to all binaries in the request handler
    cdir = os.path.abspath(args.directory)
    for chal in args.challenge_binaries:
        ChallengeHandler.challenges.append(os.path.join(cdir, chal))

    # Start the challenge server
    srv = ForkingTCPServer(('localhost', args.port), ChallengeHandler)
    try:
        print('Starting server at localhost:{}'.format(args.port))
        srv.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        srv.server_close()


if __name__ == '__main__':
    exit(main())
