#include "card.h"

void print_card(card_t *card, char *append) {
    char *suit;

    switch (card->suit) {
        case 0:
            suit = "hearts";
            break;
        case 1:
            suit = "diamonds";
            break;
        case 2:
            suit = "spades";
            break;
        case 3:
            suit = "clover";
            break;
        default:
            break;
    }

    printf("%d of %s%s", card->number, suit, append);
}

int same_suit(card_t *a, card_t *b) {
    return a->suit == b->suit;
}
