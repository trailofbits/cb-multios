# A_Game_of_Chance

## Author Information

"Nick Davis" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description:

Card players often spend significant effort memorizing all of the strategies and odds of possible each state of a game. This style of game presents a high bar to entry for those who have problems learning and remembering strategies and odds. For those people, we've created, A Game of Chance.

We simplified the deck to remove face cards and Aces; leaving the cards numbered 2 - 10. We've removed the need and ability to calculate odds, by making every deck into randomly generated collections of the possible valid card numbers. And lastly, we've minimized the need to develop strategies by making it a 2 card game where the bids are placed after the first card is dealt, face up, and the results are calculated after the second card is dealt, face up.

The rules of each round are simple. First, the dealer deals one card face up to each player. Then each player makes a wager. Then the dealer deals the second card face up to each player. The winner is the player that has the highest 2-card sum. If there is a tie for winner, each is considered a winner. The dealer does not play a hand. The players are playing against each other.

Those that win, are given a dollar amount equal to their wager. Those that do not win, lose their wager.

The most common strategy, that all current players use, is to wager 0 if the first card is a 2 or 3, and wager some other amount when the first card is 4 or greater.

## Feature List:

One CB (cb\_1) is the dealer, the others are the players (cb\_2 - cb\_7). The poller/pov/CRS communicates only with the dealer.

Each cb\_1 - cb\_7 represents a player at the table and functions the same, except that they have different parameters to provide variations.

There are 6 possible messages that the dealer accepts from the poller/pov/CRS.

Get Player Count - This message is used to ask the dealer how many players are in the game.

Supply New Deck - This message is used to supply the dealer with a new deck. This could be at the start of a game. Or during a game if the dealer runs out of cards.

Deal One Round - This message directs the dealer to deal one hand to each player and process the results of that hand.

Get Round Data - This message asks the dealer to report the wagers and results of each player.

Get Player Earnings - This message asks the dealer to report the dollar amount that each player as won/lost.

Quit - This message asks the dealer to inform each player that the dealer has to quit for the day and the table is closed.

## Vulnerability 1

Each player uses the flag page to determine how much they will wager. All players use the first byte of the flag page as their first wager. If they win, their flag page index pointer will shift by 126 char mod 4096 to determine which flag page byte to use for the next wager. If they lose, their flag page index pointer will shift by -77 chars mod 4096 to determine which flag page byte to use for the next wager.

Since the CRS provides the deck to the dealer, and it can ask the dealer for the number of players, it can stack the deck such that the players move through the flag page indices in a manner that will eventually cause 4 consecutive flag page bytes to be used for wagers. Also, the Get Round Data command provides the CRS with the wagers that were made by all players in that round, so the CRS can track each byte that was used by each player.

### Generic Class of Vulnerability

Information Leakage

### CWE Classification

CWE-201: Information Exposure Through Sent Data

### Challenges

* The biggest challenge this CB was designed to test was how well a CRS can associate a large number of disperate bytes with their origin location from the flag page. A taint tracking tool can certainly determine which functions will cause flag page bytes to be released (as a wager). But those are only single bytes, so the CRS will have to determine which indices each byte comes from, so they can then determine when 4 consecutive bytes have been released.
* A challenge the CRS's will have to figure out is that the 5 byte command buffer that the CRS sends to cb\_1 has byte indices associated with each command. So, there are a large number of buffers that can trigger each command. And the order in which that buffer is parsed will determine which command gets run. A smart fuzzer will be helpful to narrow down which bytes trigger each command.
* Each of the 5 player CBs has the same code, but as they win or lose a hand, their flag page pointers will diverge. This will enable the CRS to direct the players to move their flag page pointers through the flag page, so it will be a challenge for the CRS to develop the proper deck at the start that will enable the wagers made during the game to provide at least one set of 4 consecutive bytes.

### Difficulty

* Discovering is medium
* Proving is hard
* Fixing is easy
