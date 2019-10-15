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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_squarerabbit.h"

#define INPUT_SIZE 512

typedef enum {MAIN_MENU, SQUARE_RABBIT } screen_select;
typedef struct {
    int money;
    int current_game;
    int current_bet;
} player_t;

//GLOBAL VARIABLES
static player_t g_player;

static char cgc_readchar(int fd)
{
    cgc_size_t rx;
    char c, delim;

    if (cgc_receive(fd, &c, 1, &rx) != 0 || rx == 0)
        return -1;
    if (cgc_receive(fd, &delim, 1, &rx) != 0 || rx == 0)
        return -1;

    if (delim != '\n')
        return -1;

    return c;
}

static int cgc_readline(int fd, char *buf, cgc_size_t size)
{
    cgc_size_t i;
    cgc_size_t rx;

    for (i = 0; i < size; i++) {
        if (cgc_receive(fd, buf, 1, &rx) != 0 || rx == 0)
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

static void cgc_init_player() {
    g_player.money = 100000;
    g_player.current_game = MAIN_MENU;
    g_player.current_bet = 0;
}

void cgc_print_game_menu()
{
    cgc_printf("Game Sultan: Main Menu\n");
    cgc_printf("1. Square Rabbit\n");
    cgc_printf("2. Quit\n\n");
    cgc_printf("Select:-@ ");

}

char *cgc_cardtos(card_t *card) {
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

char *cgc_suittos(card_t *card) {
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

static void cgc_print_winner(int player_score, int dealer_score) {
    if (player_score > 21)
        cgc_printf("  Busted! Better luck next time\n");
    else if (player_score > dealer_score || dealer_score > 21)
        cgc_printf("  Winner!\n");
    else if (player_score == dealer_score)
        cgc_printf("  Pushed.\n");
    else
        cgc_printf("  Dealer Wins.\n");
}

static int cgc_print_cards()
{
    int i = 1, dealer_score, player_score;
    card_t *card;
    squarerabbit_t *srabbit = cgc_get_srabbit_game();
    squarerabbit_t *split_hand = cgc_get_split_hand();
    hand_t *player = srabbit->player_hand;
    hand_t *dealer = srabbit->dealer_hand;
    player_score = cgc_calc_score(player, NULL);
    squarerabbit_t *split;

    if (!cgc_is_player_finished()) {
        card = srabbit->dealer_hand->card;
        cgc_printf("Dealer: |%s%s|?|\n", cgc_cardtos(card), cgc_suittos(card));
        cgc_printf("----------------\n");
    } else {
        cgc_dealer_hit();
        dealer_score = cgc_calc_score(dealer, NULL);
        cgc_printf("Dealer: |");
        while (dealer != NULL) {
            card = dealer->card;
            cgc_printf("%s%s|", cgc_cardtos(card), cgc_suittos(card));
            dealer = dealer->next;
        }
        cgc_printf("    Score: %d\n", dealer_score);
        cgc_printf("-------------------------------\n");
    }

    cgc_printf("Player: |");
    while (player != NULL) {
        card = player->card;
        cgc_printf("%s%s|", cgc_cardtos(card), cgc_suittos(card));
        player = player->next;
    }
    cgc_printf("    Score: %d\n", player_score);
    if (!srabbit->player_finished) {
        cgc_printf("Select (H/S");
        if (srabbit->double_or_split) {
            cgc_printf("/D");
            if (cgc_can_split(srabbit) && cgc_split_len() < cgc_max_split()) {
                cgc_printf("/X");
            }
        }
        cgc_printf("): ");
        return 1;
    } else {
        if (cgc_is_player_finished())
            cgc_print_winner(player_score, dealer_score);
    }

    for (i = 0; i < cgc_split_len(); i++) {
        split = &split_hand[i];
        player = split->player_hand;
        player_score = cgc_calc_score(player, NULL);
        cgc_printf("Split %d: |", i + 1);
        while (player != NULL) {
            card = player->card;
            cgc_printf("%s%s|", cgc_cardtos(card), cgc_suittos(card));
            player = player->next;
        }
        cgc_printf("    Score: %d\n", player_score);
        if (!split->player_finished) {
            cgc_printf("Select (H/S");
            if (split->double_or_split) {
                cgc_printf("/D");
                if (cgc_can_split(split) && cgc_split_len() < cgc_max_split()) {
                    cgc_printf("/X");
                }
            }
            cgc_printf("): ");
            return 1;
        } else {
            if (cgc_is_player_finished())
                cgc_print_winner(player_score, dealer_score);
        }
    }

    return 0;
}

void cgc_play_squarerabbit()
{
    int quit = FALSE;
    int bet;
    int status_code;
    char response = 0;
    char input[INPUT_SIZE];

    cgc_printf("******************\n");
    cgc_printf("* Square Rabbit! *\n");
    cgc_printf("******************\n");
    while (!quit) {
        cgc_printf("Total Money: $%d\n", g_player.money);
        cgc_printf("\nType QUIT to exit to main menu\n");
        cgc_printf("Place Bet (100, 200, 500, 1000): ");
        if (cgc_readline(STDIN, input, INPUT_SIZE) != 0)
            continue;

        if (cgc_memcmp(input, "QUIT", sizeof("QUIT")) == 0)
            return;

        bet = cgc_strtol(input, NULL, 10);
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
            cgc_printf("Bad Bet\n\n");
            continue;
        }

        if (g_player.current_bet > g_player.money) {
            cgc_printf("Not enough money, bet with a lower amount\n");
            continue;
        }

        status_code = cgc_deal_srabbit(g_player.current_bet);
        switch (status_code) {
        case 0:
            cgc_print_cards();
            cgc_printf("Square Rabbit!\n");
            break;
        case 1: //Both have square rabbit, push
            cgc_print_cards();
            break;
        case 2: //Deal with a dealer who has squarerabbit
            cgc_printf("Dealer has a Duck... Insurance? (y\\n): ");
            response = '\x00';
            while(response != 'y' && response != 'n')
                response = cgc_readchar(STDIN);
            if (response == 'y')
                cgc_pay_insurance();

            cgc_check_dealer_squarerabbit();
            if(!cgc_check_dealer_squarerabbit2() && cgc_check_player_squarerabbit(cgc_get_srabbit_game())) {
                cgc_print_cards();
                cgc_printf("Square Rabbit!\n");
                break;
            }
        case 3:
            while(cgc_print_cards() != 0) {
                response = cgc_readchar(STDIN);
                switch (response) {
                case 'H':
                    if (cgc_hit() < 0)
                        cgc_printf("INVALID CHOICE");
                    break;
                case 'S':
                    if (cgc_stand() < 0)
                        cgc_printf("INVALID CHOICE");
                    break;
                case 'D':
                    if (g_player.money < g_player.current_bet || cgc_double_down() < 0)
                        cgc_printf("CAN'T DOUBLE DOWN'");
                    break;
                case 'X':
                    if (g_player.money < g_player.current_bet || cgc_split() < 0)
                        cgc_printf("CAN'T SPLIT");
                    break;
                default:
                    cgc_printf("INVALID CHOICE");
                }
                cgc_printf("\n");
            }
        }

        g_player.money += cgc_srabbit_payout();
    }
}

void cgc_play_poker()
{
    return;
}

int main(int cgc_argc, char *cgc_argv[])
{
    char input[INPUT_SIZE];
    unsigned int seed = 0;

    cgc_printf("Enter a number greater than 0: ");
    if (cgc_readline(STDIN, input, INPUT_SIZE) != 0) {
        cgc_printf("INVALID INPUT\n");
        cgc_printf("Exiting...\n");
        return 0;
    }

    seed = cgc_strtol(input, NULL, 10);
    if (seed == 0) {
        cgc_printf("INVALID INPUT\n");
        cgc_printf("Exiting...\n");
        return 0;
    }

    cgc_printf("\n\n");
    cgc_printf("*************************\n");
    cgc_printf("*Welcome to Game Sultan!*\n");
    cgc_printf("*************************\n\n");

    cgc_init_player();
    cgc_init_squarerabbit(&seed);
    //init_poker();

    char choice = '0';
    while(choice != '2') {
        cgc_print_game_menu();
        choice = cgc_readchar(STDIN);
        switch(choice) {
        case '1':
            cgc_play_squarerabbit();
            break;
        case '2':
            //play_poker();
            break;
        case '3':
            //break;
        default:
            cgc_printf("Bad Choice. Select another option\n\n");
        }
    }

    cgc_printf("Thanks for playing!\n");
}

