#include "poca.h"

card_t **init_deck() {
    card_t **deck = calloc(52, sizeof(card_t*));

    for (int i = 0; i < 52; i++) {
        deck[i] = calloc(1, sizeof(card_t));
        deck[i]->suit = i / 13;
        deck[i]->number = i % 13;
    }

    return deck;
}
void print_hand(card_t **hand) {
    print_card(hand[0], ", ");
    print_card(hand[1], "\n");
}


void print_dealed_cards(dealed_cards_t *dealed_cards) {
    printf("Your hand: ");
    print_hand(dealed_cards->my_hand);

    printf("The table: ");
    for (int i = 0; i < 4; i++) {
        print_card(dealed_cards->table[i], ", ");
    }
    print_card(dealed_cards->table[4], "\n");

    printf("Opponents hand: ");
    print_hand(dealed_cards->op_hand);
}

void deal_cards(card_t **deck) {
    dealed_cards_t *dealed_cards = calloc(1, sizeof(dealed_cards_t));

    dealed_cards->my_hand[0] = deck[35];
    dealed_cards->my_hand[1] = deck[36];
    dealed_cards->table[0] = deck[30];
    dealed_cards->table[1] = deck[29];
    dealed_cards->table[2] = deck[28];
    dealed_cards->table[3] = deck[26];
    dealed_cards->table[4] = deck[25];
    dealed_cards->op_hand[0] = deck[13];
    dealed_cards->op_hand[1] = deck[12];

    print_dealed_cards(dealed_cards);
}


int main(int argc, char *argv[]) {
    card_t **deck = init_deck();


    deal_cards(deck);

    return 0;
}
