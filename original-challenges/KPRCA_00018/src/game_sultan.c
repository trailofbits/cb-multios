/*
 * Copyright (c) 2014 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#include <libcgc.h>
#include <stdlib.h>
#include <string.h>

#include "squarerabbit.h"

#define INPUT_SIZE 512

typedef enum {MAIN_MENU, SQUARE_RABBIT } screen_select;
typedef struct {
    int money;
    int current_game;
    int current_bet;
} player_t;

//GLOBAL VARIABLES
static player_t g_player;

static char readchar(int fd)
{
    size_t rx;
    char c, delim;

    if (receive(fd, &c, 1, &rx) != 0 || rx == 0)
        return -1;
    if (receive(fd, &delim, 1, &rx) != 0 || rx == 0)
        return -1;

    if (delim != '\n')
        return -1;

    return c;
}

static int readline(int fd, char *buf, size_t size)
{
    size_t i;
    size_t rx;

    for (i = 0; i < size; i++) {
        if (receive(fd, buf, 1, &rx) != 0 || rx == 0)
            break;
        if (*buf == '\n')
            break;
        buf++;
    }

    if (i == size && *buf != '\n')
        return -1;
    else if (*buf != '\n')
        return 1;
    else
        *buf = '\0';

    return 0;
}

static void init_player() {
    g_player.money = 100000;
    g_player.current_game = MAIN_MENU;
    g_player.current_bet = 0;
}

void print_game_menu()
{
    printf("Game Sultan: Main Menu\n");
    printf("1. Square Rabbit\n");
    printf("2. Quit\n\n");
    printf("Select:-@ ");

}

char *cardtos(card_t *card) {
    switch (card->face) {
    case WILD:
        return "W";
    case DUCK:
        return "D";
    case TWO:
        return "2";
    case THREE:
        return "3";
    case FOUR:
        return "4";
    case FIVE:
        return "5";
    case SIX:
        return "6";
    case SEVEN:
        return "7";
    case EIGHT:
        return "8";
    case NINE:
        return "9";
    case TEN:
        return "10";
    case RABBIT:
        return "R";
    case BEE:
        return "B";
    case LION:
        return "L";
    default:
        return "ERROR";
   }
}

char *suittos(card_t *card) {
    return "";
    switch (card->suit) {
    case SQUARE:
        return "S";
    case TRIANGLE:
        return "T";
    case CIRCLE:
        return "C";
    case PENTAGON:
        return "P";
    default:
        return "ERROR";
   }
}

static void print_winner(int player_score, int dealer_score) {
    if (player_score > 21)
        printf("  Busted! Better luck next time\n");
    else if (player_score > dealer_score || dealer_score > 21)
        printf("  Winner!\n");
    else if (player_score == dealer_score)
        printf("  Pushed.\n");
    else
        printf("  Dealer Wins.\n");
}

static int print_cards()
{
    int i = 1, dealer_score, player_score;
    card_t *card;
    squarerabbit_t *srabbit = get_srabbit_game();
    squarerabbit_t *split_hand = get_split_hand();
    hand_t *player = srabbit->player_hand;
    hand_t *dealer = srabbit->dealer_hand;
    player_score = calc_score(player, NULL);
    squarerabbit_t *split;

    if (!is_player_finished()) {
        card = srabbit->dealer_hand->card;
        printf("Dealer: |%s%s|?|\n", cardtos(card), suittos(card));
        printf("----------------\n");
    } else {
        dealer_hit();
        dealer_score = calc_score(dealer, NULL);
        printf("Dealer: |");
        while (dealer != NULL) {
            card = dealer->card;
            printf("%s%s|", cardtos(card), suittos(card));
            dealer = dealer->next;
        }
        printf("    Score: %d\n", dealer_score);
        printf("-------------------------------\n");
    }

    printf("Player: |");
    while (player != NULL) {
        card = player->card;
        printf("%s%s|", cardtos(card), suittos(card));
        player = player->next;
    }
    printf("    Score: %d\n", player_score);
    if (!srabbit->player_finished) {
        printf("Select (H/S");
        if (srabbit->double_or_split) {
            printf("/D");
            if (can_split(srabbit) && split_len() < max_split()) {
                printf("/X");
            }
        }
        printf("): ");
        return 1;
    } else {
        if (is_player_finished())
            print_winner(player_score, dealer_score);
    }

    for (i = 0; i < split_len(); i++) {
        split = &split_hand[i];
        player = split->player_hand;
        player_score = calc_score(player, NULL);
        printf("Split %d: |", i + 1);
        while (player != NULL) {
            card = player->card;
            printf("%s%s|", cardtos(card), suittos(card));
            player = player->next;
        }
        printf("    Score: %d\n", player_score);
        if (!split->player_finished) {
            printf("Select (H/S");
            if (split->double_or_split) {
                printf("/D");
                if (can_split(split) && split_len() < max_split()) {
                    printf("/X");
                }
            }
            printf("): ");
            return 1;
        } else {
            if (is_player_finished())
                print_winner(player_score, dealer_score);
        }
    }

    return 0;
}

void play_squarerabbit()
{
    int quit = FALSE;
    int bet;
    int status_code;
    char response = 0;
    char input[INPUT_SIZE];

    printf("******************\n");
    printf("* Square Rabbit! *\n");
    printf("******************\n");
    while (!quit) {
        printf("Total Money: $%d\n", g_player.money);
        printf("\nType QUIT to exit to main menu\n");
        printf("Place Bet (100, 200, 500, 1000): ");
        if (readline(STDIN, input, INPUT_SIZE) != 0)
            continue;

        if (memcmp(input, "QUIT", sizeof("QUIT")) == 0)
            return;

        bet = strtol(input, NULL, 10);
        switch(bet) {
        case 100:
        case 200:
        case 500:
        case 1000:
            g_player.current_bet = bet;
            break;
        default:
            bet = -1;
        }

        if(bet == -1) {
            printf("Bad Bet\n\n");
            continue;
        }

        if (g_player.current_bet > g_player.money) {
            printf("Not enough money, bet with a lower amount\n");
            continue;
        }

        status_code = deal_srabbit(g_player.current_bet);
        switch (status_code) {
        case 0:
            print_cards();
            printf("Square Rabbit!\n");
            break;
        case 1: //Both have square rabbit, push
            print_cards();
            break;
        case 2: //Deal with a dealer who has squarerabbit
            printf("Dealer has a Duck... Insurance? (y\\n): ");
            response = '\x00';
            while(response != 'y' && response != 'n')
                response = readchar(STDIN);
            if (response == 'y')
                pay_insurance();

            check_dealer_squarerabbit();
            if(!check_dealer_squarerabbit2() && check_player_squarerabbit(get_srabbit_game())) {
                print_cards();
                printf("Square Rabbit!\n");
                break;
            }
        case 3:
            while(print_cards() != 0) {
                response = readchar(STDIN);
                switch (response) {
                case 'H':
                    if (hit() < 0)
                        printf("INVALID CHOICE");
                    break;
                case 'S':
                    if (stand() < 0)
                        printf("INVALID CHOICE");
                    break;
                case 'D':
                    if (g_player.money < g_player.current_bet || double_down() < 0)
                        printf("CAN'T DOUBLE DOWN'");
                    break;
                case 'X':
                    if (g_player.money < g_player.current_bet || split() < 0)
                        printf("CAN'T SPLIT");
                    break;
                default:
                    printf("INVALID CHOICE");
                }
                printf("\n");
            }
        }

        g_player.money += srabbit_payout();
    }
}

void play_poker()
{
    return;
}

int main()
{
    char input[INPUT_SIZE];
    unsigned int seed = 0;

    printf("Enter a number greater than 0: ");
    if (readline(STDIN, input, INPUT_SIZE) != 0) {
        printf("INVALID INPUT\n");
        printf("Exiting...\n");
        return 0;
    }

    seed = strtol(input, NULL, 10);
    if (seed == 0) {
        printf("INVALID INPUT\n");
        printf("Exiting...\n");
        return 0;
    }

    printf("\n\n");
    printf("*************************\n");
    printf("*Welcome to Game Sultan!*\n");
    printf("*************************\n\n");

    init_player();
    init_squarerabbit(&seed);
    //init_poker();

    char choice = '0';
    while(choice != '2') {
        print_game_menu();
        choice = readchar(STDIN);
        switch(choice) {
        case '1':
            play_squarerabbit();
            break;
        case '2':
            //play_poker();
            break;
        case '3':
            //break;
        default:
            printf("Bad Choice. Select another option\n\n");
        }
    }

    printf("Thanks for playing!\n");
}

