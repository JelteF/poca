#ifndef POCA_H
#define POCA_H

#include <stdio.h>
#include <stdlib.h>

#include "card.h"
#include "deck.h"

typedef struct dealt_cards_t {
    card_t *my_hand[2];
    card_t *table[5];
    card_t *op_hand[2];
} dealt_cards_t;

#include "evaluate.h"


typedef struct win_loss_t {
    long wins;
    long losses;
} win_loss_t;

#define min(a,b) \
    ({ __typeof__ (a) _a = (a); \
     __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define max(a,b) \
    ({ __typeof__ (a) _a = (a); \
     __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#endif
