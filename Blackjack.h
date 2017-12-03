//
// Created by Davis Lee on 12/2/17.
//

#ifndef BLACKJACK_BLACKJACK_H
#define BLACKJACK_BLACKJACK_H
#include "Deck.h"
#include <iostream>
#include <vector>
#include <stdlib.h>

class Blackjack {
private:

    int currentMoney;

public:

    Blackjack();

    Blackjack(int startMoney);

    int getMoney();

    int playGame();

    int getVal(Card input);

    int playOneRound(Deck &playingDeck, int bet);

    int testForBlackjack(int houseSum, int playerSum);

    int runSplitRound(int houseSum, string houseString, int playerSum, string playerString,
                      Deck &playingDeck);

    int playOneHand(string playerString, int playerSum, Deck &playingDeck);

    int playHouseHand(string houseString, int houseSum, Deck &playingDeck);

    int findWinner(int playerSum, int houseSum, bool doubleDown);

};


#endif //BLACKJACK_BLACKJACK_H
