//
// Created by Davis Lee on 11/25/17.
//

#ifndef BLACKJACK_CARD_H
#define BLACKJACK_CARD_H
#include <string>
using namespace std;
#include <iostream>

class Card {

private:

    string cvalue;

    string csuit;

public:

    Card();

    Card(string value, string suit);

    string getSuit();

    string getValue();

    string toString();
};


#endif //BLACKJACK_CARD_H
