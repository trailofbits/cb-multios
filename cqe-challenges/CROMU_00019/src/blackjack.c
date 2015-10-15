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

#include <libcgc.h>
#include "stdlib.h"
#include "deck.h"
#include "blackjack.h"

int is_an_ace(char card)
{
    return ((card == 13)||(card == 26)||(card == 39)||(card == 52));
}

// Returns the total value of the hand.
// Aces are given point value of 11 unless that puts the hand over 21, in which
// case they are given point value of 1. 
int hand_total(char *hand, size_t size, int running_total)
{
    for (int i=0; i<size; i++)
    {
        if (is_an_ace(hand[i]))
        {
            i += 1;
            int soft_total = hand_total(&hand[i], size - i, running_total + 11);
            int hard_total = hand_total(&hand[i], size - i, running_total + 1);
            if (soft_total > 21)
            {
                return hard_total;
            }
            else
            {
                return soft_total;
            }
        }
        else
        {
            running_total += bj_value[hand[i]];
        }
    }
    return running_total;
}


// Plays blackjack
void blackjack(player_info *player)
{
    char player_hand[11];
    char dealer_hand[11];
    bzero(player_hand, sizeof(player_hand));
    bzero(dealer_hand, sizeof(dealer_hand));

    player_info placeholder;
    if (player == 0)
    {
        player = &placeholder;
    }
    
    standard_deck deck;
    shuffle(&deck);
    player->blackjack_score += 50;
    if (player->wallet >= 10)
    {
        player->wallet -= 10;
    }

    // Deal
    player_hand[0] = draw(&deck);
    dealer_hand[0] = draw(&deck);
    player_hand[1] = draw(&deck);
    dealer_hand[1] = draw(&deck);

    printf("D: * @s \n", card_names[dealer_hand[1]]);
    printf("P: @s @s \n", card_names[player_hand[0]], card_names[player_hand[1]]);

    // Handle Blackjacks
    if (hand_total(dealer_hand, sizeof(dealer_hand), 0) == 21)
    {
        if (hand_total(player_hand, sizeof(player_hand), 0) == 21)
        {
            printf("Dealer Blackjack! Player Blackjack! You Tie :/\n");
            player->wallet += payouts[BLACKJACK_PUSH];
            return;
        }

        printf("Dealer Blackjack! You Lose!\n");
        return;
    }

    if (hand_total(player_hand, sizeof(player_hand), 0) == 21)
    {
        printf("Blackjack! You Win!\n");
        player->wallet += payouts[BLACKJACK_BLACKJACK];
        return;
    }

    // Play Player hand
    char input = '\0';
    int hand_position = 2;
    while( 1 )
    {
        printf("Enter h for hit or s for stand:");
        receive_fixed_input(&input, '\n', sizeof(input));
        if (input == 'h')
        {
            player_hand[hand_position++] = draw(&deck);
            printf("P: ");
            print_hand(player_hand, sizeof(player_hand));
            if (hand_total(player_hand, sizeof(player_hand), 0) > 21)
            {
                printf("Bust\n");
                break;
            }
        } 
        if (input == 's')
        {
            break;
        }
    }
    
    // Play Dealer hand
    hand_position = 2;
    printf("D: ");
    print_hand(dealer_hand, sizeof(dealer_hand));
    while ( hand_total(dealer_hand, sizeof(dealer_hand), 0) < 17 )
    {
        dealer_hand[hand_position++] = draw(&deck);
        printf("D: ");
        print_hand(dealer_hand, sizeof(dealer_hand));
    }

    // Resolve
    printf("P:@d D:@d\n", hand_total(player_hand, sizeof(player_hand), 0),
        hand_total(dealer_hand, sizeof(dealer_hand), 0));

    if ( hand_total(player_hand, sizeof(player_hand), 0) > 21 )
    {
        printf("Player Bust. You Lose.\n");
    }
    else if ( hand_total(dealer_hand, sizeof(dealer_hand), 0) > 21)
    {
        printf("Dealer Bust. You Win.\n");
        player->wallet += payouts[BLACKJACK_WIN];
    }
    else if (hand_total(player_hand, sizeof(player_hand), 0) > 
        hand_total(dealer_hand, sizeof(dealer_hand), 0) )
    {
        printf("You Win.\n");
        player->wallet += payouts[BLACKJACK_WIN];
    }
    else if (hand_total(player_hand, sizeof(player_hand), 0) == 
         hand_total(dealer_hand, sizeof(dealer_hand), 0) )
    {
        printf("Push.\n");
        player->wallet += payouts[BLACKJACK_PUSH];
    }
    else
    {
        printf("You Lose.\n");
    }
}
