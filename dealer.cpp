#include "dealer.h"
#include <iostream>
#include <string>

using namespace std;
using std::string;

//Constructors
Dealer::Dealer(Strategy initialStrategy) {
    strategy = initialStrategy;
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
    switch(strategy) {

        case HARD_17:
            if(hand->getHandValue() >= 17) {
                return Dealer::Decision::S;
            } else {
                return Dealer::Decision::H;
            }
            break;
        
        case SOFT_17:
            if(hand->getHandValue() >= 17 && !hand->hasAce()) {
                return Dealer::Decision::S;
            } else {
                return Dealer::Decision::H;
            }
            break;
    }
}


//Payments
void Dealer::payOut(Player* player) {
    player->increaseBalance(player->getBet());
}

void Dealer::collectBet(Player* player) {
    player->decreaseBalance(player->getBet());
}


//Visible Card
void Dealer::printVisibleCard() {
    cout << "Dealer's Hand: ";

    cout << " ???, ";
    cout << (hand->getCard(1))->toString() << endl;     //Only show 2nd Card in Hand
}

Card* Dealer::getVisibleCard() {
    return hand->getCard(1);
}

