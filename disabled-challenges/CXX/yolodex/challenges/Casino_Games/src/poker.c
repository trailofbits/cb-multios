/*

Author: Debbie Nuttall <debbie@cromulence.co>

Copyright (c) 2015 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_deck.h"
#include "cgc_poker.h"

// Sorts the hand in increasing numerical order including suit
void cgc_sort_by_suit(char *hand, cgc_size_t size)
{
	for (int i=1; i<size; i++)
	{	
		int j = i;
		char temp = hand[j];
		while ((j > 0) && (hand[j] < hand[j-1]))
		{
			hand[j] = hand[j - 1];
			j--;
			hand[j] = temp;
		}
	}
}

// Sorts the hand in increasing value ignoring suit
void cgc_sort_by_value(char *hand, cgc_size_t size)
{
	for (int i=1; i<size; i++)
	{	
		int j = i;
		char temp = hand[j];
		while ((j > 0) && (poker_value[hand[j]] < poker_value[hand[j-1]])) 
		{
			hand[j] = hand[j - 1];
			j--;
			hand[j] = temp;
		}
		
	}
}

// Counts instances of a card in the hand assuming only face value (ignoring suit)
int cgc_count_cards(char *hand, cgc_size_t size, char card)
{
	int count = 0;
	for (int i=0; i<size; i++)
	{
		if (poker_value[hand[i]] == poker_value[card])
		{
			count++;
		}
	}
	return count;
}

// Plays poker until user enters q to quit
void cgc_poker(player_info *player)
{
	standard_deck deck;
	char hand[5];
	char input[5];

	player_info placeholder;
	if (player == 0)
	{
		player = &placeholder;
	}

	while (1)
	{
		
		cgc_shuffle(&deck);

		hand[0] = cgc_draw(&deck);
		hand[1] = cgc_draw(&deck);
		hand[2] = cgc_draw(&deck);
		hand[3] = cgc_draw(&deck);
		hand[4] = cgc_draw(&deck);

		cgc_print_hand(hand, sizeof(hand));

		// Allow User Hold
		cgc_bzero(input, sizeof(input));
		cgc_printf("Enter cards to hold by number (ex: 13 or 12345). Others will be replaced.\n");
		cgc_receive_fixed_input(input, '\n', sizeof(input));
		
		if (input[0] == 'q')
		{
			break;
		}
		player->poker_score += 100;
		
		if (player->wallet >= 5)
		{
			player->wallet -= 5;
		}

		// Mark any cards to hold (Card positions are numbered 1 through 5)
		char hold[5];
		cgc_bzero(hold, sizeof(hold));
		for (int i=0; i<5; i++)
		{
			if ((input[i] >= '1')&&(input[i]<= '5'))
			{
				hold[input[i] - '0' - 1] = 1;
			}
		}
		// Draw Again
		for (int i=0; i<5; i++)
		{
			if (hold[i] == 0)
			{
				hand[i] = cgc_draw(&deck);
			}
		}

		// Resolve
		cgc_print_hand(hand, sizeof(hand));

		cgc_sort_by_suit(hand, sizeof(hand));

		// 	Poker hand rankings:
		//		Straight Flush 
		//		Four of  Kind 
		//		Full house 
		//		Flush 
		//		Straight 
		//		3 of a kind 
		//		2 pairs 
		//		1 pair
		// Some checks can go out of order because certain hands preclude existence of 
		// others (if its a flush it cannot be a full house, etc).

		// Check for Flush
		if (cgc_get_suit(hand[0])==cgc_get_suit(hand[1]) &&
			cgc_get_suit(hand[0])==cgc_get_suit(hand[2]) &&
			cgc_get_suit(hand[0])==cgc_get_suit(hand[3]) &&
			cgc_get_suit(hand[0])==cgc_get_suit(hand[4]) )
		{
			// Check for royal flush
			if (hand[0]==9 || hand[0]==22 || hand[0]==35 || hand[0]==48)
			{
				cgc_printf("Royal Flush!\n");
				player->wallet += cgc_payouts[POKER_ROYAL_FLUSH];
				goto DONE;
			}
			// Check for straight flush
			else if (hand[4] == hand[0] + 4)
			{
				cgc_printf("Straight Flush!\n");
				player->wallet += cgc_payouts[POKER_STRAIGHT_FLUSH];
				goto DONE;
			} 
			else
			{
				cgc_printf("Flush!\n");
				player->wallet += cgc_payouts[POKER_FLUSH];
				goto DONE;
			}
			
		}

		cgc_sort_by_value(hand, sizeof(hand));

		// Check for multiples
		int i = 0;
		int four_of_a_kind = 0;
		int three_of_a_kind = 0;
		int pair = 0;
		int jacks_or_better = 0;

		while (i < sizeof(hand))
		{
			int count = cgc_count_cards(hand, sizeof(hand), hand[i]);
			if (count == 4)
			{
				cgc_printf("Four of a kind!\n");
				player->wallet += cgc_payouts[POKER_FOUR_OF_A_KIND];
				goto DONE;
			}
			if (count == 3)
			{
				if (pair == 1)
				{
					cgc_printf("Full House!\n");
					player->wallet += cgc_payouts[POKER_FULL_HOUSE];
					goto DONE;
				}
				three_of_a_kind = 1;
			}
			if (count == 2)
			{
				if (three_of_a_kind == 1)
				{
					cgc_printf("Full House!\n");
					player->wallet += cgc_payouts[POKER_FULL_HOUSE];
					goto DONE;
				}
				if (poker_value[hand[i]] >= 11)
				{
					jacks_or_better = 1;
				}
				if (pair == 1)
				{
					cgc_printf("Two Pair!\n");
					player->wallet += cgc_payouts[POKER_TWO_PAIR];
					goto DONE;
				}
				pair = 1;
			}
			i += count;
		}
		if (three_of_a_kind == 1)
		{
			cgc_printf("Three of a kind!\n");
			player->wallet += cgc_payouts[POKER_THREE_OF_A_KIND] ;
			goto DONE;
		}
		if (jacks_or_better == 1)
		{
			cgc_printf("Jacks or better!\n");
			player->wallet += cgc_payouts[POKER_JACKS_OR_BETTER];
			goto DONE;
		}

		// Check for straight
		if ((pair == 0) && (poker_value[hand[4]] == poker_value[hand[0]] + 4))
		{
			cgc_printf("Straight!\n");
			player->wallet += cgc_payouts[POKER_STRAIGHT];
			goto DONE;
		}

		cgc_printf("You Lose!\n");
		goto DONE;
	
	DONE:
		continue;
	}
}



