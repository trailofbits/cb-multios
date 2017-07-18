# CGC Challenge Binary (KPRCA\_00017): HackMan

### DARPA performer group
Kaprica Security (KPRCA)

## Description

HackMan is a game that the player needs to guess the word correctly. The word list is pre-populated with 20 dictionary words of various length. Unlike its sister game, Hangman, HackMan allows the player to try as many times as possible until he or she gets the answer. The word is picked based on the seed value the user provides. When a player wins, he or she can leave a comment to brag. However, this comment is immediately discarded. It's just there for making players feel good about themselves. The game even keeps track of how many tries a player tried for each word. This is a solid game for all ages.

### Feature List

It's a game. That's the only feature.

There are some control characters to access limited menu:

  - '+' starts a new challenge word
  - '?' resets the current challenge (# tries & progress)
  - '/' quits the game

## Vulnerability

When the game starts (*play_game* function), the internal state for the game (*h_state*) is set up on the stack. However, this struct is not initialized always. It is only set to the sane value (pointers to the correct functions) when the pointer members inside of the struct are NULL.

In general, those function pointers will be NULL due to the side-effect of *banner* function, where allocates a large stack space and initializes with NULL bytes. Initialized stack area coincides with where *h_state* is located on the stack.

However, one can attack this uninitialized stack variable (struct) by leveraging *record_winner* function after winning a round of the game. Since *record_winner* also uses a large stack buffer, it is possible to control the contents of the stack  area that coincides with where *h_state* will be located. Note that *banner* does not get invoked when *record_winner* is executed, therefore **not** initializing the stack with NULL bytes. And since the function pointers in *h_state_* is not initialized if they are not NULL, the attacker can make the program to call an arbitrary address (EIP control).

### Generic class of vulnerability

Unitialized stack variable usage

Function pointer overwrite

### CWE classification

Use of Uninitialized Variable (CWE-457)

## Challenges

This CB tests if the competitors can detect uninitialized stack variable and its insecure usage. This requires a good understanding and reasoning of the stack throughout interprocedural control flows. The CB also tests the ability to analyze unusual control-flow introduced by *goto* statements. 
