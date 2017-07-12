#!/usr/bin/env python

"""
CB Testing tool

Copyright (C) 2014,2015 - Brian Caswell <bmc@lungetech.com>

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

This tool allows verification of POV and POLLs with a CGC challenge binary
using 'cb-replay', 'tcpdump', and 'cb-server'.
"""

import re
import argparse
import platform
import glob
import logging
import os
import signal
import subprocess
import sys
import time
import thread
import threading
import Queue
import ansi_x931_aes128

from common import IS_WINDOWS
if not IS_WINDOWS:
    import resource


def add_ext(s):
    return '{}{}'.format(s, '.exe' if IS_WINDOWS else '')


class Background(object):
    """ Run an external command in a background thread

    Usage:
        a = Background(['echo', 'hello'])
        a.wait()

    Attributes:
        cmd: The command that should be run (as a list)
        process: The subprocess handle
        threads:  A list of threads being maintained, one for stderr, one for
            stdout.
    """

    def __init__(self, cmd, command_name=None):
        logging.debug('launching %s', ' '.join(cmd))
        if command_name is None:
            self.cmd = cmd[0]
        else:
            self.cmd = command_name
        # print("RUNNING : " + cmd[0])
        self.process = subprocess.Popen(cmd, stdout=subprocess.PIPE,
                                        stderr=subprocess.PIPE)
        self.threads = []
        self.log_queue = Queue.Queue()
        self.log_handle(self.process.stdout, False)
        self.log_handle(self.process.stderr, True)

    def log_handle(self, filehandle, should_repr):
        """ Create a thread to log all of the output from the provided file
        handle.

        Arguments:
            filehandle: File handle to monitor
            should_repr: Should the output be passed through 'repr' before
                writing to the log.  (Useful for untrusted input)

        Returns:
            None

        Raises:
            None
        """

        def log_background(log, should_repr, queue):
            """ Thread callback to log the output from the background process

            Arguments:
                log: File handle to monitor
                should_repr: should the output be passed through repr before
                    writing to the log.  (Useful for untrusted input)
            """
            try:
                for line in iter(log.readline, ''):
                    queue.put(line)
                    if should_repr:
                        logging.warning('%s: %s', self.cmd, repr(line[:-1]))
                    else:
                        logging.warning('%s: %s', self.cmd, line[:-1])
                log.close()
                queue.put(None)
            except KeyboardInterrupt:
                thread.interrupt_main()

        my_thread = threading.Thread(target=log_background,
                                     args=(filehandle, should_repr, self.log_queue))
        my_thread.daemon = True
        my_thread.start()
        self.threads.append(my_thread)

    def terminate(self):
        """ Terminate the running process and associated threads.

        Arguments:
            None

        Returns:
            None

        Raises:
            None
        """
        logging.debug('terminating %s', self.cmd)
        try:
            self.process.terminate()
        except OSError:
            pass
        for my_thread in self.threads:
            my_thread.join()

    def wait(self):
        """ Wait for the process to exit.

        Arguments:
            None

        Returns:
            Return code from the process

        Raises:
            None
        """
        logging.debug('waiting for %s to terminate (pid: %s)', self.cmd, self.process.pid)
        wval = self.process.wait()
        result = []

        waiting = 2
        while waiting > 0:
            item = self.log_queue.get()
            if item is None:
                waiting -= 1
                continue
            result.append(item)
            self.log_queue.task_done()

        logging.debug('process returned %s', repr(wval))
        return wval, ''.join(result)


class Runner(object):
    """ Run an external command in a background thread

    Usage:
        a = Runner(port, cb_list, xml_list, pcap, wrapper, directory,
                   should_core, failure_ok, should_debug, timeout, log_fh,
                   cb_seed, cb_seed_skip, max_send, concurrent,
                   negotiate_seed, pov_seed, cb_no_attach)
        a.run()

    Attributes:
        port: TCP port the CB should run on.
        cb_list: Set of CBs being tested
        xml_list: List of XML files to test the CB with
        pcap: Path the pcap file should be written to
        wrapper: The wrapper executable to run the CBs through
        directory: The directory containing the CBs
        should_core: Is the CB expected to core with the provided XML
        failure_ok: Should failures stop the testing process
        should_debug: Should debugging be enabled on child processes
        timeout: Timeout for child processes
        log_fh: The file handle for the log
        ip_address: IP Address of the CB server
        cb_seed: PRNG for CBs
        cb_seed_skip: Amount to advance the PRNG for CBs
        max_send: Maximum data to send per request from the poll
        concurrent: Number of polls/povs to send concurrently
        negotiate_seed: Should the CB seed be negotiated from cb-replay
        pov_seed: the PRNG seed for POVs
        cb_no_attach: Should the CB not be attached within cb-server
    """
    pov_signals = [signal.SIGSEGV, signal.SIGILL]
    if not IS_WINDOWS:
        pov_signals.append(signal.SIGBUS)

    def __init__(self, port, cb_list, xml_list, pcap, wrapper, directory,
                 should_core, failure_ok, should_debug, timeout, log_fh,
                 cb_seed, cb_seed_skip, max_send, concurrent, negotiate_seed,
                 pov_seed, cb_no_attach):
        self.port = port
        self.cb_list = cb_list
        self.cb_no_attach = cb_no_attach
        self.xml_list = xml_list
        self.pcap = pcap
        self.wrapper = wrapper
        self.concurrent = concurrent
        self.directory = directory
        self.should_core = should_core
        self.should_debug = should_debug
        self.failure_ok = failure_ok
        self.timeout = timeout
        self.processes = []
        self.log_fh = log_fh
        self.cb_seed = cb_seed
        self.cb_seed_skip = cb_seed_skip
        self.max_send = max_send
        self.negotiate_seed = negotiate_seed
        self.pov_seed = pov_seed

        if not IS_WINDOWS:
            resource.setrlimit(resource.RLIMIT_CORE, (resource.RLIM_INFINITY,
                                                      resource.RLIM_INFINITY))

    def background(self, cmd, cmd_name=None):
        """ Run a command in the background, and verify it started

        Arguments:
            cmd: Command to be run
            cmd_name: Name of the command to show up in the logs

        Returns:
            None

        Raises:
            Exception: if the process didn't get created effectively
        """
        process = Background(cmd, cmd_name)
        self.processes.append(process)
        if process.process.poll():
            raise Exception('background process failed: %s' % (' '.join(cmd)))
        return process

    def launch(self, cmd):
        """ Run a command in the foreground, logging the stderr and stdout

        Arguments:
            cmd: Command to be run

        Returns:
            None

        Raises:
            None
        """
        logging.debug('launching %s', ' '.join(cmd))
        process = subprocess.Popen(cmd, stdout=subprocess.PIPE,
                                   stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        if len(stderr):
            for line in stderr.split('\n'):
                logging.error('%s (stderr): %s', cmd[0], repr(line))
        self.log_fh.flush()
        self.log_fh.write(stdout)
        self.log_fh.flush()
        return process.returncode, stdout

    def cleanup(self):
        """ Cleanup the current enviornment.

        Terminates all background processes, and removes files uploaded to
        remote nodes.

        Arguments:
            None

        Returns:
            None

        Raises:
            None
        """
        for process in self.processes:
            process.terminate()

    @staticmethod
    def log_packages():
        """ Logs all of the installed CGC packages

        Arguments:
            None

        Returns:
            None

        Raises:
            None
        """
        if 'debian' in platform.dist()[0]:
            import apt
            cache = apt.Cache()
            cgc_packages = []
            for package_name in cache.keys():
                if 'cgc' not in package_name:
                    continue
                package = cache[package_name]

                status = '%s: (installed: %s)' % (package.name,
                                                  repr(package.is_installed))
                for version in package.versions:
                    status += ' version: %s' % version.version

                cgc_packages.append(status)

            cgc_packages.sort()
            for package in cgc_packages:
                logging.warning('package: %s', package)

    @staticmethod
    def signal_name(sig_id):
        """ Translate a signal number to its name

        Arguments:
            sig_id: signal number

        Returns:
            The signal name, or 'UNKNOWN' if it is an undefined signal number

        Raises:
            None
        """
        for name, value in signal.__dict__.iteritems():
            if sig_id == value:
                return name
        return 'UNKNOWN'

    def start_replay(self, xml):
        """ Start cb-replay

        Arguments:
            None

        Returns:
            The handle to the running process

        Raises:
            None
        """
        cb_paths = [os.path.join(self.directory, cb) for cb in self.cb_list]

        replay_bin = os.path.join('.', 'cb-replay.py')
        if xml[0].endswith(add_ext('.pov')):
            replay_bin = os.path.join('.', 'cb-replay-pov.py')

        replay_cmd = [sys.executable, replay_bin, '--debug', '--cbs'] + cb_paths

        if self.timeout > 0:
            replay_cmd += ['--timeout', '%d' % self.timeout]

        if self.negotiate_seed:
            replay_cmd += ['--negotiate']
            if self.cb_seed is not None:
                replay_cmd += ['--cb_seed', self.cb_seed]

        if self.pov_seed and replay_bin == os.path.join('.', 'cb-replay-pov.py'):
            replay_cmd += ['--pov_seed', self.pov_seed]

        if self.should_debug:
            replay_cmd += ['--debug']

        if replay_bin == os.path.join('.', 'cb-replay.py'):
            if self.failure_ok:
                replay_cmd += ['--failure_ok']

            if self.concurrent:
                replay_cmd += ['--concurrent', '%d' % self.concurrent]

        if self.max_send is not None and self.max_send > 0:
            replay_cmd += ['--max_send', '%d' % self.max_send]

        replay_cmd += xml

        return self.launch(replay_cmd)

    def _check_result_cqe(self, sig, ret):
        # if sig == signal.SIGALRM:
        #     if self.failure_ok:
        #         logging.warning('ok - process timed out', extra={'raw': True})
        #         ret = 0
        #     else:
        #         logging.error('not ok - process timed out', extra={'raw': True})
        #         ret = -1
        # el
        if sig in Runner.pov_signals:
            if self.should_core:
                logging.warning('ok - process cored as expected: (signal %d: %s)',
                                sig, self.signal_name(sig), extra={'raw': True})
                ret = 0
            else:
                logging.error('not ok - process cored: (signal %d: %s)',
                              sig, self.signal_name(sig), extra={'raw': True})
                ret = -1
        elif self.should_core:
            logging.error('not ok - core expected, no cores identified', extra={'raw': True})
            ret = -1
        elif sig == 0:
            logging.warning('ok - process did not core as expected', extra={'raw': True})
            ret = 0

        return ret

    def _check_result_type1(self, sig, replay_stdout):
        if sig == 0:
            if self.should_core:
                logging.error('not ok - POV type 1 should have cored, and did not.', extra={'raw': True})
                return -1
            else:
                logging.warning('ok - POV type 1 did not core, as expected', extra={'raw': True})
                return 0
        elif not self.should_core:
            logging.error('not ok - POV type 1 expected to not core, but did. (signal %d: %s)', sig,
                          self.signal_name(sig), extra={'raw': True})
            return -1

        match = re.match(r"(?ms).*\n# type 1 masks: ([a-fA-F0-9]+) ([a-fA-F0-9]+)", replay_stdout)
        if not match:
            logging.error('not ok - POV type 1 negotation failed', extra={'raw': True})
            return -1
        ip_mask = int(match.group(1), 16)
        reg_mask = int(match.group(2), 16)

        match = re.match(r"(?ms).*\n# type 1 pov: ([a-fA-F0-9]+) ([a-fA-F0-9]+) (\d)", replay_stdout)
        if not match:
            logging.error('not ok - POV type 1 negotation failed', extra={'raw': True})
            return -1

        ip_value = int(match.group(1), 16)
        reg_value = int(match.group(2), 16)

        # All the registers we can check, regardless of 32/64 bit
        reg_names = ["ax", "cx", "dx", "bx", "sp", "bp", "si", "di", "ip"]

        # Get the register we need to check
        reg_num = int(match.group(3))
        reg_target = reg_names[reg_num]

        logging.warning('POV type 1 negotated masks: %08x %08x %d', ip_mask, reg_mask, reg_num)

        register_state_re = r"register states"
        register_state_re2 = r"register states - (([a-z]+\:[a-fA-F0-9]+\ ?)+)"

        match = re.search(register_state_re, replay_stdout)
        if not match:
            logging.error('not ok - cb-server did not log register states', extra={'raw': True})
            return -1

        lines = replay_stdout.split('\n')

        expected_eip = ip_value & ip_mask
        expected_reg = reg_value & reg_mask

        results = []
        for line in lines:
            match = re.search(register_state_re2, line)
            if not match:
                continue

            # Parse out all of the registers in reg_names
            reg_str = match.group(1)
            registers = {}
            for reg in reg_names:
                reg_match = re.search(r'[re]{}\:([a-fA-F0-9]+)'.format(reg), reg_str)
                if reg_match is not None:
                    registers[reg] = int(reg_match.group(1), 16)

            # Make sure the registers we want are there
            for check_reg in ['ip', reg_target]:
                if check_reg not in registers:
                    logging.error('not ok - {} not logged'.format(check_reg), extra={'raw': True})
                    return -1

            eip = registers['ip']

            result_eip = eip & ip_mask
            result_reg = registers[reg_target] & reg_mask

            if (result_eip == expected_eip and result_reg == expected_reg):
                logging.warning('ok - TYPE 1 POV', extra={'raw': True})
                return 0

            results.append([result_eip, result_reg])

        for values in results:
            logging.error(
                'not ok - TYPE 1 POV FAILED.  expected eip: %08x actual eip: %08x expected reg: %08x actual reg: %08x',
                expected_eip, values[0], expected_reg, values[1], extra={'raw': True})

        return -1

    def _check_result_type2(self, replay_stdout):
        seed = self.cb_seed
        if not seed:
            match = re.search(r'using seed: ([a-fA-F0-9]+)', replay_stdout)
            if not match:
                logging.error('not ok - POV type 2 server did not print seed', extra={'raw': True})
                return -1

            seed = match.group(1)

        prng = ansi_x931_aes128.PRNG(seed.decode('hex'))
        flag_page = prng.get(0x1000)

        match = re.search(r'secret value: ([a-fA-F0-9]+)', replay_stdout)
        if not match:
            if self.should_core:
                logging.error('not ok - POV type 2 did not return a secret value', extra={'raw': True})
                return -1
            else:
                logging.warning('ok - POV type 2 did not return a secret value as expected', extra={'raw': True})
                return 0

        value = match.group(1).decode('hex')
        if value not in flag_page:
            if not self.should_core:
                logging.warning('ok - POV type 2 secret value is not part of the secret page (as expected)',
                                extra={'raw': True})
                return 0
            else:
                logging.error('not ok - TYPE 2 POV FAILED.  %s not in %s', value.encode('hex'), flag_page.encode('hex'),
                              extra={'raw': True})
                return -1

        logging.warning('ok - TYPE 2 POV PASSED', extra={'raw': True})
        return 0

    def _check_result_cfe(self, sig, replay_stdout):
        pov_type = None
        match = re.search(r'negotiation type: (\d)', replay_stdout)
        if not match:
            logging.error("not ok - pov did not negotiate", extra={'raw': True})
            return -1

        pov_type = int(match.group(1))
        if pov_type not in [1, 2]:
            logging.error("not ok - pov negotation is not 1 or 2: %d\n" % pov_type, extra={'raw': True})
            return -1

        if pov_type == 1:
            return self._check_result_type1(sig, replay_stdout)

        if pov_type == 2:
            return self._check_result_type2(replay_stdout)

    def check_result(self, replay_result, xml_list):
        """ Check the results of cb-server and cb-replay

        Arguments:
            replay_result: the output of cb-replay
            xml_list: list of paths to all tests that were run

        Returns:
            Returns 0 if the test 'passed'
            Returns -1 if the test 'failed'

        Raises:
            None
        """
        ret, replay_stdout = replay_result

        passed = 0
        for xml in xml_list:
            # Pull out the section of the replay output
            # corresponding to this test
            xml_replay_stdout = replay_stdout.split(xml, 1)[1]
            xml_replay_stdout = xml_replay_stdout.split('END REPLAY', 1)[0]

            # Check if the CB crashed on this test, get its return code
            sig = 0
            sig_re = r'Process generated signal.+signal: (\d+)\)'
            match = re.search(sig_re, xml_replay_stdout)
            if match:
                sig = int(match.group(1))

            # Verify the result of this test
            if not xml.endswith(add_ext('.pov')):
                res = self._check_result_cqe(sig, ret)
            else:
                res = self._check_result_cfe(sig, xml_replay_stdout)

            # Keep track of how many tests passed verification
            if res == 0:
                passed += 1

        return passed

    def run(self):
        """ Runs the test

        Arguments:
            None

        Returns:
            Returns 0 if the tests all pass
            Returns non-0 if any of the tests failed

        Raises:
            None
        """
        self.log_packages()

        xml_sets = []
        cqe_xml = []
        cfe_xml = []
        for xml in self.xml_list:
            if xml.endswith('.xml'):
                cqe_xml.append(xml)
            else:
                cfe_xml.append(xml)

        for i in [cqe_xml, cfe_xml]:
            if len(i):
                xml_sets.append(i)

        # Run all tests, keeping track of how many passed
        total_tests = sum(len(xmls) for xmls in xml_sets)
        passed_tests = 0
        for xml_list in xml_sets:
            replay_result = self.start_replay(xml_list)
            passed_tests += self.check_result(replay_result, xml_list)

        # Report the final results
        logging.warning('TOTAL TESTS: {}'.format(total_tests))
        logging.warning('TOTAL PASSED: {}'.format(passed_tests))

        return 0 if passed_tests == total_tests else -1


class CB_Formatter(logging.Formatter):
    def format(self, record):
        s = super(CB_Formatter, self).format(record)
        result = []

        for line in s.split('\n'):
            if 'raw' in dir(record) and record.raw:
                if line.startswith('# '):
                    line = line[2:]
            else:
                if line[:2] != '# ':
                    line = '# ' + line
            result.append(line)
        return '\n'.join(result)


def main():
    """ Test a challenge binary using cb-server and cb-replay, with either
    local or remote support.

    Arguments:
        None

    Returns:
        Returns 0 on test success
        Returns non-0 if any of the tests failed

    Raises:
        None
        """

    formatter = argparse.ArgumentDefaultsHelpFormatter
    parser = argparse.ArgumentParser(description='Send CGC Polls and POVs',
                                     formatter_class=formatter)

    required = parser.add_argument_group(title='required')
    required.add_argument('--cb', required=True, type=str, nargs='+',
                          help='Challenge Binaries to run')
    required.add_argument('--directory', required=True, type=str,
                          help='Directory containing challenge binaries')

    parser.add_argument('--debug', required=False, action='store_true',
                        default=False, help='Enable debugging')
    parser.add_argument('--log', required=False, type=str, help='Log filename')
    parser.add_argument('--pcap', required=False, type=str,
                        help='PCAP output file')
    parser.add_argument('--concurrent', required=False, type=int,
                        help='Number of Polls/POVs to throw concurrently')
    parser.add_argument('--cb_seed', required=False, type=str,
                        help='CB PRNG Seed')
    parser.add_argument('--cb_seed_skip', required=False, type=int,
                        help='Advance the CB PRNG Seed before launch')
    parser.add_argument('--port', required=False, type=int,
                        help='PORT to run the CB')
    parser.add_argument('--pov_seed', required=False, type=str,
                        help='POV PRNG Seed')
    parser.add_argument('--timeout', required=False, type=int, default=15,
                        help='Maximum duration for each Poll or POV')
    parser.add_argument('--should_core', required=False, action='store_true',
                        default=False, help='This test should cause a core')
    parser.add_argument('--wrapper', required=False, type=str,
                        help='Executable to wrap each CB for instrumentation')
    parser.add_argument('--failure_ok', required=False, action='store_true',
                        default=False, help='Failures for this test are '
                                            'accepted')
    parser.add_argument('--max_send', required=False, type=int,
                        help='Maximum data to send in each request from the '
                             'poll')
    parser.add_argument('--negotiate_seed', required=False, action='store_true',
                        default=False, help='Negotate the CB seed from cb-replay')
    parser.add_argument('--cb_no_attach', required=False, action='store_true',
                        default=False, help='Do not attach to the CB')

    exgroup = parser.add_argument_group(title='XML files')
    group = exgroup.add_mutually_exclusive_group(required=True)
    group.add_argument('--xml', type=str, nargs='+', help='POV/POLL XML File '
                                                          'to evaluate')
    group.add_argument('--xml_dir', type=str, help='Directory containing '
                                                   'POV/POLL XML Files to evaluate')

    args = parser.parse_args()

    xml_files = args.xml
    if args.xml is None:
        assert os.path.isdir(args.xml_dir), "not a directory: " + args.xml_dir
        xml_files = glob.glob(os.path.join(args.xml_dir, '*.xml'))
        xml_files += glob.glob(os.path.join(args.xml_dir, add_ext('*.pov')))
        xml_files.sort()

    assert len(xml_files), "No Polls or POVs"

    if args.cb_seed_skip is not None:
        assert args.cb_seed_skip > 0, "Invalid cb_seed_skip: %d" % args.cb_seed_skip

    for filename in xml_files:
        assert filename.endswith(add_ext('.pov')) or filename.endswith('.xml'), 'invalid POV/Poll'

    if args.cb_seed is not None:
        assert len(args.cb_seed) == 96, "--cb_seed must be 96 bytes"

    if args.pov_seed is not None:
        assert len(args.pov_seed) == 96, "--pov_seed must be 96 bytes"

    logger = logging.getLogger()
    logger.setLevel(logging.WARNING)
    if args.debug:
        logger.setLevel(logging.DEBUG)

    if args.log is not None:
        log_fh = open(args.log, 'w')
    else:
        log_fh = sys.stdout

    log_handler = logging.StreamHandler(log_fh)
    log_handler.setFormatter(CB_Formatter('# %(message)s'))

    logger.addHandler(log_handler)

    if log_fh != sys.stdout:
        error_handler = logging.StreamHandler(sys.stdout)
        error_handler.setLevel(logging.ERROR)
        error_handler.setFormatter(logging.Formatter('# %(message)s'))
        logger.addHandler(error_handler)

    ret = -1
    runner = Runner(args.port, args.cb, xml_files, args.pcap, args.wrapper,
                    args.directory, args.should_core, args.failure_ok,
                    args.debug, args.timeout, log_fh, args.cb_seed,
                    args.cb_seed_skip, args.max_send, args.concurrent,
                    args.negotiate_seed, args.pov_seed, args.cb_no_attach)

    try:
        ret = runner.run()
    except KeyboardInterrupt:
        logger.warning('interrupted')
    finally:
        runner.cleanup()
    return ret


if __name__ == "__main__":
    exit(main())
