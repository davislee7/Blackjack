//
// Created by Davis Lee on 11/26/17.
//
#include "Deck.h"
#include <iostream>
#include <vector>
#include <stdlib.h>

/*
 * int codes:
 * 0 = house win
 * 1 = push
 * 2 = player win
 * 3 = player blackjack
 * 4 = player wins double (both split wins or successful double down)
 * 5 = player loses double (both split loses or unsuccessful double down)
 */
int getVal(Card input);

int playOneRound(Deck &playingDeck);

int testForBlackjack(int houseSum, int playerSum);

int runSplitRound(int houseSum, string houseString, int playerSum, string playerString,
                  Deck &playingDeck);

int playDoubleDownRound(int houseSum, string houseString, int playerSum,
                        string playerString, Deck playingDeck);

int playOneHand(string playerString, int playerSum, Deck &playingDeck);

int playHouseHand(string houseString, int houseSum, Deck &playingDeck);

int findWinner(int playerSum, int houseSum);


int main(void) {
    Deck playingDeck;
    int endWinnings;
    playOneRound(playingDeck);
}

int playOneRound(Deck &playingDeck) {
    int houseSum = 0;
    int playerSum = 0;

    string houseString = "";
    string playerString = "";
    string test = "";
    Card curCard;

    curCard = playingDeck.deal();
    houseSum += getVal(curCard);
    houseString += curCard.toString() + " ";

    curCard = playingDeck.deal();
    playerSum += getVal(curCard);
    playerString += curCard.toString() + " ";
    test = curCard.getValue();

    curCard = playingDeck.deal();
    houseSum += getVal(curCard);
    houseString += curCard.toString() + " ";

    curCard = playingDeck.deal();
    playerSum += getVal(curCard);
    playerString += curCard.toString() + " ";

    cout << "House Hand: " << houseString.substr(0, 3) << endl;
    cout << "Player Hand: " << playerString << endl << endl;
    int blackjackTest = testForBlackjack(houseSum, playerSum);
    if (blackjackTest != -1) {
        return blackjackTest;
    }

    if (curCard.getValue() == test) {
        cout << "Split Cards?" << endl;
        cin >> test;
        if (test == "y" || test == "yes" || test == "Yes") {
            return runSplitRound(houseSum, houseString, playerSum, playerString,
                                 playingDeck);
        }
    }

    cout << "Double Down? ";
    cin >> test;
    if(test == "yes" || test == "Yes"){
        playDoubleDownRound(houseSum, houseString, playerSum, playerString,
                            playingDeck);
    }
    playerSum = playOneHand(playerString, playerSum, playingDeck);
    if (playerSum == 0) {
        return 0;
    }
    houseSum = playHouseHand(houseString, houseSum, playingDeck);

    if (houseSum == 0) {
        return 1;
    }

    return findWinner(playerSum, houseSum);

}


int getVal(Card input) {
    if (input.getValue() == "2") {
        return 2;
    } else if (input.getValue() == "3") {
        return 3;
    } else if (input.getValue() == "4") {
        return 4;
    } else if (input.getValue() == "5") {
        return 5;
    } else if (input.getValue() == "6") {
        return 6;
    } else if (input.getValue() == "7") {
        return 7;
    } else if (input.getValue() == "8") {
        return 8;
    } else if (input.getValue() == "9") {
        return 9;
    } else if (input.getValue() == "A") {
        return 11;
    } else {
        return 10;
    }
}

int testForBlackjack(int houseSum, int playerSum) {
    if (houseSum == 21 && playerSum == 21) {
        cout << "Double Blackjack!! Player and House Push" << endl;
        return 1;
    } else if (houseSum == 21) {
        cout << "House Blackjack, House Wins" << endl;
        return 0;
    } else if (playerSum == 21) {
        cout << "Player Blackjack!! Player Wins Bet and a Half!" << endl;
        return 3;
    } else {
        return -1;
    }
}

int runSplitRound(int houseSum, string houseString, int playerSum,
                  string playerString, Deck &playingDeck) {
    string playerString2 = "";
    int playerSum2 = playerSum / 2;
    if (playerSum2 == 10) {
        playerString2 = playerString.substr(4);
        playerString = playerString.substr(0, 4);
    } else {
        playerString2 = playerString.substr(3);
        playerString = playerString.substr(0, 3);
    }

    Card curCard;

    curCard = playingDeck.deal();
    playerSum += getVal(curCard);
    playerString += curCard.toString() + " ";

    cout << "Player Hand 1: " << playerString << endl << endl;
    playerSum = playOneHand(playerString, playerSum, playingDeck);

    cout << "Player Hand 2: " << playerString2 << endl << endl;
    playerSum2 = playOneHand(playerString2, playerSum2, playingDeck);

    if (playerSum == 0 && playerSum2 == 0) {
        cout << "House Wins Both Hands" << endl;
        return 5;
    }

    houseSum = playHouseHand(houseString, houseSum, playingDeck);

    int hand1result = findWinner(playerSum, houseSum);
    int hand2result = findWinner(playerSum2, houseSum);
    if (hand1result == 0 && hand2result == 0) {
        cout << "House Wins Both Hands" << endl;
        return 5;
    }
    if (hand1result == 1 && hand2result == 1) {
        cout << "Player Wins Both Hands!" << endl;
        return 4;
    }
    if (hand1result == 1 && hand2result == 0) {
        cout << "Player Wins Hand 1, House Wins Hand 2" << endl;
        return 1;
    }
    if (hand1result == 0 && hand2result == 1) {
        cout << "House Wins Hand 1, Player Wins Hand 2" << endl;
        return 1;
    }
    if (hand1result == 1) {
        cout << "Player Wins Hand 1, Push for Hand 2" << endl;
        return 2;
    }
    if (hand2result == 1) {
        cout << "Push for Hand 1, Player Wins Hand 2" << endl;
        return 2;
    }
    if (hand1result == 0) {
        cout << "House Wins Hand 1, Push for Hand 2" << endl;
        return 0;
    }
    if (hand2result == 0) {
        cout << "Push for Hand 1, House Wins Hand 2" << endl;
    }
    cout << "Push for Both Hands" << endl;
    return 2;
}

int playDoubleDownRound(int houseSum, string houseString, int playerSum,
                        string playerString, Deck playingDeck){
    Card curCard;
    cout << "Hit or Stay? ";
    string command = "";
    cin >> command;
    bool aceUsed = false;
    while (command == "hit" || command == "Hit") {
        curCard = playingDeck.deal();
        playerSum += getVal(curCard);
        playerString += curCard.toString() + " ";
        cout << "Next Card: " << curCard.toString() << endl;
        if (playerSum > 21) {
            if (playerString.find("A") != string::npos && !aceUsed) {
                playerSum -= 10;
                aceUsed = true;
            } else {
                cout << "Player Bust! House Wins" << endl;
                return 0;
            }
        }
        cout << "Current Hand: " << playerString << endl;
        cout << "Hit or Stay? ";
        cin >> command;
    }
    cout << "Player Sum: " << playerSum << "\n" << endl;
    return playerSum;
}

int playOneHand(string playerString, int playerSum, Deck &playingDeck) {
    Card curCard;
    cout << "Hit or Stay? ";
    string command = "";
    cin >> command;
    bool aceUsed = false;
    while (command == "hit" || command == "Hit") {
        curCard = playingDeck.deal();
        playerSum += getVal(curCard);
        playerString += curCard.toString() + " ";
        cout << "Next Card: " << curCard.toString() << endl;
        if (playerSum > 21) {
            if (playerString.find("A") != string::npos && !aceUsed) {
                playerSum -= 10;
                aceUsed = true;
            } else {
                cout << "Player Bust! House Wins" << endl;
                return 0;
            }
        }
        cout << "Current Hand: " << playerString << endl;
        cout << "Hit or Stay? ";
        cin >> command;
    }
    cout << "Player Sum: " << playerSum << "\n" << endl;
    return playerSum;
}

int playHouseHand(string houseString, int houseSum, Deck &playingDeck) {
    Card curCard;
    cout << "House Hand: " << houseString << endl;
    bool aceUsed = false;
    while (houseSum < 17 || houseSum > 21) {
        cout << "Current House Hand: " << houseString << endl;
        curCard = playingDeck.deal();
        houseSum += getVal(curCard);
        houseString += curCard.toString() + " ";
        cout << "Next Card: " << curCard.toString() << endl;

        if (houseSum > 21) {
            if (houseString.find("A") != string::npos && !aceUsed) {
                houseSum -= 10;
                aceUsed = true;
            } else {
                cout << "House Bust! Player wins" << endl;
                return 0;
            }
        }
    }
    return houseSum;
}

int findWinner(int playerSum, int houseSum) {
    if (houseSum > playerSum) {
        cout << "House Wins With " << houseSum << endl;
        return 0;
    } else if (houseSum < playerSum) {
        cout << "Player Wins With " << playerSum << endl;
        return 1;
    } else {
        cout << "Push at " << houseSum << endl;
        return 2;
    }
}