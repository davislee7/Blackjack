//
// Created by Davis Lee on 11/25/17.
// Deck object header

#ifndef BLACKJACK_DECK_H
#define BLACKJACK_DECK_H

#include "Card.h"


class Deck {
private:
    //Tracks position in deck of next undealt card
    int place;

    //Array holds 52 card deck
    Card myDeck[52];

public:
    //Constructs deck with four suits C D H S
    //13 values 2-10, J, Q, K, A
    Deck();

    //Returns current place in deck
    int getPlace();

    //Shuffle deck by swapping each card with another card at a random index
    //Random number generated with seed based on current time
    void shuffle();

    //Deals one card
    Card deal();
};


#endif //BLACKJACK_DECK_H
