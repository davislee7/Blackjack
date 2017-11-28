//
// Created by Davis Lee on 11/25/17.
//

#ifndef BLACKJACK_DECK_H
#define BLACKJACK_DECK_H

#include "Card.h"

class Deck {
private:
    int place;
    Card myDeck[52];

public:
    Deck();
    void shuffle();
    Card deal();
};


#endif //BLACKJACK_DECK_H
