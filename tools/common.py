import os
import sys

# For OS specific tasks
IS_DARWIN = sys.platform == 'darwin'
IS_LINUX = 'linux' in sys.platform
IS_WINDOWS = sys.platform == 'win32'

if IS_WINDOWS:
    import win32file

TOOLS_DIR = os.path.dirname(os.path.abspath(__file__))
RUNNER = os.path.join(TOOLS_DIR, 'challenge_runner.py')
AJL = os.path.join(TOOLS_DIR, 'AppJailLauncher', 'Debug', 'AppJailLauncher.exe')


def try_delete(path):
    try:
        os.remove(path)
    except OSError:
        pass


def stdout_flush(s):
    sys.stdout.write(s)
    sys.stdout.flush()
