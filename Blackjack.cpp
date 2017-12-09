//
// Created by Davis Lee on 12/2/17.
// Blackjack game implementation

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


//Finds a valid amount of starting money
//Calls playGame()
//Once the game ends, currentMoney will reflect the money remaining
Blackjack::Blackjack() {
    cout << "Starting money amount? ";
    cin >> currentMoney;
    while (currentMoney <= 0) {
        cout << "Please enter valid amount: ";
        cin >> currentMoney;
    }
    playGame();
}

//Takes starting money as a parameter and asks for another if invalid
//Calls playGame()
//Once the game ends, currentMoney will reflect the money remaining
Blackjack::Blackjack(int startMoney) {
    currentMoney = startMoney;
    while (currentMoney <= 0) {
        cout << "Please enter valid amount: ";
        cin >> currentMoney;
    }
    playGame();
}

//Retrieves currentMoney
int Blackjack::getMoney() {
    return currentMoney;
}

//Plays one game of Blackjack
//Function ends when player chooses to stop or has run out of money
int Blackjack::playGame() {
    cout << "\nPLAYING BLACKJACK, STARTING MONEY: " << currentMoney << endl;
    string another = "yes";

    //Create Deck
    Deck myDeck;
    int bet;
    int roundOutcome;

    //loop of hands that continues until player runs out of money or chooses to stop
    while (another == "yes" || another == "Yes" || another == "y") {
        myDeck.shuffle();
        cout << "Bet amount? ";
        cin >> bet;
        while (bet > currentMoney) {
            cout << "Insufficient money, please place lower bet" << endl;
            cout << "Bet amount? ";
            cin >> bet;
        }

        //Call playOneRound to find the result of one round
        //Adjust currentMoney depending on outcome
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

        //If player runs out of money, end game
        cout << "\nCurrent Money: $" << currentMoney << endl;
        if (currentMoney <= 0) {
            cout << "You Lose!" << endl;
            return 0;
        }

        //Ask if player wants to play again
        cout << "\nPlay another? ";
        cin >> another;
    }

    //Tell user how much money they finished with
    cout << "\nThanks for playing Blackjack!" << endl;
    cout << "\nFinished with $" << currentMoney << endl;
    return currentMoney;
}

//Plays one round
int Blackjack::playOneRound(Deck &playingDeck, int bet) {

    //track player and house totals
    int houseSum = 0;
    int playerSum = 0;

    //track player and house hands through strings to print to update player on what
    // the hands are
    string houseString = "";
    string playerString = "";
    string test = "";
    Card curCard;

    //Deal house first card
    curCard = playingDeck.deal();
    houseSum += getVal(curCard);
    houseString += curCard.toString() + " ";

    //Deal player first card
    curCard = playingDeck.deal();
    playerSum += getVal(curCard);
    playerString += curCard.toString() + " ";
    test = curCard.getValue();

    //Deal house second card
    curCard = playingDeck.deal();
    houseSum += getVal(curCard);
    houseString += curCard.toString() + " ";

    //Deal player second card
    curCard = playingDeck.deal();
    playerSum += getVal(curCard);
    playerString += curCard.toString() + " ";

    //Display hands, hide house second card
    cout << "\nHouse Hand: " << houseString.substr(0, 3) << endl;
    cout << "Player Hand: " << playerString << endl << endl;

    //Test for blackjack, end round if found
    int blackjackTest = testForBlackjack(houseSum, playerSum);
    if (blackjackTest != -1) {
        return blackjackTest;
    }

    //Don't offer to split or double down if player doesn't have enough money
    if (currentMoney >= bet * 2) {

        //Ask to split if player has two same value cards
        if (curCard.getValue() == test) {
            cout << "Split Cards? ";
            cin >> test;
            if (test == "y" || test == "yes" || test == "Yes") {
                return runSplitRound(houseSum, houseString, playerSum, playerString,
                                     playingDeck);
            }
        }

        //Ask if player wants to double down
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

    //Call playOneHand to find final playerSum
    playerSum = playOneHand(playerString, playerSum, playingDeck);

    //If player busts, house wins and house does not need to draw any cards
    if (playerSum == 0) {
        return 0;
    }

    //Call playHouseHand to find final houseSum
    houseSum = playHouseHand(houseString, houseSum, playingDeck);

    //Call findWinner to find winner
    return findWinner(playerSum, houseSum, false);

}



//Test for blackjack, if none found return -1
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

//Runs a hand if player chooses to split
int Blackjack::runSplitRound(int houseSum, string houseString, int playerSum,
                             string playerString, Deck &playingDeck) {

    //Split player hand into two sums and two strings
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

    //Deal second card to player first hand
    curCard = playingDeck.deal();
    playerSum += getVal(curCard);
    playerString += curCard.toString() + " ";

    //Find final sum for player first hand
    cout << "Player Hand 1: " << playerString << endl << endl;
    playerSum = playOneHand(playerString, playerSum, playingDeck);

    //Deal second card to player second hand
    curCard = playingDeck.deal();
    playerSum2 += getVal(curCard);
    playerString2 += curCard.toString() + " ";

    //Find final sum for player second hand
    cout << "Player Hand 2: " << playerString2 << endl << endl;
    playerSum2 = playOneHand(playerString2, playerSum2, playingDeck);

    //If both hands bust, house wins both and does not have to run
    if (playerSum == 0 && playerSum2 == 0) {
        cout << "House Wins Both Hands" << endl;
        return 5;
    }

    //Calculate final houseSum
    houseSum = playHouseHand(houseString, houseSum, playingDeck);

    //Find results for each hand, double down on split not allowed
    cout << "\nHand 1 Result: ";
    int hand1result = findWinner(playerSum, houseSum, false);
    cout << "\nHand 2 Result: ";
    int hand2result = findWinner(playerSum2, houseSum, false);

    //Alert player of result and return appropriate integer for hand result
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

//Plays a single hand for player
int Blackjack::playOneHand(string playerString, int playerSum, Deck &playingDeck) {
    Card curCard;
    cout << "Hit or Stay? ";
    string command = "";
    cin >> command;
    bool aceUsed = false;

    //Continue to deal cards as player requests hit
    while (command == "hit" || command == "Hit") {
        curCard = playingDeck.deal();
        playerSum += getVal(curCard);
        playerString += curCard.toString() + " ";
        cout << "Next Card: " << curCard.toString() << endl;

        //End loop if player busts
        if (playerSum > 21) {

            //If hand with ace goes over 21, ace counts as 1
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

//Plays house hand
int Blackjack::playHouseHand(string houseString, int houseSum, Deck &playingDeck) {
    //if house hand starts as 17-21, no more cards are necessary
    if (houseSum > 16) {
        cout << "House Hand: " << houseString << endl;
        return houseSum;
    }
    Card curCard;
    bool aceUsed = false;

    //Continue dealing cards until house reaches sum 17-21 or busts
    while (houseSum < 17 || houseSum > 21) {
        cout << "\nCurrent House Hand: " << houseString << endl;
        curCard = playingDeck.deal();
        houseSum += getVal(curCard);
        houseString += curCard.toString() + " ";
        cout << "Next Card: " << curCard.toString() << endl;

        //Test for bust
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

//Find winner by comparing playerSum and houseSum, stakes are doubled if doubleDown==true
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

//acts as atoi for blackjack, 10 J Q K all count as 10
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