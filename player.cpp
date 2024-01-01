#include "player.h"
#include "hand.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;
using std::string;
using std::vector;
using std::map;
using std::unordered_map;

//Constructors
Player::Player(int initialBalance, int initialBet, Strategy initialStrategy) {
    balance = initialBalance;
    bet = initialBet;
    strategy = initialStrategy;
    
    //Initialize Empty Initial Hand
    hands.push_back(new Hand());
}

Player::~Player() {
    for (Hand* hand : hands) {
        delete hand;
    }
}


//Balance
int Player::getBalance() {
    return balance;
}

void Player::increaseBalance(int amount) {
    balance += amount;
}

void Player::decreaseBalance(int amount) {
    balance -= amount;
}


//Bet
int Player::getBet() {
    return bet;
}

void Player::placeBet(int amount) {
    bet = amount;
}


//Hand
Hand* Player::getHand(int handIndex) {
    return hands[handIndex];
}

vector<Hand*> Player::getHands() {
    return hands;
}

void Player::clearAllHands() {
    for(auto& hand : hands) {
        hand->clearHand();          //Empty The Hand
        delete hand;                //Delete It
    }
    hands.clear();

    //Add a new REGULAR Empty Hand object to the vector so it is not empty for future operations/accessing
    hands.push_back(new Hand());
}

void Player::split(int handIndex) {
    Hand* splitHand = new Hand();
    hands.insert(hands.begin() + handIndex + 1, splitHand);

    (getHand(handIndex + 1))->addCardToHand((getHand(handIndex))->getCard(1));      //Move 2nd card in first hand to 1st card in 2nd split hand
    (getHand(handIndex))->removeCardFromHand(1);                                //Remove 2nd card in first hand

    for(Hand* hand : getHands()) {
        hand->printHand();
    }

}


//Decision
Player::Decision Player::makeDecision(Hand* hand, int dealerCardVal) {
    switch(strategy) {

        case HARD_17:
            if(hand->getHandValue() >= 17) {
                return Player::Decision::S;
            } else {
                return Player::Decision::H;
            }
            break;

        case SOFT_17:
            if(hand->getHandValue() >= 17 && !hand->hasAce()) {
                return Player::Decision::S;
            } else {
                return Player::Decision::H;
            }
            break;
        
        case OPTIMAL_CHART:
            
            return opChart(hand, dealerCardVal);

            break;
    }   
}


//Table
int Player::getTablePos() {
    return tablePos;
}

void Player::setTablePos(int position) {
    tablePos = position;
}


//Optimal Chart
vector<vector<Player::Decision>> Player::optimalChart = {

    //Player                      Dealer's Card
    // Hand       A    2    3    4    5    6    7    8    9    10
    /* 8 */     { H,   H,   H,   H,   H,   H,   H,   H,   H,   H  },
    /* 9 */     { H,   H,   DH,  DH,  DH,  DH,  H,   H,   H,   H  },
    /* 10 */    { H,   DH,  DH,  DH,  DH,  DH,  DH,  DH,  DH,  H  },
    /* 11 */    { DH,  DH,  DH,  DH,  DH,  DH,  DH,  DH,  DH,  DH },
    /* 12 */    { H,   H,   H,   S,   S,   S,   H,   H,   H,   H  },
    /* 13 */    { H,   S,   S,   S,   S,   S,   H,   H,   H,   H  },
    /* 14 */    { H,   S,   S,   S,   S,   S,   H,   H,   H,   H  },
    /* 15 */    { H,   S,   S,   S,   S,   S,   H,   H,   H,   RH },
    /* 16 */    { RH,  S,   S,   S,   S,   S,   H,   H,   RH,  RH },
    /* 17 */    { S,   S,   S,   S,   S,   S,   S,   S,   S,   S  },
    /* A,2 */   { H,   H,   H,   H,   DH,  DH,  H,   H,   H,   H  },
    /* A,3 */   { H,   H,   H,   H,   DH,  DH,  H,   H,   H,   H  },
    /* A,4 */   { H,   H,   H,   DH,  DH,  DH,  H,   H,   H,   H  },
    /* A,5 */   { H,   H,   H,   DH,  DH,  DH,  H,   H,   H,   H  },
    /* A,6 */   { H,   H,   DH,  DH,  DH,  DH,  H,   H,   H,   H  },
    /* A,7 */   { H,   DS,  DS,  DS,  DS,  DS,  S,   S,   H,   H  },
    /* A,8 */   { S,   S,   S,   S,   S,   S,   S,   S,   S,   S  },
    /* A,9 */   { S,   S,   S,   S,   S,   S,   S,   S,   S,   S  },
    /* A,10 */  { S,   S,   S,   S,   S,   S,   S,   S,   S,   S  },
    /* A,A */   { P,   P,   P,   P,   P,   P,   P,   P,   P,   P  },
    /* 2,2 */   { H,   P,   P,   P,   P,   P,   P,   H,   H,   H  },
    /* 3,3 */   { H,   P,   P,   P,   P,   P,   P,   H,   H,   H  },
    /* 4,4 */   { H,   H,   H,   H,   P,   P,   H,   H,   H,   H  },
    /* 5,5 */   { H,   DH,  DH,  DH,  DH,  DH,  DH,  DH,  DH,  H  },
    /* 6,6 */   { H,   P,   P,   P,   P,   P,   H,   H,   H,   H  },
    /* 7,7 */   { H,   P,   P,   P,   P,   P,   P,   H,   H,   H  },
    /* 8,8 */   { P,   P,   P,   P,   P,   P,   P,   P,   P,   P  },
    /* 9,9 */   { S,   P,   P,   P,   P,   P,   S,   P,   P,   S  },
    /* 10,10 */ { S,   S,   S,   S,   S,   S,   S,   S,   S,   S  },
};

Player::Decision Player::opChart(Hand* playerHand, int dealerCardVal) {

    //If Player over 17 without an Ace, STAND
    if(playerHand->getHandValue() >= 17 && !playerHand->hasAce()) {
        return Player::S;
    }

    //If Player Under 8, HIT
    if(playerHand->getHandValue() < 8) {
        return Player::H;
    }

    //If Hand has More than 2 Cards OR (Has 2 Cards AND No Ace AND No Double)
    if(playerHand->getSize() > 2 || !playerHand->hasAce() && !playerHand->isDoubles()) {
        return optimalChart[playerHand->getHandValue() - 8][dealerCardVal - 1];               //-8 B/c Chart Starts at 9
    }

    //If Player has an Ace, and it is not double Aces (Only 2 Cards in Hand)
    else if(playerHand->hasAce() && !playerHand->isDoubles()) {
        return optimalChart[playerHand->cardNotAce() + 8][dealerCardVal - 1];
    }

    else if(playerHand->isDoubles()) {
        int doubledCardVal = (playerHand->getCard(0))->getFaceValue();
        return optimalChart[doubledCardVal + 18][dealerCardVal - 1];
    }

}
