#include "player.h"

//Constructors
Player::Player(int initialBalance) : balance(initialBalance) {}

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

    for(Card* card : hand) {
        handValue += card->getFaceValue();
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









