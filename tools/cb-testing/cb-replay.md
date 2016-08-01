% CB-REPLAY(1) Cyber Grand Challenge Manuals
% Brian Caswell <bmc@lungetech.com>
% April 18, 2014

# NAME

cb-replay - POV/Poll replay utility

# SYNOPSIS

cb-replay [options] --host *HOST* --port *PORT* *XML* [*XML* ...]

# DESCRIPTION

cb-replay is a utility to send deterministic testing traffic to a CGC challenge binary (CB), following an XML specification.  Results are recorded in the TAP format.

# ARGUMENTS
\-\-port *PORT*
:   Specify the TCP port used for testing the CB.

\-\-host *HOST*
:   Specify the IP address used for testing the CB.

*XML*
:   Specify the XML files to be used with the replay tool.  These can be POVs or polls.  Multiple XML files can be tested at once.

# OPTIONS
\-h
:   Display a usage message and exit

\-\-concurrent *NUMBER*
:   Specify the number of POVs/polls to run concurrently.

\-\-timeout *TIMEOUT*
:   Specify the timeout for connecting to challenge binaries.

\-\-failure_ok
:   Specify if failures are acceptable.  Useful for testing a POV against a patched CB.

\-\-debug
:   Specify if debug output should be enabled.

# EXAMPLE USES

* cb-replay --host 127.0.0.1 --port 10000 test-1.xml

This will test the challenge binary listening on port '10000' on the IP address '127.0.0.1' with the Poll/POV 'test-1.xml'.

* cb-replay --host 10.10.10.10 --port 31337 test-1.xml test-2.xml test-3.xml

This will test the challenge binary listening on port '31337' on the IP address '10.10.10.10' with the Poll/POVs 'test-1.xml', 'test-2.xml', 'test-3.xml'.

# COPYRIGHT

Copyright (C) 2014, Brian Caswell <bmc@lungetech.com>

# SEE ALSO
For the Replay DTD, see '/usr/share/cgc-docs/replay.dtd'.

For information regarding the TAP Format, see <http://testanything.org/>

For more information relating to DARPA's Cyber Grand Challenge, please visit <http://www.darpa.mil/cybergrandchallenge/>
