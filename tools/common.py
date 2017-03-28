import os
import sys
import thread
import threading

# For OS specific tasks
IS_DARWIN = sys.platform == 'darwin'
IS_LINUX = 'linux' in sys.platform
IS_WINDOWS = sys.platform == 'win32'

TOOLS_DIR = os.path.dirname(os.path.abspath(__file__))
RUNNER = os.path.join(TOOLS_DIR, 'challenge_runner.py')
AJL = os.path.join(TOOLS_DIR, 'AppJailLauncher', 'Debug', 'AppJailLauncher.exe')

# Key to get the server output fd
SERVER_OUT_KEY = 'SERVER_OUT_FD'

# Keys to grab the replay sync pipe fds
_RP_R = 'REPLAY_PIPE_R'
_RP_W = 'REPLAY_PIPE_W'

# Define all os-specific functions
if IS_WINDOWS:
    import win32api
    import win32pipe
    import win32security
    import win32file

    def rp_create():
        sattr = win32security.SECURITY_ATTRIBUTES()
        sattr.bInheritHandle = 1
        r, w = win32pipe.CreatePipe(sattr, 0)

        os.putenv(_RP_R, str(int(r)))
        os.putenv(_RP_W, str(int(w)))
        return r, w

    def rp_send_sync():
        try:
            fd = win32file._open_osfhandle(int(os.getenv(_RP_W)), os.O_APPEND)
            os.write(fd, 'R')
            os.close(fd)
        except TypeError:
            sys.stderr.write('Write end of sync pipe not specified\n')
        except Exception as e:
            print e

    def rp_recv_sync():
        try:
            fd = win32file._open_osfhandle(int(os.getenv(_RP_R)), os.O_RDONLY)
            while os.read(fd, 1) != 'R':
                pass
            os.close(fd)
        except TypeError as e:
            print e
            sys.stderr.write('Read end of sync pipe not specified\n')
        except Exception as e:
            print e

    def terminate(proc):
        win32api.TerminateProcess(proc._handle, 1)

else:
    def rp_create():
        r, w = os.pipe()
        os.putenv(_RP_R, str(r))
        os.putenv(_RP_W, str(w))

    def rp_send_sync():
        try:
            fd = int(os.getenv(_RP_W))
            os.write(fd, 'R')
            os.close(fd)
        except TypeError:
            sys.stderr.write('Write end of sync pipe not specified')

    def rp_recv_sync():
        try:
            fd = int(os.getenv(_RP_R))
            while os.read(fd, 1) != 'R':
                pass
            os.close(fd)
        except TypeError:
            sys.stderr.write('Read end of sync pipe not specified')

    def terminate(proc):
        proc.terminate()


def try_delete(path):
    try:
        os.remove(path)
    except OSError:
        pass


def stdout_flush(s):
    sys.stdout.write(s)
    sys.stdout.flush()


class TimeoutError(Exception):
    pass


class Timeout(object):
    """
    A timeout context manager that uses a thread based timer instead of SIGALRM

    Usage example:
        with Timeout(5):  # 5 seconds
            do_slow_stuff()

    By default when a timeout occurs, a TimeoutError will be raised
    To have the block exit silently, use TimeoutSilent

    NOTE: this can only interrupt the main thread, so using this
    from other threads will not work
    """
    raise_timeout = True  # Raises a TimeoutError if this is True

    def __init__(self, seconds):
        self.timer = threading.Timer(seconds, thread.interrupt_main)
        self.timed_out = False

    def __enter__(self):
        self.timer.start()
        return self

    def __exit__(self, extype, ex, trace):
        if extype is None:
            return self.timer.cancel()
        elif extype is KeyboardInterrupt:
            # The timer sent an interrupt after the timeout
            self.timed_out = True

            # Option to silently timeout
            if not self.raise_timeout:
                return True

            # raise a TimeoutError in place of the interrupt
            raise TimeoutError('Timed out after {}s'.format(self.timer.interval))


class TimeoutSilent(Timeout):
    raise_timeout = False
