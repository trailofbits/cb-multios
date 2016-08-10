#!/usr/bin/env python

import argparse
import os
import subprocess
import sys
from SocketServer import ForkingTCPServer, StreamRequestHandler


class ChallengeHandler(StreamRequestHandler):
    challenges = []

    def handle(self):
        # Basic running one challenge as a start
        p = subprocess.Popen(self.challenges[0], stdin=self.wfile, stdout=self.rfile)
        p.communicate()


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
        srv.serve_forever()
    except KeyboardInterrupt:
        pass
    srv.server_close()


if __name__ == '__main__':
    exit(main())
