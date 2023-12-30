#include "dealer.h"
#include <iostream>
#include <string>

using namespace std;
using std::string;

//Constructors
Dealer::Dealer() {}

Dealer::~Dealer() {}


//Hand
void Dealer::addCardToHand(Card* card) {
    hand.push_back(card);
}

void Dealer::clearHand() {
    hand.clear();               //Do not delete cards as they need to exist in shoe
}

int Dealer::getHandValue() {
    int handValue = 0;

    for(Card* card : hand) {
        handValue += card->getFaceValue();
    }

    return handValue;
}

//Decision
Dealer::Decision Dealer::makeDecision() {
    if(getHandValue() >= 16) {
        return Dealer::Decision::STAND;
    } else {
        return Dealer::Decision::HIT;
    }
}


//Payments
void Dealer::payOut(Player* player) {
    player->increaseBalance(player->getBet());
}

void Dealer::collectBet(Player* player) {
    player->decreaseBalance(player->getBet());
}


//Actions
bool Dealer::isBust() {
    if(getHandValue() > 21) {
        return true;
    } 
    return false;
}

bool Dealer::isBlackJack() {
    if(getHandValue() == 21) {
        return true;
    } 
    return false;
}


//Print
void Dealer::printVisibleCard() {
    cout << "Dealer's Hand: ";

    cout << " ???, ";
    cout << hand[1]->toString() << endl;
}

void Dealer::printHand() {
    cout << "Dealer's Hand:" << endl;
    for(size_t i = 0; i < hand.size(); ++i) {
        cout << hand[i]->toString();
        if(i != hand.size() - 1) {      // If it's not the last card
            cout << ", ";
        }
    }
    cout << " = " << getHandValue() << endl;
}