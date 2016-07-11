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

#include "squarerabbit.h"

#define MAX_SPLIT 2

// Global Variables
static squarerabbit_t *g_srabbit;
static squarerabbit_t split_hand[MAX_SPLIT];

static void clear_squarerabbit(squarerabbit_t *srabbit)
{
    discard_hand(&srabbit->dealer_hand);
    discard_hand(&srabbit->player_hand);
    srabbit->current_bet = 0;
    srabbit->paid_insurance = 0;
    srabbit->player_finished = FALSE;
    srabbit->double_or_split = TRUE;
    srabbit->busted = FALSE;
    srabbit->split_len = 0;
}

static void clear_split_squarerabbit()
{
    int i;
    squarerabbit_t *temp;

    for (i = 0; i < split_len(); i++) {
        temp = &split_hand[i];
        temp->dealer_hand = NULL;
        clear_squarerabbit(temp);
    }
}


static void new_srabbit_game(bet)
{
    clear_split_squarerabbit();
    clear_squarerabbit(g_srabbit);
    g_srabbit->current_bet = bet;
    shuffle_deck_if_needed(g_srabbit->deck);
}

static int dealer_has_duck() {
    hand_t *dealer = g_srabbit->dealer_hand;
    if (dealer->card->face == DUCK)
        return TRUE;
    else
        return FALSE;
}

void init_squarerabbit(unsigned int *seed)
{
    g_srabbit = malloc(sizeof(squarerabbit_t));
    g_srabbit->deck = malloc(sizeof(deck_t));
    g_srabbit->dealer_hand = NULL;
    g_srabbit->player_hand = NULL;
    g_srabbit->current_bet = 0;
    g_srabbit->paid_insurance = 0;
    g_srabbit->player_finished = FALSE;
    g_srabbit->double_or_split = TRUE;
    g_srabbit->busted = FALSE;
    g_srabbit->split_len = 0;

    init_deck(g_srabbit->deck, seed);
    shuffle_deck(g_srabbit->deck);
}

squarerabbit_t *get_srabbit_game()
{
    return g_srabbit;
}

squarerabbit_t *get_split_hand()
{
    return split_hand;
}

int max_split()
{
    return MAX_SPLIT;
}

int split_len()
{
    return (g_srabbit->split_len > MAX_SPLIT) ? MAX_SPLIT : g_srabbit->split_len;
}


int all_hands_busted()
{
    int i;
    squarerabbit_t *temp = g_srabbit;
    if (temp->busted == FALSE)
        return FALSE;
    for (i = 0; i < split_len(); i++) {
        temp = &split_hand[i];
        if (temp->busted == FALSE)
            return FALSE;
    }

    return TRUE;
}

int is_player_finished()
{
    int i;
    squarerabbit_t *temp = g_srabbit;
    if (temp->player_finished == FALSE)
        return FALSE;
    for (i = 0; i < split_len(); i++) {
        temp = &split_hand[i];
        if (temp->player_finished == FALSE)
            return FALSE;
    }

    return TRUE;
}

int calc_score(hand_t *srabbit_hand, int *is_soft) {
    int score = 0;
    int num_ducks = 0;
    while (srabbit_hand != NULL) {
        switch (srabbit_hand->card->face) {
            case DUCK:
                num_ducks++;
                score += 1;
                break;
            case RABBIT:
            case BEE:
            case LION:
                score += 10;
                break;
            default:
                score += srabbit_hand->card->face;
        }

        srabbit_hand = srabbit_hand->next;
    }

    if (score <= 11 && num_ducks) {
        score += 10;
        if (is_soft != NULL)
            *is_soft = TRUE;
    } else {
        if (is_soft != NULL)
            *is_soft = FALSE;
    }

    return score;
}

int srabbit_payout()
{
    int i = 0;
    squarerabbit_t *srabbit = g_srabbit;
    int dealer_score = calc_score(srabbit->dealer_hand, NULL), player_score;
    int winnings = 0;

    if (check_dealer_squarerabbit() && calc_score(srabbit->player_hand, NULL) != 21) {
        winnings = (srabbit->current_bet * -1) + srabbit->paid_insurance * 2;
        return winnings;
    }

    winnings -= srabbit->paid_insurance;

    player_score = calc_score(srabbit->player_hand, NULL);
    if (check_player_squarerabbit(srabbit) && dealer_score != 21)
        winnings += (srabbit->current_bet * 3) / 2;
    else if (srabbit->busted)
        winnings -= srabbit->current_bet;
    else if (dealer_score > 21)
        winnings += srabbit->current_bet;
    else if (dealer_score > player_score)
        winnings -= srabbit->current_bet;
    else if (dealer_score < player_score)
        winnings += srabbit->current_bet;

    for (i = 0; i < split_len(); i++) {
        srabbit = &split_hand[i];
        player_score = calc_score(srabbit->player_hand, NULL);
        if (check_player_squarerabbit(srabbit) && dealer_score != 21)
            winnings += (srabbit->current_bet * 3) / 2;
        else if (srabbit->busted)
            winnings -= srabbit->current_bet;
        else if (dealer_score > 21)
            winnings += srabbit->current_bet;
        else if (dealer_score > player_score)
            winnings -= srabbit->current_bet;
        else if (dealer_score < player_score)
            winnings += srabbit->current_bet;
    }

    return winnings;
}

int deal_srabbit(int bet)
{
    int i;

    squarerabbit_t *srabbit = g_srabbit;
    new_srabbit_game(bet);
    for (i = 0; i < 2; i++) {
        if (get_card(&g_srabbit->player_hand, draw_card(g_srabbit->deck)) != 0 ||
            get_card(&g_srabbit->dealer_hand, draw_card(g_srabbit->deck)) != 0) {
            return -1;  // Couldn't get cards from the deck
        }
    }

    if (calc_score(srabbit->player_hand, NULL) == 21 && calc_score(srabbit->dealer_hand, NULL) == 21) {
        srabbit->player_finished = TRUE;
        return 1; //PUSH
    } else if (dealer_has_duck()) {
        return 2; //Check for insurance
    } else if (calc_score(srabbit->player_hand, NULL) == 21) {
        srabbit->player_finished = TRUE;
        return 0; //Square Rabbit!
    } else if (calc_score(srabbit->player_hand, NULL) == 21) {
        srabbit->player_finished = TRUE;
        return 0; //Square Rabbit!
    } else {
        return 3; //Choose to hit or stand
    }
}

void pay_insurance()
{
    squarerabbit_t *srabbit = g_srabbit;

    g_srabbit->paid_insurance = srabbit->current_bet / 2;
}

int check_player_squarerabbit(squarerabbit_t *srabbit)
{
    hand_t *player = srabbit->player_hand;
    int score = calc_score(player, NULL);
    if (score == 21 && player->next->next == NULL) {
        srabbit->player_finished = TRUE;
        return TRUE;
    }

    return FALSE;
}

int check_dealer_squarerabbit()
{
    hand_t *dealer = g_srabbit->dealer_hand;
    if (dealer->card->face != DUCK)
        return FALSE; // Bad Logic. We should have never called this funciton

    dealer = dealer->next;
    switch (dealer->card->face) {
        case TEN:
        case RABBIT:
        case BEE:
        case LION:
            g_srabbit->player_finished = TRUE;
            return TRUE;
        default:
            return FALSE;
   }
}

int check_dealer_squarerabbit2()
{
    hand_t *dealer= g_srabbit->dealer_hand;
    int score = calc_score(dealer, NULL);
    if (score == 21 && dealer->next->next == NULL) {
        return TRUE;
    }

    return FALSE;
}

int hit()
{
    squarerabbit_t *srabbit = g_srabbit;
    int score = 0;
    int i = 0;

    while (srabbit->player_finished && i < split_len())
        srabbit = &split_hand[i++];

    if (get_card(&srabbit->player_hand, draw_card(srabbit->deck)) != 0)
        return -1;

    score = calc_score(srabbit->player_hand, NULL);
    if (score > 21) {
        srabbit->player_finished = TRUE;
        srabbit->busted = TRUE;
    }

    srabbit->double_or_split = FALSE;
    return score;
}


int stand()
{
    int i = 0;
    squarerabbit_t *srabbit = g_srabbit;
    while (srabbit->player_finished && i < split_len())
        srabbit = &split_hand[i++];

    srabbit->player_finished = TRUE;
    return calc_score(srabbit->player_hand, NULL);
}

int double_down()
{
    int i = 0;
    squarerabbit_t *srabbit = g_srabbit;
    int score = 0;

    while (srabbit->player_finished && i < split_len())
        srabbit = &split_hand[i++];

    if (!srabbit->double_or_split)
        return -1;  //Can only double on the first hit

    score = hit();
    srabbit->player_finished = TRUE;
    srabbit->current_bet *= 2;
    return score;
}

int can_split(squarerabbit_t *srabbit)
{
    if (srabbit->player_hand->card->face != srabbit->player_hand->next->card->face &&
       (srabbit->player_hand->card->face < TEN || srabbit->player_hand->next->card->face < TEN)) {
        return FALSE; //Can only split cards that have identical value
    }

    return TRUE;
}

//split
int split()
{
    int i = 0;
    squarerabbit_t *srabbit = g_srabbit;

    while (srabbit->player_finished && i < split_len())
        srabbit = &split_hand[i++];

    if (!srabbit->double_or_split || !can_split(srabbit))
        return -1;  //Can only split or double on the first hit
#ifdef PATCHED
    if (g_srabbit->split_len >= MAX_SPLIT)
        return -1;
    g_srabbit->split_len++;
#else
    if (g_srabbit->split_len++ >= MAX_SPLIT)
        return -1;
#endif

    i = g_srabbit->split_len - 1;
    squarerabbit_t *split_srabbit = &split_hand[i];
    split_srabbit->deck = srabbit->deck;
    split_srabbit->dealer_hand = srabbit->dealer_hand;
    split_srabbit->player_hand = NULL;
    split_srabbit->current_bet = srabbit->current_bet;
    split_srabbit->paid_insurance = 0;
    split_srabbit->player_finished = FALSE;
    split_srabbit->double_or_split = TRUE;
    split_srabbit->busted = FALSE;

    if (get_card(&split_srabbit->player_hand, srabbit->player_hand->next->card) != 0)
        goto error;

    if (remove_card(&srabbit->player_hand, srabbit->player_hand->next->card) != 0)
        goto error;

    if (get_card(&srabbit->player_hand, draw_card(srabbit->deck)) != 0)
        goto error;

    if (get_card(&split_srabbit->player_hand, draw_card(split_srabbit->deck)) != 0)
        goto error;

    return 0;

error:
    return -1;
}

int dealer_hit()
{
    int score = 0;
    int is_soft = FALSE;
    if (!g_srabbit->player_finished)
        return -1;  // Dealer should only ever hit after all players are done

    score = calc_score(g_srabbit->dealer_hand, &is_soft);
    if (all_hands_busted())
        return score;

    if (check_player_squarerabbit(g_srabbit) && split_len() == 0)
        return score;

    while(score <= 17) {
        if (score == 17 && !is_soft)
            break;

        if (get_card(&g_srabbit->dealer_hand, draw_card(g_srabbit->deck)) != 0)
            return -1;

        score = calc_score(g_srabbit->dealer_hand, &is_soft);
    }

    return score;
}

