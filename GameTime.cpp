//
// Created by Davis Lee on 11/26/17.
// Plays game of user's choice

#include "Blackjack.h"

int main(void) {

    int money = 0;

    cout << "How much money would you like to start with? ";
    cin >> money;

    while(money <= 0){
        cout << "Enter valid amount ";
        cin >> money;
    }

    string gameName;
    cout << "What game would you like to play? ";
    cin >> gameName;

    if(gameName == "Blackjack" || gameName == "blackjack"){
        Blackjack blackjackGame(money);
        money = blackjackGame.getMoney();
    }

}