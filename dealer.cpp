#include "dealer.h"
#include <iostream>
#include <string>

using namespace std;
using std::string;

//Constructors
Dealer::Dealer() {
    hand = new Hand();
}

Dealer::~Dealer() {
    delete hand;
}


//Hand
Hand* Dealer::getHand() {
    return hand;
}


//Decision
Dealer::Decision Dealer::makeDecision() {
    if(hand->getHandValue() >= 16) {
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


//Print
void Dealer::printVisibleCard() {
    cout << "Dealer's Hand: ";

    cout << " ???, ";
    cout << (hand->getCard(1))->toString() << endl;     //Only show 2nd Card in Hand
}

