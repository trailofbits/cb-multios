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
#include "hand.h"

int get_card(hand_t **h, card_t *card)
{
    if (card == NULL)
        return -1;

    hand_t *drawn_card = malloc(sizeof(hand_t));
    hand_t *temp = *h;
    drawn_card->card = card;
    drawn_card->next = NULL;

    if (*h == NULL) {
        *h = drawn_card;
    } else {
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = drawn_card;
    }

    return 0;
}

int get_card_in_order(hand_t **h, card_t *card)
{
    if (card == NULL)
        return -1;

    hand_t *drawn_card = malloc(sizeof(hand_t));
    hand_t *temp = *h, *prev;
    drawn_card->card = card;
    drawn_card->next = NULL;

    if (*h == NULL) {
        *h = drawn_card;
    } else {
        while (temp != NULL) {
            if (drawn_card->card->face < temp->card->face) {
                drawn_card->next = temp;
                if (temp == *h)
                    *h = drawn_card;
                return 0;
            }
            prev = temp;
            temp = temp->next;
        }
        prev->next = drawn_card;
    }

    return 0;
}

int replace_card(hand_t **h, card_t *new_card, card_t *old_card)
{
    if (*h == NULL)
        return -1;

    hand_t *temp = *h;
    while (temp != NULL) {
        if(temp->card == old_card) {
            temp->card = new_card;
            return 0;
        }
        temp = temp->next;
    }

    return -1;
}

int remove_card(hand_t **h, card_t *card)
{
    if (*h == NULL)
        return -1;

    hand_t *temp = *h;
    hand_t *prev = *h;
    while (temp != NULL) {
        if(temp->card->face == card->face && temp->card->suit == card->suit) {
            if (*h == temp)
                *h = temp->next;
            else
                prev->next = temp->next;
            free(temp);
            return 0;
        }
        prev = temp;
        temp = temp->next;
    }

    return -1;
}

void discard_hand(hand_t **h)
{
    if (*h == NULL)
        return;

    hand_t *temp, *temp_h = *h;
    while (temp_h->next != NULL) {
        temp = temp_h;
        temp_h = temp_h->next;
        free(temp);
    }
    free(temp_h);
    *h = NULL;
}
