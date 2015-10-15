#ifndef HAND_H_
#define HAND_H_

#include "card.h"

typedef struct hand hand_t;
struct hand
{
    card_t *card;
    hand_t *next;
};

int get_card(hand_t **h, card_t *card);
int get_card_in_order(hand_t **h, card_t *card);
int replace_card(hand_t **h, card_t *new_card, card_t *old_card);
int remove_card(hand_t **h, card_t *card);
void discard_hand(hand_t **h);

#endif /* HAND_H_ */
