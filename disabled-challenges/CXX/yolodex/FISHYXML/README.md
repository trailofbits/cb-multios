# CGC Challenge Binary Template

## Author Information

"Nick Davis" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

FISHYXML brings the world-renowned game Go Fish to an ultra-low bandwidth wireless handset near you. When you are sitting by the campfire at the family picnic, you don't have to worry about terrible cellular reception to keep the e-children entertained. Whip out a set of ultra-low bandwidth wireless handsets featuring FISHYXML and they will be entertained for hours.

### Feature List

This service is the server side of a 2-player Go Fish game, and provides an excellent AI to test your Go Fish Witts against. The service is designed to only handle a single remote player and a bot player run by the server.

The serialization protocol of this service is a stripped-down version of wbxml, a binary xml format, called FISHYXML. So, the client and server communicate using FISHYXML.

Yes, the game and the serialization protocol share the same name.

And fishy is not just because of the name Go Fish, it is also because of the fishy implementation of the shuffle algorithm's choice of a random seed.

The rules of this version of the game Go Fish are as follows:

# Starting
* The remote player provides their name to get the game started.

# Dealing
* A single 52 card deck is used. No jokers.
* There can be 2 to 4 players in standard Go Fish, but we only support 2 players total. The remote player and an opponent played by the server.
* Initial deal for 2 players is 7 cards each
* The remainder of the deck becomes the pool.

# Play a turn
* First player is the remote player.
* In a turn, the player first selects a card from their hand and asks the other player if that player has any cards of that rank. If the asked player does, then they give all cards of that rank to the asking player. If the asked player does not, then they tell the asking player to Go Fish. Then the asking player selects a single card from the pool. If the asking player picks a card from the pool that matches the rank they asked for, they show the card to the other player. At the end of a turn, if a player has 4 cards of a rank, they have a book, which they play face up. Then the turn ends. At no point does a player get to take another turn, even if they get cards of the asked rank.

# Runing out of cards
* If a player runs out of cards, they draw a new hand from the pool of size equal to their initially dealt hand.
* If the pool has less cards than the player needs to draw, the player draws the remaining cards.
* If the player goes fish and the pool has no more cards, the players turn is over.

# Ending the game
* The game ends when all books have been laid down (all cards are laid down face up)

# Scoring
* The winner is the player with the most books. It is possible to have a tie.


## Vulnerability

The primary vulnerability is in parse\_xml\_cards() in fishyxml.c:150. The loop reads in cards provided by the remote player. But, it does not check against a known quantity of cards that are expected. So, it will continue to read in cards provided the data is properly formatted xml for a card. The cards are created as they are read and pointers to the cards are saved into the cards[] buffer. This leads to writing beyond the end of the cards[] buffer. The cards buffer is allocated adjacent to other allocations, so it takes a total of 625 cards to overflow; which equates to 5004 bytes.

The solution to this vuln is to check the count of cards received against the qty value; the known number of cards expected.

Cooperating with this vulnerability is an excessivly large buffer in read\_cards() in rxtx.c:88. This buffer size is defined by bytes\_needed and is set to 5120 (10*512). It only needed to be 5003, but 5120 makes for even memory allocations.

By lowering the bytes\_needed value to less than 5004, the vuln in parse\_xml\_cards() is not reachable.

### Generic class of vulnerability

Improper Input Validation

Heap Buffer overflow

Improper checking of loop invariant

Improper array bounds checking

### CWE classification

Improper Input Validation
CWE-20

Heap-based Buffer Overflow
CWE-122

Improper Validation of Array Index
CWE-129

Incorrect Calculation of Buffer Size
CWE-131

Out-of-bounds Write
CWE-787

## Challenges
* Solving the grammar for the fishyxml serialization protocol will be a good challenge. I stripped the fishyxml grammar to as minimal as possible to lessen the tokens that need to be discovered. Plus, the binary version of xml has very short tokens (most are 1 byte). So, that makes it a little easier.
* Learning the rules of the game to get enough plays to reach the vulnerabilities, and further to complete/win a game, will be challenging.
* To reach the vulnerability through dynamic analysis, the player has to play part of the game and provide input that matches the xml grammar. And then the code required to trigger the vulnerability has to be properly formatted xml as well.
* Due to the requirement for formatted xml grammar for all I/O, a fuzzer is not going to be of any use.
* 
