# Hug_Game

## Author Information

"Dustin Fraze" <df@cromulence.com>

### DARPA performer group
Cromulence (CROMU)

## Description

This is a challenge modelled after one of the author's favorite DEF CON Capture The Flag challenges - perudo, from the Kenshoto group.

### Feature List

This service is a simple gambling parlor for the user. Upon connecting, the user is asked for a name and then given a selection of four games to play. The name is used to seed a PRNG. The games are:

* Coin Flip
* Hangman
* Dice Roll
* War

## Vulnerability

The dice roll game stores the results of the rolls into a staticly sized array. If the player decides to play more than 16 rounds of dice, stack corruption occurs.

### Generic class of vulnerability
Unbounded memory write

### CWE classification
Improper Restriction of Operations within the Bounds of a Memory Buffer
CWE-119

## Challenges

This CB takes a "less is more" approach to proving vulnerability. The CRS will have very little control over the state of the application at crash - namely, the output from the PRNG is what is used to determine EIP and any other corrupted registers. Because of this, type1 proofs of vulnerability should be less straight forward than typical - instead of being able to use the function epilogue to pop corrupted values into preserved registers, a CRS will have to generate a payload which sets EIP to a sequence of instructions that points the stack into the name buffer, and then pops, for example.
