% CB-ACCEPTANCE(1) Cyber Grand Challenge Manuals
% Brian Caswell <bmc@lungetech.com>
% May 5, 2015

# NAME

cb-acceptance - Challenge Binary acceptance testing utility

# SYNOPSIS

cb-acceptance [options] *CB* [*CB* ...]

# DESCRIPTION

cb-acceptance is a utility to verify CGC challenge binary (CB) acceptability.  

cb-acceptance output is in the TAP format.

# ARGUMENTS
*CB* [*CB* ...]

# OPTIONS

\-\-help
:   Show the available options

\-\-debug
:   Enable debugging output

\-\-list_checks
:   List available checks and exit

\-\-check *CHECK*
:   Only run the specified check

\-\-check_type *CHECK_TYPE*
:   Only run checks that match the provided type

\-\-cb_type *CB_TYPE*
:   Validate a binary to be a specific type of CB (CFE or CQE)

# EXAMPLE USES

* cb-acceptance /usr/share/cgc-sample-challenges/examples/CADET_00001

This will test the CADET_00001 binary.

* cb-acceptance --cb_type cqe /usr/share/cgc-sample-challenges/examples/CADET_00001

This will test the CADET_00001 binary, verifying it is a CB for CQE.

* cb-acceptance --check_type static /usr/share/cgc-sample-challenges/examples/CADET_00001

This will test the CADET_00001 binary, only verifying the static components that do not require any content generation.

# COPYRIGHT

Copyright (C) 2015, Brian Caswell <bmc@lungetech.com>

# SEE ALSO

`cb-test` (1), `poll-validate` (1)

For information regarding the TAP Format, see <http://testanything.org/>

For more information relating to DARPA's Cyber Grand Challenge, please visit <http://www.darpa.mil/cybergrandchallenge/>
