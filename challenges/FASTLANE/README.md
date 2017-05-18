# FASTLANE Challenge Binary

## Author Information

"Narf Industries" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

You are lab rat in a maze constructed by a duo of megalomaniacal mice with lofty aspirations of taking over the world.

You don't care so much about that, but you do care about cheese - and the mice are charging to use the fast ways through the maze.  Rich lab rats can afford the FASTLANE and get to their cheese faster.  Poor lab rats like yourself need to take more circuitous routes.

Your challenge is emulated as an HTTP-like service where the "cheese" are files and what you're after is file contents.

### Feature List

Everyone gets "free" content via the SLOWLANE, faster content for those who can afford the FASTLANE.

Non-FASTLANE file request:
client: 
	MOOCH <URI>\n
server:
	<pause>
	<data>

FASTLANE file request:
client:
	AUTH <credit voucher key>\n
	GIMME <URI>\n
server:
	<data>

Using a FASTLANE verb consumes a credit in the user's account.

Verbs:
* TIP (FASTLANE) / SMORE (SLOWLANE): Get the first 4 bytes of a chosen file.  Requires a filename as argument, e.g.: "TIP abcdefghijklmnop\n"
* STATUS (FASTLANE) / YOUUP (SLOWLANE): A simple ping-like query asking whether the server is responsive.
* GIMME (FASTLANE) / MOOCH (SLOWLANE): Get the entire contents (16 bytes) of a chosen file.  Requires a filename as argument.
* LIST (FASTLANE) / SUP (SLOWLANE): Get a listing of filenames.
* AUTH: Redeem a voucher for FASTLANE credits.

## Vulnerability

FASTLANE implements an HTTP-inspired protocol.  It has a number of verbs, all of which allow users to copy 1 extra byte into an adjacent buffer (off-by-one).  This vulnerability emulates a classic misunderstanding of string lengths in C.

In all but two cases, this off-by-one error does not cause any side effects.  In the cases where a side-effect is not caused, the extra byte harmlessly overflows into the adjacent verb buffer, only to be overwritten with new content when the verb is later issued.

high addrs	/-----------------------------------\	end of stack
			|	*ptr_crash						|
			|	FASTLANE TIP URI buff 			|
			|	FASTLANE GIMME URI buff 		|
			|	3 dummy bytes					|
			|	# of FASTLANE credits (1 byte)	|
			|	SLOWLANE SMORE URI buff 		|
			|	SLOWLANE MOOCH URI buff 		|
			|	SLOWLANE AUTH buff 				|
low addrs	\-----------------------------------/

Proving vulnerability involves making use of the verbs with side-effects triggered by overflow (SMORE and TIP).

When TIP is overflown, the last byte clobbers the least significant byte of a pointer (ptr_crash) that is used in a write shortly thereafter.  If the overflown byte causes ptr_crash to point too high on the stack, this write will result in a SIGSEGV condition caused by attempting to write beyond to the end of the stack (a stack overflow) into unmapped memory.

TIP cannot be exercised without FASTLANE credits.  There are two means to obtain FASTLANE credits:
* Redeem a credit voucher via the AUTH verb.  CRSs are not expected to solve this path.  This path allows testing infrastructure to add FASTLANE credits even on the patched CB.  Keys are verified with a prime cyclic group calculation.
* Overflow the SMORE buffer and clobber the credit byte.  In doing so, the CRS can add up to 255 (\xFF) credits to the FASTLANE account.

First, the client overflows the SMORE verb buffer, adding credits to his/her FASTLANE account:
client:
	SMORE <'A' * 16>\n
server:
	here's a lil' bit\n
    -----------------\n
    requested file not found\n

An overflow of 'A' (\x41) would provide 65 FASTLANE credits.

Next, the client overflows the TIP verb buffer, made accessible with the new credits:
client:
	TIP <'\xFF' * 16> 
server:
	(SIGSEGV)

In all CBs, the stack ends at 0xbaaaafff.  Therefore, any write to 0xbaaab000 or beyond should cause SIGSEGV.

*ptr_crash initially points to 0xbaaaafd8, or very close to the end of the stack.

Because the possibly-crashing write is a 4-byte write through *ptr_crash, the TIP overflow must end in a character in the range of [\xfd, \xff].  In other words, after the overflow, *ptr_crash must point to location in the range [0xbaaaaffd, 0xbaaaafff].  Any of these values would cause a write to 0xbaaab000 or beyond.

### Generic class of vulnerability

Buffer Overflow

### CWE classification

120: Buffer Overflow
121: Stack-Based Buffer Overflow

## Challenges

* Reasoning about types in adjacent memory and their usages based on access patterns.
* Reasoning about mapped address ranges.  The CRS must understand that a write to a location beyond the end of the stack will result in SIGSEGV and then solve constraints to cause this to happen.
* Avoiding time-sinks presented by busy work done in SLOWLANE verbs and probably-misguided attempts at brute-forcing the AUTH verb.

