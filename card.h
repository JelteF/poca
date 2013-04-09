#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <stdlib.h>

typedef struct card_t {
    int suit;
    int number;
    short dealed;
} card_t;

void print_card(card_t *card, char *append);
int same_suit(card_t *a, card_t *b);

#endif
