#ifndef DECK_H
#define DECK_H

#include <stdlib.h>
#include "card.h"

card_t **init_deck();
card_t *take_card(card_t *card);
void put_card_back(card_t *card);

#endif
