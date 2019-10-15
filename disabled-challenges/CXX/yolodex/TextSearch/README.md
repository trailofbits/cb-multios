# CGC Challenge Binary (KPRCA\_00036): TextSearch

### DARPA performer group
Kaprica Security (KPRCA)

## Description

TextSearch is a simple service that allows a user to input a large amount of text and search for lines that have matching strings. The user can enter a block of printable text and a search string or search pattern and discover what lines of the text match. 

### Feature List

The text searching capability either allows partial or exact matching. The user may turn on partial line matching which will return a line if it matches any part of the search string. Exact matching which will only return a line when the entire line matches the search string.

The search algorithm is inspired by Ken Thompson's 1968 paper on matching using NFAs (Nondeterministic Finite Automaton) and DFAs (Deterministic Finite Automaton). It uses a shunting yard algorithm to convert the pattern from infix to postfix, and then proceeds to convert the pattern into a series of connected states. 

The approach builds a not quite NFA a not quite DFA, but stores the transitions from state to state as a directed graph. Epsilon transitions (no character input) are a special transition that enables operators like * and ? to function properly. 

Each operator has a very specifically designed digraph that enables the proper state transtion to occur. These digraphs were built in order to accommodate all the operators as well as be attached to new states. These are stored in the **state_t** strucuture with either a left or right path (**t1, t2**).

## Vulnerability

NFA's have a special type of transition, an epsilon transition, that enable one state to transition to another without requiring any input. The kleene star (**"*"**) operator says that the pattern can match 0-n quantities of its input. This graph was built such that **state_t** s looks something like:
s-t1 = s(input)
s-t2 = s
t1-t1 = s
In this there are 2 epsilon transitions, t (s to itself) and t1-t1 (t1 back to s). When it's just a single loop the code knows that once it hits an empty string and starts looping, to return back to the parent call with a failed match.

The vulnerability occurs when a pattern has a group where every input has a kleene star and then the group itself uses the star operator. For example **(pattern = (a*b*)*)**. This creates an episilon transition loop that allows the text to continue moving through the graph without ever having to go down an input transistion. The match function is recursive and only has information about where it can go next, and does not know where it has already been. This was done as an alternative to enumerating every valid path. In order to protect against loops there is a check to make sure that the input has never been there with the same number of characters. If the input is in a state with the same number of characters as a previous time, then we know it's already been traversed at this point in the string and it exits. 

The code however checks the number incorrectly and does a **(last_length >= current_lenth)**. Because of this nested groupings can get to an epsilon loop on an empty string and continue infinitely travering the graph in a loop and exhausting the stack (recursive calls).

The second vulnerability relies on the tema being able to set up the memory very specifically to allow a unitialized memory bug. By allocating, freeing, and reallocating text blocks and then setting the search string to anything will cause one of the state->ids to be overwritten. The state->ids are meant to be a count of the string length, and with the id value set arbitrarily high it is possible to crash the system. The uninitialized check occurs in trex.c:204, temp_state is never actually set to NULL.

### Generic class of vulnerability

Resource Exhaustion

### CWE classification

CWE-193: Off-by-one Error
CWE-674: Uncontrolled Recursion
CWE-457: Use of Uninitialized Variable

## Challenges

This service hopes to challenge a teams ability to characterize recursive loops. Naively the length check will work on the majority of cases and prevent the NFA from looping. Additionally the vulnerable input is specific enough that the goal is that it will not be discovered via fuzzing. The intention is to have a participant specifically study the kleene star operator and how it is different than all of the other operators. Even the ? operator does not loop, but instead has 3 unique states that always move in a single direction. Discovering that the * operator is the only one that creates a loop in the directed graph is meant to be a hint as to how to crash the service.

For the unitialized vulnerability error, the challenge here is setting up memory such that the unitialized variable can be taken advantage of.
