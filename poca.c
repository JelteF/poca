#include "poca.h"

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


win_loss_t *deal_flop(dealed_cards_t *dc, card_t **deck) {
    win_loss_t *win_loss;
    int max_first = 39;
    int max_second = 52;
    int max_third = 52;
    int multi_first = 2;
    int multi_second = 1;
    int multi_third = 1;

    if (same_suit(dc->my_hand[0], dc->my_hand[1])) {
        max_first = 26;
        max_second = 39;
    }

    for (int i = 0; i < max_first; i++) {
        dc->table[0] = take_card(deck[i]);
        for (int j = i; j < max_second; j++) {
            dc->table[1] = take_card(deck[j]);
            for (int k = j; k < max_second; k++) {
                dc->table[2] = take_card(deck[k]);
            }
        }
    }

    return win_loss;
}

int deal_my_hand(dealed_cards_t *dc, card_t **deck) {
    for (int i = 0; i < 13; i++) {
        dc->my_hand[0] = take_card(deck[i]);

        for (int j = i + 1; j < 26; j++) {

            // skip similar combinations
            if (j == 13) {
                j += i;
            }

            dc->my_hand[1] = take_card(deck[j]);

            win_loss_t *win_loss = deal_flop(dc, deck);
        }
    }
}


void start_game(card_t **deck) {
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

    start_game(deck);

    return 0;
}
