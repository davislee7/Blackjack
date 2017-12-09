//
// Created by Davis Lee on 11/25/17.
// Card object implementation

#include "Card.h"

//Default constructor constructs invalid card that needs to be assigned value and suit
Card::Card() {
    cvalue = "0";
    csuit = "?";
}

//Alternate constructor with proper value and suit
//Assumes proper input to improve efficiency
Card::Card(string value, string suit){
    cvalue = value;
    csuit = suit;
}

//Gets suit
string Card::getSuit() {
    return csuit;
}

//Gets value
string Card::getValue() {
    return cvalue;
}

//Converts card contents to string
string Card::toString() {
    return cvalue + csuit;
}