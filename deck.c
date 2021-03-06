#include "deck.h"

card_t **init_deck() {
    card_t **deck = calloc(52, sizeof(card_t*));

    for (int i = 0; i < 52; i++) {
        deck[i] = calloc(1, sizeof(card_t));
        deck[i]->suit = i / 13;
        deck[i]->number = i % 13;
    }

    return deck;
}

card_t *take_card(card_t *card) {
    if (card->dealed) {
        return NULL;
    }
    card->dealed = 1;
    return card;
}

void put_card_back(card_t *card) {
    card->dealed = 0;
}
