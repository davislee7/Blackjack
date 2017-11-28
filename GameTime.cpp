//
// Created by Davis Lee on 11/26/17.
//
#include "Deck.h"
#include <iostream>
#include <vector>
#include <stdlib.h>

int getVal(Card input);
int playOneRound(Deck &playingDeck);
int testForBlackjack(int houseSum, int playerSum);
int runSplitRound(int houseSum, string houseString, int playerSum, string playerString,
                  Deck &playingDeck);

int main(void){
    Deck playingDeck;
    playOneRound(playingDeck);
}

int playOneRound(Deck &playingDeck) {
    int houseSum = 0;
    int playerSum = 0;

    string houseString = "";
    string playerString = "";
    string splitTest = "";
    Card curCard;

    curCard = playingDeck.deal();
    houseSum += getVal(curCard);
    houseString += curCard.toString() + " ";

    curCard = playingDeck.deal();
    playerSum += getVal(curCard);
    playerString += curCard.toString() + " ";
    splitTest = curCard.getValue();

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
    if (curCard.getValue() == splitTest) {
        cout << "Split Cards?" << endl;
        cin >> splitTest;
        if (splitTest == "y" || splitTest == "yes" || splitTest == "Yes") {
            return runSplitRound(houseSum, houseString, playerSum, playerString,
                                 playingDeck);
        }
    }
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
                cout << "Player Bust! House wins" << endl;
                return 0;
            }
        }
        cout << "Current hand: " << playerString << endl;
        cout << "Hit or Stay? ";
        cin >> command;
    }
    cout << "Player sum: " << playerSum << "\n" << endl;

    cout << "House Hand: " << houseString << endl;
    aceUsed = false;

    while (houseSum < 17 || houseSum > 21) {
        cout << "Current house hand: " << houseString << endl;
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
                return 1;
            }
        }
    }
    if (houseSum > playerSum) {
        cout << "House wins with " << houseSum << endl;
        return 0;
    } else if (houseSum < playerSum) {
        cout << "Player wins with" << playerSum << endl;
        return 1;
    } else {
        cout << "Push at " << houseSum << endl;
        return 2;
    }
}


int getVal(Card input){
    if(input.getValue() == "2"){
        return 2;
    } else if(input.getValue() == "3"){
        return 3;
    } else if(input.getValue() == "4"){
        return 4;
    } else if(input.getValue() == "5"){
        return 5;
    } else if(input.getValue() == "6"){
        return 6;
    } else if(input.getValue() == "7"){
        return 7;
    } else if(input.getValue() == "8"){
        return 8;
    } else if(input.getValue() == "9"){
        return 9;
    } else if(input.getValue() == "A"){
        return 11;
    } else {
        return 10;
    }
}
int testForBlackjack(int houseSum, int playerSum){
    if(houseSum == 21 && playerSum == 21){
        cout << "Double Blackjack!! Player and House Push" << endl;
        return 2;
    } else if(houseSum == 21){
        cout << "House Blackjack, House Wins" << endl;
        return 3;
    } else if(playerSum == 21){
        cout << "Player Blackjack!! Player Wins Bet and a Half!" << endl;
        return 4;
    } else{
        return -1;
    }
    
}

int runSplitRound(int houseSum, string houseString, int playerSum,
                  string playerString, Deck &playingDeck){
    string playerString2 = "";
    int playerSum2 = playerSum/2;
    if(playerSum2 == 10) {
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
    int blackjackTest = testForBlackjack(houseSum, playerSum);
    if (blackjackTest != -1){
        cout << "Player Hand 1 Blackjack!";

    }


    cout << "Hit or Stay? ";
    string command = "";
    cin >> command;
    while(command == "hit" || command == "Hit"){
        curCard = playingDeck.deal();
        playerSum += getVal(curCard);
        playerString += curCard.toString() + " ";
        cout << "Next Card: " << curCard.toString() << endl;
        if(playerSum>21){
            cout << "Player Bust! House wins" << endl;
            return 0;
        } else {
            cout << "Current hand: " << playerString << endl;
            cout << "Hit or Stay? ";
            cin >> command;
        }
    }
    if(command != "lose"){
        while(houseSum < 17 || houseSum > 21){
            cout << "Current house hand: " << houseString << endl;
            curCard = playingDeck.deal();
            houseSum += getVal(curCard);
            houseString += curCard.toString() + " ";
            cout << "Next Card: " << curCard.toString() << endl;
        }
        if(houseSum > 21){
            cout << "House Bust! Player wins" << endl;
            return 1;
        } else {
            if(houseSum>playerSum){
                cout << "House wins" << endl;
                return 0;
            } else if(houseSum<playerSum){
                cout << "Player wins!" << endl;
                return 1;
            } else {
                cout << "Push" << endl;
                return 2;
            }
        }
    }
    return 0;
}

