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

#ifndef DECK_H
#define DECK_H

#define SIZE_OF_DECK 52

// Each card in the deck is represented by a number from 1 to 52
// 0 is used to indicate the absence of a card
// 1 through 13 is 2,3,4,5,6,7,8,9,10,J,Q,K,A of Diamonds
// 14 through 26 is 2,3,4,5,6,7,8,9,10,J,Q,K,A of Spades
// 27 through 39 is 2,3,4,5,6,7,8,9,10,J,Q,K,A of Hearts
// 40 through 52 is 2,3,4,5,6,7,8,9,10,J,Q,K,A of Clubs
#define DIAMONDS 1
#define SPADES 	2
#define HEARTS 	3
#define CLUBS 	4

typedef struct {
	char deck[SIZE_OF_DECK];
	char top;
} standard_deck;

void shuffle(standard_deck *deck);
char draw(standard_deck *deck);
int is_empty(standard_deck *deck);
void print_deck(standard_deck *deck);
void print_hand(char *hand, size_t size);
int get_suit(char card);

static const char *card_names[SIZE_OF_DECK + 1] = {
	"NC", // 0
	"2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "10D", 	//1 - 9
	"JD", "QD", "KD", "AD",									// 10 - 13
	"2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S", "10S",	// 14 - 22
	"JS", "QS", "KS", "AS",									// 23 - 26
	"2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "10H",	// 27 - 35
	"JH", "QH", "KH", "AH", 								// 36 - 39
	"2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C", "10C",	// 40 - 48
	"JC", "QC", "KC", "AC"									// 49 - 52
};


#endif // DECK_H