#include "player.h"
#include <iostream>
#include <string>

using namespace std;
using std::string;

//Constructors
Player::Player(int initialBalance, int initialBet) : balance(initialBalance), bet(initialBet) {}

Player::~Player() {}


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
void Player::addCardToHand(Card* card) {
    hand.push_back(card);
}

void Player::clearHand() {
    hand.clear();               //Do not delete cards as they need to exist in shoe
}

int Player::getHandValue() {
    int handValue = 0;
    bool hasAce = false;        //Initially Assume No Ace

    for(Card* card : hand) {
        if(card->getRank() == card->ACE) {
            hasAce = true;
        }
        handValue += card->getFaceValue();
    }

    //If Ace is Present, and Counting Ace as 11 will not cause bust, count as 11 by adding 10 to intial 1 added above
    //If there is more than 1 ace, only one can be considered as 11 without causing bust, so this works for any # of aces
    if(hasAce && handValue <= 11) {
        handValue += 10;
    }

    return handValue;
}


//Decision
Player::Decision Player::makeDecision() {
    if(getHandValue() >= 16) {
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

//Actions
bool Player::isBust() {
    if(getHandValue() > 21) {
        return true;
    } 
    return false;
}

bool Player::isBlackJack() {
    if(getHandValue() == 21) {
        return true;
    } 
    return false;
}


//Print
void Player::printHand() {
    cout << "Player " << to_string(getTablePos()) << ": ";
    for(size_t i = 0; i < hand.size(); ++i) {
        cout << hand[i]->toString();
        if(i != hand.size() - 1) {      // If it's not the last card
            cout << ", ";
        }
    }
    cout << " = " << getHandValue() << endl;
}