#include "card.h"

void print_card(card_t *card) {
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

    printf("%d of %s\n", card->number, suit);
}

