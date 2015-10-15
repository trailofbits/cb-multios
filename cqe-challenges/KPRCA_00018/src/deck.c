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
#include "deck.h"

static unsigned int a=1234567890, b=2345678901, c=3456789012, d=4567890123; //d overflows, but it's okay
static unsigned int rng()
{
    unsigned int temp = a ^  (a << 7);
    a = b; b = c; c = d;
    return d = (d ^ (d >> 22)) ^ (temp ^ (temp >> 16));
}

void init_deck(deck_t *d, unsigned int *seed)
{
    if (seed != NULL)
        a = *seed;

    int i, j;
    for (i = 0; i < NUM_SUITS; i++) {
        for (j = 0; j < CARDS_PER_SUIT; j++) {
            d->cards[CARDS_PER_SUIT * i + j].face = j + 1;
            d->cards[CARDS_PER_SUIT * i + j].suit = i;
        }
    }

    d->top_of_deck = 0;
}

int shuffle_deck(deck_t *d)
{
    unsigned int i, pos1, pos2;
    unsigned int num_swaps = 10000;
    card_t temp_card;

    for (i = 0; i < num_swaps; i++) {
        pos1 = rng() % NUM_CARDS;
        pos2 = rng() % NUM_CARDS;

        temp_card = d->cards[pos1];
        d->cards[pos1] = d->cards[pos2];
        d->cards[pos2] = temp_card;
    }

    d->top_of_deck = 0;
    return TRUE;
}

int shuffle_deck_if_needed(deck_t *d)
{
    if (d->top_of_deck > RESHUFFLE_CARD) {
        if (!shuffle_deck(d))
            return -1;
        else
            return 1;
    }

    return 0;
}

card_t *draw_card(deck_t *d)
{
    return &d->cards[d->top_of_deck++];

}
