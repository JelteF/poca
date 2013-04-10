#include "evaluate.h"

card_t ***get_usable_cards(dealt_cards_t *dc) {
    card_t ***usable_cards = calloc(2, sizeof(card_t*));
    usable_cards[0] = calloc(7, sizeof(card_t*));
    usable_cards[1] = calloc(7, sizeof(card_t*));

    memcpy((void *) &usable_cards[0][2],
            (const void*) dc->table, 5*sizeof(card_t*));
    memcpy((void *) &usable_cards[1][2],
            (const void*) dc->table, 5*sizeof(card_t*));

    memcpy((void *) usable_cards[0],
            (const void*) dc->my_hand, 2*sizeof(card_t*));
    memcpy((void *) usable_cards[1],
            (const void*) dc->op_hand, 2*sizeof(card_t*));

    return usable_cards;
}
int evaluate_dealt_cards(dealt_cards_t *dc) {
    card_t ***usable_cards = get_usable_cards(dc);


    free(usable_cards[0]);
    free(usable_cards[1]);
    free(usable_cards);
    return 0;
}
