//
// Created by Davis Lee on 11/25/17.
//

#include "Deck.h"

Deck::Deck() {
    place = 0;
    myDeck[0] = Card("A", "C");
    for(int i = 1; i < 10; i++){
        myDeck[i] = Card(to_string(i+1), "C");
    }
    myDeck[10] = Card("J", "C");
    myDeck[11] = Card("Q", "C");
    myDeck[12] = Card("K", "C");
    myDeck[13] = Card("A", "D");
    for(int i = 14; i < 23; i++){
        myDeck[i] = Card(to_string(i%13 + 1), "D");
    }
    myDeck[23] = Card("J", "D");
    myDeck[24] = Card("Q", "D");
    myDeck[25] = Card("K", "D");
    myDeck[26] = Card("A", "H");
    for(int i = 27; i < 36; i++){
        myDeck[i] = Card(to_string(i%13 + 1), "H");
    }
    myDeck[36] = Card("J", "H");
    myDeck[37] = Card("Q", "H");
    myDeck[38] = Card("K", "H");
    myDeck[39] = Card("A", "S");
    for(int i = 40; i < 49; i++){
        myDeck[i] = Card(to_string(i%13 + 1), "S");
    }
    myDeck[49] = Card("J", "S");
    myDeck[50] = Card("Q", "S");
    myDeck[51] = Card("K", "S");
    shuffle();
}

void Deck::shuffle() {
    srand(time(NULL));
    int randNum = 0;
    for(int i = 0; i < 52; i++){
        randNum = rand()%52;
        swap(myDeck[i], myDeck[randNum]);
    }
}

Card Deck::deal(){
    if(place>51){
        place = 0;
        cout << "finished deck" << endl;
    }
    place++;

    return myDeck[place - 1];
}