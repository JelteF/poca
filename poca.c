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

/*
 * Add the src wl to dest wl and multiply it when needed. This is needed when
 * the last suit is used.
 */
void merge_wl(win_loss_t *dest, win_loss_t *src, int multi, int i) {
    // check if it should be multiplied
    if (multi > 1 && i < 52 - 13 * multi) {
        multi = 1;
    }

    dest->wins += src->wins * multi;
    dest->losses += src->losses * multi;
}

win_loss_t deal_turn(dealed_cards_t *dc, card_t **deck) {
    win_loss_t turn_wl = {0};
    return turn_wl;
}

win_loss_t deal_flop(dealed_cards_t *dc, card_t **deck) {
    win_loss_t flop_wl = {0};
    int max_first = 39;
    int max_second = 52;
    int max_third = 52;
    int multi_first = 2;
    int multi_second = 1;
    int multi_third = 1;

    // When there is a pair in hand, one less suit has to be used in both the
    // first and second card
    if (same_suit(dc->my_hand[0], dc->my_hand[1])) {
        max_first = 26;
        max_second = 39;
        multi_first = 3;
        multi_second = 2;
    }

    for (int i = 0; i < max_first; i++) {
        win_loss_t second_wl = {0};

        dc->table[0] = take_card(deck[i]);

        // When the first card is the same suit as one of the cards in hand,
        // both other cards get the max and multi of the one before them
        if (same_suit(dc->my_hand[1], deck[i]) ||
                    same_suit(dc->my_hand[0], deck[i])) {
            max_third = max_second;
            max_second = max_first;
            multi_third = multi_second;
            multi_second = multi_first;
        }

        for (int j = i; j < max_second; j++) {
            win_loss_t third_wl = {0};

            // skip similar combinations
            if (j == max_first) {
                j += i % 13;
            }

            dc->table[1] = take_card(deck[j]);

            for (int k = j; k < max_third; k++) {
                win_loss_t turn_wl;

                if (k == max_second) {
                    k += j % 13;
                }
                dc->table[2] = take_card(deck[k]);

                turn_wl = deal_turn(dc, deck);

                merge_wl(&third_wl, &turn_wl, max_third, k);
            }

            merge_wl(&second_wl, &third_wl, max_second, j);

        }

        merge_wl(&flop_wl, &second_wl, max_first, i);
    }

    return flop_wl;
}

/*
 * It doesn't matter for the first hand what cards have been pulled, only if
 * they are the same suit or not.
 * Order also doesn't matter, we make sure the second card is never a lower
 * card than the first.
 */
int deal_my_hand(dealed_cards_t *dc, card_t **deck) {
    win_loss_t full_wl[13];

    for (int i = 0; i < 13; i++) {

        dc->my_hand[0] = take_card(deck[i]);

        for (int j = i + 1; j < 26; j++) {
            win_loss_t flop_wl;

            // skip similar combinations
            if (j == 13) {
                j += i;
            }

            dc->my_hand[1] = take_card(deck[j]);

            flop_wl = deal_flop(dc, deck);

            merge_wl(&full_wl[i], &flop_wl, 1, 0);
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
