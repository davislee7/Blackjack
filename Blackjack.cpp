//
// Created by Davis Lee on 12/2/17.
//
/*
 * int codes:
 * 0 = house win
 * 1 = push
 * 2 = player win
 * 3 = player blackjack
 * 4 = player wins double (both split wins or successful double down)
 * 5 = player loses double (both split loses or unsuccessful double down)
 */


#include "Blackjack.h"

Blackjack::Blackjack() {
    cout << "Starting money amount? ";
    cin >> currentMoney;
    while (currentMoney <= 0) {
        cout << "Please enter valid amount: ";
        cin >> currentMoney;
    }
    playGame();
}

Blackjack::Blackjack(int startMoney) {
    currentMoney = startMoney;
    while (currentMoney <= 0) {
        cout << "Please enter valid amount: ";
        cin >> currentMoney;
    }
    playGame();
}

int Blackjack::getMoney() {
    return currentMoney;
}

int Blackjack::playGame() {
    cout << "\nPLAYING BLACKJACK, STARTING MONEY: " << currentMoney << endl;
    string another = "yes";
    Deck myDeck;
    int bet;
    int roundOutcome;
    while (another == "yes" || another == "Yes" || another == "y") {
        myDeck.shuffle();
        cout << "Bet amount? ";
        cin >> bet;
        while (bet > currentMoney) {
            cout << "Insufficient money, please place lower bet" << endl;
            cout << "Bet amount? ";
            cin >> bet;
        }
        roundOutcome = playOneRound(myDeck, bet);
        if (roundOutcome == 0) {
            currentMoney -= bet;
        } else if (roundOutcome == 1) {
        } else if (roundOutcome == 2) {
            currentMoney += bet;
        } else if (roundOutcome == 3) {
            currentMoney += bet * 1.5;
        } else if (roundOutcome == 4) {
            currentMoney += bet * 2;
        } else {
            currentMoney -= bet * 2;
        }

        cout << "\nCurrent Money: $" << currentMoney << endl;
        if (currentMoney <= 0) {
            cout << "You Lose!" << endl;
            return 0;
        }
        cout << "\nPlay another? ";
        cin >> another;
    }
    cout << "\nThanks for playing Blackjack!" << endl;
    cout << "\nFinished with $" << currentMoney << endl;
    return currentMoney;
}

int Blackjack::playOneRound(Deck &playingDeck, int bet) {
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

    cout << "\nHouse Hand: " << houseString.substr(0, 3) << endl;
    cout << "Player Hand: " << playerString << endl << endl;

    int blackjackTest = testForBlackjack(houseSum, playerSum);
    if (blackjackTest != -1) {
        return blackjackTest;
    }

    if (currentMoney >= bet * 2) {
        if (curCard.getValue() == test) {
            cout << "Split Cards? ";
            cin >> test;
            if (test == "y" || test == "yes" || test == "Yes") {
                return runSplitRound(houseSum, houseString, playerSum, playerString,
                                     playingDeck);
            }
        }

        cout << "Double Down? ";
        cin >> test;
        if (test == "yes" || test == "Yes") {
            curCard = playingDeck.deal();
            playerSum += getVal(curCard);
            playerString += curCard.toString() + " ";
            cout << "Next Card: " << curCard.toString() << endl;
            if (playerSum > 21) {
                playerSum -= 10;
            }
            cout << "Player Sum: " << playerSum << endl;
            houseSum = playHouseHand(houseString, houseSum, playingDeck);
            return findWinner(playerSum, houseSum, true);
        }
    }
    playerSum = playOneHand(playerString, playerSum, playingDeck);
    if (playerSum == 0) {
        return 0;
    }

    houseSum = playHouseHand(houseString, houseSum, playingDeck);

    return findWinner(playerSum, houseSum, false);

}


int Blackjack::getVal(Card input) {
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

int Blackjack::testForBlackjack(int houseSum, int playerSum) {
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

int Blackjack::runSplitRound(int houseSum, string houseString, int playerSum,
                             string playerString, Deck &playingDeck) {
    string playerString2 = "";
    int playerSum2 = playerSum / 2;
    playerSum = playerSum2;
    if (playerString.substr(0, 2) == "10") {
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

    curCard = playingDeck.deal();
    playerSum2 += getVal(curCard);
    playerString2 += curCard.toString() + " ";

    cout << "Player Hand 2: " << playerString2 << endl << endl;
    playerSum2 = playOneHand(playerString2, playerSum2, playingDeck);

    if (playerSum == 0 && playerSum2 == 0) {
        cout << "House Wins Both Hands" << endl;
        return 5;
    }

    houseSum = playHouseHand(houseString, houseSum, playingDeck);

    cout << "\nHand 1 Result: ";
    int hand1result = findWinner(playerSum, houseSum, false);

    cout << "\nHand 2 Result: ";
    int hand2result = findWinner(playerSum2, houseSum, false);

    if (hand1result == 0 && hand2result == 0) {
        cout << "House Wins Both Hands" << endl;
        return 5;
    }
    if (hand1result == 2 && hand2result == 2) {
        cout << "Player Wins Both Hands!" << endl;
        return 4;
    }
    if (hand1result == 2 && hand2result == 0) {
        cout << "Player Wins Hand 1, House Wins Hand 2" << endl;
        return 1;
    }
    if (hand1result == 0 && hand2result == 2) {
        cout << "House Wins Hand 1, Player Wins Hand 2" << endl;
        return 1;
    }
    if (hand1result == 2) {
        cout << "Player Wins Hand 1, Push for Hand 2" << endl;
        return 2;
    }
    if (hand2result == 2) {
        cout << "Push for Hand 1, Player Wins Hand 2" << endl;
        return 2;
    }
    if (hand1result == 0) {
        cout << "House Wins Hand 1, Push for Hand 2" << endl;
        return 0;
    }
    if (hand2result == 0) {
        cout << "Push for Hand 1, House Wins Hand 2" << endl;
        return 0;
    }
    cout << "Push for Both Hands" << endl;
    return 2;
}

int Blackjack::playOneHand(string playerString, int playerSum, Deck &playingDeck) {
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
        cout << "\nCurrent Hand: " << playerString << endl;
        cout << "Hit or Stay? ";
        cin >> command;
    }
    cout << "Player Sum: " << playerSum << "\n" << endl;
    return playerSum;
}

int Blackjack::playHouseHand(string houseString, int houseSum, Deck &playingDeck) {
    if (houseSum > 16) {
        cout << "House Hand: " << houseString << endl;
        return houseSum;
    }
    Card curCard;
    bool aceUsed = false;
    while (houseSum < 17 || houseSum > 21) {
        cout << "\nCurrent House Hand: " << houseString << endl;
        curCard = playingDeck.deal();
        houseSum += getVal(curCard);
        houseString += curCard.toString() + " ";
        cout << "Next Card: " << curCard.toString() << endl;

        if (houseSum > 21) {
            if (houseString.find("A") != string::npos && !aceUsed) {
                houseSum -= 10;
                aceUsed = true;
            } else {
                cout << "House Bust!" << endl;
                return 0;
            }
        }
    }
    return houseSum;
}

int Blackjack::findWinner(int playerSum, int houseSum, bool doubleDown) {
    if (houseSum > playerSum) {
        cout << "House Wins With " << houseSum << endl;
        if (doubleDown) {
            return 5;
        }
        return 0;
    } else if (houseSum < playerSum) {
        cout << "Player Wins With " << playerSum << endl;
        if (doubleDown) {
            return 4;
        }
        return 2;
    } else if (houseSum == 0) {
        cout << "Push, Both Bust" << endl;
        return 1;
    }
    cout << "Push at " << houseSum << endl;
    return 1;
}
