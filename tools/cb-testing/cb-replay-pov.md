% CB-REPLAY-POV(1) Cyber Grand Challenge Manuals
% Brian Caswell <bmc@lungetech.com>
% May 5, 2015

# NAME

cb-replay-pov - CB POV replay utility

# SYNOPSIS

cb-replay-pov [options] --host *HOST* --port *PORT* *POV* [*POV* ...]

# DESCRIPTION

cb-replay-pov is a utility to send deterministic testing traffic to a CGC challenge binary (CB) from a POV that is an executable.

# ARGUMENTS
\-\-port *PORT*
:   Specify the TCP port used for testing the CB.

\-\-host *HOST*
:   Specify the IP address used for testing the CB.

*POV*
:   Specify the POV binary to be used with the replay tool.  Multiple POVs can be tested at once.

# OPTIONS
\-h
:   Display a usage message and exit

\-\-timeout *TIMEOUT*
:   Specify the timeout for connecting to challenge binaries.

\-\-debug
:   Specify if debug output should be enabled.

\-\-cb_seed *SEED*
:   Specify the CB seed

\-\-pov_seed *SEED*
:   Specify the POV seed

\-\-source_host *HOST*
:   Specify the Source IP of the connection to the CB

\-\-source_host *PORT*
:   Specify the Source PORT of the connection to the CB

\-\-negotiate
:   Specify the PRNG for the CB should be negotiated

\-\-attach_port *PORT*
:   Attach to the POV with gdbserver prior to execution on the specified port

# EXAMPLE USES

* cb-replay-pov --host 127.0.0.1 --port 10000 test.pov

This will test the challenge binary listening on port '10000' on the IP address '127.0.0.1' with the POV 'test.pov'

* cb-replay-pov --host 10.10.10.10 --port 31337 test-1.pov test-2.pov test-3.pov

This will test the challenge binary listening on port '31337' on the IP address '10.10.10.10' with the Poll/POVs 'test-1.pov', 'test-2.pov', 'test-3.pov'.

# COPYRIGHT

Copyright (C) 2015, Brian Caswell <bmc@lungetech.com>

# SEE ALSO
For information regarding the TAP Format, see <http://testanything.org/>

For more information relating to DARPA's Cyber Grand Challenge, please visit <http://www.darpa.mil/cybergrandchallenge/>
