//
// Created by Davis Lee on 12/2/17.
// Blackjack game header

#ifndef BLACKJACK_BLACKJACK_H
#define BLACKJACK_BLACKJACK_H
#include "Deck.h"
#include <iostream>
#include <vector>
#include <stdlib.h>

class Blackjack {
private:

    //Tracks player money
    int currentMoney;

public:

    //Finds a valid amount of starting money
    //Calls playGame()
    //Once the game ends, currentMoney will reflect the money remaining
    Blackjack();

    //Takes starting money as a parameter and asks for another if invalid
    //Calls playGame()
    //Once the game ends, currentMoney will reflect the money remaining
    Blackjack(int startMoney);

    //Retrieves currentMoney
    int getMoney();

    //Plays one game of Blackjack
    //Function ends when player chooses to stop or has run out of money
    int playGame();

    //Plays one round
    int playOneRound(Deck &playingDeck, int bet);

    //Test for blackjack, if none found return -1
    int testForBlackjack(int houseSum, int playerSum);

    //Runs a hand if player chooses to split
    int runSplitRound(int houseSum, string houseString, int playerSum, string playerString,
                      Deck &playingDeck);

    //Plays a single hand for player
    int playOneHand(string playerString, int playerSum, Deck &playingDeck);

    //Plays house hand
    int playHouseHand(string houseString, int houseSum, Deck &playingDeck);

    //Compare playerSum and houseSum, return winner,
    // stakes are doubled if doubleDown == true
    int findWinner(int playerSum, int houseSum, bool doubleDown);

    //acts as atoi for blackjack, 10 J Q K all count as 10
    int getVal(Card input);
};


#endif //BLACKJACK_BLACKJACK_H
