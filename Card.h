//
// Created by Davis Lee on 11/25/17.
// Card object header

#ifndef BLACKJACK_CARD_H
#define BLACKJACK_CARD_H

#include <string>

using namespace std;

#include <iostream>

class Card {

private:

    //Card value
    string cvalue;

    //Card suit
    string csuit;

public:
    //Default constructor constructs invalid card that needs to be assigned value and suit
    Card();

    //Alternate constructor with proper value and suit
    //Assumes proper input to improve efficiency
    Card(string value, string suit);

    //Gets suit
    string getSuit();

    //Gets value
    string getValue();

    //Converts card contents to string
    string toString();
};


#endif //BLACKJACK_CARD_H
