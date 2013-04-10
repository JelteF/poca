#include "poca.h"

void print_hand(card_t **hand) {
    print_card(hand[0], ", ");
    print_card(hand[1], "\n");
}


void print_dealt_cards(dealt_cards_t *dc) {
    printf("Your hand: ");
    print_hand(dc->my_hand);

    printf("The table: ");
    for (int i = 0; i < 4; i++) {
        print_card(dc->table[i], ", ");
    }
    print_card(dc->table[4], "\n");

    printf("Opponents hand: ");
    print_hand(dc->op_hand);
    printf("\n");
}

/*
 * Add the src wl to dest wl and multiply it when needed. This is needed when
 * the last suit is used.
 */
void merge_wl(win_loss_t *dest, win_loss_t *src, int multi, int i) {
    // check if it should be multiplied
    if (multi > 1 && i > 52 - 13 * multi) {
        multi = 1;
    }

    dest->wins += src->wins * multi;
    dest->losses += src->losses * multi;
}

win_loss_t deal_oponent(dealt_cards_t *dc, card_t **deck) {
    win_loss_t op_wl = {0};
    int max_first = 52;
    int multi_first = 1;
    int max_second = 52;
    int multi_second = 1;

    for (int i = 0; i < max_first; i++) {
        win_loss_t second_wl = {0};
        if (!dc->op_hand[0]) continue;

        for (int j = 0; j < max_first; j++) {
            int winner;

            dc->op_hand[1] = take_card(deck[j]);
            if (!dc->op_hand[1]) continue;

            winner = evaluate_dealt_cards(dc);

            if (winner == 1) {
                second_wl.wins += multi_second;
            }
            else if (winner == 2) {
                second_wl.losses += multi_second;
            }
            put_card_back(dc->op_hand[1]);
        }

        merge_wl(&op_wl, &second_wl, multi_first, i);
        put_card_back(dc->op_hand[0]);
    }

    return op_wl;
}


win_loss_t deal_river(dealt_cards_t *dc, card_t **deck) {
    win_loss_t river_wl = {0};
    int max_river = 52;
    int multi_river = 1;

    for (int i = 0; i < max_river; i++) {
        win_loss_t op_wl;

        dc->table[4] = take_card(deck[i]);
        if (!dc->table[4]) continue;

        op_wl = deal_oponent(dc, deck);

        merge_wl(&river_wl, &op_wl, multi_river, i);

        put_card_back(dc->table[4]);
    }
    return river_wl;
}

win_loss_t deal_turn(dealt_cards_t *dc, card_t **deck) {
    win_loss_t turn_wl = {0};
    int max_turn = 52;
    int multi_turn = 1;

    for (int i = 0; i < max_turn; i++) {
        win_loss_t river_wl;

        dc->table[3] = take_card(deck[i]);
        if (!dc->table[3]) continue;

        river_wl = deal_river(dc, deck);

        merge_wl(&turn_wl, &river_wl, multi_turn, i);
        put_card_back(dc->table[3]);
    }
    return turn_wl;
}

win_loss_t deal_flop(dealt_cards_t *dc, card_t **deck) {
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
        if (!dc->table[0]) continue;

        // When the first card is the same suit as one of the cards in hand,
        // both other cards get the max and multi of the one before them
        if (same_suit(dc->my_hand[1], deck[i]) ||
                    same_suit(dc->my_hand[0], deck[i])) {
            max_third = max_second;
            max_second = max_first;
            multi_third = multi_second;
            multi_second = multi_first;
        }
        else {
            max_second = min(max_first + 13, 52);
            max_third = min(max_second + 13, 52);
            multi_second = 4 - max_second/13;
            multi_third = 4 - max_third/13;
        }

        for (int j = i + 1; j < max_second; j++) {
            win_loss_t third_wl = {0};

            // skip similar combinations
            if (j == max_first) {
                j += i % 13;
            }

            dc->table[1] = take_card(deck[j]);
            if (!dc->table[1]) continue;

            if (same_suit(dc->my_hand[1], deck[j]) ||
                        same_suit(dc->my_hand[0], deck[j]) ||
                        same_suit(deck[i], deck[j])) {
                max_third = max_second;
                multi_third = multi_second;
            }
            else {
                max_third = min(max_second + 13, 52);
                multi_third = 4 - max_third/13;
            }



            for (int k = j + 1; k < max_third; k++) {
                win_loss_t turn_wl;

                if (k == max_second) {
                    k += j % 13;
                }
                dc->table[2] = take_card(deck[k]);
                if (!dc->table[2]) continue;

                turn_wl = deal_turn(dc, deck);

                merge_wl(&third_wl, &turn_wl, max_third, k);

                put_card_back(dc->table[2]);
            }

            if (j == 25) {
                //printf("%d, %d, %d\n", max_first, max_second, max_third);
                printf("%d, %d, %d\n", multi_first, multi_second, multi_third);
                print_dealt_cards(dc);
            }
            merge_wl(&second_wl, &third_wl, max_second, j);

            put_card_back(dc->table[1]);

        }

        merge_wl(&flop_wl, &second_wl, max_first, i);
        put_card_back(dc->table[0]);
    }

    return flop_wl;
}

/*
 * It doesn't matter for the first hand what cards have been pulled, only if
 * they are the same suit or not.
 * Order also doesn't matter, we make sure the second card is never a lower
 * card than the first.
 */
int deal_my_hand(dealt_cards_t *dc, card_t **deck) {
    win_loss_t full_wl[13];

    for (int i = 0; i < 13; i++) {

        dc->my_hand[0] = take_card(deck[i]);
        if (!dc->my_hand[0]) continue;

        for (int j = i + 1; j < 26; j++) {
            win_loss_t flop_wl;

            // skip similar combinations
            if (j == 13) {
                j += i;
            }

            dc->my_hand[1] = take_card(deck[j]);
            if (!dc->my_hand[1]) continue;


            flop_wl = deal_flop(dc, deck);

            merge_wl(&full_wl[i], &flop_wl, 1, 0);

            put_card_back(dc->my_hand[1]);
        }

        put_card_back(dc->my_hand[0]);
    }
}


void start_game(card_t **deck) {
    dealt_cards_t *dc = calloc(1, sizeof(dealt_cards_t));

    dc->my_hand[0] = deck[35];
    dc->my_hand[1] = deck[36];
    dc->table[0] = deck[30];
    dc->table[1] = deck[29];
    dc->table[2] = deck[28];
    dc->table[3] = deck[26];
    dc->table[4] = deck[25];
    dc->op_hand[0] = deck[13];
    dc->op_hand[1] = deck[12];

    print_dealt_cards(dc);
    deal_my_hand(dc, deck);
}


int main(int argc, char *argv[]) {
    card_t **deck = init_deck();

    start_game(deck);

    return 0;
}
