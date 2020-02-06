# CROMU_00019 - Casino Games

## Author Information

"Debbie Nuttall" <debbie@cromulence.co>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This is a casino game service. It runs poker, blackjack, and slots. It offers registration in a player's club to track player information. It also has a hidden programming interface that allows modifying game payouts.  

### Feature List

In order to simulate randomness while still having a deterministic game the casino service implements an xorshift pseudo random number generator (PRNG) and seeds it with a string taken from the player at game start. This PRNG is used to shuffle the deck before each round of poker or blackjack and to generate the symbols for the slot machine. 

The casino game service runs poker in the style of a 5 card draw video poker machine. The player is dealt a 5 card hand and allowed to keep or discard each of the cards. Replacement cards are drawn for any discarded and then the new hand is scored. The scoring system pays out anything that is a pair of jacks or better using standard poker hand rankings. To play a round of poker costs the player $10 and the default payouts range from $10 for a pair to $500 for a royal flush. 

The service runs a blackjack game where the goal is to reach closest to 21 points without going over. The player hand is scored against a dealer hand. The player receives a 2 card hand and then may choose to hit (recieve an additional card) or stand (receive no more cards and play moves to the dealer). The dealer will hit until reaching a hand value of 17 or greater (dealer stands on soft 17). A hand of blackjack costs the player $10 and pays out 2 to 1 for a win, and 2.5 to 1 for a 'blackjack' (an initial hand value of 21). 

The casino service slots game can generate a slot machine with 2, 3, 4, or 5 rows/columns. A symbol match in all positions of a row or column is considered a win. Each size slot machine has slightly different odds of winning. The cost to play is $2 and the default payout is $4. Multiple matches in one round will all pay out. 

The players club is used to track how many rounds of each game have been played as well as the player's wallet balance. The service does not begin tracking a player until they have been registered and logged in. 

When a secret password is entered at game start, the service enters a programming mode where it will accept an encoded blob of data. The data is decoded and used to program new payouts for slots, blackjack, and poker. 	

## Vulnerability
This challenge contains two vulnerabilities. 
The first vulnerability is a stack buffer overflow early in the main function of the program.  In casino.c a stack buffer is declared on line 277. On line 284, a call to receive() allows a 20 byte overwrite of that stack buffer with user data. The vulnerability can only be leveraged if the main function returns normally. There are only two scenarios that allow the main function to return, all other code paths result in a call to _terminate() to end the program. 

The second vulnerability is in the hidden programming interface. It is a stack buffer overflow that occurs when the encoded blob of data decodes to a larger size than the destination buffer. In casino.c on line 261 an array is declared on the stack. On line 264 a call to decode() uses this array as the destination buffer. If the user data input into decode() contains the '`' character, it will generate output longer than the destination array. Enough instances of '`' will cause an overflow large enough to overwrite the return address on the stack. 

### Generic class of vulnerability
Stack Buffer Overflow

### CWE classification
CWE-121: Stack-based Buffer Overflow

## Challenges
The first vulnerability is a classic buffer overflow that should be straightforward to detect and patch. The challenge in proving it is that the CRS must determine the correct sequence of events to reach the end of the main function and return. This involves exploring most of the functionality of the program including registering a player, logging in as that player, playing a round of blackjack, poker, and slots, and then exiting. Attempting to exit the program before exploring those code paths results in a call to _terminate and the overflow thus has no provability. 

An alternate path to reach the end of the main function is to amass enough winnings through gambling to exceed $5000 in which case the program exits normally; however, the odds and payouts of the casino games make it very unlikely that this could be achived through standard fuzzing. 

The second vulnerability is more difficult to reach. Initial user input is hashed to create the seed to the PRNG. If the seed matches a specific value, the service enters a programming mode. The CRS will need to solve for the initial input which leads to the specific hash before this portion of the service can be accessed. Once this portion of the service is reached, a blob of encoded data is accepted and decoded into a stack buffer. For most inputs, the decoding algorithm shrinks the data by half, but for specific values of input, the decoding algorithm generates a same sized output which will overflow the destination stack buffer in the unpatched service. 