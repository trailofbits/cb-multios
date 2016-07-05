# KPRCA-00018

## DARPA performer group
Kaprica Security (KPRCA)

## Description:

Square Rabbit is a casino inspired game that lets players gamble with their hard earned virtual cash. Square Rabbit is designed to slightly favor the dealer, but if played right (and with a little bit of luck) the player could win some serious cash.

The game randomly assigns the dealer two numbers and the player two numbers. If the dealer gets assigned a Duck this can either be worth a 1 or an 11 (the service will always assign the hand to the highest possible values). Other animals include a Rabbit, a Bee, and a Lion - all of which are worth 10 points in total. There are are a total of 52 values made up of 4 sets of {Duck, 2-10, Rabbit, Bee, Lion}. These are sitting in a stack that will be distributed to the dealer and player. When the stack is depleted to 35% of its original value it gets randomized and reset. The act of betting, winning and losing can go on until the player is out of money.

The basic rules are simple, draw as many values as you want in order to get as close to 21 as you can, but be careful not to go over 21.

### Feature List

A player can choose to bet $100, $200, $500, or $1000. Once the money has been bet a user is alway presented with the options to:

H - Hit  
        Get another number
S - Stay 
        This ends the player's turn at the current score.
D - Double 
        Only available on the first turn - Double your bet and receive one more number for a chance to double your loses or quadruple your winnings.
X - Split 
        If the first two numbers/animals are identical in value the player can double his or her money and play Split each of the numbers into its own hand. Only available on the first turn.

Insurance: This option appears when the dealer is showing a Duck. It costs half the current bet to elect insurance, and pays 2:1.

## Vulnerability

All of the split hands are stored in a global array defined by squarerabbit.c. The size of this array is defined by MAX_SPLIT which has been set to 2. The current number of split hands is tracked via the global squarerabbit_t structure, which holds the deck and other pertinent info. It is here that the current number of split hands is stored. In a situation where a user can split more than the maximum allowed, there is a bug with how the split hands index is incremented.

When the number of split hands (total hands - 1) == MAX_SPLIT, the "X" option will no longer be displayed as a valid option. In the vulnerable version continuing to submit an "X" (the split command) will erroneously continue to increment the spilt_hand length. Normally this isn't an issue because all of the checks make sure the number split hands < MAX_SPLIT. However if entered enough times (126 extra times) a player can overflow the char that stores the number of split hands to a negative value. Doing this will allow the check against MAX_SPLIT to pass and result in accessing the split hands array with a negative index causing the program to immediately crash. 

### CWE classification
CWE-190: Integer Overflow or Wraparound

## Challenges

This problem poses challenges because of its random nature. We provide the ability to specify the seed in order to control and predict the programs behavior, but in a more realistic scenario it would be much harder to predict. Arriving at the state that enables the crash is not trivial, but also not overly difficult. 
~
