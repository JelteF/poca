#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <stdlib.h>

typedef struct card_t {
    int suit;
    int number;
} card_t;

void print_card(card_t *card);

#endif
