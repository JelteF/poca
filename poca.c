#include "poca.h"

card_t **init_deck() {
    card_t **deck = calloc(52, sizeof(card_t*));
    for (int i = 0; i < 52; i++) {
        deck[i] = calloc(1, sizeof(card_t));
        deck[i]->suit = i / 13;
        deck[i]->number = i % 13;
        print_card(deck[i]);
    }
}



int main(int argc, char *argv[]) {
    card_t **deck = init_deck();
}
