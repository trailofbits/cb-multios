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
#include "cgc_prng.h"


// Shuffle the deck using the Knuth shuffle agorithm with array initialization
void cgc_shuffle(standard_deck *deck)
{
	for (int i=0; i<SIZE_OF_DECK; i++)
	{
		int j = cgc_random_in_range(0, i);
		deck->deck[i] = deck->deck[j];
		// Initialize array with the numbers 1 to 52
		deck->deck[j] = (char)(i + 1); 
	}
	deck->top = 0;
}

// Print the face value of each card in the deck (2D, AH, etc)
void cgc_print_deck(standard_deck *deck)
{
	cgc_printf("deck: ");
	for (int i=0; i< SIZE_OF_DECK; i++)
	{
		cgc_printf("@s ", card_names[deck->deck[i]]);
	}
	cgc_printf("\ntop: @d\n", deck->top);
} 

// Print the face value of each card in the hand
void cgc_print_hand(char *hand, cgc_size_t size)
{
	for (int i=0; i<size; i++)
	{
		if ((hand[i] > 0) && (hand[i] < SIZE_OF_DECK + 1))
		{
			cgc_printf("@s ", card_names[hand[i]]);
		}
	}
	cgc_printf("\n");
}

// Draw a card from the deck.
// Returns the numeric representation of the card drawn (1 to 52)
char cgc_draw(standard_deck *deck)
{
	if (cgc_is_empty(deck))
	{
		cgc_printf("Error: Drawing from an empty deck!\n");
		cgc__terminate(1);
	}
	else
	{
		deck->top += 1;
		return deck->deck[deck->top - 1];
	}

}

int cgc_is_empty(standard_deck *deck)
{
	return (deck->top >= SIZE_OF_DECK);
}

int cgc_get_suit(char card)
{
	if ((card <= 0) || (card > SIZE_OF_DECK + 1))
		return 0;
	else if (card < 14)
		return DIAMONDS;
	else if (card < 27)
		return SPADES;
	else if (card < 40)
		return HEARTS;
	else
		return CLUBS;
}

