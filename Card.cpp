//
// Created by Davis Lee on 11/25/17.
//

#include "Card.h"

Card::Card() {
    cvalue = "0";
    csuit = "?";
}

Card::Card(string value, string suit){
        cvalue = value;
        csuit = suit;
}

string Card::getSuit() {
    return csuit;
}

string Card::getValue() {
    return cvalue;
}

string Card::toString() {
    return cvalue + csuit;
}