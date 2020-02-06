#ifndef VSQUARERABBIT_H
#define VSQUARERABBIT_H

#include "cgc_card.h"
#include "cgc_hand.h"
#include "cgc_deck.h"

typedef struct squarerabbit squarerabbit_t;
struct squarerabbit {
    deck_t *deck;
    hand_t *dealer_hand;
    hand_t *player_hand;
    int current_bet;
    int paid_insurance;
    char player_finished;
    char double_or_split;
    char busted;

    char split_len;
};

void cgc_init_squarerabbit(unsigned int *seed);
squarerabbit_t *cgc_get_srabbit_game();
squarerabbit_t *cgc_get_split_hand();
int cgc_max_split();
int cgc_split_len();
int cgc_all_hands_busted();
int cgc_is_player_finished();
int cgc_calc_score(hand_t *srabbit_hand, int *is_soft);
int cgc_srabbit_payout();
int cgc_deal_srabbit(int bet);
void cgc_pay_insurance();
int cgc_check_player_squarerabbit(squarerabbit_t *srabbit);
int cgc_check_dealer_squarerabbit();
int cgc_check_dealer_squarerabbit2();
int cgc_hit();
int cgc_stand();
int cgc_double_down();
int cgc_can_split(squarerabbit_t *srabbit);
int cgc_split();
int cgc_dealer_hit();

#endif /* VSQUARERABBIT_H */
