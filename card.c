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

// src: http://p2p.wrox.com/visual-c/66347-quick-sort-c-code.html#post66347
void q_sort(card_t **cards, int left, int right) {
    int pivot = cards[left]->number;
    int l_hold = left;
    int r_hold = right;

    while (left < right) {
        while ((cards[right]->number >= pivot) && (left < right)) {
            right--;
        }

        if (left != right) {
            cards[left] = cards[right];
            left++;
        }

        while ((cards[left]->number <= pivot) && (left < right)) {
            left++;
        }

        if (left != right) {
            cards[right] = cards[left];
        }

    }
}

void sort_cards(card_t **cards, int length) {
    q_sort(cards, 0, length - 1);
}

void print_card_array(card_t **cards, int length) {
    for (int i = 0; i < length - 1; i++) {
        print_card(cards[i], ", ");
    }

    print_card(cards[length - 1], "\n");
}

int same_suit(card_t *a, card_t *b) {
    return a->suit == b->suit;
}
