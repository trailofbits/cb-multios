#ifndef VSQUARERABBIT_H
#define VSQUARERABBIT_H

#include "card.h"
#include "hand.h"
#include "deck.h"

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

void init_squarerabbit(unsigned int *seed);
squarerabbit_t *get_srabbit_game();
squarerabbit_t *get_split_hand();
int max_split();
int split_len();
int all_hands_busted();
int is_player_finished();
int calc_score(hand_t *srabbit_hand, int *is_soft);
int srabbit_payout();
int deal_srabbit(int bet);
void pay_insurance();
int check_player_squarerabbit(squarerabbit_t *srabbit);
int check_dealer_squarerabbit();
int check_dealer_squarerabbit2();
int hit();
int stand();
int double_down();
int can_split(squarerabbit_t *srabbit);
int split();
int dealer_hit();

#endif /* VSQUARERABBIT_H */
