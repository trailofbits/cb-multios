#ifndef CARD_H_
#define CARD_H_

#define FALSE 0
#define TRUE 1

typedef enum { WILD, DUCK, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, RABBIT, BEE, LION } card_face_e;
typedef enum { SQUARE, TRIANGLE, CIRCLE, PENTAGON } card_suit_e;

typedef struct card
{
    card_face_e face;
    card_suit_e suit;
} card_t;

#endif /* CARD_H_ */
