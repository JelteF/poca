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
void print_card_array(card_t **cards, int length);

int same_suit(card_t *a, card_t *b);

#endif
