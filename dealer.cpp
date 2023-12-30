#include "dealer.h"

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
