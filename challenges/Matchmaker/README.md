# Matchmaker

## Author Information
"Maxwell Koo" <info@narfindustries.com>

### DARPA performer group
Narf Industries (NRFIN)

## Description
Parsing as a service! This service handles all of your regular language
recognition needs. Input a description of a regular language compiled into a
series of statements representing a discrete finite automaton, and then enter in
strings to test if they are accepted by the language or not. Also included is a
method to generate strings which match a language, for testing purposes.
Configurable actions are taken on a match.

### Feature List
This service allows a user to test strings against a description of a regular
language.

- Parses descriptions of DFAs
- Tests user input to see if it is accepted by a DFA
- Can reset language description on the fly
- Can generate example strings satisfying the language
- Can configure custom actions to be taken on a match

## Vulnerability 1
This service leaks data from the flag page. The "magic" action uses the input
string to calculate an offset into the flag page to take a byte, and then drops
the user into a "guess the number" style game. A byte from the flag page can be
leaked then by binary search.

### Generic class of vulnerability
Information exposure through sent data

### CWE classification
CWE-201 Information exposure through sent data

### Challenges
- The vulnerability can be discovered by a CRS which does taint tracking, this
  is made more difficult by hiding the vulnerable function behind an indirect
  function call which requires a specific input to enable.
- Proving the vulnerability requires the ability to enable the vulnerable
  function through a specific command, provide a series of inputs which result
  in the leak of four consecutive bytes, and reasoning about the functionality
  of the number game in order to successfully leak the required information.
- Fixing the vulnerability is easy once identified. The byte retrieved from the
  flag page is not crucial to the operation of the game, so changing where that
  byte comes from is sufficient to prevent the leakage.

### Difficulty
- Discovering is medium
- Proving is hard
- Fixing is easy

## Vulnerability 2
The service uses a signed type improperly as an array index, allowing crafted
data to be parsed by the application leading to control of EIP and EAX. By
transitioning to a state >= 128, state objects are looked up outside of the
states array due to interpreting the state as a signed char. This allows an
attacker to control the onmatch handler and data pointer.

### Generic class of vulnerability
Improper input validation
Integer overflow or wraparound
Improper validation of array index

### CWE classification
CWE-20: Improper input validation
CWE-190: Integer overflow or wraparound
CWE-129: Improper validation of array index

### Challenges
- The vulnerability can be discovered by a CRS which looks for out of bounds
  array accesses, including those who do not directly lead to a crash. This is
  made more difficult by requiring an input with >= 128 states to lead to an out
  of bounds access.
- This vulnerability was designed to make proving through fuzzing or symbolic
  execution difficult by use of an input language with a specific grammar and
  behaviors which require specific structure to the inputs and depend on input
  length, etc. In order to trigger this vulnerability, an input with >= 128
  states followed by an input which can successfully transition to an accept
  state beyond 127 is required.
- Fixing the vulnerability is easy once identified, by inserting bounds checks
  around all potentially vulnerable accesses.

### Difficulty
- Discovering is medium
- Proving is hard
- Fixing is easy

