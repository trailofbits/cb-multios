% GENERATE-POLLS(1) Cyber Grand Challenge Manuals
% Brian Caswell <bmc@lungetech.com>
% May 1, 2015

# NAME

generate-polls - Generate CGC CB Polls

# SYNOPSIS

generate-polls [-h] [--count COUNT] [--depth DEPTH] [--seed SEED] [--duplicate DUPLICATE] [--repeat REPEAT] [--rounds ROUNDS] [--store_seed] [--package PACKAGE] machine state_graph output

# DESCRIPTION

generate-polls is a generative graph traversal engine that can be used to automatically generate deterministic iterations of a non-deterministic state graph.  The resulting output is intended to be used with 'cb-replay'.

# ARGUMENTS

`machine`
:   Specify the python file that implements an Actions class, which controls the state machine

`state_graph`
:   Specify the yaml file that specifies the state graph

`output`
:   Specify the output directory

# OPTIONS

-h
:   Display a usage message and exit

--count *COUNT*
:   Specify the number of traversals through the state graph per round

--depth *COUNT*
:   Specify the maximum number of state transitions per iteration

--seed *SEED*
:   Specify the PRNG seed value

--duplicate *DUPLICATE*
:   Specify the number of polls that should be duplicated in a round

--repeat *REPEAT*
:   Specify the maximum number of times a duplicated poll may be repeated in a round

--rounds *ROUND*
:   Specify the number of rounds to generate polls

--store_seed
:   Store the PRNG seed for the magic page in the XML

--package *PACKAGE*
:   Package the polls in a single binary file

# EXAMPLE USES

* generate-polls machine.py state-graph.yaml /tmp

This will generate 100 XML files in '/tmp' that each correspond to a traversal through the state machine.

* generate-polls --count 10 --seed 0 machine.py state-graph.yaml /tmp

This will generate 10 XML files in '/tmp' that each correspond to a traversal through the state machine, setting the PRNG seed to 0.

* generate-polls --depth 5 machine.py state-graph.yaml /tmp

This will generate 100 XML files in '/tmp' that each correspond to a traversal through the state machine, with traversing a maximum of 5 nodes in the graph.

# ADDITIONAL OUTPUT

In addition to the generated XML, the following additional content is generated:

* edges.png

A bar chart that shows the count of times a given edge is traversed per depth of traversal

* nodes.png

A bar chart that shows the count of times a given node is executed at a given depth of traversal

* counts.png

A bar chart that shows the count of times a given node is included within the polls.

* graph.dot

A dot notation of the graph, appropriate for use with GraphViz

# COPYRIGHT

Copyright (C) 2015, Brian Caswell <bmc@lungetech.com>

# SEE ALSO

`cb-replay` (1)

For more information relating to DARPA's Cyber Grand Challenge, please visit <http://www.darpa.mil/cybergrandchallenge/>
