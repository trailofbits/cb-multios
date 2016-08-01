% CB-TEST(1) Cyber Grand Challenge Manuals
% Brian Caswell <bmc@lungetech.com>
% April 18, 2014

# NAME

cb-test - Challenge Binary testing utility

# SYNOPSIS

cb-test [options] --cb *CB* [*CB* ...] --directory *DIRECTORY* (--xml *XML* [*XML* ...] | --xml_dir *DIR*)

# DESCRIPTION

cb-test is a utility to manage testing a CGC challenge binary (CB) with the replay tool, and recording the resulting network traffic.  If any of the XML files does not validate, the replay tool indicates failures, or a core file is generated, the cb-test tool returns failure.

cb-test output is in the TAP format.

# ARGUMENTS
\-\-cb *CB* [*CB* ...]
:   Specify the challenge binaries to be used in testing.

\-\-directory *DIRECTORY*
:   Specify the directory containing challenge binaries.

# MUTUALLY EXCLUSIVE ARGUMENTS

\-\-xml *XML* [*XML* ...]
:   Specify the XML files to be used with the replay tool.  These can be POVs or polls.

\-\-xml_dir *DIR*
:   Specify the directory containing XML files to be used with the replay tool.  These can be POVs or polls.

# OPTIONS
\-\-log *LOG_FILE*
:   Specify the filename to write output, rather than STDOUT

\-\-port *PORT*
:   Specify the TCP port used for testing the CB.  If *PORT* is not provided, a random port will be used.

\-\-pcap *PCAP*
:   Specify the directory containing the challenge binaries.  If *PCAP* is not provided, the traffic resulting from testing will not be recorded.

\-\-wrapper *WRAPPER*
:   Specify the executable to wrap each challenge binary for instrumentation.

\-\-timeout *TIMEOUT*
:   Specify the maximum duration for each Poll/POV.

\-\-ids_rules *RULES_FILE*
:   Specify the filename to read IDS rules, for use with cb-proxy.  *ONLY* supported with remote testing enabled.

\-\-should_core
:   Specify if inspecting for a 'core' in the *DIRECTORY* takes precedent over all other testing.

\-\-cb_env *ENV*
:   Specify an enviornment variable to use in the CB.

\-\-cb_seed *SEED*
:   Specify the PRNG seed to use in the CB.

\-\-cb_seed_skip *SKIP*
:   Specify the amount to advance the PRNG state before launching the CB.

\-\-pov_seed *SEED*
:   Specify the PRNG seed to use in the POV.

\-\-negotiate_seed
:   Specify if the PRNG should be negotiated by cb\-replay.

\-\-enable_remote
:   Specify if remote testing should be enabled, via uploading the required artifacts via *SCP* and running the underlying tools via *SSH* to the nodes specified via --remote_nodes

\-\-remote_nodes *CB_SERVER* *POV_SERVER* *IDS_SERVER*
:   Specify the hostnames or IP addresses for the nodes to be used in remote testing.

\-\-failure_ok
:   Specify if failing the 'replay' interaction is acceptable.  Useful for testing a POV against a patched CB.

\-\-debug
:   Specify if debug output should be enabled.

# EXAMPLE USES

* cb-test --port 10000 --cb echo --xml echo-test.xml --directory /bin --pcap /tmp/echo-test.pcap 

This will test the challenge binary 'echo' in the directory '/bin', using the XML file 'echo-test.xml', on TCP port 10000, recording any resulting network traffic to '/tmp/echo-test.pcap'.

* cb-test --cb my-service --xml test-1.xml test-2.xml --directory /usr/local/bin

This will test the challenge binary 'my-service' in the directory '/usr/local/bin', using the XML files 'test-1.xml' and 'test-2.xml', on a random TCP port.  No network traffic is recorded.

* cb-test --cb my-service --xml_dir . --directory /usr/local/bin

This will test the challenge binary 'my-service' in the directory '/usr/local/bin', using the XML files that match the file globbing '*.xml' in the current working directory, on a random TCP port.  No network traffic is recorded.

* cb-test --cb cb-1 cb-2 cb-3 --xml ipc.xml --directory /tmp --pcap /tmp/ipc.pcap

This will test the IPC challenge binary made up of the challenge binaries 'cb-1', 'cb-2', and 'cb-3' in the directory '/tmp', using the XML file 'ipc.xml', on a random TCP port, record any resulting network traffic to '/tmp/ipc.pcap'.

# COPYRIGHT

Copyright (C) 2014, Brian Caswell <bmc@lungetech.com>

# SEE ALSO

`cb-server` (1), `poll-validate` (1), `cb-replay` (1), `tcpdump` (8)

For information regarding the TAP Format, see <http://testanything.org/>

For more information relating to DARPA's Cyber Grand Challenge, please visit <http://www.darpa.mil/cybergrandchallenge/>
