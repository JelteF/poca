#include <stdio.h>
#include <stdlib.h>

#include "card.h"

typedef struct dealed_cards_t {
    card_t *my_hand[2];
    card_t *table[5];
    card_t *op_hand[2];
} dealed_cards_t;

