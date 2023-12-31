#include "player.h"
#include "hand.h"
#include <iostream>
#include <string>

using namespace std;
using std::string;

//Constructors
Player::Player(int initialBalance, int initialBet) : balance(initialBalance), bet(initialBet) {
    hands.push_back(new Hand());        //Initialize Empty Initial Hand
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

    //Add a new Hand object to the vector so it is not empty for future operations/accessing
    hands.push_back(new Hand());
}


//Decision
Player::Decision Player::makeDecision(Hand* hand) {
    if(hand->getHandValue() >= 16) {
        return Player::Decision::STAND;
    } else {
        return Player::Decision::HIT;
    }
}


//Table
int Player::getTablePos() {
    return tablePos;
}

void Player::setTablePos(int position) {
    tablePos = position;
}
