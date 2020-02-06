# KPRCA-00032

### DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service implements an anagram game and solver with a simple binary interface. At launch, the service is sent an initial dictionary that is used to sort the anatree. THe user can then add more words, remove words, query for anagrams, or play a game.

### Feature List

The anagram solver can answer queries for normal anagrams and subset anagrams. The solver is built using an anatree where each level of the tree represents a letter of the alphabet and the edges represent number of occurences of that letter. While this is slower than the alternative hash-based algorithm, it can support subset anagrams without explosion of runtime. The game will send the user ten words and the user must respond with half of the possible anagrams for each word in order to win.

## Vulnerability

The vulnerability is triggered in **atree_add** (atree.c:255) when there is an out-of-memory condition. The error handling code fails to correct the number of degrees which results in it becoming larger than the max degree, and thus causing a buffer overflow or overread later. One way that the overflow can occur is if degree is too large and then a word at the beginning of the array is deleted, which causes the memmove in **atree_remove** (atree.c:301) to modify memory that is outside of the buffer. An overread can occur in **atree_query** trivially if degree is too large.

### Generic class of vulnerability
Heap-based Buffer Overflow

### CWE classification
CWE-122: Heap-based Buffer Overflow
CWE-755: Improper Handling of Exceptional Conditions

## Challenges

The unique challenge for this service is exploiting an out-of-memory condition. Due to the limitations of the environment, the only reliable way to cause an out-of-memory condition that is exploitable is by exhausting the amount of virtual memory available to the process. The only way to do this reliably is by controlling the allocation in **read_initial_words**.

Patching the bug may be difficult. The trivial patch would be exiting the service if an out-of-memory condition occurs. This is tested for by a poller, however, which should make that patch invalid. Either fixing degree or detecting the out-of-bounds access would be valid patches.
